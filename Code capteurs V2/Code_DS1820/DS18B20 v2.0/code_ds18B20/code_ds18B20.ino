/**
 * Exemple de code pour lire plusieurs capteurs DS18B20 sur un même bus 1-Wire via leur adresse unique.
 */
 
/* Dépendance pour le bus 1-Wire */
#include <OneWire.h>
 
 
/* Broche du bus 1-Wire */
const byte BROCHE_ONEWIRE = A4;

/* Adresses des capteurs de température */
const byte SENSOR_ADDRESS_1[] = { 0x28, 0x9E, 0x9C, 0x1F, 0x00, 0x00, 0x80, 0x04 };
const byte SENSOR_ADDRESS_2[] = { 0x28, 0x1D, 0x9B, 0x1F, 0x00, 0x00, 0x80, 0xE6 };
const byte SENSOR_ADDRESS_3[] = { 0x28, 0x0F, 0x91, 0x1F, 0x00, 0x00, 0x80, 0x6E };


/* Création de l'objet OneWire pour manipuler le bus 1-Wire */
OneWire ds(BROCHE_ONEWIRE);

 
/**
 * Fonction de lecture de la température via un capteur DS18B20.
 */
float getTemperature(const byte addr[]) {
  byte data[9];
  // data[] : Données lues depuis le scratchpad
  // addr[] : Adresse du module 1-Wire détecté
  
  /* Reset le bus 1-Wire et sélectionne le capteur */
  ds.reset();
  ds.select(addr);
  
  /* Lance une prise de mesure de température et attend la fin de la mesure */
  ds.write(0x44, 1);
  delay(800);
  
  /* Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad */
  ds.reset();
  ds.select(addr);
  ds.write(0xBE);
 
 /* Lecture du scratchpad */
  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
   
  /* Calcul de la température en degré Celsius */
  return (int16_t) ((data[1] << 8) | data[0]) * 0.0625; 
}
 
 
/** Fonction setup() **/
void setup() {

  /* Initialisation du port série */
  Serial.begin(115200);
}
 
 
/** Fonction loop() **/
void loop() {
  float temperature[1];
   
  /* Lit les températures des trois capteurs */
  temperature[0] = getTemperature(SENSOR_ADDRESS_1);
  
  
  /* Affiche les températures */
  Serial.print(F("Temperature : "));
  Serial.print(temperature[0], 2);
  Serial.write(176); // Caractère degré
  Serial.print(F("C, "));
 
}
