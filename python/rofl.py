import time
import random
from Filter import Filter

def get_primitive_polynomial(lfsr_length_N):
    polynomials = {
        2048: [0, 12, 13, 18, 2047],
        1024: [5, 18, 1023],
        512: [1, 4, 7, 511]
    }
    return polynomials.get(lfsr_length_N)

def generate_quadratic_function(variables_n, function_type):
    if function_type == 'u':
        return [[0]] + [[2*i-1, 2*i] for i in range(1, 1 + (variables_n-1)//2)]
    elif function_type == 't':
        return [[0], [1, 2]]

def speed_assessment_mode(variables_n, keystream_length_l):
    for lfsr_length_N in [512, 1024, 2048]:
        print(f"\nTesting for N = {lfsr_length_N}")
        
        initial_state_key = [random.getrandbits(1) for _ in range(lfsr_length_N)]
        feedback_polynomial_P = get_primitive_polynomial(lfsr_length_N)
        
        if not feedback_polynomial_P:
            print("Invalid N value. Please use 512, 1024, or 2048.")
            continue

        quadratic_functions_lg = [
            generate_quadratic_function(variables_n, 'u'),
            generate_quadratic_function(variables_n, 't')
        ]

        for base_function_g in quadratic_functions_lg:
            filter_generator_G = Filter(initial_state_key, lfsr_length_N, feedback_polynomial_P, base_function_g, variables_n)
            
            start_time = time.time()
            keystream = [filter_generator_G.generate_bit() for _ in range(keystream_length_l * 8)]
            end_time = time.time()

            execution_time = end_time - start_time
            print(f"Function type: {'u' if len(base_function_g) > 2 else 't'}")
            print(f"Execution time: {execution_time:.4f} seconds")

def user_chosen_mode(variables_n, lfsr_length_N, keystream_length_l):
    initial_state_key = [random.getrandbits(1) for _ in range(lfsr_length_N)]
    feedback_polynomial_P = get_primitive_polynomial(lfsr_length_N)
    
    if not feedback_polynomial_P:
        print("Invalid N value. Please use 512, 1024, or 2048.")
        return

    quadratic_functions_lg = [
        generate_quadratic_function(variables_n, 'u'),
        generate_quadratic_function(variables_n, 't')
    ]

    for base_function_g in quadratic_functions_lg:
        filter_generator_G = Filter(initial_state_key, lfsr_length_N, feedback_polynomial_P, base_function_g, variables_n)
        
        print(f"\nFunction type: {'u' if len(base_function_g) > 2 else 't'}")
        keystream = [filter_generator_G.generate_bit() for _ in range(keystream_length_l * 8)]
        print(f"Generated keystream (first 64 bits): {''.join(map(str, keystream[:64]))}")

def main():
    mode = input("Choose mode (1 for speed assessment, 2 for user-chosen N): ")
    variables_n = int(input("Enter n (number of variables): "))
    keystream_length_l = int(input("Enter the length of the keystream to generate in bytes: "))

    if mode == '1':
        speed_assessment_mode(variables_n, keystream_length_l)
    elif mode == '2':
        lfsr_length_N = int(input("Enter N (LFSR length, choose 512, 1024, or 2048): "))
        user_chosen_mode(variables_n, lfsr_length_N, keystream_length_l)
    else:
        print("Invalid mode selected. Please choose 1 or 2.")

if __name__ == "__main__":
    main()

