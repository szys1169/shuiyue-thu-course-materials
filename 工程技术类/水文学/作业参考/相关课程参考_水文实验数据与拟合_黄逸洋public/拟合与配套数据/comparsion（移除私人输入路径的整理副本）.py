# coding: utf-8
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

with open("VSA_sum.csv") as file: #enter the absolute path of your csv file
    dataframe = pd.read_csv(file)
    vsa_vn = np.array(dataframe["volume content of soil(n)"])
    vsa_vn_clean = np.array([100*i for i in vsa_vn if str(i)!= "nan"]) # drop nan 
    vsa_vn_135 = vsa_vn_clean*1.35
    vsa_vn_145 = vsa_vn_clean*1.45
    vsa_sn = np.array(dataframe["soil water potential(n)"])
    vsa_sn_clean = np.array([-1000*i for i in vsa_sn if str(i)!= "nan"])

    vsa_vs = np.array(dataframe["volume content of soil(s)"])
    vsa_vs_clean = np.array([100*i for i in vsa_vs if str(i)!= "nan"]) 
    vsa_vs_135 = vsa_vs_clean*1.35
    vsa_vs_145 = vsa_vs_clean*1.45
    vsa_ss = np.array(dataframe["soil water potential(s)"])
    vsa_ss_clean = np.array([1000*i for i in vsa_ss if str(i)!= "nan"])


with open("自动数据_sum.csv") as file:
    dataframe = pd.read_csv(file)
    auto_vs_145 = np.array(dataframe["volume content of soil(1)"])
    auto_vs_145_clean = np.array([100 * i for i in auto_vs_145 if str(i) != "nan"]) 
    auto_ss_145 = np.array(dataframe["soil water potential(1)"])
    auto_ss_145_clean = np.array([-i for i in auto_ss_145 if str(i) != "nan"])

    auto_vn_145 = np.array(dataframe["volume content of soil(2)"])
    auto_vn_145_clean = np.array([100 * i for i in auto_vn_145 if str(i) != "nan"])  
    auto_sn_145 = np.array(dataframe["soil water potential(2)"])
    auto_sn_145_clean = np.array([-i for i in auto_sn_145 if str(i) != "nan"])

    auto_vs_135 = np.array(dataframe["volume content of soil(3)"])
    auto_vs_135_clean = np.array([100 * i for i in auto_vs_135 if str(i) != "nan"])  
    auto_ss_135 = np.array(dataframe["soil water potential(3)"])
    auto_ss_135_clean = np.array([-i for i in auto_ss_135 if str(i) != "nan"])

    auto_vn_135 = np.array(dataframe["volume content of soil(4)"])
    auto_vn_135_clean = np.array([100 * i for i in auto_vn_135 if str(i) != "nan"])  
    auto_sn_135 = np.array(dataframe["soil water potential(4)"])
    auto_sn_135_clean = np.array([-i for i in auto_sn_135 if str(i) != "nan"])


with open("张力计_sum.csv") as file:
    dataframe = pd.read_csv(file)
    tens_vs_145 = np.array(dataframe["volume content of soil(1-3)"])
    tens_vs_145_clean = np.array([100 * i for i in tens_vs_145 if str(i) != "nan"])  
    tens_ss_145 = np.array(dataframe["attraction(1-3)/cm"])
    tens_ss_145_clean = np.array([1000 * 9.8 * i / 100 / 1000 for i in tens_ss_145 if str(i) != "nan"])

    tens_vn_145 = np.array(dataframe["volume content of soil(2-3)"])
    tens_vn_145_clean = np.array([100 * i for i in tens_vn_145 if str(i) != "nan"])  
    tens_sn_145 = np.array(dataframe["attraction(2-3)/cm"])
    tens_sn_145_clean = np.array([1000 * 9.8 * i / 100 / 1000 for i in tens_sn_145 if str(i) != "nan"])

    tens_vs_135 = np.array(dataframe["volume content of soil(3-4)"])
    tens_vs_135_clean = np.array([100 * i for i in tens_vs_135 if str(i) != "nan"])  
    tens_ss_135 = np.array(dataframe["attraction(3-4)/cm"])
    tens_ss_135_clean = np.array([1000 * 9.8 * i / 100 / 1000 for i in tens_ss_135 if str(i) != "nan"])

    tens_vn_135 = np.array(dataframe["volume content of soil(4-2)"])
    tens_vn_135_clean = np.array([100 * i for i in tens_vn_135 if str(i) != "nan"]) 
    tens_sn_135 = np.array(dataframe["attraction(4-2)/cm"])
    tens_sn_135_clean = np.array([1000 * 9.8 * i / 100 / 1000 for i in tens_sn_135 if str(i) != "nan"])


with open("WP4C_sum.csv") as file:
    dataframe = pd.read_csv(file)
    wp4c_vs_145 = np.array(dataframe["volume content of soil(1-7)"])
    wp4c_vs_145_clean = np.array([100*i for i in wp4c_vs_145 if str(i)!= "nan"]) 
    wp4c_ss_145 = np.array(dataframe["soil water potential(1-7)"])
    wp4c_ss_145_clean = np.array([-1000*i for i in wp4c_ss_145 if str(i)!= "nan"])

    wp4c_vn_145 = np.array(dataframe["volume content of soil(2-7)"])
    wp4c_vn_145_clean = np.array([100*i for i in wp4c_vn_145 if str(i)!= "nan"]) 
    wp4c_sn_145 = np.array(dataframe["soil water potential(2-7)"])
    wp4c_sn_145_clean = np.array([-1000*i for i in wp4c_sn_145 if str(i)!= "nan"])

    wp4c_vs_135 = np.array(dataframe["volume content of soil(3-7)"])
    wp4c_vs_135_clean = np.array([100*i for i in wp4c_vs_135 if str(i)!= "nan"]) 
    wp4c_ss_135 = np.array(dataframe["soil water potential(3-7)"])
    wp4c_ss_135_clean = np.array([-1000*i for i in wp4c_ss_135 if str(i)!= "nan"])

    wp4c_vn_135 = np.array(dataframe["volume content of soil(4-7)"])
    wp4c_vn_135_clean = np.array([100*i for i in wp4c_vn_135 if str(i)!= "nan"]) 
    wp4c_sn_135 = np.array(dataframe["soil water potential(4-7)"])
    wp4c_sn_135_clean = np.array([-1000*i for i in wp4c_sn_135 if str(i)!= "nan"])


plt.rcParams['font.sans-serif'] = ['SimHei']
plt.xlim([0, max(vsa_vn_145.max(), auto_vn_145_clean.max(), tens_vn_145_clean.max(), wp4c_vn_145_clean.max())*1.1])
plt.semilogy(vsa_vn_145, vsa_sn_clean, "r", label="VSA",linewidth=0.75)
plt.semilogy(auto_vn_145_clean, auto_sn_145_clean, "b", label="自动", linewidth=0.75)
plt.semilogy(tens_vn_145_clean, tens_sn_145_clean, "m", label="张力计", linewidth=0.75)
plt.semilogy(wp4c_vn_145_clean, wp4c_sn_145_clean, "k", label="WP4C", linewidth=0.75)

plt.xlabel("土壤含水率"+"$ \\theta$"+"/%")
plt.ylabel("土壤吸力"+"S/KPa")
plt.legend()
plt.show()





