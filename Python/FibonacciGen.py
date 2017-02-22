"""Generates the Fibonacci sequence up to the nth term."""
import sys
N = int(sys.argv[1])

def fibb(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibb(n-1) + fibb(n-2)

def fibbseq(n):
    sequence = []
    for i in range(1,n+1):
        sequence.append(fibb(i))
    print(sequence)

fibbseq(N)
