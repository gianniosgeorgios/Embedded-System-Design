#!/usr/bin/python3

import sys
from subprocess import check_output

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python3 time_block.py phods_v4 [iterations]")
        raise SystemExit

    if sys.argv[1] == 'phods_v4':
        block_sizes = [1, 2, 4, 8, 16]
        for N in block_sizes:
            cmd = ['./' + sys.argv[1], str(N)]
            iterations = int(sys.argv[2])

            sum_time = 0
            for i in range(iterations):
                value = float(check_output(cmd).decode())
                #print('./', sys.argv[1], sys.argv[2], '--> Value', i, ':', value)
                sum_time += value

            avg_time = sum_time/iterations
            print('Block size', N, ':', str.format('{0:.6f}', avg_time), 'sec')

    else:
        print("Usage: python3 time_block.py phods_v4 [iterations]")
        raise SystemExit
