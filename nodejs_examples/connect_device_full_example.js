// Get help from Kakopappa's Sinric repository

const WebSocket = require('ws');
const token = 'Your api key from iot.webservice.lk';
const device_id = 'Your device id fro iot.webservice.lk';

const ws = new WebSocket('ws://'+token+':'+device_id+'@iot.webservice.lk:8080');

ws.on('open', function open () {
  console.log('Connected with iot.webservice.lk. waiting for commands..');
})

ws.on('message', function incoming (data) {
  console.log(data);
  var jsonData = JSON.parse(data)
  console.log(jsonData);
  if (jsonData.deviceId === device_id) {
    if (jsonData.action === 'setPowerState') {
      // command: "Ok Google turn on MY_DEVICE"
      // {"deviceId":"8xxxxxxxxxxxxxxxxxxxxxx","action":"setPowerState","value":"ON"}
      // command: "Ok Google turn off MY_DEVICE"
      // {"deviceId":"8xxxxxxxxxxxxxxxxxxxxxx","action":"setPowerState","value":"OFF"}
      if (jsonData.value === 'ON') {
	       // here you can handle signal sending to your hadware (A Relay or Something)
        console.log('Turning ON MY_DEVICE...');
      } else {
	       // here you can handle signal sending to your hadware (A Relay or Something)
        console.log('Turning OFF MY_DEVICE...');
      }
    } 
  }
})

