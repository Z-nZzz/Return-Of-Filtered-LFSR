from sage.rings.finite_rings import *
from scipy.special import comb
from sage.crypto.boolean_function import BooleanFunction
import math
import numpy as np
import matplotlib.pyplot as plt
import concurrent.futures

#parallel
def process_i(i):
    x = bin(i)[2:]
    state = [0] * (n - len(x)) + [int(xi) for xi in x]
    state = state[::-1]
    # hamming weight
    hw = sum(state)
    b = 0
    for monomial in g:
        tmp = 1
        for k in monomial:
            j = (k + hw) % n
            tmp *= state[j]
        b = b ^ tmp
    return b * 2**i

'''
#g = [[0], [1, 2]]
n_vals = range(29, 30)
vals = []
for n in n_vals:
    g = [[0]]
    for i in range(1, 1+ (n-1)//2):
        g+=[[2*i-1, 2*i]]
    N = pow(2, n)
    truth_table = 0
    #truth_table = []
    with concurrent.futures.ProcessPoolExecutor(max_workers=7) as executor:
        truth_table = sum(list(executor.map(process_i, range(N))))
    B = BooleanFunction(str(hex(truth_table))[2:])
    #P = B.algebraic_normal_form()
    #print(P)
    #print("nl:", B.nonlinearity())
    #print("AI:", B.algebraic_immunity())
    nl = B.nonlinearity()
    vals.append(math.log2(2^(n-1) - nl))
    #print(nl)
print(vals)
#Lower bound of the nonlinearity of a CWQ functions
def lb_nl_cwq(n):
    if n % 2 == 1:
        # n est impair
        n_sup = math.ceil(n/2)

        r = 2*(2*comb(n-3, n_sup-2) + comb(n-2, n_sup-1) + 1)
    else:
        # n est pair
        r = 2*(2*comb(n-3, n//2-2) + comb(n-2, n//2-1) + 2**(n//2-1) + comb(n-2, n//2-1) + 1)

    return math.log2(r)
N = int(input("N (1024 or 512):"))
l = int(input("l (128 or 256):"))
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
'''
N = 521
l = 128
t = 9

#Known value of log(2^n-1 - nl) for the wwq function t
l_r = [8 - 4, 16 - 10, 32-22,64- 46,128- 96,256- 196,512- 404,1024- 816, 2048-1672, 4096-3358,8192- 6854, 16384- 13722,32768- 27884]
nl_vals = list(map(math.log2, l_r))
#Known value of log(2^n-1 - nl) for the wwq function u
#nl_vals = np.array([2.0, 2.584962500721156, 3.0, 4.0, 4.584962500721156, 5.169925001442312, 5.807354922057604, 6.643856189774724, 7.321928094887363, 7.870364719583405, 8.554588851677638, 9.312882955284355, 10.169925001442312, 10.556506054671928, 11.330916878114618, 12.0, 13.087462841250339, 13.323054760341646, 14.146568675740786, 14.736190500960927, 16.044564882812626, 16.01976445284974, 17.076356332828116, 17.576956664706092, 19.022432836880434])

#nl_vals = vals
n_vals = range(4, len(nl_vals)+4)
#nl_vals = nl_vals.astype(float)

#Linear approximation
coefficients = np.polyfit(n_vals, nl_vals, 1)
slope, intercept = coefficients
x_extended = np.linspace(min(n_vals), max(n_vals) * 9, 100)
y_extended = slope * x_extended + intercept

plt.plot(x_extended, y_extended, '--', label='Linear approximation')
plt.plot(n_vals, nl_vals,'o', label="r = f(n); nl(f) = 2^(n-1) - 2^r")
n_vals = x_extended
r_vals = [(N-l)/(2*t*(t - 2))+ n -1 - l/(2*t)  for n in n_vals]

plt.plot(n_vals, r_vals, label="max(r)")
plt.plot(n_vals, [n//2 for n in n_vals], label="y = n//2")
plt.plot(n_vals, [1+2*n//3 + n//5 for n in n_vals], label="y = 1 + 2n/3")
#plt.plot(n_vals, [lb_nl_cwq(n) for n in n_vals], label="y = lb_nl_cwq(n)")
plt.grid()
plt.legend()
plt.xlabel("n")
plt.ylabel("r")
plt.show()
