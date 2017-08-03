#! /usr/bin/env python
# encoding: utf-8

import getpass
user = getpass.getuser()    # 返回的是系统的用户名称
passwd = getpass.getpass()
print('User:', user)
print('Passwd:', passwd)
