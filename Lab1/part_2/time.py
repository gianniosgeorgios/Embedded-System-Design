#!/usr/bin/python3

import sys
import time
from subprocess import check_output

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: time.py [tables] <iterations>")
        raise SystemExit

    cmd = ['./' + sys.argv[1]]
    iterations = int(sys.argv[2])

    sum_time = 0
    min_time = 1
    max_time = 0

    for i in range(iterations):
        value = float(check_output(cmd).decode())

        #print('Value', i, ':', value)
        sum_time += value
        if value < min_time:
            min_time = value
        if value > max_time:
            max_time = value

    avg_time = sum_time/iterations

    print('(min, average, max)= ', min_time,str.format('{0:.6f}',avg_time), max_time)
