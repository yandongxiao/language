#!/usr/bin/env python3
# encoding: utf-8

from tempfile import TemporaryFile
from tempfile import NamedTemporaryFile
from tempfile import TemporaryDirectory


with TemporaryFile("w+t") as f:
    f.write("helloworld")
    f.seek(0)
    line = f.read()
    print(line)

import time
import os
with TemporaryDirectory() as dirname:
    print(dirname)
    os.chdir(dirname)
    # 新建立的文件并非是在临时目录下
    with open("testfile.txt", "wt") as f:
        f.write("HELLOWOLD")
        f.flush()
    time.sleep(600)
