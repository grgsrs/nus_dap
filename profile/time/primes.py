import argparse
import logging
import math
import sys
import time

from collections.abc import Generator


def sieve(n : int) -> list[int]:
    '''Yield the prime numbers between 2 and n.'''
    arr: list[bool] = [True for _ in range(n+1)]

    for i in range(2, math.ceil(math.sqrt(n)) + 1):
        if arr[i]:
            for j in range(i*i, n+1, i):
                arr[j] = False

    return list(i for i, is_prime in enumerate(arr[2:n+1], 2) if is_prime)
            


def main():
    parser = argparse.ArgumentParser(
        description='Print the largest prime numbers no greater than n.')
    parser.add_argument('n', help='maximum number to print', type=int)
    args = parser.parse_args()
    
    # start = time.monotonic()
    primes = sieve(args.n)
    # end = time.monotonic()
    print(primes[-1])
    
    # print("calculating took %.2f seconds" % (end - start,))


if __name__ == '__main__':
    main()
