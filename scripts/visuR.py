import matplotlib.pyplot as plt

x = [67,16,21,75,35]
y = [62,55,92,18,60]

plt.scatter(x, y, c='black', label='Producteurs', marker="^", s=100)

x = [24,46,72,51,65,54,34,41,52,91]
y = [23,5,28,14,26,82,80,58,49,54]

plt.scatter(x, y, c='grey', label='Clients', s=100)


plt.xlim([0, 100])
plt.ylim([0, 100])

plt.legend(loc='lower left', fontsize=12)

plt.title('Instance de type R', fontsize=20)
plt.xlabel('x', fontsize=14)
plt.ylabel('y', fontsize=14)
plt.tick_params(axis='both', which='major', labelsize=14)
plt.savefig('figR.png')
plt.show()
