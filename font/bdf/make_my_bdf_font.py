#!/usr/bin/python3

"""Script de génération de la fonte utilisée au format bdf.

La fonte contient les caractères ascii de 32 à 126 inclus.
Ensuite on ajoute le cursor (127) puis toutes les barres de progressions
de une barre verticale à 7 barres (128 à 134) soit un total de 103
caractères. Le nom des caratères ajoutés est cursor, bar1 jusqu'à bar7.

L'ascii vient de la fonte :
-Misc-Fixed-Medium-R-Normal--14-130-75-75-C-70-ISO10646-1
Le fichier source est 7x14.bdf dont le premier caractère char0 (ascii 0)
est le caractère zéro en pointillé.
"""

code = ["40", "60", "70", "78", "7C", "7E", "FE"]

def cursor():
    print("STARTCHAR cursor")
    print("ENCODING 127")
    print("SWIDTH 960 0\nDWIDTH 7 0\nBBX 7 14 0 -2\nBITMAP")
    print("00")
    print("00")
    for i in range(6):
        print(code[i])
    for i in range(5):
        print(code[4 - i])
    print("00")
    print("ENDCHAR\n")

def bar(n):
    print("STARTCHAR bar" + str(n))
    print("ENCODING " + str(127 + n))
    print("SWIDTH 960 0\nDWIDTH 7 0\nBBX 7 14 0 -2\nBITMAP")
    print("00")
    print("00")
    for i in range(11):
        print(code[n - 1])
    print("00")
    print("ENDCHAR\n")

f = open("7x14.bdf", 'r')
for i in range(32):
    print(f.readline(), end='')
print("CHARS 103\n", end='')
f.readline()
for i in range(22 * 96):
    print(f.readline(), end='')
print()
cursor()
for i in range(1, 8):
    bar(i)
print("ENDFONT")
f.close()
