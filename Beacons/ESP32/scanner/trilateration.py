import numpy as np

def trilaterate(p1, r1, p2, r2, p3, r3):
    P1 = np.array(p1)
    P2 = np.array(p2)
    P3 = np.array(p3)

    ex = (P2 - P1) / np.linalg.norm(P2 - P1)
    i = np.dot(ex, P3 - P1)
    ey = (P3 - P1 - i * ex) / np.linalg.norm(P3 - P1 - i * ex)
    d = np.linalg.norm(P2 - P1)
    j = np.dot(ey, P3 - P1)

    x = (r1**2 - r2**2 + d**2) / (2 * d)
    y = ((r1**2 - r3**2 + i**2 + j**2) / (2 * j)) - ((i / j) * x)

    final_position = P1 + x * ex + y * ey
    return final_position
