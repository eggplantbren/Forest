import dnest4.classic as dn4
import matplotlib.pyplot as plt

data = dn4.my_loadtxt("toy_data.txt")
posterior_sample = dn4.my_loadtxt("posterior_sample.txt")

plt.errorbar(data[:,0], data[:,1], yerr=data[:,2], fmt="ko")
plt.hold(True)

# Overplot first 100 posterior samples
num = min([100, posterior_sample.shape[0]])
for i in range(0, num):
    plt.plot(data[:,0], posterior_sample[0, 0:data.shape[0]], "g",\
                    alpha=0.2)
plt.show()

