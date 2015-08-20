import os,sys

path="."
ipath=unicode(path, "utf8")

newname=unicode("world", "utf8")

files=os.listdir(ipath)
if 'hello' in files:
	os.rename(os.path.join(ipath, 'hello'), os.path.join(ipath, newname))
