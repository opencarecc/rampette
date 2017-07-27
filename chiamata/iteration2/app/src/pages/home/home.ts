import { Component, NgZone } from '@angular/core';
import { NavController, Platform, Events, AlertController } from 'ionic-angular';


// plugins
import { LocalNotifications } from '@ionic-native/local-notifications';
import { BackgroundMode } from '@ionic-native/background-mode';
import { BLE } from 'ionic-native';

// providers
import { BeaconProvider } from '../../providers/beacon-provider';
import { BleProvider } from '../../providers/ble-provider';
import { PlacesDataProvider } from '../../providers/places-data/places-data';

// models
import { BeaconModel } from '../../models/beacon-model';


@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {
  beacons: BeaconModel[] = [];
  zone: any;
  connected: boolean =false;
  device: any;
  debug:boolean=false;
  beaconStatus:number=0; //0=disconnected, 1=connected and calling, 2=callreceived
  shops=[];
  nearbyshops=[];
  indexConnectedDevice:number=0;


  constructor(public navCtrl: NavController,
    public platform: Platform,
    public beaconProvider: BeaconProvider,
    public events: Events,
    private LocalNotifications: LocalNotifications,
    private backgroundMode: BackgroundMode,
    private bleProvider: BleProvider,
    public places:PlacesDataProvider,
    public alertCtrl: AlertController

  ) {

    // required for UI update
    this.zone = new NgZone({ enableLongStackTrace: false });
  }

  ionViewDidLoad() {
    this.places.load().then(data=>{
      console.log(data.shops);
      this.shops=data.shops;
    })

    this.platform.ready().then(() => {
      if (BLE.isEnabled) {
        BLE.enable();
      }
      this.bleProvider.checkConnection();

      this.beaconProvider.initialise().then((isInitialised) => {
        if (isInitialised) {
          this.listenToBeaconEvents();
          this.backgroundMode.setDefaults({ silent: true });
          this.backgroundMode.enable();
        }
      });
      this.listenToBleEvents();
    });
  }

  listenToBeaconEvents() {
    this.events.subscribe('didRangeBeaconsInRegion', (data) => {

      // update the UI with the beacon list
      this.zone.run(() => {

        //this.beacons = [];

        let beaconList = data.beacons;

        this.beacons.forEach((beacon) => {
          for (var i = 0; i < this.beacons.length; i++) {
            //for each element already present in the array check if I need to remove any that doesn't exist in the new list
            var indexInArray = this.findWithAttr(beaconList, 'minor', beacon.minor);

            if (indexInArray == -1) { //the device is not in the new list
              this.beacons.splice(indexInArray, 1);
            }
          }

        });

        beaconList.forEach((beacon) => {

          //check if a device with the same minor is present in the array
          var indexInArray = this.findWithAttr(this.beacons, 'minor', beacon.minor);

          //if there is not I notify that we have a new device in range
          if (indexInArray == -1) {

            let beaconObject = new BeaconModel(beacon);

            this.LocalNotifications.schedule({
              id: beaconObject.minor,
              text: 'open rampetta nelle vicinanze',
              icon: 'http://example.com/icon.png'
            });

            this.beacons.push(beaconObject);

            //else I just update rssi
          } else {
            this.beacons[indexInArray].rssi = beacon.rssi;
          }
        });

        this.nearbyshops=[];//empty the shops array
        for (var i=0; i<this.beacons.length;i++){
          for(var j=0; j<this.shops.length; j++){

            //console.log(this.beacons[i].minor);
            //console.log(this.shops[j].minor_ID);

            if (this.beacons[i].minor==this.shops[j].minor_ID){
              this.nearbyshops.push(this.shops[j]);
              //console.log(this.nearbyshops);
            }
          }
        }


      });
    });
  }

  connect(index){
    if (this.bleProvider.deviceID==null){
      this.bleProvider.scanDevices().then((device) => {
        console.log(JSON.stringify(device));

        //i think we need to check here if we are connectin to the right device
      //  this.bleProvider.connect(this.nearbyshops[index].mac_address).then((device)=>{

        this.bleProvider.connect(device.id).then((device)=>{
          this.indexConnectedDevice=index;

          console.log(JSON.stringify(device));

          this.bleProvider.registerToEvents();
          this.connected=true;
          this.device=device;
          this.bleProvider.callBell();
          this.beaconStatus=1;
        });
      });
    }
  }

  listenToBleEvents(){
    this.events.subscribe('bleDisconnected', (data) => {
      console.log("ble disconnected", data);

      this.beaconStatus=0;
      this.connected=false;

    });

    this.events.subscribe('characteristicUpdated', (data) => {
      console.log("characteristic Updated", data);
      this.beaconStatus=data;

      if (this.beaconStatus==2){
        this.doAlert();
      }
    });
  }

  // checkConnection(){
  //   this.bleProvider.checkConnection();
  // }
  // scan(){
  //   this.bleProvider.scanDevices();
  // }

  doAlert() {
    let alert = this.alertCtrl.create({
      title: 'Chiamata ricevuta',
      message: 'stai per ricevere assistenza.',
      buttons: [
        {
          text: 'OK',
          handler: data => {
            console.log('back to begin');
            this.resetToHome();
          }
        }
      ]
    });
    alert.present();
  }

  resetToHome(){
    this.bleProvider.askForDisconnect();
    //this.bleProvider.disconnect();
     this.connected=false;
     this.beaconStatus=0; //0=disconnected, 1=connected and calling, 2=callreceived
     this.indexConnectedDevice=0;
  }


  findWithAttr(array, attr, value) {
    for (var i = 0; i < array.length; i += 1) {
      if (array[i][attr] === value) {
        return i;
      }
    }
    return -1;
  }

}
