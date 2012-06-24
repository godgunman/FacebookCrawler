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

def fetch_core(uid, access_token):

    uid = str(uid)

    # Initialize the needed modules
    CHandler = urllib2.HTTPCookieProcessor(cookielib.CookieJar())
    browser = urllib2.build_opener(CHandler)
    browser.addheaders = [('User-agent', 'InFB - ruel@ruel.me - http://ruel.me')]
    urllib2.install_opener(browser)

#     print 'Using access token: %s' % access_token + '\n'

    url = 'https://graph.facebook.com/%s?access_token=%s' % (uid, access_token)
    print url
    res = browser.open(url)
    fres = res.read()
    jdata = json.loads(fres)
    fres = json.dumps(jdata, ensure_ascii=False)

    FileUtility.write('data/profile/%s.json' % uid,fres)

# fetch profile picture

    f = open('data/profile/%s_picture.png'%uid,"wb")
    f.write(urllib.urlopen('https://graph.facebook.com/%s/picture?type=large'%uid ).read())
    f.close()


if __name__ == '__main__':
   
    FileUtility.user = 'godgunman'
    FileUtility.make_data_path()

    user = 'godgunman@gmail.com'
    passw = 'tt1235813'
    token = Token.get(user, passw)

    fp = open("people_list","r")
    lines = fp.read()


    lines = lines.split("\n")
    
    print len(lines)
    i = 1
    for line in lines:
	fetch_core(line, token)
	print line,i 
	i+=1 
 
