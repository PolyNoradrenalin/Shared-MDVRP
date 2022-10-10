from random import *
from tkinter import E
import numpy as np 

# generateur de fichier d'instance
# permet de generer 30 instances d'un couple (p,c) de producteurs et de clients pour chacuns des quatre types que nous utiliserons (3*40=120 instances par couple)
# type 1 : placement des producteurs au centre de la zone etudiee
# type 2 : placement des clients au centre de la zone etudiee
# type 3 : placement des producteurs a gauche et a droite des clients, qui se retrouvent au centre de la zone
# type R : placement aleatoire de tous les acteurs

# (3,7)  (5,10)  (5,20)  (10,20)  (10,50)  

#######################################################################################

nombre_prod = 10
nombre_client = 50
nom_fichier = ""
path = "c:/Users/hcroc/OneDrive/Bureau/Stage/Code/Dataset/"

#######################################################################################

# genere 30 instances pour T1
for i in range (0,30):
    nom_fichier = "I_"
    if len(str(nombre_prod))<2:
        nom_fichier += "0" + str(nombre_prod) + "_"
    else:
        nom_fichier += str(nombre_prod) + "_"
    if len(str(nombre_client))<2:
        nom_fichier += "0" + str(nombre_client) + "_T1_"
    else: 
        nom_fichier += str(nombre_client) + "_T1_"
    nom_fichier += str(i) + ".txt"
        
# creer le fichier dans le repertoire data   
    fichier = open(path + nom_fichier, "w")
    fichier.write(str(nombre_prod) + "\n")
    fichier.write(str(nombre_client) + "\n")
    
# rempli la matrice de distance  
    coord = [[] for l in range(nombre_prod + nombre_client)]
    for l in range(0,nombre_prod):
        x, y = randint(25,75), randint(25,75)
        coord[l].append(x)
        coord[l].append(y)
    for l in range(nombre_prod,nombre_prod + nombre_client):
        pos = True
        while pos:
            x, y = randint(0,100), randint(0,100)
            if x >= 25 and x <= 75 and y >= 25 and y <= 75:
                pos = True
            else : 
                pos = False
        coord[l].append(x)
        coord[l].append(y)
        
    for j in range (0,nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range (0,nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b) 
            distance = round(distance)
            fichier.write(str(distance) + " ")
        fichier.write("\n")
    for n in range(0,nombre_prod + nombre_client):
        fichier.write(str(coord[n][0]) + " ")
        fichier.write(str(coord[n][1]) + "\n")
    fichier.close()

#######################################################################################  

# genere 30 instances pour T2
for i in range (0,30):
    nom_fichier = "I_"
    if len(str(nombre_prod))<2:
        nom_fichier += "0" + str(nombre_prod) + "_"
    else:
        nom_fichier += str(nombre_prod) + "_"
    if len(str(nombre_client))<2:
        nom_fichier += "0" + str(nombre_client) + "_T2_"
    else: 
        nom_fichier += str(nombre_client) + "_T2_"
    nom_fichier += str(i) + ".txt"
        
# creer le fichier dans le repertoire data   
    fichier = open(path + nom_fichier, "w")
    fichier.write(str(nombre_prod) + "\n")
    fichier.write(str(nombre_client) + "\n")
    
# rempli la matrice de distance  
    coord = [[] for l in range(nombre_prod + nombre_client)]
    for l in range(0,nombre_prod):
        pos = True
        while pos:
            x, y = randint(0,100), randint(0,100)
            if x >= 25 and x <= 75 and y >= 25 and y <= 75:
                pos = True
            else : 
                pos = False
        coord[l].append(x)
        coord[l].append(y)
    for l in range(nombre_prod,nombre_prod + nombre_client):
        x, y = randint(25,75), randint(25,75)
        coord[l].append(x)
        coord[l].append(y)
        
    for j in range (0,nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range (0,nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b) 
            distance = round(distance)
            fichier.write(str(distance) + " ")
        fichier.write("\n")
    for n in range(0,nombre_prod + nombre_client):
        fichier.write(str(coord[n][0]) + " ")
        fichier.write(str(coord[n][1]) + "\n")
    fichier.close()
    
#######################################################################################  

# genere 30 instances pour T3
for i in range (0,30):
    nom_fichier = "I_"
    if len(str(nombre_prod))<2:
        nom_fichier += "0" + str(nombre_prod) + "_"
    else:
        nom_fichier += str(nombre_prod) + "_"
    if len(str(nombre_client))<2:
        nom_fichier += "0" + str(nombre_client) + "_T3_"
    else: 
        nom_fichier += str(nombre_client) + "_T3_"
    nom_fichier += str(i) + ".txt"
        
# creer le fichier dans le repertoire data   
    fichier = open(path + nom_fichier, "w")
    fichier.write(str(nombre_prod) + "\n")
    fichier.write(str(nombre_client) + "\n")
    
# rempli la matrice de distance  
    coord = [[] for l in range(nombre_prod + nombre_client)]
    for l in range(0,nombre_prod):
        bool = randint(0,1)
        if bool == 0:
            x, y = randint(0,25), randint(0,100)
        else : 
            x, y = randint(75,100), randint(0,100)
        coord[l].append(x)
        coord[l].append(y)
    for l in range(nombre_prod,nombre_prod + nombre_client):
        x, y = randint(25,75), randint(0,100)
        coord[l].append(x)
        coord[l].append(y)
        
    for j in range (0,nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range (0,nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b) 
            distance = round(distance)
            fichier.write(str(distance) + " ")
        fichier.write("\n")
    for n in range(0,nombre_prod + nombre_client):
        fichier.write(str(coord[n][0]) + " ")
        fichier.write(str(coord[n][1]) + "\n")
    fichier.close()
    
#######################################################################################  

# genere 30 instances pour TR
for i in range (0,30):
    nom_fichier = "I_"
    if len(str(nombre_prod))<2:
        nom_fichier += "0" + str(nombre_prod) + "_"
    else:
        nom_fichier += str(nombre_prod) + "_"
    if len(str(nombre_client))<2:
        nom_fichier += "0" + str(nombre_client) + "_TR_"
    else: 
        nom_fichier += str(nombre_client) + "_TR_"
    nom_fichier += str(i) + ".txt"
        
# creer le fichier dans le repertoire data   
    fichier = open(path + nom_fichier, "w")
    fichier.write(str(nombre_prod) + "\n")
    fichier.write(str(nombre_client) + "\n")
    
# rempli la matrice de distance  
    coord = [[] for l in range(nombre_prod + nombre_client)]
    for l in range(0,nombre_prod):
        x, y = randint(0,100), randint(0,100)
        coord[l].append(x)
        coord[l].append(y)
    for l in range(nombre_prod,nombre_prod + nombre_client):
        x, y = randint(0,100), randint(0,100)
        coord[l].append(x)
        coord[l].append(y)
        
    for j in range (0,nombre_prod + nombre_client):
        x_a = coord[j][0]
        y_a = coord[j][1]
        a = np.array((x_a, y_a))
        for k in range (0,nombre_prod + nombre_client):
            x_b = coord[k][0]
            y_b = coord[k][1]
            b = np.array((x_b, y_b))
            distance = np.linalg.norm(a - b) 
            distance = round(distance)
            fichier.write(str(distance) + " ")
        fichier.write("\n")
    for n in range(0,nombre_prod + nombre_client):
        fichier.write(str(coord[n][0]) + " ")
        fichier.write(str(coord[n][1]) + "\n")
    fichier.close()