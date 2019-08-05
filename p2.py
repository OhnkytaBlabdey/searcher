import sys
from time import sleep
req = int(input().strip())
while req > 1:
	if req%2 == 0:
		req //= 2
	else:
		req = req * 3 + 1
	print(req)
	print('p2:', req, file=sys.stderr)
	sys.stdout.flush()
	req=0
	while req==0:
		try:
			req = int(input().strip())
		except EOFError:
			print('p2 waiting', file=sys.stderr)
			sleep(0.1)
# for line in sys.stdin:
# 	req = int(line)

# 	if req%2 == 0:
# 		req //= 2
# 	else:
# 		req = req * 3 + 1
# 	print(req)
# 	print(req, file=sys.stderr)
# 	if req == 1:
# 		break