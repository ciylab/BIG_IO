## PRÉSENTATION
Ce code permet d'utiliser une entrée MIDI sur le module MIDI2CVGATE pour générer des CV et GATE avec la possibilité d'enregistrer ce qui sort du clavier. La note maximale est calibrée (minimum C0 = 0 volt) pour que C4 corresponde à 4 volts. Compte tenu de l'alimentation il devrait être possible d'atteindre C5.

## MODE D'EMPLOI
À la mise sous tension les leds s'allument à tour de rôle pendant que l'écran affiche pendant quelques secondes un message d'information :

~~~~~~~
 MIDI
 TO 
 CV/GATE
 vx.y.z
~~~~~~~

suivi du numéro de version.

Pour choisir un des algorithmes installés, il faut tourner l'encodeur PARAMETER au-dessus de l'écran.

~~~~~~~
>DRUM 1  TIME
 DRUM 2
 ARP 1
 LOOPER 2
~~~~~~~

Ce même encodeur PARAMETER permet ensuite d'afficher la liste des paramètres par simple pression et de sélectionner le paramètre qu'on souhaite modifier.

~~~~~~~
 IN      DIVIDE
 CLOCK
>BPM
 MULT
~~~~~~~

Une nouvelle pression permet de revenir à la liste des algorithmes.

Une fois le paramètre sélectionné, l'encodeur VALUE à gauche de l'écran permet d'en modifier la valeur. À noter qu'une rotation d'un seul cran de l'encodeur VALUE affiche la valeur sans la modifier. On modifie la valeur par rotation ou par pression suivant le type de paramètre.

~~~~~~~
 IN      DIVIDE
 CLOCK
> 80
 MULT
~~~~~~~

**Reboot** : une pression longue sur l'encodeur PARAMETER affichant la liste redémarre le module.

**Program Change** : le module réagit aux messages PC

**Control Change** : le module réagit aux messages CC dont le numéro de 2 à 8 est celui du paramètre sur le canal midi. Le numéro de canal midi ne peut être changé que manuellement.


