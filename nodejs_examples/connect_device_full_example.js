// Get help from Kakopappa's Sinric repository

const WebSocket = require('ws');
const token = 'Your api key from webservice.lk';
const device_id = '8xxxxxxxxxxxxxxxxxxxxxx';
const options = {
  headers: {
    // needs node.js version >= 5.10.0 for this to work as Buffer.from() is added at that milestone!
    'Authorization': Buffer.from('apikey:' + token).toString('base64');
  }
}

const ws = new WebSocket('ws://webservice.lk:8080', options);

ws.on('open', function open () {
  console.log('Connected with webservice.lk. waiting for commands..');
})

ws.on('message', function incoming (data) {
  console.log(data);
  var jsonData = JSON.parse(data)
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

