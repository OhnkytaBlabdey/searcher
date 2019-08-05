import sys
from time import sleep
req = 7
# print(req)
# print(req, file=sys.stderr)
while(req > 1):
	print(req)
	print('p1:', req, file=sys.stderr)
	sys.stdout.flush()
	req = 0
	while req==0 and not sys.stdin.closed:
		try:
			req = int(input().strip())
		except EOFError:
			# print('p1 waiting', file=sys.stderr)
			sleep(0.1)
if req == 1:
	print(req)
	print('p1:', req, file=sys.stderr)
	sys.stdout.flush()
sys.stdout.close()
# for line in sys.stdin:
# 	req = int(line)
# 	print(req)
# 	print(req, file=sys.stderr)
# 	if req == 1:
# 		break