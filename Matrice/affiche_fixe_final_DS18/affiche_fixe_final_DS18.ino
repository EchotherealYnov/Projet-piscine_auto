#include <gamma.h>
#include <OneWire.h> //Librairie  OneWire
#include <DallasTemperature.h> //Librairie du capteur

#include "SPI.h"  // Charger la bibliothèque pour les interfaces sérielles
#include "DMD419.h" 
#include "TimerOne.h"
# include "SystemFont5x7.h"
/* you can remove the fonts if unused */
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD419 dmd( DISPLAYS_ACROSS , DISPLAYS_DOWN );
void ScanDMD()
{ 
 dmd.scanDisplayBySPI();
}
/*------------------------------PARTIE SONDE-----------*/ 
unsigned long previousMillis = 0;//variable delay sans arrêt du programme
 
const long interval = 1000;// variable delay sans arrêt du programme qui prevoit une lecture de 1 seconde par mesure
 
OneWire oneWire(5); //PIN digital de la sonde sur la pin 2 de l'arduino
DallasTemperature sensors(&oneWire); //Utilistion du bus Onewire pour les capteurs
DeviceAddress sensorDeviceAddress; //Vérifie la compatibilité des capteurs avec la librairie
/*--------------------------FIN PARTIE SONDE----------------*/
void setup()
{
 Timer1.initialize( 5000 ); //Temps d'initialiser la matrice
 Timer1.attachInterrupt( ScanDMD ); 
 dmd.clearScreen( true ); 
 dmd.selectFont(SystemFont5x7); // Utilise une matrice pour dessiner de caratere avec 5 led en horizontal et 7 led en vertical // 
 Serial.begin(9600); //9600 bauds dans le moniteur série
 sensors.begin(); //Sonde activée
 Serial.print("Etape 1");
 sensors.getAddress(sensorDeviceAddress, 0); //Adresse de la sonde à 0
 Serial.print("Etape 2");
 sensors.setResolution(sensorDeviceAddress, 12); //Résolutions
 Serial.print("Etape 3");
 
delay(2000); //Delai de 2 secondes
}
void loop()
{
 float t = sensors.getTempCByIndex(0);
 char temp[8];
 dtostrf(t, 6, 2, temp); //on convertit la variable float t (la température) en char qui se nomme temp pour l'afficher sur la matrice
 unsigned long currentMillis = millis();// inclure une variable de temps par rapport à millis()
 
  if (currentMillis - previousMillis >= interval) {
       previousMillis = currentMillis;
 
    sensors.requestTemperatures(); //Demande la température au capteur
    Serial.print("Température de l'eau des bassins : ");
    //Serial.print(temp); //Information récupérée sur l'adresse 0 de la sonde
    Serial.println(" DEGRES ");
 
  }
 
 
 //Affichages sur la matrice :

 
dmd.drawString(-4,0, temp, 15, GRAPHICS_NORMAL ); //-4 correspond au colonne et 0 au ligne
dmd.drawString(14,8,"C", 10, GRAPHICS_NORMAL ); // Affiche le C pour Celsius
//dmd.drawString(10,3,".", 10, GRAPHICS_NORMAL ); // Pour afficher le ° de degré Celsius mais il y a un problème d'affichage

}
