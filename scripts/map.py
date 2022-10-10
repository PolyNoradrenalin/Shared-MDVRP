from tkinter import *

Fenetre=Tk()

Shift = 10 #décalage du bord gauche et haut
Delta = 5 # décalage vertical et horizontal de l'affichage 
Taille_pave = 100 #taille de la fenetre 100 x 100
larg_case = 5 #taille d'une unité
N=larg_case*Taille_pave+2*Shift
zone_dessin = Canvas(Fenetre,width=N,height=N,bd=3,background='white')
tv = 10

acteurs = open("test.txt","r")
tous_les_acteurs = acteurs.readlines();
acteurs.close()

NbProd = int(tous_les_acteurs[0])
NbCli = int(tous_les_acteurs[1])
NbActeurs = NbCli+NbProd
acteur_X = []
acteur_Y = []

cpt = 0
for line in tous_les_acteurs:
    if cpt>1+NbActeurs :
        L = line.split(" ")
        acteur_X.append(int(L[0]))
        acteur_Y.append(int(L[1].strip("\n")))
    cpt+=1

def PlaceActeur(v,color):
    x = acteur_X[v]
    y = acteur_Y[v]
    x0 = Shift + x*larg_case-tv/2
    y0 = Shift + (Taille_pave-y)*larg_case-tv/2
    x1 = x0+tv
    y1 = y0+tv
    zone_dessin.create_oval(x0,y0,x1,y1,fill=color)
    zone_dessin.create_text(x0+0.5*tv,y0-0.75*tv,text=str(v))
    
for j in range(0,NbProd):
    PlaceActeur(j,"blue")
    
for j in range(NbProd,NbActeurs):
    PlaceActeur(j,"red")

Fenetre.title(str(NbProd) + " producteurs (bleu), " + str(NbCli) + " clients (rouge)")
zone_dessin.pack()
Fenetre.mainloop() 



