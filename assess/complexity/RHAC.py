import math
import numpy as np
import matplotlib.pyplot as plt

s = 256
s2 = 128
N = int(input("LFSR length:"))
n = 128
plt.figure(figsize=(16,9))

def somme_coeff_binomiaux(n, a):
    return sum([math.comb(n, i) for i in range(a+1)])

#Complexity of the RHA
def compl_RH(d):
    return math.log2(somme_coeff_binomiaux(N, d))

c_vals = [compl_RH(d) for d in range(n)]
plt.plot(range(n), c_vals, label='RHA complexity')
plt.plot(range(n), [s for _ in range(n)], label = "y = "+str(s))
plt.plot(range(n), [s2 for _ in range(n)], label = "y = "+str(s2))
#plt.title("Courbe de la compléxité de l'attaque de Ronjhom-Hellset en fonction de d, avec N = "+str(N)+" pour un niveau de sécurité 2^"+str(s))
plt.legend(prop={'size': 20})
plt.grid()
plt.xlabel('d', fontsize=20)
plt.ylabel('Log(complexity)', fontsize=20)
plt.show()

