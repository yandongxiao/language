#!/usr/bin/python
# -*- coding: utf-8 -*-
from socket import *
from time import ctime
import sys
from thread import *

#是否可实现全双工通信,利用两个socket，两个线程，一个收一个发. 或者在一个socket的两个线程上进行收和发送

def msg(msg):
	print msg
	exit(-1)

def portcheck(port):
	try:
		PORT = int(sys.argv[2])
		if(PORT < 0):
			msg('not a legal port')
	except:
		msg('not a legal port')

def paramcheck():
	if 3 != len(sys.argv):
		msg('not enough param')
	portcheck(sys.argv[2])


def recvFunction(sock, argv):
	while True:
		data = sock.recv(BUFSIZ)
		if not data :
			continue
		print data
		#print 'input your words > ',

if __name__ == '__main__':
	paramcheck();
	HOST = sys.argv[1]
	PORT = int(sys.argv[2])
	ADDR = (HOST, PORT)
	BUFSIZ = 1024

	tcpCliSock = socket(AF_INET, SOCK_STREAM)
	tcpCliSock.connect(ADDR)
	start_new_thread(recvFunction, (tcpCliSock,0))

	while True:
		data1 = raw_input('')
		if not data1: 				#user input enter key directly
			break
		tcpCliSock.send(data1)
		print ctime()," : " ,data1
	tcpCliSock.close()
