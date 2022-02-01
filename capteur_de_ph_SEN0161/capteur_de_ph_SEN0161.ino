/*
 # This sample code is used to test the pH meter V1.0.
 # Editor : YouYou
 # Ver    : 1.0
 # Product: analog pH meter
 # SKU    : SEN0161
*/
#define SensorPin A1 //Branchement sur le pin A1
// pH metre sortie analogique à Arduino entrée analogique 0
#define Offset 0.00            //deviation compensate
#define LED 13  //on définit le PIN de la LED, utile comme indicateur mais facultatif 
                //pour le fonctionnement de la sonde à PH
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //Définit taille du tableau
int pHArray[ArrayLenth];   //Stock la valeur moyenne du retour du capteur
int pHArrayIndex=0;
void setup(void)
{
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("pH meter experiment!");    //Test dans le moniteur série
}
void loop(void)
{
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
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();
  }
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //Si inférieur à 5, calcule directement statistique
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
