#include <OneWire.h>
// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire  ds(4);  // bus 1wire sur pin x ds(x)  (ne pas oublier une resistance de 4.7K entre cette ligne et +5V)

void setup(void) {
  Serial.begin(115200);
}

void loop(void) {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;
  byte crc;
  if ( !ds.search(addr)) {

    Serial.println("------------------ FIN DU SCAN ADRESSE---------------");
    Serial.println();
    Serial.println();
    Serial.println("                   DEBUT DU SCAN ADRESSE");
    Serial.println(" Family Code <--  ADRESSE  --> Checksum");
    
    ds.reset_search();
    delay(250);
    return;
  }

  //Serial.print("ROM =");
  for ( i = 0; i < 8; i++) {
    Serial.write(' ');
    if (addr[i] < 16) Serial.print("0");
    Serial.print(addr[i], HEX);
  }
  Serial.print(" ");

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC n'est pas valide!");
    return;
  }


  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      Serial.print("  Chip = DS18S20 ");  // or old DS1820 ou ds1920 ibutton
      type_s = 1;
      break;
    case 0x28:
      Serial.print("  Chip = DS18B20 ");
      type_s = 0;
      break;
    case 0x22:
      Serial.print("  Chip = DS1822 ");
      type_s = 0;
      break;
    default:
      Serial.println(" L'appareil n'est pas de la famille DS18x20 d'appareils.");
      return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // Commence la conversion , avec la puissance à la fin

  delay(1000);    
  // on peut peut être faire ds.depower() ici, mais le reset va s'en occuper.
  //ds.depower();
  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);         // Lit le scratchpad

  Serial.print("  Data = ");

  for ( i = 0; i < 9; i++) {           // On a besoin de 9 bits
    data[i] = ds.read();
    if (data[i] < 16) Serial.print("0");
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  //Serial.print(" CRC=");
  crc = OneWire::crc8(data, 8);
  //if (crc<16) Serial.print("0");
  //Serial.print(crc,HEX);
  //Serial.print("  ");

  // Converti la donnée en température réel
  // Parce que le résultat est un 16 bit entier signé,il devrait
  // être stocké en entier de type 16,  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default 
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit 
      
      resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  }
  else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  //fahrenheit = celsius * 1.8 + 32.0;
  Serial.print("      Temperature = ");
  Serial.print(celsius);

  Serial.println();
  delay(250);
}
