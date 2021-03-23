#!/usr/bin/python3

import sys
from subprocess import check_output

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python3 time_block2.py phods_v4_2d [iterations]")
        raise SystemExit

    if sys.argv[1] == 'phods_v4_2d':
        N = 144
        M = 176
        minimum = 1
        bx = 1
        by = 1

        for bx in range (1,N+1,1):
            if N%bx == 0:
                for by in range (1,M+1,1):
                    if M%by == 0:
                        cmd = ['./' + sys.argv[1], str(bx), str(by)]
                        iterations = int(sys.argv[2])

                        sum_time = 0
                        for i in range(iterations):
                            value = float(check_output(cmd).decode())
                            sum_time += value

                        avg_time = sum_time/iterations
                        print('Block size', bx,'x',by,':', str.format('{0:.6f}', avg_time), 'sec')

                    if avg_time < minimum:
                        minimum = avg_time
                        bx_min = bx
                        by_min = by

        print('Best block size:', bx_min, 'x', by_min, ':', str.format('{0:.6f}', minimum), 'sec')

    else:
        print("Usage: python3 time_block2.py phods_v4_2d [iterations]")
        raise SystemExit

