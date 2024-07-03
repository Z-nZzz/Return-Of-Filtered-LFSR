class LFSR:
    def __init__(self, key, poly):
        self._s = key
        self._p = poly

    def _sum(self, L):
        s = 0
        for x in L:
            s = s ^ x
        return s

    def _clock(self):
        b = self._s[-1]
        self._s = [self._sum(self._s[p] for p in self._p)] + self._s[:-1]
        return b

    def bit(self):
        return self._clock()
