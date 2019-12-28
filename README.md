# HVAC Monitor

The HVAC monitor is a PCB that was designed to monitor various aspects of a forced air HVAC system.
The system is capable of monitoring the following:

- System State - There are three inputs for heat, cool and fan. The inputs are designed for 24VAC, which is the common control voltage for HVAV systems.
- Differential Pressure - There are provisions for two diferential pressure sensors (Sensirion SDP810-500PA). The initial thought was that these sensors would provide a good way of deterministically knowing if the filters need to be changed.
- Temperature Sensors - There are three MAX31856 IC's on the board for reading thermocouple sensors. The MAX31856 can handle types K, J, N, R, S, T, E, and B thermocouples. 
- Water Detect - There are two inputs for detection of water. This was implmented so that water in the supply plenum or in a drip pan could be detected. This is done by a simple transistor circuit.

System control is accomplished by an ESP32, on a Adafruit HUZZAH32. Power for the system is derived through the HUZZAH32's USB connection.
