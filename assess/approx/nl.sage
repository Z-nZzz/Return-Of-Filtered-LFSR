import math
import numpy as np
import matplotlib.pyplot as plt
from sage.rings.finite_rings import *
from sage.crypto.boolean_function import BooleanFunction

def generate_truth_table(n, g):
    """Generate truth table for a given Boolean function."""
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
                j = (k + hw - 1) % n
                tmp *= state[j]
            b = b ^^ tmp
        truth_table += [b]
    return truth_table

def calculate_nonlinearity(n, g):
    """Calculate nonlinearity for a given Boolean function."""
    truth_table = generate_truth_table(n, g)
    B = BooleanFunction(truth_table)
    return math.log2(pow(2, n-1) - B.nonlinearity())

def lb_nl_cwq(n):
    """Calculate the proven lower bound for f of base g = x1 + x2x3"""
    if n % 2 == 1:
        n_sup = math.ceil(n/2)
        r = 2*(2*math.comb(n-3, n_sup-2) + math.comb(n-2, n_sup-1) + 1)
    else:
        r = 2*(2*math.comb(n-3, n//2-2) + math.comb(n-2, n//2-1) + 2**(n//2-1) + math.comb(n-2, n//2-1) + 1)
    return math.log2(r)

def plot_nonlinearity(n_vals, vals, g_description):
    """Plot nonlinearity values and linear approximation."""
    plt.figure(figsize=(16, 9))
    
    # Calculate linear approximation
    coefficients = np.polyfit(n_vals, vals, 1)
    slope, intercept = coefficients
    x_extended = np.linspace(min(n_vals), max(n_vals) * 7, 100)
    y_extended = [math.ceil(slope * x + intercept) for x in x_extended]
    
    # Plotting
    plt.plot(x_extended, y_extended, '--', label='Linear approximation of 2^(n-1) - nl(f)')
    plt.plot(n_vals, vals, 'o', label=f"2^(n-1) - nl(f), g = {g_description}")
    plt.plot(x_extended, [n//2 - 1 for n in x_extended], label="y = n//2")
    plt.plot(x_extended, [1+2*n//3 + n//5 for n in x_extended], label="y = n/10 + 2n/3")
    #plt.plot(x_extended, [lb_nl_cwq(n) for n in x_extended], label="Proven lower bound")
    
    plt.grid()
    plt.legend(prop={'size': 20})
    plt.xlabel("n", fontsize=20)
    plt.ylabel("AI", fontsize=20)
    plt.title("Nonlinearity Analysis", fontsize=24)

    plt.show()

def get_user_input():
    """Get user input for the range of n values."""
    while True:
        try:
            start = int(input("Enter the start value for n (minimum 4): "))
            end = int(input("Enter the end value for n(max 20 or it will be too long to compute): "))
            if start < 4:
                print("Start value must be at least 4.")
            elif end <= start:
                print("End value must be greater than start value.")
            else:
                return range(start, end + 1)
        except ValueError:
            print("Please enter valid integer values.")

def gen_g_v(n):
    """Generate base function g x_0 + sum(x_-i)(x_2i)"""
    g = [[0]]
    for i in range(1, n//3):
        g.append([-i % n, 2*i % n])
    return g

def main():
    # Define the Boolean functions
    g_t = [[0], [1, 2]]  # x0 + x1x2
    #g_u = [[0]] + [[2*i-1, 2*i] for i in range(1, 1 + (n)//2)]

    # Known values
    l_r = [8 - 4, 16 - 10, 32-22,64- 46,128- 96,256- 196,512- 404,1024- 816, 2048-1672, 4096-3358,8192- 6854, 16384- 13722,32768- 27884]
    vals_t = list(map(math.log2, l_r))
    n_vals_t = range(4, len(vals_t) + 4)
    
    vals_u = np.array([2.0, 2.584962500721156, 3.0, 4.0, 4.584962500721156, 5.169925001442312, 5.807354922057604, 6.643856189774724, 7.321928094887363, 7.870364719583405, 8.554588851677638, 9.312882955284355, 10.169925001442312, 10.556506054671928, 11.330916878114618, 12.0, 13.087462841250339, 13.323054760341646, 14.146568675740786, 14.736190500960927, 16.044564882812626, 16.01976445284974, 17.076356332828116, 17.576956664706092, 19.022432836880434])
    vals_u = vals_u.astype(float)
    n_vals_u = range(4, len(vals_u) + 4)

    print("This program plots the Nonlinearity for Boolean functions.")
    print("1. Plot known values for f with g = x0 + x1x2")
    print("2. Plot known values for f with g = x0 + x1x2 + x3x4 + x5x6 + ... + xn/2xn/2+1")
    print("3. Calculate and plot values for g = x0 + x1x2")
    print("4. Calculate and plot values for g = x0 + sum(x_-i)(x_2i)")
    
    choice = input("Enter your choice (1, 2, 3 or 4): ")

    if choice == '1':
        plot_nonlinearity(n_vals_t, vals_t, "x0 + x1x2 (known values)")
    elif choice == '2':
        plot_nonlinearity(n_vals_u, vals_u, "x0 + sum(x(2i)x(2i+1)) (known values)")
    elif choice == '3':
        n_vals = get_user_input()
        print("Calculating nonlinearity...")
        vals = [calculate_nonlinearity(n, g_t) for n in n_vals]
        print("Nonlinearity values:", vals)
        print("Coefficients of linear approximation:", np.polyfit(n_vals, vals, 1))
        plot_nonlinearity(n_vals, vals, "x0 + x1x2")
    elif choice == '4':
        n_vals = get_user_input()
        print("Calculating nonlinearity...")
        vals = [calculate_nonlinearity(n, gen_g_v(n)) for n in n_vals]
        print("Nonlinearity values:", vals)
        print("Coefficients of linear approximation:", np.polyfit(n_vals, vals, 1))
        plot_nonlinearity(n_vals, vals, "x0 + sum(x_-i)(x_2i)")
    else:
        print("Invalid choice. Please run the program again and select 1, 2, 3 or 4.")
    
if __name__ == "__main__":
    main()

