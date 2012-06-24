#!/usr/bin/python

import sys
import re
import urllib
import urllib2
import cookielib
import csv
import json

def get(user , passw):

     # Initialize the needed modules
     CHandler = urllib2.HTTPCookieProcessor(cookielib.CookieJar())
     browser = urllib2.build_opener(CHandler)
     browser.addheaders = [('User-agent', 'InFB - ruel@ruel.me - http://ruel.me')]
     urllib2.install_opener(browser)


     # Initialize the cookies and get the post_form_data
     print 'Initializing..'
     res = browser.open('http://m.facebook.com/index.php')
     print 
     mxt = re.search('name="m_ts" value="(\w+)"', res.read())
     pfi = mxt.group(1)
     print 'Using PFI: %s' % pfi
     res.close()

     # Initialize the POST data
     data = urllib.urlencode({
          'lsd'				: '',
          'post_form_id'		: pfi,
          'charset_test' 		: urllib.unquote_plus('%E2%82%AC%2C%C2%B4%2C%E2%82%AC%2C%C2%B4%2C%E6%B0%B4%2C%D0%94%2C%D0%84'),
          'email'				: user,
          'pass'				: passw,
          'login'				: 'Login'
          })

     # Login to Facebook
     print 'Logging in to account ' + user
     res = browser.open('https://www.facebook.com/login.php?m=m&refsrc=http%3A%2F%2Fm.facebook.com%2Findex.php&refid=8', data)

     rcode = res.code
     rdata = res.read()
     if not re.search('Logout', rdata):
          print 'Login Failed'

          # For Debugging (when failed login)
          fh = open('debug.html', 'w')
          fh.write(rdata)
          fh.close

          # Exit the execution :(
          exit(2)
     res.close()

     # Get Access Token
     res = browser.open('http://developers.facebook.com/docs/reference/api')
     conft = res.read()
     mat = re.search('access_token=(.*?)"', conft)
     acct = mat.group(1)
     print 'Using access token: %s' % acct

     return acct

if __name__ == '__main__':
     
    user = 'godgunman@gmail.com'
    passw = 'tt1235813'
     
    token = get(user, passw)
    print token
