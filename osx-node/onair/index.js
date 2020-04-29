var exec = require('child_process').exec;
var sleep = require('system-sleep');
var child,child1,child2;
var command = "/usr/local/bin/do-not-disturb status";
var mqttCommand_on = "mosquitto_pub -t onair1/status -m \"1\" -d -h tank";
var mqttCommand_off = "mosquitto_pub -t onair1/status -m \"0\" -d -h tank";

while(true){
   child = exec(command,
      function (error, stdout, stderr) {
         if (error !== null) {
            console.log('exec error: ' + error);
         } else {
            if(stdout.startsWith("on")){
               child1 = exec(mqttCommand_on,
                  function (error, stdout, stderr) {
                     //console.log("Sign Turned On");
                  }
               );
            } else {
               child2 = exec(mqttCommand_off,
                  function (error, stdout, stderr) {
                     //console.log("Sign Turned Off");
                  }
               );
            }
         }
      });
      sleep(5*1000); // sleep for 10 seconds
}


