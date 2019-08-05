import sys
req = 7
# print(req)
# print(req, file=sys.stderr)
while(req > 1):
	print(req)
	print('p1:', req, file=sys.stderr)
	sys.stdout.flush()
	req = 0
	while req==0:
		try:
			req = int(input().strip())
		except EOFError:
			print('p1 waiting', file=sys.stderr)
			sleep(0.1)
# for line in sys.stdin:
# 	req = int(line)
# 	print(req)
# 	print(req, file=sys.stderr)
# 	if req == 1:
# 		break