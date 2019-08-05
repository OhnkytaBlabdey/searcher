
"""
@echo off
:lb1
cbuf -head |maze tree.txt 2>log.txt|ans 2>nul|cbuf -rear 
chk 0<log.txt

if %errorlevel% leq 0 (
echo fail
goto lb1
)
if %errorlevel% leq 1(
echo successed
goto lb2
)
echo not found
:lb2
"""
		# query = fin1.readline().strip()
		# query = int(query)
		# fin1.flush()
		# fin2.flush()

import subprocess
import os
import time
import sys

flag = True
while flag:
	flog = open('log.txt', 'w')
	fout1 = open('buf1.txt', 'w') # maze -> ans
	fin1 = open('buf1.txt', 'r') # maze -> ans
	# ffin1 = open('buf1.txt', 'r') # maze -> ans
	fout2 = open('buf2.txt', 'w') # ans -> maze
	fin2 = open('buf2.txt', 'r') # ans -> maze
	# ffin2 = open('buf2.txt', 'r') # ans -> maze
	# pm = subprocess.Popen(['maze', 'tree.txt'], stderr = flog, stdout = fout1, stdin = subprocess.PIPE)
	# pa = subprocess.Popen(['ans'], stdout = subprocess.PIPE, stdin = fin1)
	pm = subprocess.Popen(['py', 'p1.py'], stderr = flog, stdout = fout1, stdin = fin2)
	pa = subprocess.Popen(['py', 'p2.py'], stdout = fout2, stdin = fin1)

	flag1 = True

	while subprocess.Popen.poll(pa)==None :
		time.sleep(0.25)
		# res = ffin1.readline()
		# print('query', res)
		# fout1.write(res)
		fout1.flush()

		time.sleep(0.25)
		# res = ffin2.readline()
		# print('ans', res)
		# fout2.write(res)
		fout2.flush()

		print('1 tick')
		
	
	flog.close()
	fin1.close()
	fin2.close()
	fout1.close()
	fout2.close()
	print('1 circle finished.')

	with open('log.txt', 'r') as f:
		line2 = ''
		for line in f.readlines():
			if line2 == line:
				# duplication
				flag = False
				print('duplication.')
				break
			# elif '1' in line:
			elif 'win' in line:
				# found
				flag = False
				print('found.')
				break
			line2 = line
		print('failed')

