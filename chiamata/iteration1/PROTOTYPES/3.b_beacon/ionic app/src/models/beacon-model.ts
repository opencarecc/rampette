export class BeaconModel {

  uuid: string;
  major: number;
  minor: number;
  rssi: number;
  notified: boolean;

  constructor(public beacon: any) {
    this.uuid = beacon.uuid;
    this.major = beacon.major;
    this.minor = beacon.minor;
    this.rssi = beacon.rssi;
    this.notified=false;
  }

  setNotified(status:boolean){
    this.notified=status;
  }
}
