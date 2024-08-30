import numpy as np
import matplotlib.pyplot as plt
import random

#List of primes
p = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741]
#taps that are increasing sum of primes
def get_tapsp (N, n):
    sp = [0]
    c = 1
    i = 0
    while c < n:
        x = (sp[c-1] + p[i])%N
        if not x in sp:
            sp +=[x]
            c += 1
        i += 1
    print(sp)
    sp.sort()
    return sp
'''
#This part is used to generate the list of taps for the optimized version in C, using words of 64 or 32 bits
    wsize = 64
    #wsize = 32
    lpos = []
    for x in sp:
        lpos += [[x // wsize, x % wsize]]
    print(lpos)
    tap = [0]*(1 + N//wsize)
    for li in lpos:
        i, x = li[0], li[1]
        tap[i]+= 2**x
    return tap
'''
#prime modulo N
def get_tapp (N, n):
    sp = [0]
    c = 1
    i = 0
    while c < n:
        x = (p[i])%N
        if not x in sp:
            sp +=[x]
            c += 1
        i += 1
    print(sp)
    sp.sort()
    return sp

#Mix of sum of primes taps and regularly spaced taps
def get_taphp (N, n, t):
    tmp = get_tapsp(N, 160)
    sp = []
    c = 0
    i = 0
    while c < n//2:
        #print(c)
        x = tmp[i]
        if (x % 2)== 0:
            sp += [x, (x + t) % N]
            c += 1
        i += 1
    print(sp)
    sp.sort()
    return sp

#N, n = 521, 128
N = int(input("N: "))
n = int(input("n: "))
s = int(input("shift for the half regular distribution: "))
labels = ["primes", "sum of primes", "half regularly distributed taps", "regularly distributed", "random distribution"]
tap1 = get_tapp(N, n)
tap2 = get_tapsp(N, n)
tap3 = get_taphp(N, n, s)
tap4 = [i * N//n for i in range(n)]
tap5 = []
c = 0
while c < n:
    x = random.randint(0, N-1)
    if x not in tap5:
        tap5 += [x]
        c +=1
tap5.sort()
print("tap5 random :", tap5) 

TAP = [tap1, tap2, tap3, tap4, tap5]
n_vals = range(N)
for k, tap in enumerate(TAP):
    distr = [0]*N
    for i in range(n-1):
        x = tap[i]
        for j in range(i+1, n):
            y = tap[j]
            distr[abs(x-y)] += 1        
        #y = tap[i+1]
        #distr[abs(x-y)] += 1        
    plt.bar(n_vals, distr, label = labels[k])
    plt.xlabel("Distance", fontsize=15)
    plt.ylabel("Occurrence", fontsize=15)
    plt.legend()
    plt.show()
'''
'''

