## PRÉSENTATION
Ce code permet de gérer un module qui possède des entrées et des sorties MIDI/CV/GATE. Les entrées et les sorties sont associées par des algorithmes.

## MODE D'EMPLOI
À la mise sous tension les leds s'allument à tour de rôle pendant que l'écran affiche pendant quelques secondes un message d'information suivi du numéro de version :

~~~~~~~
 THE BIG ONE
 by 
 CIYLab
 vx.y.z
~~~~~~~

La page principale permet les manipulations de base :

~~~~~~~
>CONFIG
 PLAY
 LOAD   SAVE
 CALIBR 
~~~~~~~

**Navigation** :

  - on tourne l'encodeur gauche pour naviguer dans le menu
  - on presse l'encodeur gauche pour remonter (hiérarchie)
  - on tourne l'encodeur droit pour charger la page CONF/PLAY ou modifier la valeur
  - on presse l'encodeur droit pour valider la modification

Une configuration consiste à choisir un algorithme, une entrée et une sortie parmi :

**In** :

  - NONE
  - MIDI (numéro de canal de 1 à 16)
  - CLOCK
  
**Out** :

  - NONE
  - MIDI (numéro de canal de 1 à 16)
  - GATE (CLOCK, DRUM 1, DRUM 2,  GATE 1 et GATE 2)
  - CV (CV 1, CV 2, CV 3)
 
 **Remarque** :
 
 Les noms des cvs et des gates correspondent à la sérigraphie mais ils sont interchangeables.
 
**Algorithmes** :

  - ____ : ne fait rien (none)
  - SIMPLE : redirection du canal MIDI ou MIDI vers CV/GATE
  - RAND : générateur aléatoire
  - LOOPER : enregistrement d'une séquence
  - BASS : quelques notes (ligne de basse)
  - DRUM : rythmique (drum)
  - TIME : gestion de l'horloge

Le module est configuré par défaut :

|ID| IN    | OUT    | ACTION   | COMMENTS          |
|:-|:------|:-------|:---------|------------------:|
| 1| NONE |  CH1/CLOCK | TIME     | clock             |
| 2| NONE  | CH2/DRUM1 | DRUM | rythme euclidien  |
| 3| NONE  | CH3/CV1/DRUM2  | BASS  |  bass line |
| 4| CH1  | CH4/CV2/GATE1  | LOOP | séquenceur         |
| 5| NONE  |  CH5/CV3/GATE2   |  RAND    | notes aléatoires |
| 6| NONE  | NONE|   ____   | ne fait rien   |
| 7| NONE   |  NONE   | ____     |   ne fait rien  |
| 8|  NONE | NONE|  ____  | ne fait rien |

La calibration **CALIBR** permet de contrôler la justesse des notes sur un rack modulaire. Pour la calibration, la sortie CV1 doit fournir 4 volts. 

La page **PLAY** permet d'accéder aux paramètres de chacun des 8 modules.

Il est possible de sauvegarder **SAVE** ou de charger **LOAD** une configuration. La validation se fait par pression de l'encodeur droit. Il y a 8 slots. Chaque slot contient les 8 modules y compris les éventuelles séquences du looper. Le premier slot **FACT** est modifiable mais ne peut pas être écrasé. On peut le sauvegarder sur un des autres 7 slots. Sur le même principe le premier module d'une configuration sera toujours **TIME** pour la gestion de l'horloge. Il n'y aura pas d'autre module disponible en première position.

**Reboot** : une pression longue sur l'encodeur de gauche redémarre le module.

**Program Change** : le module réagit aux messages PC (1 à 8) et affiche le module

**Control Change** : message CC (1 à 8) est celui du paramètre sur le canal midi correspondant


