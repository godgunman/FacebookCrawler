# -*- coding: utf-8 -*-
# coding=utf-8 

import os
import sys
reload(sys)
sys.setdefaultencoding('utf8')

user = 'test'

def write(file_path, data, debug=True):

    if debug is True:
	print 'write %s to %s' % ('data', file_path) + '\n'

    fh = open(file_path, 'w')
    fh.write(data)
    fh.close()

def get_feed_data_path():
    return "data/users/"+user+"/feed"

def get_posts_data_path():
    return "data/users/"+user+"/posts"

def make_data_path():

    dir_paths = [
	    'data', 
	    'data/users', 
	    'data/posts',
	    'data/profile',
	    'data/users/'+user,
	    get_feed_data_path(),
	    get_posts_data_path()
	    ]

    for path in dir_paths:
	if os.path.isdir(path) == False :
	    os.mkdir(path)

def clean():
    pass

if __name__ == '__main__':

    user = 'godgunman'
    make_data_path()
    write('testutf8',u"你好")
