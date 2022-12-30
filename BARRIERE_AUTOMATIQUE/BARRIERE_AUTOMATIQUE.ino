/**
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : RACHEL SYSTEME
 * DATE : 21/12/2022
 * 
 * @Board : Arduino Uno
 * 
 * Barrière automatique
 * 
*/

#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define PIN_SERVO 5 // Pin connecté au servomoteur
#define IR_CAPT_E 3 // Pin capteur IR à l'entrée
#define IR_CAPT_S 4 // Pin capteur IR à la sortie

#define ATTENTE   10    // Attente après chaque incrémentation
#define DETECTION LOW   // Capteur actif si LOW
#define HAUT 	  180   // Angle servomoteur (porte ouverte) 
#define BAS 	  90    // Angle servomoteur (porte fermer)
#define OPEN 	  false // Constante porte fermé
#define CLOSE     true  // Constante porte ouvert

// Déclaration des objets
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

// Prototypes des fonctions
void gestion_porte(const bool etat);   // Permet de positionner le servomoteur
void gestionES(const int pin_capteur); // Détermine si les 2 capteurs sont franchit

void setup(){
	// Configuration de l'écran LCD
	lcd.init();
	lcd.backlight();
	// Configuration servomoteur
	servo.attach(PIN_SERVO);
	servo.write(BAS);
	//Configuration pins
	pinMode(IR_CAPT_E, INPUT);
	pinMode(IR_CAPT_S, INPUT);
}

void loop(){
	// Affichage du message
	lcd.clear();
	lcd.setCursor(3,0);
	lcd.print("BIENVENUE");
	lcd.setCursor(2,1);
	lcd.print("PEAGE DE @RS");

	// Entrée
	if(digitalRead(IR_CAPT_E) == DETECTION && digitalRead(IR_CAPT_S) == not DETECTION){
		// Affichage du message
		lcd.clear();
		lcd.setCursor(3,0);
		lcd.print("BIENVENUE");
		lcd.setCursor(3,1); // positionnement du curseur 
		lcd.print("BON ARRIVE");//BONNE SORTIE
		// Ouverture porte
		gestion_porte(OPEN);
		// Dectection si capteur IR 1 franchit
		gestionES(IR_CAPT_S);
		// Fermeture porte
		gestion_porte(CLOSE);
	}// fin if

	// Sortie
	if(digitalRead(IR_CAPT_E) == not DETECTION && digitalRead(IR_CAPT_S) == DETECTION){
		// Affichage du message
		lcd.clear();
		lcd.setCursor(3,0);
		lcd.print("BIENVENUE");
		lcd.setCursor(2,1); // positionnement du curseur
		lcd.print("BONNE SORTIE");
		// Ouverture porte
		gestion_porte(OPEN);
		// Dectection si capteur IR 1 franchit
		gestionES(IR_CAPT_E);
		// Fermeture porte
		gestion_porte(CLOSE);
	}// fin if
	delay(500);
}

void gestion_porte(const bool etat){
	if(etat == OPEN){
		for (int i = servo.read(); i <= HAUT; ++i){
			servo.write(i);
			delay(ATTENTE);
		}
	}
	if (etat == CLOSE){
		for (int i = servo.read(); i >= BAS; --i){
			servo.write(i);
			delay(ATTENTE);
		}
	}
}

void gestionES(const int pin_capteur){
	while(digitalRead(pin_capteur) == not DETECTION){delay(ATTENTE);}
	while(digitalRead(pin_capteur) == DETECTION){delay(ATTENTE);}
	delay(1000);
}
