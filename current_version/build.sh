#!/bin/sh
# apt-get install libsdl-dev libdevil-dev
# http://ftp.debian.org/debian/pool/main/d/devil/libdevil-dev_1.7.8-10+b2_amd64.deb
# sudo dpkg -i libdevil-dev_1.7.8-10+b2_amd64.deb
g++ -I./K2D -I/usr/include/SDL -I/usr/include/GL -I/usr/include main.cpp K2D/K2D_Engine.h CGame.h