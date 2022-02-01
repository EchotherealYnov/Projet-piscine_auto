#include <DHT.h> 
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/*-----------------------------PARTIE PH----------------------------------------------*/
#define SensorPin A0 //pH meter Analog output to Arduino Analog Input 0 Ph met                     
#define Offset 0.00            //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;
/*------------------------------------------FIN-----------------------------------------*/

/*Code DHT 22*/
#define DHTPIN 2 // broche ou l'on a branche le capteur
#define DHTTYPE DHT22 // DHT 22 (AM2302)

double orpValue;
DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur
/*------------------------------------------FIN-------------------------------------*/
/*---------------------------PARTIE ORP REDOX-----------------------------------*/
#define VOLTAGE 5.00    //system voltage
#define OFFSET 0        //zero drift voltage

#define ArrayLenth  40    //times of collection
#define orpPin 1          //orp meter output,connect to Arduino controller ADC pin

int orpArray[ArrayLenth];
int orpArrayIndex=0;

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    printf("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
/*------------------------------FIN PARTIE ORP REDOX-----------------------*/
void setup(void)
{
 Serial.begin(9600); //Moniteur série sur 9600 bauds 
 Serial.println("DHT22 test!");  //Test le moniteur série
 dht.begin();
 Serial.println("pH mètre test!"); //Test le moniteur série

 
 }

 
void loop(void)
{
  /*----------------------------------------------PARTIE DHT 22 --------------------------------*/
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
 
 
 // Calcul de l'indice de temperature en Celsius
 float hic = dht.computeHeatIndex(t, h, false);
 
 //Affichages :
 Serial.print("Humidite: "); // Afficher l'humidité
 Serial.print(h);           // Variable qui contient l'humidité
 Serial.print(" %\t");
 Serial.print("Temperature: "); // Afficher la temperature 
 Serial.print(t);               // Variable qui contient la temperature
 Serial.print(" *C\n ");        // Afficher en °C celcius 
 /*-----------------------------------FIN PARTIE DHT22-----------------------------------------*/
 
/*----------------------------------------PARTIE PH--------------------------------------------*/


static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Toutes les 800 millisecondes, affiche un numérique, 
                                             //Converti l'état de l'indicateur de la LED
  {
    Serial.print("Volt:");
        Serial.print(voltage,2);
        Serial.print("    Valeur de PH = ");
    Serial.println(pHValue,2);
      
        printTime=millis();
  }
}
double averagearray(int* arr, int number){
  int i;
  int max,min;
  double avg1;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //Si inférieur à 5, calcule directement statistique
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg1 = amount/number;
    return avg1;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg1 = (double)amount/(number-2);
  }//if
  return avg1;
}

/*------------------------------------------FIN PARTIE PH------------------------------------------*/
/*-------------------------------------PARTIE ORP REDOX--------------------------------------------*/
  static unsigned long orpTimer=millis();   //analog sampling interval
  static unsigned long printTime=millis();
  if(millis() >= orpTimer)
  {
    orpTimer=millis()+20;
    orpArray[orpArrayIndex++]=analogRead(orpPin);    //read an analog value every 20ms
    if (orpArrayIndex==ArrayLenth) {
      orpArrayIndex=0;
    }
    orpValue=((30*(double)VOLTAGE*1000)-(75*avergearray(orpArray, ArrayLenth)*VOLTAGE*1000/1024))/75-OFFSET;

    //convert the analog value to orp according the circuit
  }
  if(millis() >= printTime)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
    printTime=millis()+800;
    Serial.print("ORP: ");
    Serial.print((int)orpValue);
    Serial.println("mV");
       
  }

/*----------------------------------FIN PARTIE ORP REDOX-------------------------------------------*/
}
