
// Initialisierung benötigter Variablen
int Counter = 0; 
boolean Richtung;
int Pin_clk_Letzter;  
int Pin_clk_Aktuell;

// Definition der Eingangs-Pins
int pin_clk = 1;  
int pin_dt = 11; 
int button_pin = 12;


 
 
void setup() 
{ 
   // Eingangs-Pins werden initialisiert...
   pinMode (pin_clk,INPUT_PULLUP);
   pinMode (pin_dt,INPUT_PULLUP);
   pinMode (button_pin,INPUT_PULLUP);
   
   for(int pins=2; pins <=10; pins++){
  pinMode(pins, OUTPUT);
  }
   
   // Initiales Auslesen des Pin_CLK
   Pin_clk_Letzter = digitalRead(pin_clk);   
   Serial.begin (115200);
 } 

// Das Programm überprüft, falls eine Änderung der Pin-Zustände sich ereignet hat, welcher der beiden
// Pins sich zuerst geändert hatte, was auf die Drehrichtung schließen lässt.
// Diese Information erhält man, in dem man einen der beiden Pin-Werte aus einem vorherigen
// Durchlauf mit dem Wert des aktuellen Durchlaufs vergleicht.
// Nachdem die Richtung festgestellt wurde, werden die Schritte von der Startposition an gezählt und ausgegeben.
// Ein Drücken auf den Knopf des Drehgebers resettet die aktuelle Position.

void loop()
{ 
 for(int pinLed=2; pinLed<=10; pinLed++){
  digitalWrite(pinLed, pinLed<=Counter);
  }
   // Auslesen des aktuellen Statuses  
   Pin_clk_Aktuell = digitalRead(pin_clk);
   
   // Überprüfung auf Änderung
   if (Pin_clk_Aktuell != Pin_clk_Letzter)
   { 
		 
		if (digitalRead(pin_dt) != Pin_clk_Aktuell) 
		{  
			// Pin_CLK hat sich zuerst verändert
			Counter ++;
     
     Counter = min(10, Counter);
			Richtung = true;
		} 
		 
		else 
		{       // Andernfalls hat sich Pin_DT zuerst verändert
			Richtung = false;
			Counter--;
          Counter = max(2, Counter);
		}
		Serial.println ("Drehung erkannt: ");
		Serial.print ("Drehrichtung: ");
		
		if (Richtung)
		{
		   Serial.println ("Im Uhrzeigersinn");
		}
		else
		{
		   Serial.println("Gegen den Uhrzeigersinn");
		}
		
		Serial.print("Aktuelle Position: ");
		Serial.println(Counter);
		Serial.println("------------------------------");
		 
   } 
   
   // Vorbereitung für den nächsten Druchlauf:
   // Der Wert des aktuellen Durchlaufs ist beim nächsten Druchlauf der vorherige Wert
   Pin_clk_Letzter = Pin_clk_Aktuell;
   
   // Reset-Funktion um aktuelle Position zu speichern
   if (!digitalRead(button_pin) && Counter!=0)
     {
       Counter = 0;
       Serial.println("Position resettet");
     }

 
 } 
