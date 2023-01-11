# Shared Multi Depot Vehicle Routing Problem
## Installation (source)
> Cette installation est uniquement pour Windows. Elle devrait fonctionner sur les distros Linux avec l'installation
> appropriée des dépendances (Boost et Python).

### Boost
Pour Windows, téléchargez la version 1.80.0 de Boost [ici](https://www.boost.org/users/history/version_1_80_0.html). Extrayez l'archive et copiez le dossier dans `C:\Program Files\boost_1_80_0`.

### Python (optionnel)
Si vous devez exécuter les scripts Python présents dans le dossier `scripts`, vous aurez besoin de Python 3.10 qui
peut être téléchargé [ici](https://www.python.org/downloads/release/python-3109/).

Lorsque toutes les dépendances sont installées, vous pouvez construire le projet avec CMake.

## Utilisation
Avant de lancer le .exe, vous devez avoir un fichier `params.json` dans le même répertoire que le .exe. 
Ce fichier stocke la configuration de l'AG telle que la taille de la population ou le nombre de générations.
Un exemple de ce fichier peut être trouvé dans le fichier `params.json` à la racine du projet.

> **population**: Taille de la population, l'AG restera à cette taille pour toute la durée de l'exécution
> 
> **generation_max**: Nombre de générations
>
> **crossover_rate**: Probabilité d'appliquer un croisement
> 
> **mutation_rate**:  Probabilité d'appliquer une mutation


## English version
## Installation (source)
> This installation is only for Windows. It should work on Linux distros with the appropriate installation
> of the dependencies (Boost and Python).
### Boost
For Windows, download the version 1.80.0 of Boost from [here](https://www.boost.org/users/history/version_1_80_0.html). Extract the archive and copy the folder to `C:\Program Files\boost_1_80_0`.

### Python (optional)
If you need to run the Python scripts can be found in the `scripts` directory, you will need Python 3.10 which
can be downloaded [here](https://www.python.org/downloads/release/python-3109/).

When all the dependencies are installed, you can build the project with CMake.

## Usage
Before launching the .exe, you need a `params.json` file in the same directory as the .exe. 
This file stores the configuration for the GA such as the number of generation or the population size.
An example of this file can be found in the `params.json` file in the root directory.
>
> **population**: Population size, the GA will stay at this population size for the whole run
> 
> **generation_max**: Number of generations
>
> **crossover_rate**: Probability of applying a cross-over
> 
> **mutation_rate**:  Probability of applying a mutation

