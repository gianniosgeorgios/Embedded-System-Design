#!/usr/bin/python3

import sys
import time
from subprocess import check_output
import pandas as pd
import matplotlib.pyplot as plt

if __name__ == '__main__':
    iterations = 10

    phods=[]
    phods_v2=[]
    phods_v3=[]
    phods_v4=[]
    phods_v4_2d=[]

    for i in range(iterations):
      cmd = ['./' + "phods"]
      value = float(check_output(cmd).decode())
      phods.append(value)

      cmd = ['./' + "phods_v2"]
      value = float(check_output(cmd).decode())
      phods_v2.append(value)

      cmd = ['./' + "phods_v3"]
      value = float(check_output(cmd).decode())
      phods_v3.append(value)
  
      cmd = ['./' + "phods_v4"]
      value = float(check_output(cmd).decode())
      phods_v4.append(value)

      cmd = ['./' + "phods_v4_2d", str(144), str(8)]
      value = float(check_output(cmd).decode())
      phods_v4_2d.append(value)

    df = pd.DataFrame({'phods': phods, 'phods_v2': phods_v2, 'phods_v3': phods_v3, 'phods_v4': phods_v4, 'phods_v4_2d': phods_v4_2d})

    boxplot = df.boxplot(column=['phods', 'phods_v2', 'phods_v3', 'phods_v4', 'phods_v4_2d'])
    plt.title("Box plot")
    plt.xlabel("Versions")
    plt.ylabel("time(s)")
    plt.show()
