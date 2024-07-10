#line 1 "C:\\Users\\robbi\\repos\\firFiltering\\README.md"
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

## Analysising Signal through SNR (Signal Noise Ratio)

Calculate SNR of an EMG signal using three steps:

1. Determine the Signal Power (P_signal)
  * estimated by computing average power of the signal over a time interval or frequency band. Involves squaring the signal amplitude and averaging over a choosen period
  * Mathematically x(t) represents the EMG signal: where T is the duration of the signal over which you are averaging
> $`Psignal​\=T1​∫0T​∣x(t)∣2dt`$
2. Determine the Noise Power (P_noise)
  * Noise comes from electrical interference, ambient noise, motion artifact, inherent instability of signal, etc
  * estimate noise power by measuring it during periods where no EMG activity is present (assuming such a period exists and is noise dominated)
  * Mathematically n(t) represents the noise component
> $`Pnoise​\=T1​∫0T​∣n(t)∣2dt`$
3. Calculate SNR
  * Once you have P_signal and P_noise you can caluculate SNR
> $`SNR\=10log10​(Pnoise​Psignal​​)`$
  * This gives you SNR in decibels (dB)

### Practical Considerations

* signal and noise power are averaged over about the same time interval
* the proper preprocessing is necessary