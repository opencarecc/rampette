#include <SPI.h>
#include <BLEPeripheral.h>
#include <iBeacon.h>

#if !defined(NRF51) && !defined(NRF52) && !defined(__RFduino__)
#error "This example only works with nRF51 boards"
#endif

char* beaconserviceUUID = "a196c876-de8c-4c47-ab5a-d7afd5ae7127";
char* serviceUUID = "a196c876-de8c-4c47-ab5a-d7afd5ae7126";
char* callCharacteristicUUID = "a196c876-de8c-4c47-ab5a-d7afd5ae7128";

char* localName = "vineriaMinerva";
unsigned short major         = 0;
unsigned short minor         = 1;
unsigned short measuredPower = -55;

int state = 0;
int oldState=0;

BLEPeripheral blePeripheral = BLEPeripheral();

BLEService doorBellService = BLEService(serviceUUID);

BLEIntCharacteristic callCharacteristic = BLEIntCharacteristic(callCharacteristicUUID,  BLERead | BLEWrite | BLENotify);

iBeacon beacon;

int buttonAState = 1;
int oldbuttonAState = 1;

int buttonBState = 1;
int oldbuttonBState = 1;


void setup() {
  Serial.begin (9600);
  beacon.setConnectable(true);

  beacon.setLocalName(localName);
  beacon.addAttribute(doorBellService);
  beacon.addAttribute(callCharacteristic);

  // assign event handlers for connected, disconnected to peripheral
  beacon.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  beacon.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handlers for characteristic
  callCharacteristic.setEventHandler(BLEWritten, characteristicWritten);

  beacon.begin(beaconserviceUUID, major, minor, measuredPower);
  pinMode(PIN_BUTTON_A, INPUT_PULLUP);
  pinMode(PIN_BUTTON_B, INPUT_PULLUP);

}

void loop() {
  beacon.loop();

  printState();

  if  (readButtonB()){
    state=0;
    beacon.disconnect();
  }
  
  switch (state) {
    case 0:
      
      break;
    case 1:
      
      break;
    case 2:
      if (readButtonA()) {
        state = 3;
        Serial.println("ricevuto");
        notifyReceivedCall();
      }
      break;
    case 3:

      break;
  }
}

void printState(){
  if (oldState!=state){
    Serial.println(state);
  }
  oldState=state;
}

void blePeripheralConnectHandler(BLECentral& central) {
  // central connected event handler
  Serial.print(F("Connected event, central: "));
  Serial.println(central.address());
  state = 1;

}

void blePeripheralDisconnectHandler(BLECentral& central) {
  // central disconnected event handler
  Serial.print(F("Disconnected event, central: "));
  Serial.println(central.address());
  state = 0;
  Serial.println("waiting for someone");


}

void characteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // characteristic value written event handler
  Serial.print(F("Characteristic event, writen: "));
  Serial.println(callCharacteristic.value(), DEC);
  if (callCharacteristic.value()==1){
    state = 2;  
  }
}

boolean readButtonA() {
  buttonAState = digitalRead(PIN_BUTTON_A);
  int buttonReleased = false;
  if (buttonAState && !oldbuttonAState) {
    buttonReleased = true;
  } else {
    buttonReleased = false;
  }
  oldbuttonAState = buttonAState;
  return (buttonReleased);
}

boolean readButtonB() {
  buttonBState = digitalRead(PIN_BUTTON_B);
  int buttonReleased = false;
  if (buttonBState && !oldbuttonBState) {
    buttonReleased = true;
  } else {
    buttonReleased = false;
  }
  oldbuttonBState = buttonBState;
  return (buttonReleased);
}


void notifyReceivedCall(){
  callCharacteristic.setValue(2);
}



