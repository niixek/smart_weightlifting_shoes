import matplotlib.pyplot as plt
import matplotlib as mpl
from datetime import datetime

mpl.rcParams['axes.prop_cycle'] = mpl.cycler(color=['r', 'b', 'y'])

times = []
s1_data = []
s2_data = []
s3_data = []

with open("footdata2.csv", 'r') as file:
    data = file.readlines()
    for i in data:
        temp = i.strip().split(",")
        times.append(datetime.strptime(temp[0], '%H:%M:%S.%f'))
        s1_data.append(float(temp[1]))      
        s2_data.append(float(temp[2]))   
        s3_data.append(float(temp[3]))   

accumulated_time = 0
times_to_plot = []
for i in range(len(times)-1):
    if (i == 0):
        times_to_plot.append(0)
    else:
        times_to_plot.append(accumulated_time + (times[i+1] - times[i]).total_seconds())
        accumulated_time += (times[i+1] - times[i]).total_seconds()


#plt.plot(times_to_plot, s1_data[:-1])
fig, (ax1, ax2, ax3) = plt.subplots(3, sharex=True, sharey = True)
ax1.plot(times_to_plot, s1_data[:-1])
ax2.plot(times_to_plot, s2_data[:-1])
ax3.plot(times_to_plot, s3_data[:-1])
ax2.set_ylabel("Sensor Reading")
ax3.set_xlabel("Seconds")
ax1.set_title("Sensor Readings vs. Seconds")

plt.show()