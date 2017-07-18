#include <SPI.h>
#include <RH_RF95.h>

/* for feather32u4 */
#define RFM95_CS  10   // "B"
#define RFM95_RST 11   // "A"
#define RFM95_INT  6   // "D"
#define VBATPIN A9  //  Pin where you can measure the battery power 
#define RF95_FREQ 868.0

#define packetLength 6  // n. byte del payload

byte ECHO = 1;


byte radiopacket[packetLength];
word vbatTX = 0;
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf);
int conta = 0;

////////////////////////////////////////////////////////
word  npacket =     0;
int   nletture =    0;
float Vout =        0;
/////////////////////////////////////////////////////////////////////

RH_RF95 rf95(RFM95_CS, RFM95_INT);


void initradio() {
  pinMode(RFM95_RST, OUTPUT);  // equivale al tasto del reset
  digitalWrite(RFM95_RST, HIGH);
  if (ECHO) {
   // while (!Serial);
    Serial.begin(9600);
    delay(100);
    Serial.println(" feather_TX_Celle.ino ");
  }

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    if (ECHO) {
      Serial.println("LoRa radio init failed");
    }
  }

  if (ECHO) {
    Serial.println("LoRa radio init OK!");
  }

  // Set frequency. Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  rf95.setFrequency(RF95_FREQ);

  if (ECHO) {
    Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  }

  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:

  rf95.setTxPower(23, false);
}

void sendData() {
  //  Trasferisce i dati nel buffer di trasmissione
  radiopacket[0]  = highByte(ID);
  radiopacket[1]  = lowByte(ID);
  radiopacket[2]  = highByte(vbatTX);
  radiopacket[3]  = lowByte(vbatTX);
  radiopacket[4]  = highByte(npacket);
  radiopacket[5]  = lowByte(npacket);


  if (ECHO) {
    Serial.println("Sending...");
  }
  rf95.send((uint8_t *)radiopacket, packetLength);
  delay(10);
  if (ECHO) {
    Serial.println("Waiting for packet to complete...");
  }
  rf95.waitPacketSent();
  if (ECHO) {
    Serial.println(" packet complete ");
  }


}

boolean receiveData() {
  boolean received = false;
  //azzera buffer messaggio ricevuto
  for (int i = 0; i < RH_RF95_MAX_MESSAGE_LEN; i++) {
    buf[i] = 0;
  }
  //  ascolta risposta

  if (rf95.available()) {

    // Should be a message for us now
    len = sizeof(buf);
    if (rf95.recv(buf, &len)) {

      if (ECHO) {
        Serial.println();
        Serial.println();
        RH_RF95::printBuffer("Received: ", buf, len);
      }

      word ID_msg_sender = word(buf[0], buf[1]);

      if (ECHO) {
        Serial.print(" Ricevuto messaggio di "); Serial.print(len); Serial.print(" Byte da:");
        Serial.print(" ID_TX "); Serial.println(ID_msg_sender);
        Serial.println();
        Serial.print(" RSSI: ");
        Serial.println(rf95.lastRssi(), DEC);
      }
      if (ID_msg_sender == ID_RX) {
        // spegne il LED verde
        received = true;
      }
      npacket++;
    }
  }
  return (received);
}

