import time
import random
from LFSR import LFSR
from Filter import Filter

l = int(input("Enter the length of the keystream:"))
for N in [1]:
    N = 4
    P = [1, 3]
    key = [1, 0, 0, 1]
    n = 3

#g = u or g = t, where u and t are one of the quadratic functions studied in "On the cryptographic properties of weightwise affine and weightwise quadratic functions"
    lg = [[], []]
    u = [[0]]
    for i in range(1, 1+ (n-1)//2):
        u += [[2*i-1, 2*i]]
    lg[0] = u
    t = [[0], [1, 2]]
    lg[1] = t
    
    for g in lg:
        G = Filter(key, N, P, g, n, 1)
        start_time = time.time()
        keystream = [G.bit() for _ in range(l*8)] 
        end_time = time.time()

        hkey = str(hex(int("".join(str(bit) for bit in key), 2)))
    #print("keystream: ", keystream)
        execution_time = end_time - start_time
        #print("key: ", hkey)
        #print(g)
        print(f"Execution time: {execution_time} seconds")
    print()

