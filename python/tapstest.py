import time
import random
from LFSR import LFSR
from Filter import Filter

l = int(input("Enter the length of the keystream in bytes:"))
N = 7
P = [0, 6]
key = [1, 1, 0, 0, 1, 0, 0]
n = 4

'''lg = [[], []]
u = [[0]]
for i in range(1, 1+ (n-1)//2):
u += [[2*i-1, 2*i]]
lg[0] = u
t = [[0], [1, 2]]
lg[1] = t
 '''   
g = [[0], [1, 2]]
G = Filter(key, N, P, g, n, 1)
keystream = [G.bit() for _ in range(l*8)] 
hkey = str(hex(int("".join(str(bit) for bit in key), 2)))
#print("keystream: ", keystream)
#print("key: ", hkey)
