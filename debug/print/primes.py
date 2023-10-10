import argparse
import logging
import math
import sys

from collections.abc import Generator


def sieve(n : int) -> Generator[int, None, None]:
    '''Yield the prime numbers between 2 and n.'''
    arr: list[bool] = [True for _ in range(n+1)]

    for i in range(2, math.ceil(math.sqrt(n))):
        if arr[i]:
            for j in range(i*i, n, i):
                arr[j] = False

    for i, is_prime in enumerate(arr[2:n+1], 2):
        if is_prime:
            yield i


def main():
    parser = argparse.ArgumentParser(
        description='Print the prime numbers from 2 to n.')
    parser.add_argument('n', help='maximum number to print', type=int)
    args = parser.parse_args()
    for n in sieve(args.n):
        print(n)


if __name__ == '__main__':
    main()
