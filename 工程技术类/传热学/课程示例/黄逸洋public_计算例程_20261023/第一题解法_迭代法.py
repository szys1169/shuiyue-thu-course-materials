import numpy as np

lamda = 45
deta_x = deta_y = 0.08
h = 40
tf = 25
q = 1500
t11 = t12 = t13 = t14 = t21 = t22 = t23 = t24 = t31 = t32 = t33 = t34 = t41 = t42 = t43 = t44 = t51 = t52 = t53 = t54 = t61 = t62 = t63 = t64 = 200
t0 = 150

for i in range(1000000):
    t11 = 200
    t12 = 200
    t13 = 200
    t14 = 200
    t21 = 0.25 * t11 + 0.5 * t22 + 0.25 * t31
    t22 = 0.25 * (t12 + t21 + t23 + t32)
    t23 = 0.25 * (t13 + t22 + t24 + t33)
    t24 = (lamda * (t14 + t34 + 2 * t23) + 2 * h * deta_y * tf) / (4 * lamda + 2 * h * deta_y)
    t31 = 0.25 * t21 + 0.5 * t32 + 0.25 * t41
    t32 = 0.25 * (t22 + t31 + t33 + t42)
    t33 = 0.25 * (t23 + t32 + t34 + t43)
    t34 = (lamda * (t24 + t44 + 2 * t33) + 2 * h * deta_y * tf) / (4 * lamda + 2 * h * deta_y)
    t41 = 0.25 * t31 + 0.5 * t42 + 0.25 * t51
    t42 = 0.25 * (t32 + t41 + t43 + t52)
    t43 = 0.25 * (t33 + t42 + t44 + t53)
    t44 = (lamda * (t34 + t54 + 2 * t43) + 2 * h * deta_y * tf) / (4 * lamda + 2 * h * deta_y)
    t51 = 0.25 * t41 + 0.5 * t52 + 0.25 * t61
    t52 = 0.25 * (t42 + t51 + t53 + t62)
    t53 = 0.25 * (t43 + t52 + t54 + t63)
    t54 = (lamda * (t44 + t64 + 2 * t53) + 2 * h * deta_y * tf) / (4 * lamda + 2 * h * deta_y)
    t61 = (deta_y * q + lamda * (t51 + t62)) / (2 * lamda)
    t62 = (lamda * (t61 + t63 + 2 * t52) + 2 * q * deta_x) / (4 * lamda)
    t63 = (lamda * (t62 + t64 + 2 * t53) + 2 * q * deta_x) / (4 * lamda)
    t64 = (lamda * (t54 + t63) + h * deta_y * tf + q * deta_x) / (h * deta_y + 2 * lamda)
    e = abs(t64 - t0) / t0 
    if e > 0.00001:
        t0 = t64
    else:
        print("迭代次数：", i)
        break

print(t11, t12, t13, t14)
print(t21, t22, t23, t24)
print(t31, t32, t33, t34)
print(t41, t42, t43, t44)
print(t51, t52, t53, t54)
print(t61, t62, t63, t64)
