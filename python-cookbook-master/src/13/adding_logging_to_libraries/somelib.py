#! /usr/bin/env python
# encoding: utf-8

import logging

# 注意logging 和 logger 的区别
# logging是一个模块，该模块下的setBasicConfig方法，对整体日志系统进行配置
# logger是一个对象，一般一个模块对应一个logger。
# NOTE: logger可以定制自己的日志配置
log = logging.getLogger(__name__)
log.addHandler(logging.NullHandler())   # 如果日至系统配置不存在，则忽略打印信息

# Example function (for testing)
def func():
    log.critical("A Critical Error!")
    log.debug("A debug message")
