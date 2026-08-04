## PRÉSENTATION
Ce code permet de gérer un module qui possède des entées et des sorties MIDI/CV/GATE. Les entrées et les sorties sont associées par des algorithmes.

## MODE D'EMPLOI
À la mise sous tension les leds s'allument à tour de rôle pendant que l'écran affiche pendant quelques secondes un message d'information :

~~~~~~~
 BIG InOut
 by 
 CIYLab
 vx.y.z
~~~~~~~

suivi du numéro de version.

La page principale permet les manipulations de base :

~~~~~~~
>CONFIG
 CALIBR
 PLAY
 LOAD   SAVE
~~~~~~~

** Navigation ** :

  - on tourne l'encodeur gauche pour naviguer dans le menu
  - on presse l'encodeur gauche pour remonter (hiérarchie)
  - on tourne l'encodeur droit pour charger la page ou modifier la valeur
  - on presse l'encodeur droit pour valider (on/off, rec, del, tone...)

Une configuration consiste à choisir un algorithme, une entrée et une sortie parmi :

** In ** :

  - NONE
  - MIDI
  - GATE (0 ou 5 volts)
  
** Out ** :

  - NONE
  - MIDI
  - GATE (5 sorties)
  - CV (3 sorties)
  
** Algorithmes ** :

  - NONE : ne fait rien
  - SIMPLE : simple changement de canal MIDI ou MIDI en CV/GATE
  - RAND : générateur aléatoire
  - RECORD : enregistrement d'une séquence
  - MINI SEQ : quelques notes 
  - TRIGGER : rythmique
  - TIME : gestion de l'horloge
  - ARPEG : arpégiateur
  - COMPARE : on filtre dans un intervalle

Par exemple :

~~~~~~~
>ID     6
 IN     CH2
 OUT    TRIG1
 ACTION RECORD
~~~~~~~

Le module est configuré par défaut :

|ID| IN    | OUT    | ACTION   | COMMENTS          |
|:-|:------|:-------|:---------|------------------:|
| 1| TRIG0 | TRIG1  | TIME     | clock             |
| 2| NONE  | TRIG2  | TRIGGER  | rythme euclidien  |
| 3| NONE  | TRIG3  | TRIGGER  | rythme euclidien  |
| 4| NONE  | CH1    | MINI SEQ | bass line         |
| 5| CH2   | CH2    | RECORD   | mélodie           |
| 6| NONE  | CVGATE1| RAND     | notes aléatoire   |
| 7| CH3   | CH3    | NONE     | canal 3 inatif    |
| 8| CH14  | CVGATE2| SIMPLE   | MIDI vers CV/GATE |

La calibration CALIBR permet de contrôler la justesse des notes sur un rack modulaire. La sortie CV1 est par défaut, au moment de la calibration, pour un C4 à 4 volts. S'il est juste on doit avoir C2 (2 volts) sur CV2 et C1 (1 volt) sur CV3.

La page PLAY permet d'accéder aux paramètres de chacun des 8 modules.

Il est possible de sauvegarder (SAVE) ou de charger (LOAD) une configuration. La validation se fait par pression de l'encodeur droit.

**Reboot** : une pression longue sur l'encodeur de gauche redémarre le module.

**Program Change** : le module réagit aux messages PC

**Control Change** : le module réagit aux messages CC dont le numéro de 1 à 8 est celui du paramètre sur le canal midi.


