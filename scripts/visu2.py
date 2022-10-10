import matplotlib.pyplot as plt

x = [89,7,45,80,19]
y = [84,32,92,18,60]

plt.scatter(x, y, c='black', label='Producteurs', marker="^", s=100)

x = [27,42,54,72,61,50,62,54,33,39]
y = [50,42,64,70,60,32,29,48,67,30]

plt.scatter(x, y, c='grey', label='Clients', s=100)

a = [25,25]
b = [25,75]
plt.plot(a,b,'--', c="black",linewidth=1.5)
a = [75,75]
b = [25,75]
plt.plot(a,b,'--', c="black",linewidth=1.5)
b = [25,25]
a = [25,75]
plt.plot(a,b,'--', c="black",linewidth=1.5)
b = [75,75]
a = [25,75]
plt.plot(a,b,'--', c="black",linewidth=1.5)

plt.xlim([0, 100])
plt.ylim([0, 100])

plt.legend(loc='lower left', fontsize=12)

plt.title('Instance de type 2 : Clients centrés', fontsize=20)
plt.xlabel('x', fontsize=14)
plt.ylabel('y', fontsize=14)
plt.tick_params(axis='both', which='major', labelsize=14)
plt.savefig('fig2.png')
plt.show()