from LFSR import LFSR

class Filter:
    """
    Cyclic Weightwise degree d Boolean function for Filter generators

    Args:
        initial_state (list): The initial state of the LFSR.
        lfsr_length (int): Length of the LFSR.
        feedback_polynomial (list): The feedback polynomial of the LFSR.
        base_function (list): The base function of the filter, represented as a list of monomials.
                              E.g., g(x) = x0 + x1x2 would be [[0], [1, 2]].
        num_variables (int): The number of variables in the filter function.
        debug (bool, optional): Enable debug mode. Defaults to False.
    """

    def __init__(self, initial_state, lfsr_length, feedback_polynomial, base_function, num_variables, debug=False):
        self.LFSR = LFSR(initial_state, feedback_polynomial)
        self.debug = debug
        self.lfsr_length = lfsr_length
        self.base_function = base_function
        self.num_variables = num_variables
        
        self.taps = self._generate_taps()

    def _generate_taps(self):
        """Generate the taps sequence as the sum of primes modulo LFSR length."""
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021]
        taps = [0]
        sum_primes = 0
        count = 1
        index = 0
        while count < self.num_variables:
            tap = (sum_primes + primes[index]) % self.lfsr_length
            if tap not in taps:
                count += 1
                taps.append(tap)
            sum_primes += primes[index]
            index += 1
        taps.sort()
        assert len(taps) == self.num_variables
        return taps

    def generate_bit(self):
        """Generate and return the next output bit."""
        state = [self.LFSR._state[i % self.lfsr_length] for i in self.taps]
        
        if self.debug:
            print("LFSR state:", self.LFSR._state)
            print("Input:", state)
        
        hamming_weight = sum(state)
        output_bit = 0
        for monomial in self.base_function:
            term = 1
            for i in monomial:
                j = (i + hamming_weight - 1) % self.num_variables
                term *= state[j]
            output_bit ^= term
        
        self.LFSR.generate_bit()
        
        if self.debug:
            print("Output bit:", output_bit)
        
        return output_bit

    def generate_byte(self):
        """Generate and return the next output byte."""
        byte = 0
        for i in range(8):
            bit = self.generate_bit()
            byte += bit << (7 - i)
        return byte.to_bytes(length=1, byteorder='big')

