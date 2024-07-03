import time
import random
from LFSR import LFSR
from Filter import Filter

#N = int(input("Enter N (1024 or 512 or 2048 or 2203 or 607 or 2281 or 1279 or 521):"))
n = int(input("Enter n :"))
l = int(input("Enter the length of the keystream to generate in Ko:"))
for N in [  512, 521, 607, 1024, 1279  , 2048, 2203 , 2281]:
    key = [ random.getrandbits(1) for _ in range(N) ]
#Setting the primitive polynomial of degree N
    if N == 2281:
        P = [714, 2280]
    elif N == 2203:
        P = [4, 5, 13, 2202]
    elif N == 2048:
        P = [0, 12, 13, 18, 2047]
    elif N == 1279:
        P = [215, 1278]
    elif N == 521:
        P = [31, 520]
    elif N == 607:
        P = [104, 606]
#x^1024 + x^19 + x^6 + x + 1
    elif N == 1024:
        P = [5, 18, 1023]
#x^512 + x^8 + x^5 + x^2 + 1
    elif N == 512:
        P = [1, 4, 7, 511]
    else:
        print("Bro I said 1024 or 512 or 2048 or a mersenne prime around those...")
        exit(1)
    print("N: ",N)

#g = u or g = t, where u and t are one of the quadratic functions studied in "On the cryptographic properties of weightwise affine and weightwise quadratic functions"
    lg = [[], []]
    u = [[0]]
    for i in range(1, 1+ (n-1)//2):
        u += [[2*i-1, 2*i]]
    lg[0] = u
    t = [[0], [1, 2]]
    lg[1] = t
    for g in lg:
        G = Filter(key, N, P, g, n)
        start_time = time.time()
        keystream = [G.bit() for _ in range(l*8000)] 
        end_time = time.time()

        hkey = str(hex(int("".join(str(bit) for bit in key), 2)))
    #print("keystream: ", keystream)
        execution_time = end_time - start_time
        #print("key: ", hkey)
        #print(g)
        print(f"Execution time: {execution_time} seconds")
    print()

