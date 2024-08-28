from scipy.special import comb
import math
import numpy as np
import matplotlib.pyplot as plt

def lb_nl_cwq(n):
    if n % 2 == 1:
        # n est impair
        n_sup = math.ceil(n/2)

        r = 2*(2*comb(n-3, n_sup-2) + comb(n-2, n_sup-1) + 1)
    else:
        # n est pair
        r = 2*(2*comb(n-3, n//2-2) + comb(n-2, n//2-1) + 2**(n//2-1) + comb(n-2, n//2-1) + 1)

    return math.log2(r)

N = int(input("N :"))
l = int(input("l (128 or 256 or 512 or 312 or 226):"))

#looking for the value of t s.t. the complexity is minimal
a = l
b = -2*(l + N)
c = 2*(l + N)
discriminant = b**2 - 4*a*c
t = int((-b + math.sqrt(discriminant)) / (2*a))

#Known value of log(2^n-1 - nl) for the wwq function u
nl_vals = np.array([2.0, 2.584962500721156, 3.0, 4.0, 4.584962500721156, 5.169925001442312, 5.807354922057604, 6.643856189774724, 7.321928094887363, 7.870364719583405, 8.554588851677638, 9.312882955284355, 10.169925001442312, 10.556506054671928, 11.330916878114618, 12.0, 13.087462841250339, 13.323054760341646, 14.146568675740786, 14.736190500960927, 16.044564882812626, 16.01976445284974, 17.076356332828116, 17.576956664706092, 19.022432836880434])

#nl_vals = vals
n_vals = range(4, len(nl_vals)+4)
nl_vals = nl_vals.astype(float)

#Linear approximation
coefficients = np.polyfit(n_vals, nl_vals, 1)
slope, intercept = coefficients
x_extended = np.linspace(min(n_vals), max(n_vals) * 5, 100)
y_extended = slope * x_extended + intercept

plt.plot(x_extended, y_extended, '--', label='Linear approximation of r')
plt.plot(n_vals, nl_vals,'o', label="r = 2^(n-1) - nl(f)")
n_vals = x_extended
tmp = [(N-l)/(2 * t * (t - 2))+ n -1 - l/(2*t)  for n in n_vals]
maxr_vals = [tmp[i] if tmp[i] > 0 else 0 for i in range(len(tmp))]

plt.plot(n_vals, maxr_vals, label="max(r), with N = " + str(N) + " lambda = " + str(l))
plt.plot(n_vals, [n//2 for n in n_vals], label="y = n//2")
plt.plot(n_vals, [n/10 + 2*n/3 for n in n_vals], label="y = n/10 + 2n/3")
plt.plot(n_vals, [lb_nl_cwq(n) for n in n_vals], label="Proven upper bound")
plt.grid()
plt.legend()
plt.xlabel("n", fontsize=15)
plt.ylabel("r", fontsize=15)
plt.show()












'''
if N == 521:
    if l == 128:
        t = 9
    elif l == 256:
        t = 5
    elif l == 312:
        t = 4

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
