#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//----- Adressage matériel -----
// En cas de non fonctionnement, mettez la ligne 8 en
// commentaire et retirez le commentaire à la ligne 9.
LiquidCrystal_I2C lcd(0x27, 16, 2);
//LiquidCrystal_I2C lcd(0x3F,16,2);
void setup()
{
   lcd.begin(16,2);
 lcd.init(); // initialisation de l'afficheur
 
}
 //void lcdprint(String s) {
 //for (int  i = 0; i < s.length(); i++)  lcd.print(s[i]);
 
void loop()
{
  lcd.backlight();
 //Envoi du message
 lcd.setCursor(3, 0);
 lcd.println("Bonjour");
 /*lcd.setCursor(4, 0);
 lcd.print("O");
 lcd.setCursor(5, 0);
 lcd.print("N");
 lcd.setCursor(6, 0);
 lcd.print("J");
 lcd.setCursor(7, 0);
 lcd.print("O");
 lcd.setCursor(8, 0);
 lcd.print("U");
 lcd.setCursor(9, 0);
 lcd.print("R");
 lcd.setCursor(10, 0);
 lcd.print("!");
  lcd.setCursor(0, 1);
 lcd.print("T");
  lcd.setCursor(1, 1);
 lcd.print("E");
  lcd.setCursor(2, 1);
 lcd.print("M");
  lcd.setCursor(3, 1);
 lcd.print("P");
  lcd.setCursor(4, 1);
 lcd.print("=");
  lcd.setCursor(5, 1);
 lcd.print("2");
  lcd.setCursor(6, 1);
 lcd.print("2");
  lcd.setCursor(7, 1);
 lcd.print("");
  lcd.setCursor(8, 1);
 lcd.print("C");*/
}
