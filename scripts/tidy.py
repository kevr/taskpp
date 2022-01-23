#!/usr/bin/env python3
""" Call clang-tidy on all source files found in ../src.

This script uses Python multithreading to perform Popen calls on
each thread, for `multiprocessing.cpu_count()` jobs at a time.
This speeds up clang-tidy analysis quite a lot, as its known for
being a massive CPU hog.

Copyright (C) 2022 Kevin Morris
Complete GLPv2 text canm be found in LICENSE.
"""
import multiprocessing
import os
import sys
from queue import Queue
from subprocess import PIPE, Popen
from threading import Lock, Thread

running = True
lock = Lock()

project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
jobs = Queue()

return_code = 0


def print_(*args, **kwargs):
    if running:
        print(*args, **kwargs)


def clang_tidy(src: str):
    global running, return_code

    base = src.replace(f"{project_root}/", "")

    proc = Popen(["clang-tidy", src], stderr=PIPE)
    rc = proc.wait()
    lock.acquire()
    first = False
    if rc:
        if running:
            first = True

        running = False
        _, err = proc.communicate()
        return_code = rc
        if first:
            print(f"error: {err.decode()}")
        print(f"clang-tidy({base}): FAIL")
    lock.release()

    print_(f"clang-tidy({base}): {'OK' if rc == 0 else 'Failed'}")


def main():
    srcdir = os.path.join(project_root, "src")
    sources = []
    for subdir, dirs, files in os.walk(srcdir):
        for file in files:
            if file.endswith(".hpp") or file.endswith(".cpp"):
                sources.append(os.path.join(srcdir, subdir, file))

    try:
        for src in sources:
            if jobs.qsize() == multiprocessing.cpu_count():
                jobs.get().join()

            if not running:
                continue

            thread = Thread(target=clang_tidy, args=(src,))
            thread.start()
            jobs.put(thread)
    except KeyboardInterrupt:
        print("\nCaught SIGINT, backing out...")

    # Finish the rest of the jobs.
    while not jobs.empty():
        jobs.get().join()

    return return_code


if __name__ == "__main__":
    sys.exit(main())
