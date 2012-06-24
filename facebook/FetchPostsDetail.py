#!/usr/bin/python

import os
import sys
import urllib
import urllib2
import cookielib
import json

import Token
import FileUtility

def fetch_core(post_id, access_token):
    
    if os.path.isdir("data/posts/"+post_id) == False:
        os.mkdir("data/posts/"+post_id)
    else:
	print 'File has aleary existed, skip!!'
	return

    print 'In FetchPostsDetail.py parse' + post_id 


    # Initialize the needed modules
    CHandler = urllib2.HTTPCookieProcessor(cookielib.CookieJar())
    browser = urllib2.build_opener(CHandler)
    browser.addheaders = [('User-agent', 'InFB - ruel@ruel.me - http://ruel.me')]
    urllib2.install_opener(browser)

    url = 'https://graph.facebook.com/'+post_id+ ('&access_token=%s' % access_token)
    res = browser.open(url)
    fres = res.read()
    jdata = json.loads(fres)
    fres = json.dumps(jdata, ensure_ascii=False)

    FileUtility.write("data/posts/"+post_id+"/content.json",fres)

    url = 'https://graph.facebook.com/'+post_id+'/likes'+ ('&access_token=%s' % access_token)
    res = browser.open(url)
    fres = res.read()
    jdata = json.loads(fres)
    fres = json.dumps(jdata, ensure_ascii=False)
    FileUtility.write("data/posts/"+post_id+"/likes.json",fres)


    url = 'https://graph.facebook.com/'+post_id+'/comments'+ ('&access_token=%s' % access_token)
    res = browser.open(url)
    fres = res.read()
    jdata = json.loads(fres)
    fres = json.dumps(jdata, ensure_ascii=False)
    FileUtility.write("data/posts/"+post_id+"/comments.json",fres)

if __name__ == '__main__':

    FileUtility.user = 'godgunman'
    FileUtility.make_data_path()

    user = 'godgunman@gmail.com'
    passw = 'plumggmtutu'
    token = Token.get(user, passw)

    fetch_core('100000154563058_407470182627805', token)
