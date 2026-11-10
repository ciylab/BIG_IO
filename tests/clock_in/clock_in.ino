// Définition de la broche PA8
const int pinLecture = PA8;

void setup() {
  // Initialisation de la communication série pour afficher le résultat
  Serial.begin(9600);
  
  // Configuration de PA8 en entrée avec résistance de tirage vers le haut (Pull-up interne)
  // Le bouton doit être connecté entre PA8 et le GND. 
  // État lu : HIGH (1) au repos, LOW (0) quand on appuie.
  pinMode(pinLecture, INPUT_PULLUP);
}

void loop() {
  // Lecture de l'état de la broche PA8
  int etatBroche = digitalRead(pinLecture);
  
  // Affichage du résultat dans le moniteur série
  Serial.print("Etat de PA8 : ");
  Serial.println(etatBroche);
  
  delay(200); // Petite pause de 200ms
}
