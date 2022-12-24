#!/usr/local3/coins/linux/bin/python3
# -*- coding: utf-8 -*-
# check-cgi-environ.py -- 簡単な CGI のプログラム (Pyton版)
# ~yas/syspro/www/check-cgi-environ.py

import os

def main():
    cgi_env = os.environ
    html = '<html><head><title>CGI ENVIRONMENT</title></head><body><h1>CGI ENVIRONMENT</h1><table>'
    for key, value in cgi_env.items():
        html += f'<tr><td>{key}</td><td>{value}</td></tr>'
    html += '</table></body></html>'

    print('Content-type: text/html\n')
    print(html)

    exit(0)


main()