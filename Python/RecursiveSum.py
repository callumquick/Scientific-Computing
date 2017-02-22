"""Simple attempt at calculating a sum of numbers 1 to N using recursion."""
import sys
N = int(sys.argv[1])
def sum(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return n + sum(n-1)

print("Sum is:")
print(sum(N))
