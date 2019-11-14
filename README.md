# iodub

Im in the process of renovating my family home and chose controllino as my home automation device.
- light switches are running on 24V/DI on controllino
- lights are connected to relay on controllino DO
- light switches are pushbuttons
- Multiple control cabinets (˜4) will be distributed around the house to keep cable lengths manageable
- controllinos will be connected to a mqtt broker to handle smart stuff.
- Regular light switching should work without network, mqtt, respberry etc.
...must be handled within controllino.

# Configuration 
```c
Light lights[] = {
 Light(false, CONTROLLINO_A0, CONTROLLINO_DO0, "lampe1"),
 Light(false, CONTROLLINO_A1, CONTROLLINO_DO1, "lampe2") 
};
//lamp is off by default, A0 is control input, DO0 is relay out, 
// mqtt topic will be cmnd/lampe1/power and stat/lampe1/POWER
```
It already works up to this point.


# Additional things id like to implement:
- Multiway switching
- Time switch
- Long-Press/Double click detection (e.g. for a panic or all-off function)

