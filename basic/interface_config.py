#! /usr/bin/env python
#--*-- coding:utf8 ---*---

import commands
import re
import sys

def find_encap(line, if_dict):
	line = line.lower()
	index = line.find('encap')
	up = line[index:].find(' ')
	if index != -1 and up != -1:
		key, value = line[index : up+index].split(':')
		if_dict[key] = value
		return 1
	return 0

def find_hwaddr(line, if_dict):
	line = line.lower()
	index = line.find('hwaddr')
	up = line[index+7:].find(' ')       #skip first space
	up += 7
	if index != -1:
		key, value = line[index : up+index].split(' ')
		if_dict[key] = value
		return 1
	return 0

def write_to_file(name, if_dict):
	filepath = '/etc/sysconfig/network-scripts/ifcfg-' + name
	file = open(filepath, 'w')
	file.write('DEVICE="' + name + '"\n')
	file.write('BOOTPROTO="static"' + '\n')
	file.write('TYPE="' + if_dict['encap'] + '"\n')
	file.write('HWADDR="' + if_dict['hwaddr'] + '"\n')
	file.write('ONBOOT="yes"' + '\n')
	file.write('NM_CONTROLLED="yes"' + '\n')
	file.close()
	



if __name__ == '__main__':
	ifconfig = commands.getoutput("ifconfig -a")
	ifconfig = ifconfig.split('\n')
	
	interfaces = {}
	name=None

	for line in ifconfig:
		match = re.match('^[^ \t]\S*', line)
		if match:
			name = match.group()
			interfaces[name] = {}		#save as key:value
		if name == None :
			exit(-1);		#unlikely
		if find_encap(line,  interfaces[name]):
			print interfaces[name]['encap']
		if find_hwaddr(line, interfaces[name]):
			print interfaces[name]['hwaddr']
	
	for name in interfaces.keys():
		if name == 'lo':
			continue
		write_to_file(name, interfaces[name] )


	print 'done'
