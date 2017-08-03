#! /usr/bin/env python
# encoding: utf-8

import logging

def main():
    # Configure the logging system
    logging.basicConfig(
        filename='app.log',     # 日志的名称
        level=logging.ERROR     # 日志界别
    )

    # Variables (to make the calls that follow work)
    hostname = 'www.python.org'
    item = 'spam'
    filename = 'data.csv'
    mode = 'r'

    # Example logging calls (insert into your program)
    # logging本身也是支持格式的字符串的
    logging.critical('Host %s unknown', hostname)
    logging.error("Couldn't find %s", item)
    logging.warning('Feature is deprecated')
    logging.info('Opening file %r, mode=%r', filename, mode)
    logging.debug('Got here')

if __name__ == '__main__':
    main()
