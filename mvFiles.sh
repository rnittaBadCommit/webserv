#!/bin/bash

sudo rm /etc/nginx/conf.d/*.conf
sudo cp config/nginxInception.conf /etc/nginx/conf.d/
sudo cp -R ./var/www/first_srv /var/www/
sudo cp -R ./var/www/hoge_srv /var/www/
sudo cp -R ./var/www/HTML /var/www/
