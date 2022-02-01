#define PIN 22
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PIN, OUTPUT); // Sortie pour pin D22
}

// the loop function runs over and over again forever
void loop()
{
  digitalWrite(PIN, LOW);   // Etat haut //
}
