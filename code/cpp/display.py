import dnest4.classic as dn4
import numpy as np
import matplotlib.pyplot as plt

data = dn4.my_loadtxt("toy_data.txt")
posterior_sample = dn4.my_loadtxt("posterior_sample.txt")

plt.errorbar(data[:,0], data[:,1], yerr=data[:,2], fmt="ko")
plt.hold(True)

# Overplot first 50 posterior samples
num = min([50, posterior_sample.shape[0]])
for i in range(0, num):
    plt.plot(data[:,0], posterior_sample[i, 0:data.shape[0]], "g",\
                    alpha=0.1)
plt.show()

# Posterior for N
N = posterior_sample[:,107]
bins = np.arange(0, 101)
width = 0.3
plt.hist(N, bins=bins-0.5*width, width=width, color="k", alpha=0.2)
plt.xlim([-0.5, 100.5])
plt.show()

