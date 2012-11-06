XBees
=====

Zigbee communication for one XBee to another

The Idea is to have one XBee connected to an Arduino and one that is not connected to any additional microcontroller. Then we whant to remotely controll the Digital Input and Output pins of the second XBee via commands. 

First we need to configure the first XBee as a Coordinator API. Delivering I/O data to the router radio is available only in API mode. Unfortunately we can do this only using the X-CTU tool by Digi. If you know a way to do it through the terminal, please write me!!! :)

Then we need to configure the second XBee as a Router AT and upload the Arduino code.

There is one thing that seems to be not quite right - there is a certain delay between the time you send the meesgae to the roter to set the D1 pin of the router XBee to HIGH and the time it actualy goes to HIGH. I'm still trying to figure it out but I guess it has to do with the XBee API?

[Here is more detailed look into the above few sentences I just wrote]( http://www.agilart.com/blog/using-xbee-and-wireless-communication)
