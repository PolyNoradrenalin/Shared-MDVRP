import matplotlib.pyplot as plt

x = [42,55,66,47,29]
y = [65,50,59,34,47]

plt.scatter(x, y, c='black', label='Producteurs', marker="^", s=100)

x = [89,9,52,54,22,85,92,21,80,12]
y = [85,32,92,18,60,52,79,95,20,84]

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

plt.title('Instance de type 1 : Producteurs centrés', fontsize=20)
plt.xlabel('x', fontsize=14)
plt.ylabel('y', fontsize=14)
plt.tick_params(axis='both', which='major', labelsize=14)
plt.savefig('fig1.png')
plt.show()


