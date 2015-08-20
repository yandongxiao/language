#!/usr/bin/python
# -*- coding: utf-8 -*-
from socket import *
from time import ctime
from thread import *

#同时接受多个用户的连接
#将用户发送的消息同时分发给多个人
#合适的异常处理.

clientSocket = []
BUFSIZ = 1024

def newClientSocket(sock, addr):
	while True:
		try:
			data = sock.recv(BUFSIZ)
			if not data:
				break
			for allsock in clientSocket :
				if allsock[0] != sock :
					allsock[0].send('[%s] : %s\n' % (ctime(), data))
		except Exception:
			print 'client colsed'
			break;
	sock.close()
	clientSocket.remove((sock, addr))


if __name__ == '__main__' :
	HOST = '192.168.12.90' 	#服务端的IP地址和端口号直接写死.
	PORT = 8888
	ADDR = (HOST, PORT)
	
	tcpSerSock = socket(AF_INET, SOCK_STREAM)
	tcpSerSock.bind(ADDR)
	tcpSerSock.listen(5)
	while True:
		print 'waiting for connection...'
		tcpCliSock, addr = tcpSerSock.accept()
		clientSocket.append((tcpCliSock, addr))
		start_new_thread(newClientSocket, (tcpCliSock, addr))
		print '...connected from:', addr
	tcpSerSock.close()
