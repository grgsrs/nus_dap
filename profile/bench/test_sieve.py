import array
import math

def sieve_array(n : int) -> list[int]:
    '''Return a list of prime numbers between 2 and n.'''
    arr: array = array.array('b', (1 for _ in range(n+1)))

    for i in range(2, math.ceil(math.sqrt(n)) + 1):
        if arr[i]:
            for j in range(i*i, n+1, i):
                arr[j] = 0

    return list(i for i, is_prime in enumerate(arr[2:n+1], 2) if is_prime)


def sieve_bytearray(n : int) -> list[int]:
    '''Return a list of prime numbers between 2 and n.'''
    arr: bytearray = bytearray(b'\x01'*(n+1))

    for i in range(2, math.ceil(math.sqrt(n)) + 1):
        if arr[i]:
            for j in range(i*i, n+1, i):
                arr[j] = 0

    return list(i for i, is_prime in enumerate(arr[2:n+1], 2) if is_prime)


def sieve(n: int) -> list[int]:
    '''Return a list of prime numbers between 2 and n.'''
    arr: list[bool] = [True] * (n+1)

    for i in range(2, math.ceil(math.sqrt(n)) + 1):
        if arr[i]:
            for j in range(i*i, n+1, i):
                arr[j] = False

    return list(i for i, is_prime in enumerate(arr[2:n+1], 2) if is_prime)


def test_sieve_array(benchmark):
    '''Benchmark the array-based sieve implementation.'''
    result = benchmark(sieve_array, 10000)
    assert result[-1] == 9973


def test_sieve_bytearray(benchmark):
    '''Benchmark the bytearray-based sieve implementation.'''
    result = benchmark(sieve_bytearray, 10000)
    assert result[-1] == 9973


def test_sieve_list(benchmark):
    '''Benchmark the list-based sieve implementation.'''
    result = benchmark(sieve, 10000)
    assert result[-1] == 9973
