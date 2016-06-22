#!/bin/bash 
# 这个脚本用于程序运行分析，如要使用请参考博客装好相应工具并修改Makefile CFLAG = -O0 -pg
./image_chache 
gprof ./image_chache | gprof2dot.py >x.dot
xdot.py x.dot
rm x.dot gmon.out
