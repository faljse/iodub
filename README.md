# iodub

Im in the process of renovating my family home and chose controllino as my home automation device.
- light switches are running on 24V/AI on controllino (https://oshwlab.com/martin.michael.kunz/switchpcb)
- lights are connected to relay on [controllino](https://www.controllino.biz/controllino-mega/)
 DO
- light switches are pushbuttons
- Multiple control cabinets (˜4) will be distributed around the house to keep cable lengths manageable
- controllinos will be connected to nodered to handle smart stuff.
- Regular light switching should work without network, mqtt, respberry etc.
...must be handled within controllino.

# Pushbuttons
[switchpcb](https://oshwlab.com/martin.michael.kunz/switchpcb)

<img width="554" alt="taster" src="https://user-images.githubusercontent.com/2340120/129244999-eae08bbc-dc60-44b1-a780-4484b0077b1c.PNG">

# Configuration 
[webdub](https://github.com/faljse/webdub) transpiles config.json to c. 


# Additional things id like to implement:
- Multiway switching
- Time switch
- Long-Press/Double click detection (e.g. for a panic or all-off function)

