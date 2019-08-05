import sys
from time import sleep
req=0
while req==0 and not sys.stdin.closed:
	try:
		req = int(input().strip())
	except EOFError:
		# print('p2 waiting', file=sys.stderr)
		sleep(0.1)
while req > 1:
	if req%2 == 0:
		req //= 2
	else:
		req = req * 3 + 1
	print(req)
	print('p2:', req, file=sys.stderr)
	sys.stdout.flush()
	req=0
	while req==0 and not sys.stdin.closed:
		try:
			req = int(input().strip())
		except EOFError:
			# print('p2 waiting', file=sys.stderr)
			sleep(0.1)

sys.stdout.close()
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