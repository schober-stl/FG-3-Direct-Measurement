FG-3-Direct-Measurement.
High-precision measurements using Teensy 4.0 and FG-3+ fluxgate magnetometer sensors.
This project uses a Teeny 4.0 https://www.pjrc.com/ and 2 FG-3+ fluxgate magnetometers from https://www.fgsensors.com/.
Must cut the trace that connects Vin to USB on Teensy 4.0 so powered by linear regulator circuit https://www.pjrc.com/store/teensy40.html.
The Teensy 4.0 and Fg-3+ sensors are powered by the linear regulator circuit in https://www.fgsensors.com/_files/ugd/7034a0_c59536c9022b4a5798fcc6045dcf6841.pdf.
Must use a logic leveler to convert FG3+ signal from 5.0 V to 3.3 V before connecting to pins on Teensy (pins are not 5.0 V tolerant).
Uses Interrupts to get pulse duration for both pins 6 and 9.
MainPeriod controls speed versus precision.
