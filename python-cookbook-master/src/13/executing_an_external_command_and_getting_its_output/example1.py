#! /usr/bin/env python
# encoding: utf-8

import subprocess
try:
    # 默认情况下，check_output() 仅仅返回标准输出的值
    # 出错的内容，直接输出到标准输出上面了
    # NOTE: python3 支持timeout
    # 支持shell方式运行命令
    out_bytes = subprocess.check_output(['cat', '/tmp/dsadsa'], stderr=subprocess.STDOUT, shell=True)
    out_text = out_bytes.decode('utf-8')
    print(out_text)
except subprocess.CalledProcessError as e:
    print('It did not work. Reason:', e)
    print('Exitcode:', e.returncode)
except subprocess.TimeoutExpired as e:
    print("timeout")

