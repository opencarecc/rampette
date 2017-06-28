#include <Arduino.h>
#include <SPI.h>

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#define FACTORYRESET_ENABLE      1

#define MANUFACTURER_APPLE         "0x004C"
#define MANUFACTURER_NORDIC        "0x0059"

#define BEACON_MANUFACTURER_ID     MANUFACTURER_APPLE
#define BEACON_UUID                "A1-96-C8-76-DE-8C-4C-47-AB-5A-D7-AF-D5-AE-71-27"
#define BEACON_MAJOR               "0x0000"
#define BEACON_MINOR               "0x0001"
#define BEACON_RSSI_1M             "-54"

#define SERVICE_UUID               "A1-96-C8-76-DE-8C-4C-47-AB-5A-D7-AF-D5-AE-71-26"

#define CALL_CHARACTERISTIC_UUID   "A1-96-C8-76-DE-8C-4C-47-AB-5A-D7-AF-D5-AE-71-28"

#define LOCAL_NAME                 "vineriaMinerva"

#define MINIMUM_FIRMWARE_VERSION   "0.7.0"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


void setup(void) {
  //while (!Serial);  // required for Flora & Micro
  delay(500);
  Serial.begin(115200);
  initBluetooth();


  /* Set callbacks */
  ble.setConnectCallback(connected);
  ble.setDisconnectCallback(disconnected);
  ble.setBleGattRxCallback(1, BleGattRX);

  setupBeacon();

  setupGatt();
}

void loop(void) {
}

void initBluetooth() {
  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));
  if ( !ble.begin(VERBOSE_MODE) ) {
    Serial.println(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }

  Serial.println(F("Performing a factory reset: "));
  if ( ! ble.factoryReset() ) {
    Serial.println(F("Couldn't factory reset"));
  }

  ble.echo(true);

  ble.print("AT+GAPDEVNAME="        );
  ble.print(LOCAL_NAME               );
  ble.println();

  //ble.println("ATZ");

  Serial.println("Requesting Bluefruit info:");
  ble.info();
  ble.waitForOK();

  ble.print("AT+GATTCLEAR");
  ble.println();
  ble.waitForOK();

  if ( !ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) ) {
    Serial.println( F("Callback requires at least 0.7.0") );
  }

}

void setupBeacon() {
  Serial.println(F("Setting beacon configuration details: "));
  // AT+BLEBEACON=0x004C,01-12-23-34-45-56-67-78-89-9A-AB-BC-CD-DE-EF-F0,0x0000,0x0000,-54
  ble.print("AT+BLEBEACON="        );
  ble.print(BEACON_MANUFACTURER_ID ); ble.print(',');
  ble.print(BEACON_UUID            ); ble.print(',');
  ble.print(BEACON_MAJOR           ); ble.print(',');
  ble.print(BEACON_MINOR           ); ble.print(',');
  ble.print(BEACON_RSSI_1M         );
  ble.println(); // print line causes the command to execute
  ble.waitForOK();

}

void setupGatt() {

  //AT+GATTADDSERVICE=UUID128=00-11-00-11-44-55-66-77-88-99-AA-BB-CC-DD-EE-FF
  ble.print("AT+GATTADDSERVICE="   );
  ble.print("UUID128="             );
  ble.print(SERVICE_UUID);
  ble.println();
  ble.waitForOK();

  //AT+GATTADDCHAR=UUID128=A1-96-C8-76-DE-8C-4C-47-AB-5A-D7-AF-D5-AE-71-28,PROPERTIES=0x10,MIN_LEN=1,VALUE=0
  ble.print("AT+GATTADDCHAR="       );
  ble.print("UUID128="              );
  ble.print(CALL_CHARACTERISTIC_UUID); ble.print(',');
  ble.print("PROPERTIES="           );
  ble.print("0x10"                  ); ble.print(','); //set to notify
  ble.print("MIN_LEN=1"             ); ble.print(',');
  ble.print("VALUE=1"             ); //set to notify
  ble.println();
  ble.waitForOK();

}

void BleGattRX(int32_t chars_id, uint8_t data[], uint16_t len) {
  Serial.print( F("[BLE GATT RX] (" ) );
  Serial.print(chars_id);
  Serial.print(") ");



    int32_t val;
    memcpy(&val, data, len);
    Serial.println(val);
  
}

void connected(void) {
  Serial.println( F("Connected") );
}

void disconnected(void) {
  Serial.println( F("Disconnected") );
}
