import matplotlib.pyplot as plt

x = [89,7,83,80,19]
y = [84,32,53,18,60]

plt.scatter(x, y, c='black', label='Producteurs', marker="^", s=100)

x = [27,42,54,72,48,50,62,54,33,39]
y = [50,42,84,70,67,15,29,48,87,30]

plt.scatter(x, y, c='grey', label='Clients', s=100)

a = [25,25]
b = [0,100]
plt.plot(a,b,'--', c="black",linewidth=1.5)
a = [75,75]
b = [0,100]
plt.plot(a,b,'--', c="black",linewidth=1.5)

plt.xlim([0, 100])
plt.ylim([0, 100])

plt.legend(loc='lower left', fontsize=12)

plt.title("Instance de type 3 : Producteurs de part et d'autre des clients", fontsize=20)
plt.xlabel('x', fontsize=14)
plt.ylabel('y', fontsize=14)
plt.tick_params(axis='both', which='major', labelsize=14)
plt.savefig('fig3.png')
plt.show()