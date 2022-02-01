

int sensorPin = A5;    // select the input pin for the potentiometer

int sensorValue = 0;  // variable to store the value coming from the sensor
int min = 500; 
int max=695;
void setup() {
  Serial.begin (9600);// Démarrage de la liaison série
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
 
 Serial.println (sensorValue);// Affichage de la valeur
 
 if(sensorValue>max)
  Serial.println ("attention niveau eau trop élevé");
  
  if(sensorValue<min)
Serial.println ("attention niveau eau trop faible");

if(min<sensorValue<max)
Serial.println ("Niveau d'eau normale");

delay (2000);// Attendre 1s avant la prochaine lecture

}
