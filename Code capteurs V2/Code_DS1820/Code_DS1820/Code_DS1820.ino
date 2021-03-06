#include <OneWire.h> //Librairie  OneWire
#include <DallasTemperature.h> //Librairie du capteur
 
unsigned long previousMillis = 0;//variable delay sans arrêt du programme
 
const long interval = 1000;// variable delay sans arrêt du programme qui prevoit une lecture de 1 seconde par mesure
 
OneWire oneWire(A5); //PIN digital de la sonde sur la pin 2 de l'arduino
DallasTemperature sensors(&oneWire); //Utilistion du bus Onewire pour les capteurs
DeviceAddress sensorDeviceAddress; //Vérifie la compatibilité des capteurs avec la librairie
 
void setup(void) {
 
  Serial.begin(115200); //définition de la vitesse et de l'ouverture du port série
  sensors.begin(); //Sonde activée
  Serial.print("Etape 1 \t");
  sensors.getAddress(sensorDeviceAddress, 0); //Adresse de la sonde à 0
  Serial.print("Etape 2 \t");
  sensors.setResolution(sensorDeviceAddress, 12); //Résolutions
  Serial.print("Etape 3 \n");
 
  Serial.println("Bienvenue sur les tutoriels de IHM-3D");
 
  delay (2000);
}
 
void loop(void) {
 
  unsigned long currentMillis = millis();// inclure une variable de temps par rapport à millis()
 
  if (currentMillis - previousMillis >= interval) {
       previousMillis = currentMillis;
 
    sensors.requestTemperatures(); //Demande la température aux capteurs
    Serial.print("Température de la pièce ");
    Serial.print(sensors.getTempCByIndex(0)); //Information récupérée sur l'adresse 0 de la sonde
    Serial.println(" DEGRES ");
 
  }
}
