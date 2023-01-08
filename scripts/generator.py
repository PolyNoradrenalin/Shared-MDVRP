# generateur de fichier d'instance
# permet de generer 30 instances d'un couple (p,c) de producteurs et de clients pour chacuns des
# quatre types que nous utiliserons (3*40=120 instances par couple)
# type 1 : placement des producteurs au centre de la zone etudiee
# type 2 : placement des clients au centre de la zone etudiee
# type 3 : placement des producteurs a gauche et a droite des clients, qui se retrouvent au centre de la zone
# type R : placement aleatoire de tous les acteurs
# type A : temps de trajets en fonction de la distance, equivalent dans les deux sens
# type B : temps de trajets en fonction de la distance, variation dépendant du sens
# type C : temps de trajets en fonction de la distance avec une variation forcée
import os
import random
from random import randint

import numpy as np

#######################################################################################

nom_fichier = ""
path = "../instances/"
os.makedirs(path, exist_ok=True)

#######################################################################################

def T1(file, nombre_prod, nombre_client):
    # rempli la matrice de distance
    coord = [[] for l in range(nombre_prod + nombre_client)]
    for l in range(0, nombre_prod):
        x, y = randint(25, 75), randint(25, 75)
        coord[l].append(x)
        coord[l].append(y)
    for l in range(nombre_prod, nombre_prod + nombre_client):
        pos = True
        while pos:
            x, y = randint(0, 100), randint(0, 100)
            if 25 <= x <= 75 and 25 <= y <= 75:
                pos = True
            else:
                pos = False
        coord[l].append(x)
        coord[l].append(y)

    for j in range(0, nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range(0, nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b)
            distance = round(distance)
            file.write(str(distance) + " ")
        file.write("\n")
    for n in range(0, nombre_prod + nombre_client):
        file.write(str(coord[n][0]) + " ")
        file.write(str(coord[n][1]) + "\n")
    return coord

def T2(file, nombre_prod, nombre_client):
    # rempli la matrice de distance
    coord = [[] for l in range(nombre_prod + nombre_client)]
    for l in range(0, nombre_prod):
        pos = True
        while pos:
            x, y = randint(0, 100), randint(0, 100)
            if 25 <= x <= 75 and 25 <= y <= 75:
                pos = True
            else:
                pos = False
        coord[l].append(x)
        coord[l].append(y)
    for l in range(nombre_prod, nombre_prod + nombre_client):
        x, y = randint(25, 75), randint(25, 75)
        coord[l].append(x)
        coord[l].append(y)

    for j in range(0, nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range(0, nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b)
            distance = round(distance)
            file.write(str(distance) + " ")
        file.write("\n")
    for n in range(0, nombre_prod + nombre_client):
        file.write(str(coord[n][0]) + " ")
        file.write(str(coord[n][1]) + "\n")
    return coord

def T3(file, nombre_prod, nombre_client):
    # rempli la matrice de distance
    coord = [[] for l in range(nombre_prod + nombre_client)]
    for l in range(0, nombre_prod):
        bool = randint(0, 1)
        if bool == 0:
            x, y = randint(0, 25), randint(0, 100)
        else:
            x, y = randint(75, 100), randint(0, 100)
        coord[l].append(x)
        coord[l].append(y)
    for l in range(nombre_prod, nombre_prod + nombre_client):
        x, y = randint(25, 75), randint(0, 100)
        coord[l].append(x)
        coord[l].append(y)

    for j in range(0, nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range(0, nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b)
            distance = round(distance)
            file.write(str(distance) + " ")
        file.write("\n")
    for n in range(0, nombre_prod + nombre_client):
        file.write(str(coord[n][0]) + " ")
        file.write(str(coord[n][1]) + "\n")
    return coord

def TR(file, nombre_prod, nombre_client):
    # rempli la matrice de distance
    coord = [[] for l in range(nombre_prod + nombre_client)]
    for l in range(0, nombre_prod):
        x, y = randint(0, 100), randint(0, 100)
        coord[l].append(x)
        coord[l].append(y)
    for l in range(nombre_prod, nombre_prod + nombre_client):
        x, y = randint(0, 100), randint(0, 100)
        coord[l].append(x)
        coord[l].append(y)

    for j in range(0, nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range(0, nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b)
            distance = round(distance)
            file.write(str(distance) + " ")
        file.write("\n")
    for n in range(0, nombre_prod + nombre_client):
        file.write(str(coord[n][0]) + " ")
        file.write(str(coord[n][1]) + "\n")
    return coord

def TA(file, coord, nombre_prod, nombre_client):
    for j in range(0, nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range(0, nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b)
            distance = round(distance)
            travelTime = distance / 2
            file.write(str(round(travelTime)) + " ")
        file.write("\n")

def TB(file, coord, nombre_prod, nombre_client):
    for j in range(0, nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range(0, nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b)
            distance = round(distance)
            if j > k:
                travelTime = (random.random() + 0.5) * distance / 2
            else:
                travelTime = distance / 2
            file.write(str(round(travelTime)) + " ")
        file.write("\n")

def TC(file, coord, nombre_prod, nombre_client):
    for j in range(0, nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range(0, nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b)
            distance = round(distance)
            travelTime = (random.random() + 0.5) * distance / 2
            file.write(str(round(travelTime)) + " ")
        file.write("\n")

distTypes = [T1, T2, T3, TR]
travelTimeTypes = [TA, TB, TC]

def get_file_name(index: int, distanceType: str, travelTimeType: str, nombre_prod, nombre_client):
    fName = "I_"
    if len(str(nombre_prod)) < 2:
        fName += "0" + str(nombre_prod) + "_"
    else:
        fName += str(nombre_prod) + "_"
    if len(str(nombre_client)) < 2:
        fName += "0" + str(nombre_client) + f"_{distanceType}-{travelTimeType}_"
    else:
        fName += str(nombre_client) + f"_{distanceType}-{travelTimeType}_"
    fName += str(index) + ".txt"

    return fName

sizes = [(3, 5), (5, 10), (8, 15)]
def generate_instances(instance_count: int):
    for i in range(4):
        for j in range(3):
            for (nombre_prod, nombre_client) in sizes:
                for instance_index in range(instance_count):
                    fileName = get_file_name(instance_index, distTypes[i].__name__, travelTimeTypes[j].__name__, nombre_prod, nombre_client)

                    # creer le fichier dans le repertoire data
                    f = open(path + fileName, "w")
                    f.write(str(nombre_prod) + "\n")
                    f.write(str(nombre_client) + "\n")

                    coords = distTypes[i](f, nombre_prod, nombre_client)
                    travelTimeTypes[j](f, coords, nombre_prod, nombre_client)

                    f.close()

generate_instances(10)
