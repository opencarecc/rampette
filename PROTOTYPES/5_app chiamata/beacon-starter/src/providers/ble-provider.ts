import { Injectable } from '@angular/core';
import { Platform, Events } from 'ionic-angular';
import { BLE } from 'ionic-native';
/*
Generated class for the BeaconProvider provider.

See https://angular.io/docs/ts/latest/guide/dependency-injection.html
for more info on providers and Angular 2 DI.
*/
@Injectable()
export class BleProvider {

  deviceID: any;
  deviceName:null;
  isConnected: boolean;

  beacon_service_UUID = "a196c876-de8c-4c47-ab5a-d7afd5ae7127";
  call_service_UUID = "a196c876-de8c-4c47-ab5a-d7afd5ae7126";
  callCharacteristic_UUID = "a196c876-de8c-4c47-ab5a-d7afd5ae7128";
  UUID_NO_DASH = ""

  constructor(public platform: Platform, public events: Events) {
    this.UUID_NO_DASH = this.beacon_service_UUID.replace(/-/g, "");
  }



  scanDevices(): Promise<any> {
    return new Promise((resolve, reject) => {
      BLE.scan([], 4).subscribe(
        device => {
          var adData = new Uint8Array(device.advertising);
          var advertisingUUID = this.buf2hex(adData.slice(9, 25));
          if (advertisingUUID == this.UUID_NO_DASH) {
            this.deviceID = device.id;
            this.connect(this.deviceID);
            resolve(device);
          }
        },
        error => {
          console.log(error);
          reject(error);
        });
    });
  }

  buf2hex(byteArray) { // buffer is an ArrayBuffer
    return Array.prototype.map.call(byteArray, x => ('00' + x.toString(16)).slice(-2)).join('');
  }
  ionViewDidLoad() {
    console.log('ionViewDidLoad SingleDevicePage');
  }


  connect(deviceID): Promise<any> {
    return new Promise((resolve, reject) => {
      BLE.connect(deviceID).subscribe(
        device => {
          console.log(JSON.stringify(device));
          this.deviceName = device.name;
          this.checkConnection();
          resolve(device);
        },
        error => {
          reject()
        }
      )
    });
  }


  checkConnection(): Promise<any> {
    return new Promise((resolve, reject) => {

      BLE.isConnected(this.deviceID)
        .then(() => {
          console.log("connected")
          this.isConnected = true;
          resolve(this.isConnected);
        }, () => {
          console.log("disconnected")
          this.isConnected = false;
          reject(this.isConnected);
        });
    });
  }

  callBell() {
    var bell = new Uint8Array(1);
    bell[0] = 1;

    BLE.write(this.deviceID, this.call_service_UUID, this.callCharacteristic_UUID, bell.buffer)
      .then((response) => {
        console.log(response);
      }, (error) => {
        console.log(error);
      });
  }

  registerToEvents() {
    BLE.startNotification(this.deviceID, this.call_service_UUID, this.callCharacteristic_UUID).subscribe(value => {

      var adData = new Uint8Array(value);
      console.log(adData);

      BLE.read(this.deviceID, this.call_service_UUID, this.callCharacteristic_UUID).then((data)=>{
        console.log(data);
        this.events.publish('characteristicUpdated', data);
      });
    });
  }

}
