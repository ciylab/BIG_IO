## PRÉSENTATION
Ce code permet de gérer un module qui possède des entées et des sorties MIDI/CV/GATE. Les entrées et les sorties sont associées par des algorithmes.

## MODE D'EMPLOI
À la mise sous tension les leds s'allument à tour de rôle pendant que l'écran affiche pendant quelques secondes un message d'information suivi du numéro de version :

~~~~~~~
 BIG InOut
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
  - MIDI (canal)
  - GATE (0 ou 5 volts)
  
**Out** :

  - NONE
  - MIDI (canal)
  - GATE (5 sorties)
  - CV (3 sorties)
  
**Algorithmes** :

  - NONE : ne fait rien
  - SIMPLE : simple changement de canal MIDI ou MIDI en CV/GATE
  - RAND : générateur aléatoire
  - RECORD : enregistrement d'une séquence
  - MINI SEQ : quelques notes (ligne de basse)
  - TRIGGER : rythmique (drum)
  - TIME : gestion de l'horloge

Le module est configuré par défaut :

|ID| IN    | OUT    | ACTION   | COMMENTS          |
|:-|:------|:-------|:---------|------------------:|
| 1| NONE |  CH1/CLOCK | TIME     | clock             |
| 2| NONE  | CH2/ DRUM1 | DRUM | rythme euclidien  |
| 3| NONE  | CH3  | BASS  |  bass line |
| 4| CH1  | CH4  | SEQ | séquenceur         |
| 5| NONE  |  CH5   |  RAND    | notes aléatoires |
| 6| NONE  | NONE|   NONE   | ne fait rien   |
| 7| NONE   |  NONE   | NONE     |   ne fait rien  |
| 8|  NONE | NONE|  NONE  | ne fait rien |

La calibration CALIBR permet de contrôler la justesse des notes sur un rack modulaire. La sortie CV1 est par défaut, au moment de la calibration, qui doit sortir 4 volts. 

La page PLAY permet d'accéder aux paramètres de chacun des 8 modules.

Il est possible de sauvegarder (SAVE) ou de charger (LOAD) une configuration. La validation se fait par pression de l'encodeur droit.

**Reboot** : une pression longue sur l'encodeur de gauche redémarre le module.

**Program Change** : le module réagit aux messages PC

**Control Change** : le module réagit aux messages CC dont le numéro de 1 à 8 est celui du paramètre sur le canal midi.


