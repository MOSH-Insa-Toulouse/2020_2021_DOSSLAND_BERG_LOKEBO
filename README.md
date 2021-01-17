# Smart Devices training unit
# 2020-2021 Catherine Berg, Njord Løkebø, Hermund Døssland

## This repository is split in three parts: KiCAD project, Arduino project and LTSpice lab work.

## Attachements
- Arduino project (LoRa_piste_rouge_v_final)
- KiCAD project (arduino_shield)
- LTSpice lab work

## Arduino project - LoRa communication with TTN

## Part LTSpice

The stage is composed of several filters and an operational amplifier. We used LTSpice to simulate the analog circuit.

- [ ] figure of the schema 

#### Question 1: check the operation in nominal conditions
Normally, the circuit amplifies with a gain of 100.
#### Question 2:  is the impact of the LTC1050C amplifier offset acceptable ?
The input offset is 0.5mv, with our gain of 100, the offset of output 50mv which make 1 digit error in the 12 bits ADC.
#### Question 3:  is the impact of the amplifier input current acceptable ?
With the data sheet of ltc1050, we got that the input noise current is 1.8fA/sqrt(HZ). So with a signal of 1KHz, we have an error of 5.6E-14 << 1E-9 

#### Question 4:  what is the cutoff frequency of each low-pass filter stage?
stage 1: 15.9Hz
stage 2: 1.59Hz
stage 3: 1.59KHz
#### Question 5 : What is the global attenuation of a 50 Hz current noise ?
The global attenuation equals to 40 dB of 50Hz current noise.

#### Question 6 : What is the global attenuation of a current noise occurring at the aliasing limit frequency (in the case of Arduino Uno ADC) ?
For a 16MHz Arduino, the ADC clock is set to 16MHz/128=125KHz. Each conversion takes 13 ADC clocks so 125KHz/13 = 9615Hz. At this frequency, we have an attenuation of 115 dB.


