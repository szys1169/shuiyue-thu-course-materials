# coding: utf-8
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy import optimize

with open("张力计_sum.csv") as file:
    dataframe = pd.read_csv(file)
    #print(dataframe["volume content of soil(1)"])
    v1 = np.array(dataframe["volume content of soil(1-3)"])
    v1_clean = np.array([i for i in v1 if str(i)!= "nan"]) # drop nan in v_1
    s1 = np.array(dataframe["attraction(1-3)/cm"])
    s1_clean = np.array([-i for i in s1 if str(i)!= "nan"]) # in VG model, we express attraction in height


def vG_model(x, h):
    Theta_vG = np.power(1/(1+np.power(-x[2]* h, x[3])), 1-1/x[3]) # x[2]: \alpha, x[3]: n
    theta = (x[1]-x[0])*Theta_vG+x[0] # x[0]: \theta_r, x[1]:\theta_s
    return theta


def vG_model_fit(x):
    error = 0
    for i in range(0, v1_clean.shape[0]):
        Theta = (v1_clean[i]-x[0])/(x[1]-x[0]) # x[0]: \theta_r, x[1]:\theta_s
        Theta_vG = np.power(1/(1+np.power(-x[2]*s1_clean[i],x[3])), 1-1/x[3]) # x[2]: \alpha, x[3]: n
        error += (Theta_vG-Theta)*(Theta_vG-Theta)
    return error


cons = ({'type':'ineq','fun':lambda x: x[0]-0.001},
        {'type':'ineq','fun':lambda x: 1-x[0]},
        {'type':'ineq','fun':lambda x: x[1]-x[0]},
        {'type':'ineq','fun':lambda x: 1-x[1]},
        {'type':'ineq','fun':lambda x: x[2]},
        {'type':'ineq','fun':lambda x: x[3]},
       )

result = optimize.minimize(vG_model_fit, x0=np.array([0.07, 0.45, 0.01, 1]), constraints=cons)
para = result.x
print(para)
print(result)

h = np.linspace(0, 700, 1401)
vG_model_theta = np.array([vG_model(para, -i) for i in h])

plt.rcParams['font.sans-serif'] = ['SimHei']
plt.scatter(v1_clean, -s1_clean, c="r", marker="x", label="实验观测值")
plt.plot(vG_model_theta, h, "b-", label="VG模型拟合值")
plt.xlim([0.15, 0.5])
plt.ylim([0, 700])
plt.xlabel("土壤含水率"+"$\\theta$")
plt.ylabel("土壤吸力"+"S/cm")
plt.legend()
plt.show()
