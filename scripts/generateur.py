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
from random import randint

import numpy as np

#######################################################################################

nombre_prod = 10
nombre_client = 50
nom_fichier = ""
path = "../instances/"
os.makedirs(path, exist_ok=True)

#######################################################################################

def T1(file):
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

def T2(file):
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

def T3(file):
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

def TR(file):
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

def TA(file):
    return

def TB(file):
    return

def TC(file):
    return

distTypes = [T1, T2, T3, TR]
travelTimeTypes = [TA, TB, TC]

def get_file_name(index: int, distanceType: str, travelTimeType: str):
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

def generate_instances(instance_count: int):
    for i in range(4):
        for j in range(3):
            for instance_index in range(instance_count):
                fileName = get_file_name(instance_index, distTypes[i].__name__, travelTimeTypes[j].__name__)

                # creer le fichier dans le repertoire data
                f = open(path + fileName, "w")
                f.write(str(nombre_prod) + "\n")
                f.write(str(nombre_client) + "\n")

                distTypes[i](f)
                travelTimeTypes[j](f)

                f.close()

generate_instances(10)
# genere 30 instances pour T1
'''
for i in range(0, 30):

    
    fichier.close()

#######################################################################################  

# genere 30 instances pour T2
for i in range(0, 30):

    
    fichier.close()

#######################################################################################  

# genere 30 instances pour T3
for i in range(0, 30):

    
    fichier.close()

#######################################################################################  

# genere 30 instances pour TR
for i in range(0, 30):


    
    fichier.close()'''
