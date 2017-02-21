import sys

def lcm(x,y):
    print("Lowest Common Multiple of " + x + " and " + y)
    x,y = int(x),int(y)
    if x > y:
        z = x
    else: z = y
    hcf = 1
    for i in range(1,z+1):
        if (x % i == 0) and (y % i == 0):
            hcf = i
    print("HCF is " + str(hcf))
    lowcom = (x*y)/(hcf)
    print("So LCM = " + str(lowcom))


lcm(sys.argv[1], sys.argv[2])
