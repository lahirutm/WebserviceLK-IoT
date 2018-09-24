// Get help from Kakopappa's Sinric repository

const WebSocket = require('ws');
const token = "Your api key from webservice.lk";

const options = {
    headers: {
        "Authorization" : Buffer.from("apikey:" + token).toString('base64')
    }
};

const ws = new WebSocket('ws://webservice.lk:8080', options);
 
ws.on('open', function open() {
   console.log("Connected with WebserviceLK. waiting for commands..");
});

ws.on('message', function incoming(data) {
   console.log("Request : " + data);
   let jsonObj = JSON.parse(data);

   if(jsonObj.action == "setPowerState") {
       if(jsonObj.value === "ON") {
           console.log("Turn on device");
       } else {
           console.log("Turn off device");
       } 
   }

});
