import math
import numpy as np
import matplotlib.pyplot as plt

lambda2 = 256
lambda1 = 128
N = int(input("LFSR length:"))
ai_max = 80
ai_vals = range(ai_max)
plt.figure(figsize=(16,9))

def somme_coeff_binomiaux(n, a):
    return sum([math.comb(n, i) for i in range(a+1)])

#Algebraic attack complexity
def compl_AA(ai):
    return math.log2(pow(somme_coeff_binomiaux(N, ai), 2))

c_vals = [compl_AA(a) for a in range(ai_max)]
plt.plot(ai_vals, c_vals, label='Algebraic attack complexity (AAC)')

#Fast Algebraic attack minimal complexity
def min_compl_fac(ai):
        s = somme_coeff_binomiaux(N, ai)
        return math.log2(pow(N, 2) + 2*N*s*math.log2(s))

c_vals = [min_compl_fac(ai) for ai in ai_vals]
plt.plot(ai_vals, c_vals, label='Fast algebraic attack complexity (FAAC)')
plt.plot(ai_vals, [lambda2 for _ in ai_vals], label = "y = "+str(lambda2))
plt.plot(ai_vals, [lambda1 for _ in ai_vals], label = "y = "+str(lambda1))
plt.legend(prop={'size':20} )
plt.xlabel('AI(f)', fontsize=20)
plt.ylabel('log2(complexity)', fontsize=20)
plt.grid()
plt.show()
