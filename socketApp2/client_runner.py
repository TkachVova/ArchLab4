import argparse
import sys
import os
import time

args_parser = argparse.ArgumentParser(version='1.0',
									  add_help=True,
									  prog='client runner',
									  description='Runs clients.')

args_parser.add_argument('frequency',
						  metavar='frequency',
						  type=int,
						  help='Clients per second.')

args_parser.add_argument('request_length',
						  metavar='length',
						  type=int,
						  help='Length of data which generate every client.')

args_parser.add_argument('-sec',
						  metavar='seconds',
						  type=int,
						  default=1,
						  help='Number of seconds script will work.')

start = time.time()
args = args_parser.parse_args(sys.argv[1:])
for _ in xrange(0, args.sec):
	for __ in xrange(0, args.frequency):
		os.system('./simple_client -l 1 %d' % args.request_length) #in argv[2] we have 1 or 2 means simple_client or asio_client
		#print 1.0 - (time.time() - start)
		#if (1.0 - (time.time() - start)) > 0: 
		#	time.sleep(1.0 - (time.time() - start))
		#else: 
		#	time.sleep(1.0)
		time.sleep(1/2)

final = time.time()
print "Time: ", final - start
