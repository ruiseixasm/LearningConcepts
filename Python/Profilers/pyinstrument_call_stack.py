from random import uniform

def estimate_pi(n):
    return 4 * sum(hits(point()) for _ in range(n)) / n


def hits(point):
    return abs(point) <= 1


def point():
    return complex(uniform(0, 1), uniform(0, 1))


for exponent in range(1, 8):
    n = 10 ** exponent
    estimates = [estimate_pi(n) for _ in range(5)]
    print(f"{n = :<10,} {estimates}")
    