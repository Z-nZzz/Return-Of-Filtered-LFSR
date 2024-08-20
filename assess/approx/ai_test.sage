from sage.rings.finite_rings import *
from scipy.special import comb
from sage.crypto.boolean_function import BooleanFunction
import math
import numpy as np
import matplotlib.pyplot as plt

print("AI(t):")
g = [[0], [1, 2]]
n_vals = range(16, 18)
vals = []
'''
print("AI(u):")
g = [[0]]
for i in range(1, 1+ (n-1)//2):
    g+=[[2*i-1, 2*i]]

'''
for n in n_vals:
    N = pow(2, n)
    truth_table = []
    for i in range(N):
        x = bin(i)[2:]
        state =[0]*(n - len(x)) + [int(xi) for xi in x ] 
        state = state[::-1]
        #hamming weight
        hw = sum(state)
        b = 0
        for monomial in g:
            tmp = 1
            for k in monomial:
                j = (k + hw) % n
                tmp *= state[j]
            b = b ^^ tmp
        truth_table += [b]
    B = BooleanFunction(truth_table)
    #P = B.algebraic_normal_form()
    #print(P)
    #print("nl:", B.nonlinearity())
    ai = B.algebraic_immunity()
    print("AI:", ai)
    vals.append(ai)
print(vals)

#For g = u:
vals = [2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7]
#For g = t:
#vals = [2, 3, 3, 3, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7]
n_vals = range(4, len(vals)+4)
coefficients = np.polyfit(n_vals, vals, 1)
slope, intercept = coefficients
print(coefficients)
x_extended = np.linspace(min(n_vals), max(n_vals) * 7, 100)
y_extended = slope * x_extended + intercept
y_extended = [math.ceil(y) for y in y_extended] 

plt.plot(x_extended, y_extended, '--', label='Linear approximation of AI(f)')
plt.plot(n_vals, vals,'o', label="AI(f), for g = u;")
#plt.plot(x_extended, [22 for _ in x_extended], label="y = 22")
#plt.plot(x_extended, [52 for _ in x_extended], label="y = 52")
plt.plot(x_extended, [x//3 for x in x_extended], label="y = n/3")
plt.grid()
plt.legend()
plt.xlabel("n", fontsize=15)
plt.ylabel("ai", fontsize=15)
plt.show()
