#define FACTORYRESET_ENABLE      1

#define MANUFACTURER_APPLE         "0x004C"
#define MANUFACTURER_NORDIC        "0x0059"

#define BEACON_MANUFACTURER_ID     MANUFACTURER_APPLE
#define BEACON_UUID                "A1-96-C8-76-DE-8C-4C-47-AB-5A-D7-AF-D5-AE-71-27"

#define BEACON_RSSI_1M             "-54"

#define SERVICE_UUID               "A1-96-C8-76-DE-8C-4C-47-AB-5A-D7-AF-D5-AE-71-26"

#define CALL_CHARACTERISTIC_UUID   "A1-96-C8-76-DE-8C-4C-47-AB-5A-D7-AF-D5-AE-71-28"

#define MINIMUM_FIRMWARE_VERSION   "0.7.0"




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

  /* Set callbacks */
  ble.setConnectCallback(BLE_connected_callback);
  ble.setDisconnectCallback(BLE_disconnected_callback);
  ble.setBleGattRxCallback(charid_number, BleGattRX_callback);

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


  //AT+GATTADDCHAR=UUID128=A1-96-C8-76-DE-8C-4C-47-AB-5A-D7-AF-D5-AE-71-28,PROPERTIES=0x10,MIN_LEN=1,VALUE=0
  ble.print("AT+GATTADDCHAR="       );
  ble.print("UUID128="              );
  ble.print(CALL_CHARACTERISTIC_UUID); ble.print(',');
  ble.print("PROPERTIES="           );
  ble.print("0x08"                  ); ble.print(','); //set to notify
  ble.print("MIN_LEN=1"             ); ble.print(',');
  ble.print("VALUE=1"             ); //set to notify
  ble.println();
  ble.waitForOK();

}

void getGATTList() {
  ble.print("AT+GATTLIST"   );
  ble.println();
  ble.waitForOK();
}

void readCharacteristic(int id) {
  ble.print("AT+GATTCHAR="   );
  ble.print(id);
  ble.println();
  ble.waitForOK();
}

void writeCharacteristic(int id, int val) {
  ble.print("AT+GATTCHAR="   );
  ble.print(id);
  ble.print(",");
  ble.print(val);
  ble.println();
  ble.waitForOK();
}


void BleGattRX_callback(int32_t chars_id, uint8_t data[], uint16_t len)
{
  Serial.print( F("[BLE GATT RX] (" ) );
  Serial.print(chars_id);
  Serial.print(") ");

  if (chars_id == charid_string)
  {
    Serial.write(data, len);
    Serial.println();
  } else if (chars_id == charid_number)
  {
    int32_t val;
    memcpy(&val, data, len);
    Serial.println(val);
  }
}

void disconnect(){
  
}




