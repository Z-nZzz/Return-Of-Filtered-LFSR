import math
import numpy as np
import matplotlib.pyplot as plt

#Computing the max values for r = 2^(n-1 - nl) dependin on n, to be resistant against the corelation attack (considering it's minimal complexity) with l bits of security for a chosen N. 

N = int(input("N: "))
l = int(input("Security level l: "))
n_max = 250

#looking for the value of t s.t. the complexity is minimal
a = l
b = -2*(l + N)
c = 2*(l + N)
discriminant = b**2 - 4*a*c
t = int((-b + math.sqrt(discriminant)) / (2*a))
print(t)
plt.figure(figsize=(16,9))
vals = np.array([(N-l)/(2*t*(t - 2))+ n -1 - l/(2*t)  for n in range(n_max)])
vals = np.array([vals[n] if vals[n] >= n//2 -1 else 0 for n in range(n_max)])
plt.plot(range(n_max), vals, label='max(r), with lambda = '+ str(l) + ', N = ' + str(N))
plt.plot(range(n_max), [n-1 for n in range(n_max)], label='y = n-1')
plt.plot(range(n_max), [n//2 - 1  for n in range(n_max)], label='y = n/2 - 1')
plt.grid()
plt.legend(prop={'size': 20})
plt.xlabel('n', fontsize=20)
plt.ylabel('max(r)', fontsize=20)
plt.show()






'''
lambda1= 256
lambda2 = 128

l = lambda1
if N == 512:
    if l == 128:
        t = 9
    if l == 256:
        t = 5

if N == 2048:
    if l == 128:
        t = 32
    else : 
        t = 16

if N == 1024:
    if l == 128:
        t = 17
    else : 
        t = 9
if N == 521:
    if l == 128:
        t = 9
    if l == 256:
        t = 5

if N == 2203:
    if l == 128:
        t = 32
    elif l == 512:
        t = 9 
    else : 
        t = 16

if N == 1279:
    if l == 128:
        t = 17
    elif l == 512:
        t = 5 
    else : 
        t = 9
'''
