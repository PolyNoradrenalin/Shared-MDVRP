import os

import numpy as np
import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt

directory = "..\\solutions"
fitness_best_solGA = {}
fitness_best_solSimple = []

for filename in os.listdir(directory):
    f = os.path.join(directory, filename)
    instance = filename.split('.')[0]
    if instance not in fitness_best_solGA.keys():
        fitness_best_solGA[instance] = []
    with open(f, 'r') as file:
        if "simpleSolution" in filename:
            fitness_best_solSimple.append(int(file.readlines()[-1]))
            continue
        fitness_best_solGA[instance].append(int(file.readlines()[-1]))

instance_keys = {
    "I_03_05_T1-TA_0": "p=3, c=5, p centre",
    "I_03_05_T2-TA_0": "p=3, c=5, c centre",
    "I_03_05_TR-TA_0": "p=3, c=5, aléatoire",
    "I_05_10_T1-TA_0": "p=5, c=10, p centre",
    "I_05_10_T2-TA_0": "p=5, c=10, c centre",
    "I_05_10_TR-TA_0": "p=5, c=10, aléatoire",
    "I_08_15_T1-TA_0": "p=8, c=15, p centre",
    "I_08_15_T2-TA_0": "p=8, c=15, c centre",
    "I_08_15_TR-TA_0": "p=8, c=15, aléatoire",
}

def findInstanceName(iKey):
    for k in instance_keys:
        if k in iKey:
            return instance_keys[k]

def getInstancesWithName(name, instances):
    return [instances[i] for i in instances.keys() if name in i]

data_preproc = pd.DataFrame({})

for key in fitness_best_solGA.keys():
    data_preproc[findInstanceName(key)] = fitness_best_solGA[key]

print(data_preproc.agg([min]).values.ravel())
print(fitness_best_solSimple)

sns.set_theme(style="whitegrid")
sns_plot = sns.lineplot(data=data_preproc, dashes=False)
plt.xlabel("Generation number")
plt.ylabel("Best individual's fitness")
fig = sns_plot.get_figure()
fig.savefig('ga_evolution.png')

instTypeList = ['T1', 'T2', 'TR']
for i in range(len(instTypeList)):
    instList = np.concatenate(
        (list(getInstancesWithName(instTypeList[i], instance_keys)), list(getInstancesWithName(instTypeList[i], instance_keys))))
    fitList = np.concatenate((data_preproc[data_preproc.columns[i::len(instTypeList)]].agg([min]).values.ravel(),
                              np.ravel(fitness_best_solSimple[i::len(instTypeList)])))
    typeList = ["GA" if i < len(instTypeList) else "SimpleSolution" for i in
                range(len(instTypeList) * 2)]
    barData = pd.DataFrame({"Instance": instList,
                            "Fitness": fitList,
                            "Type": typeList})

    plt.clf()
    plt.title(instTypeList[i])
    sns_barplot = sns.barplot(x="Instance", y="Fitness", hue="Type", data=barData)
    fig2 = sns_barplot.get_figure()
    fig2.savefig(f'{instTypeList[i]}-hist.png')
