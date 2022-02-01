#include <gamma.h>

#include <Adafruit_Sensor.h>

#include <DHT.h> // Charger la bibliothèque pour les interfaces sérielles
#include <DHT_U.h>

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
#define DHTPIN 2 // broche ou l'on a branche le capteur
// de-commenter le capteur utilise
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur
void setup()
{
 Timer1.initialize( 5000 ); //Temps d'initialiser la matrice
 Timer1.attachInterrupt( ScanDMD ); 
 dmd.clearScreen( true ); 
 dmd.selectFont(SystemFont5x7); // Utilise une matrice pour dessiner de caratere avec 5 led en horizontal et 7 led en vertical // 
 Serial.begin(9600); //9600 bauds dans le moniteur série
 Serial.println("DHT22 test!"); 
 dht.begin();
 }

 
void loop()
{
 delay(400); //Temps entre chaque mesure
 
 // La lecture du capteur prend 250ms
 // Les valeurs lues peuvent etre vieilles de jusqu'a 2 secondes (le capteur est lent)
 float h = dht.readHumidity();//on lit l'hygrometrie
 float t = dht.readTemperature();//on lit la temperature en celsius (par defaut)
 // pour lire en farenheit, il faut le paramère (isFahrenheit = true) :
 float f = dht.readTemperature(true);
char temp[8];
dtostrf(t, 6, 2, temp); //on convertit la variable float t (la température) en char qui se nomme temp pour l'afficher sur la matrice
 
 //On verifie si la lecture a echoue, si oui on quitte la boucle pour recommencer.
 if (isnan(h) || isnan(t) || isnan(f))
 {
   Serial.println("Failed to read from DHT sensor!");
   return;
 }
 
 
 // Calcul de l'indice de temperature en Celsius
 float hic = dht.computeHeatIndex(t, h, false);
 
 //Affichages :
 Serial.print("Humidite: "); // Afficher l'humidité
 Serial.print(h);           // Variable qui contient l'humidité
 Serial.print(" %\t");
 Serial.print("Temperature: "); // Afficher la temperature 
 Serial.print(t);               // Variable qui contient la temperature
 Serial.print(" *C\n ");        // Afficher en °C celcius 

 
dmd.drawString(-4,0, temp, 15, GRAPHICS_NORMAL ); //-4 correspond au colonne et 0 au ligne
//dmd.drawString(14,8,"C", 10, GRAPHICS_NORMAL );
//dmd.drawString(10,3,".", 10, GRAPHICS_NORMAL );

}
