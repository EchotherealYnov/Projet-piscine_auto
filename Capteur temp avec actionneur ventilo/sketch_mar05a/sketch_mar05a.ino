
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define PIN 22   // Broche Digital22 (D22)
#define DHTPIN 2 // broche ou l'on a branche le capteur
// de-commenter le capteur utilise
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur
 
void setup()
{
 Serial.begin(9600);
 Serial.println("DHT22 test!");
 dht.begin();
 pinMode(PIN, OUTPUT);
}
void loop()
{
 delay(2000);
 
 // La lecture du capteur prend 250ms
 // Les valeurs lues peuvet etre vieilles de jusqu'a 2 secondes (le capteur est lent)
 float h = dht.readHumidity();//on lit l'hygrometrie
 float t = dht.readTemperature();//on lit la temperature en celsius (par defaut)
 // pour lire en farenheit, il faut le paramère (isFahrenheit = true) :
 float f = dht.readTemperature(true);
 
 //On verifie si la lecture a echoue, si oui on quitte la boucle pour recommencer.
 if (isnan(h) || isnan(t) || isnan(f))
 {
   Serial.println("Failed to read from DHT sensor!");
   return;
 }
 
 // Calcul de l'indice de temperature en Farenheit
 float hif = dht.computeHeatIndex(f, h);
 // Calcul de l'indice de temperature en Celsius
 float hic = dht.computeHeatIndex(t, h, false);

 
 if (t > 22)
  {
    digitalWrite(PIN, HIGH); //le ventilo s'allume
  }
 else
 {
  digitalWrite(PIN, LOW); //le ventilo s'éteint
 }
 
 
 //Affichages :
 Serial.print("Humidite: ");
 Serial.print(h);
 Serial.print(" %\t");
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.print(" *C ");
 Serial.print(f);
 Serial.print(" *F\t");
 Serial.print("Indice de temperature: ");
 Serial.print(hic);
 Serial.print(" *C ");
 Serial.print(hif);
 Serial.println(" *F");
}
