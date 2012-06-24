#!/usr/bin/python
# -*- coding: utf-8 -*-
# coding=utf-8 

import os
import sys
import re
import urllib
import urllib2
import cookielib
import csv
import json

import Token
import FileUtility
import FetchPostsDetail

def fetch_core(file_dir, url, access_token):

    # Initialize the needed modules
    CHandler = urllib2.HTTPCookieProcessor(cookielib.CookieJar())
    browser = urllib2.build_opener(CHandler)
    browser.addheaders = [('User-agent', 'InFB - ruel@ruel.me - http://ruel.me')]
    urllib2.install_opener(browser)

#     print 'Using access token: %s' % access_token + '\n'

    url = 'https://graph.facebook.com/'+url+ ('?limit=100&access_token=%s' % access_token)
    print url
    res = browser.open(url)
    fres = res.read()
    jdata = json.loads(fres)
    fres = json.dumps(jdata, ensure_ascii=False)

    i=1 
    FileUtility.write(file_dir+"/data"+str(i)+".json",fres)
    while len(jdata['data'])>0:

	data = jdata['data']
	for sub_data in data:
	    pid = sub_data['id']
	    FetchPostsDetail.fetch_core(pid,access_token)
	
	url = jdata['paging']['next']
	print url
	res = browser.open(url)
	fres = res.read()
	jdata = json.loads(fres)
	fres = json.dumps(jdata, ensure_ascii=False)

	i=i+1 
	FileUtility.write(file_dir+"/data"+str(i)+".json", fres)

def feed(access_token):
    dir_path = FileUtility.get_feed_data_path()
    print 'now fetching = feed\n'
    fetch_core(dir_path, "me/feed", access_token)

def posts(access_token):
    dir_path = FileUtility.get_posts_data_path()
    print 'now fetching = posts\n'
    fetch_core(dir_path, "me/posts", access_token)

if __name__ == '__main__':

    FileUtility.user = 'godgunman'
    FileUtility.make_data_path()

    user = 'godgunman@gmail.com'
    passw = 'tt1235813'
    token = Token.get(user, passw)

    feed(token)
    posts(token)
