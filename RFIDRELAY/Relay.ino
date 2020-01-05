#include <SPI.h>
#include <MFRC522.h>
 
#define RST_PIN 9
#define SS_PIN 10 
 
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 Stand
 
String read_rfid; // Add UID
String ok_rfid_1="e199312d"; // 0-RFID Card
String ok_rfid_2="fbecb673"; // RFID Keyfob
int lock = 7; // Card
int lock2 = 7; // KeyFob

void setup() {
    Serial.begin(9600); // Initialize serial communications
    while (!Serial); // No serial port is open
    SPI.begin(); // Start SPI bus
    mfrc522.PCD_Init(); // Start MFRC522 card
 
    //Choose which lock below:
    pinMode(lock, OUTPUT);
    pinMode(lock2, OUTPUT);
}
// Dumps byte array as hex values
void dump_byte_array(byte *buffer, byte bufferSize) {
    read_rfid="";
    for (byte i = 0; i < bufferSize; i++) {
        read_rfid=read_rfid + String(buffer[i], HEX);
    }
}
 
void open_lock() {
// Relays and Solenoids
  digitalWrite(lock,HIGH);
  delay(500);
  digitalWrite(lock,LOW);
}
 
void close_lock2() {
  digitalWrite(lock2, HIGH);
  delay(5000);                
  digitalWrite(lock2,LOW);
}

void loop() {
      // New cards
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;
 
    // Selects cards
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;
 
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println(read_rfid);
    if (read_rfid==ok_rfid_1) {
      //ok, open the door.
      open_lock();
    }
 
    Serial.println(read_rfid);
    if (read_rfid==ok_rfid_2) {
      //ok, open the door.
      close_lock2();
    }
    // Add IDs if you choose
    //if (read_rfid==run_rfid_1) {
      //also ok, open the door
    //  open_lock();
    //}
}
