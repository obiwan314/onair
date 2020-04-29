# onair
Project to build a WIFI &amp; MQTT controlled on Air Sign

This project is based on a 3D model from Thingaverse which can be found [here.](https://www.thingiverse.com/thing:2847029)

My version uses an [Adafruit Feather Huzza](https://www.adafruit.com/product/2821) flashed to act like an Ardiino with build in Wifi.
It also uses a [500mAh LiPo Battery](https://www.adafruit.com/product/1578) because there never seems to be an outlet where I want to hang this sign. This part is optional if you plan to plug in USB Power.
It also requires a [Neopixel Strip](https://www.adafruit.com/product/1376?length=1)

![Finished Product](https://github.com/obiwan314/onair/blob/master/images/IMG_6416.jpg?raw=true "Picture of Finished product")
![Open Case](https://github.com/obiwan314/onair/blob/master/images/IMG_6405.jpg?raw=true "Inside view showing wiring.")
![Inside Front View](https://github.com/obiwan314/onair/blob/master/images/IMG_6406.jpg?raw=true "Inside front of case showing red plastic filter")

The Neo Pixel Strip is connected as shown below:

    Feather          Neopixel Strip
    GND ------------- GND
    USB ------------- 5V+
    13  ------------- Din

The grey wire is canabalized IDE cable ribbon wire and all the components are just hot glued down inside the case.

The OSX client requires the building and installing of a command line tool [do-not-disturb-cli](https://travis-ci.org/sindresorhus/do-not-disturb-cli)

It also requires the installtion of [Mosquito MQTT](https://mosquitto.org/) so that the mosquitto_pub command is available.

The arduino script must be modified to add your wifi credentials and MQTT server.

Here is a video demonstration
![Demo Video](https://github.com/obiwan314/onair/blob/master/images/IMG_6417.MOV?raw=true "Demo Video")