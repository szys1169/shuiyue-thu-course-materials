# coding:utf-8
import numpy as np
from matplotlib import pyplot
from scipy import optimize
import scipy

I = [2190,2600,2420,2670,3709,
     4790,5070,4540,3620,2790,
     1920,1440,1110,1030,1030,
     1030,1030]
O = [740,880,1870,2510,2670,
     3090,3990,4590,4660,4620,
     3700,3830,2450,1900,1260,
     1260,1140]

I1= []
for i in range(0,17):
     I1.append(I[i]+I[i]/44579*2821)

dS = []
for i in range(0,16):
     dS.append(0.5*(I1[i]+I1[i+1])-0.5*(O[i]+O[i+1]))

S = [0]
for i in range(0,16):
     S.append(S[i]+dS[i])

def r(x):
     Q2 = []
     for i in range(0,17):
          Q2.append(x*I1[i]+(1-x)*O[i])
     beta1 = np.cov(S,Q2)[0,1]/np.cov(S,S)[0,0]
     beta0 = sum(Q2)/17- beta1*sum(S)/17
     SSE = 0
     SST = 0
     for i in range(0,17):
          SSE += (beta1*S[i]+beta0-sum(Q2)/17)*(beta1*S[i]+beta0-sum(Q2)/17)
     for i in range(0,17):
          SST += (Q2[i]-sum(Q2)/17)*(Q2[i]--sum(Q2)/17)
     return -SSE/SST

x = optimize.minimize_scalar(r).x

Q2 = []
for i in range(0,17):
     Q2.append(x*I1[i]+(1-x)*O[i])

K = np.cov(S,Q2)[0,1]/np.cov(Q2,Q2)[0,0]
b = sum(S)/17- K*sum(Q2)/17

C0 = (0.5-K*x)/(K-K*x+0.5)
C1 = (0.5+K*x)/(K-K*x+0.5)
C2 = (K-K*x-0.5)/(K-K*x+0.5)

print(K,C0,C1,C2)


# 从I1[1]:13日10时开始计算，截止至I1[16]：14日1时
O2 = []
for i in range(0,16):
     O2.append(C0*I1[i+1]+C1*I1[i]+C2*O[i])

x = np.linspace(1000,5000,10)
SS = K*x+b

pyplot.scatter(Q2,S,color='r',s=1)
pyplot.plot(x,SS,color='b',linewidth=0.5)
pyplot.xlabel("$Q' /(m^3\cdot s^{-1})$")
pyplot.ylabel(" $S /(m^3\cdot s^{-1}\cdot h)$")
pyplot.annotate("S=2.4287Q'-2920.3",xy=(1000,8000),xytext=(1000,8000))
pyplot.annotate("$R^2=0.97466$",xy=(1000,7500),xytext=(1000,7500))
pyplot.show()


'''
t = np.linspace(10,25,16)

pyplot.scatter(t,O[1:17],color='r',s=1,label='observed')
pyplot.scatter(t,O2,color='b',s=1)
pyplot.plot(t,O2,color='b',linewidth=0.5,label='Muskingum Method')
pyplot.xlabel("$t/h$")
pyplot.ylabel(" $Q /(m^3\cdot s^{-1})$")

pyplot.legend()
pyplot.show()
'''
