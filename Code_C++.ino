#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// initialiser le LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inclure le code de la bibliothèque :
#include "DHT.h"

// La broche numérique 13 est reliée au capteur DHT.
#define DHTPIN 13

// Défini le type de capteur utilisé
#define DHTTYPE DHT11

// On indique la broche et le type de capteur
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // configurer le LCD
  lcd.init();
  lcd.backlight();

  // Initialise le capteur DHT.
  dht.begin();
}

void loop() {
  // Attend 2 secondes entre les mesures.
  delay(2000);

  // La lecture de la température ou de l'humidité prend environ 250 millisecondes !
  // Les lectures du capteur peuvent également être "anciennes" jusqu'à 2 secondes (c'est un capteur très lent)

  // Lit l'humidité
  float h = dht.readHumidity();

  // Lit la température en degrés Celsius
  float t = dht.readTemperature();

  // Vérifiez si des lectures ont échoué
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Impossible de lire à partir du capteur DHT!"));
    return;
  }

  // Affichage LCD
  lcd.setCursor(0, 0); //On place le curseur à partir de la première colonne de la première ligne sur l'écran LCD 
  lcd.print("Temp:");

  lcd.setCursor(6, 0);
  lcd.print(t);

  lcd.setCursor(13, 0);
  lcd.print((char)223); //(char)223 est un caractère spécial permettant d'afficher le symbole degré celsius °

  lcd.setCursor(14, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Hum:");

  lcd.setCursor(6, 1);
  lcd.print(h);

  lcd.setCursor(13, 1);
  lcd.print("%");
}
