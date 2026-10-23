N = 50
dt = 0.0001
lamda = 0.156
q = 500
a = 0.000008
l = 0.019
dx = l / N
Fo = a * dt / (dx * dx)
to = 20

T = {}
T1 = {}
for i in range(N + 1):
    T[i] = 20
    T1[i] = 20
for m in range(100000000000):
    T = T1
    for j in range(N + 1):
        if j == 0:
            T1[j] = T[j] + 2 * Fo * (T[j + 1] - T[j] + q * dx / lamda)
        elif j == N:
            T1[j] = T[j] + 2 * Fo * (T[j - 1] - T[j])
        else:
            T1[j] = T[j] + Fo * (T[j - 1] + T[j + 1] - 2 * T[j])
    t = m * dt
    if T1[N] >= 150:
        print("T=", t, "s")
        print(T1)
        break
