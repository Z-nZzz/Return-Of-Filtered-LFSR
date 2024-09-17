class LFSR:
    def __init__(self, initial_state, polynomial):
        """
        Initialize the Linear Feedback Shift Register.
        
        Args:
            initial_state (list): The initial state of the LFSR.
            polynomial (list): The polynomial coefficients for feedback.
        """
        self._state = initial_state
        self._polynomial = polynomial

    def _xor_sum(self, bits):
        """
        Compute the XOR sum of given bits.
        
        Args:
            bits (list): List of bits to XOR.
        
        Returns:
            int: The XOR sum (0 or 1).
        """
        return sum(bits) % 2

    def _clock(self):
        """
        Perform one clock cycle of the LFSR.
        
        Returns:
            int: The output bit.
        """
        output_bit = self._state[-1]
        feedback = self._xor_sum(self._state[p] for p in self._polynomial)
        self._state = [feedback] + self._state[:-1]
        return output_bit

    def generate_bit(self):
        """
        Generate and return the next output bit.
        
        Returns:
            int: The next output bit.
        """
        return self._clock()
