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

def calculate_algebraic_immunity(n, g):
    """Calculate algebraic immunity for a given Boolean function."""
    truth_table = generate_truth_table(n, g)
    B = BooleanFunction(truth_table)
    return B.algebraic_immunity()

def plot_algebraic_immunity(n_vals, vals, g_description):
    """Plot algebraic immunity values and linear approximation."""
    plt.figure(figsize=(16, 9))
    
    # Calculate linear approximation
    coefficients = np.polyfit(n_vals, vals, 1)
    slope, intercept = coefficients
    x_extended = np.linspace(min(n_vals), max(n_vals) * 7, 100)
    y_extended = [math.ceil(slope * x + intercept) for x in x_extended]
    
    # Plotting
    plt.plot(x_extended, y_extended, '--', label='Linear approximation of AI(f)')
    plt.plot(n_vals, vals, 'o', label=f"AI(f), g = {g_description}")
    plt.plot(x_extended, [x//3 for x in x_extended], label="y = n/3")
    
    plt.grid()
    plt.legend(prop={'size': 20})
    plt.xlabel("n", fontsize=20)
    plt.ylabel("AI", fontsize=20)
    plt.title("Algebraic Immunity Analysis", fontsize=24)
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

def main():
    # Define the Boolean functions
    g_t = [[0], [1, 2]]  # x0 + x1x2
    #g_u = [[0]] + [[2*i-1, 2*i] for i in range(1, 1 + (n)//2)]

    # Known values
    vals_t = [2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7]
    n_vals_t = range(4, len(vals_t) + 4)
    
    vals_u = [2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7]
    n_vals_u = range(4, len(vals_u) + 4)

    print("This program plots the Algebraic Immunity for Boolean functions.")
    print("1. Plot known values for f with g = x0 + x1x2")
    print("2. Plot known values for f with g = x0 + x1x2 + x3x4 + x5x6 + ... + xn/2xn/2+1")
    print("3. Calculate and plot new values for g = x0 + x1x2")
    
    choice = input("Enter your choice (1, 2, or 3): ")

    if choice == '1':
        plot_algebraic_immunity(n_vals_t, vals_t, "x0 + x1x2 (known values)")
    elif choice == '2':
        plot_algebraic_immunity(n_vals_u, vals_u, "x0 + sum(x(2i)x(2i+1)) (known values)")
    elif choice == '3':
        n_vals = get_user_input()
        print("Calculating Algebraic Immunity...")
        vals = [calculate_algebraic_immunity(n, g_t) for n in n_vals]
        print("Algebraic Immunity values:", vals)
        print("Coefficients of linear approximation:", np.polyfit(n_vals, vals, 1))
        plot_algebraic_immunity(n_vals, vals, "x0 + x1x2 (calculated)")
    else:
        print("Invalid choice. Please run the program again and select 1, 2, or 3.")
    
if __name__ == "__main__":
    main()

