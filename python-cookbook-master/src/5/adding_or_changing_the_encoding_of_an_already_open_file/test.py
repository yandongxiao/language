#!/usr/bin/env python3
# encoding: utf-8

import os
import io

with open("testfile.txt", "rb") as bf:
    print(bf.read().decode("utf-8"))

with open("testfile.txt", "rb") as bf:
    f = io.TextIOWrapper(bf, encoding="utf-8")
    print(f.read())
