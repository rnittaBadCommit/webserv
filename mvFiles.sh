#!/bin/bash

sudo cp config/basic.conf /etc/nginx/conf.d
sudo cp config/multiPort.conf /etc/nginx/conf.d
sudo cp config/multiServ.conf /etc/nginx/conf.d
sudo cp config/redirect.conf /etc/nginx/conf.d
sudo cp -R inceptionHTML /var/www/
