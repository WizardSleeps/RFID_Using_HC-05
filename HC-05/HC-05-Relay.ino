#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522
 
String read_rfid;
String ok_rfid_1 = "e199312d";
String ok_rfid_2 = "fbecb673";
int switch1 = 7; // Card
int switch2 = 7; // KeyFob
int BlueCom; // Bluetooth Command.
int Thing = 8; // Pin Connection
 
void setup() {
 
  Serial.begin(9600);
  while (!Serial);
  SPI.begin(); // Start SPI bus
  pinMode(Thing, OUTPUT); // Pin Output
  pinMode(switch1, OUTPUT); 
  pinMode(switch2, OUTPUT); // KeyFob Shutdown_cmd
 
 
}
void dump_byte_array(byte *buffer, byte bufferSize) {
  read_rfid = "";
  for (byte i = 0; i < bufferSize; i++) {
    read_rfid = read_rfid + String(buffer[i], HEX);
  }
}
 
void On_Switch() {
  digitalWrite(switch1, HIGH);
  delay(1000);
  digitalWrite(switch1, LOW);
}
 
void Off_Switch() {
  digitalWrite(switch2, HIGH);
  delay(5000);
  digitalWrite(switch2, LOW);
}
 
void BlueOn() {
 
  digitalWrite(Thing, HIGH);
  mfrc522.PCD_Init();
}
 
void BlueOff() {
 
  digitalWrite(Thing, LOW);
  mfrc522.PCD_Reset();
}
 
void loop() {
 
  while (Serial.available()) {
    BlueCom = Serial.read();
    Serial.println(BlueCom);
    {
 
      if (BlueCom == 1)
        BlueOn();
    }
    {
 
      if (BlueCom == 0)
        BlueOff();
    }
  }
 
  // Looks for cards
  if (!mfrc522.PICC_IsNewCardPresent())
    return;
 
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
    return;
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
 
  Serial.println(read_rfid);
  if (read_rfid == ok_rfid_1) {
    digitalWrite(switch1, HIGH);
    delay(1000);
    digitalWrite(switch1, LOW);
  }
  Serial.println(read_rfid);
  if (read_rfid == ok_rfid_2) {
    digitalWrite(switch2, HIGH);
    delay(5000);
    digitalWrite(switch2, LOW);
  }
}
