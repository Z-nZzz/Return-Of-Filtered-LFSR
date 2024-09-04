from LFSR import LFSR

'''
Cyclic Weightwise degree d Boolean function for Filter generators

:param key: the initial state of the LFSR, 
:param P: the feedback polynomial of the LFSR, 
:param g: the base function of our filter with a structure of a list of monomial for instance g(x) = x1 + x2x3 would give g = [[1], [2, 3]]
:param n: the number of variables of our filter function, 
:param t: the position in the LFSR where the input variables of the filter are taken, 

'''

class Filter:
    def __init__(self, key, N, P, g, n, debug = 0):
        self.LFSR = LFSR(key, P)
        self.debug = debug
        self.N = N
        self.g = g
        self.n = n
        t = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021]
        tmp = [0]
        s = 0
        count = 0
        index = 0
        while count < n:
            x = (s + t[index]) % N
            if x not in tmp:
                count += 1
                tmp += [x]
            s += t[index]
            index += 1
        self.t = tmp
        assert len(tmp) == n
        #print(tmp)

    def bit(self):
        state = [self.LFSR._s[i%self.N] for i in self.t]
        if self.debug:
            print("LFSR state: ",self.LFSR._s)
            print("input: ",state)
        #hamming weight
        hw = sum(state)
        b = 0
        for monomial in self.g:
            tmp = 1
            for i in monomial:
                j = (i + hw - 1) % self.n
                tmp *= state[j]
            b ^=tmp 
        self.LFSR.bit()
        if self.debug:
            print(b)
        return b

    def bytes(self):
        byte = 0
        for i in range(8):
            bit = self.bit()
            byte += int(bit)*2**(7-i)
        return byte.to_bytes(length = 1,byteorder='big')

