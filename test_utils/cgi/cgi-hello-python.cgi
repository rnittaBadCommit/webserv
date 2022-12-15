#!/usr/local3/coins/linux/bin/python3
# -*- coding: utf-8 -*-
# cgi-hello-python.cgi -- 簡単な CGI のプログラム (Pyton版)
# ~yas/syspro/www/cgi-hello-python.cgi

def main():
    print_content()
    exit(0)

def print_content():
    print("<HTML><HEAD></HEAD><BODY>")
    print("hello.")
    print("</BODY></HTML>")

main()