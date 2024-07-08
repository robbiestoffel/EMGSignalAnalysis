# EMG Signal Anaylsis

Code for inputing a preamplified 0V-5V EMG signal on an Arudino, filtering and smoothing the signal, and measuring and comparing SNR.

## Preprocessing requirements

### Pre-Amplifier

Uses operational amplifiers (op-amps)

amplify like x100

### Band Pass Filter (High Pass + Low Pass)

Second Order Sallen-Key High pass filters

High Pass filter supplies:
* 1 op-amp
* 2 390k resistor
* 1 51k resistor
* 1 16k resistor
* 2 22nF capacitor

Low Pass filter supplies:

* 1 op-amp
* 2 68k resistor
* 1 51k resistor
* 1 24k resistor
* 2 3.3nF capacitor

### Second Stage Amplifier

Inverting Amplifier
amplify like x100 (again)

* 2k4 resistor
* 240k resistor

### Another Second-Order Low Pass Filter

Low Pass filter supplies:

* 1 op-amp
* 2 68k resistor
* 1 75k resistor
* 1 24k resistor
* 2 3.3nF capacitor

### ADC

Feed signal into analog Ardiuno port and convert the signal from analog to digital automatically. 

## Filtering

Using a moving average filter to average out the noisy signal.