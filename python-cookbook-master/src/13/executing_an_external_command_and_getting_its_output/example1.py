#! /usr/bin/env python
# encoding: utf-8

import subprocess
try:
    out_bytes = subprocess.check_output(['ls', '-l'])
    out_text = out_bytes.decode('utf-8')
    print(out_text)
except subprocess.CalledProcessError as e:
    print('It did not work. Reason:', e)
    print('Exitcode:', e.returncode)

