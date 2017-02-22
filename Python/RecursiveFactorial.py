"""Simple attempt at calculating factorial of N using recursion."""
import sys
N = int(sys.argv[1])
def fact(n):
    if n == 0:
        return 1
    elif n == 1:
        return 1
    else:
        return n*fact(n-1)

print("Factorial is:")
print(fact(N))
