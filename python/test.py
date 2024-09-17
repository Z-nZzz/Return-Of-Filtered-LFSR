from LFSR import LFSR
from Filter import Filter


def test_keystream_generator():
    # Test parameters
    N = 8   # Very small LFSR length
    n = 3   # Small number of variables
    key = [1, 0, 1, 1, 0, 1, 0, 1]  # 8-bit initial state
    P = [1, 2, 7]  # Primitive polynomial x^8 + x^3 + x^2 + 1
    g = [[0], [1, 2]]  # Simple filter function of base g(x) = x0 + x1x2

    # Create Filter object
    filter_gen = Filter(key, N, P, g, n)

    # Generate a small keystream (e.g., 8 bits)
    keystream = [filter_gen.generate_bit() for _ in range(8)]

    # Expected output (verified manually)
    expected_keystream = [0, 0, 0, 0, 1, 0, 0, 1]

    # Print states for manual verification
    print("Initial state:", key)
    print("Generated keystream:", keystream)
    print("Expected keystream: ", expected_keystream)

    # Compare generated keystream with expected keystream
    if keystream == expected_keystream:
        print("Keystream generator test passed!")
    else:
        print("Keystream generator test failed.")


if __name__ == "__main__":
    test_keystream_generator()
















'''
l = int(input("Enter the length of the keystream:"))
N = 4
P = [1, 3]
key = [1, 0, 0, 1]
n = 3
u = [[0]]
for i in range(1, 1+ (n-1)//2):
    u += [[2*i-1, 2*i]]
t = [[0], [1, 2]]
'''
