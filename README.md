
# Baja Sensor Network
Baja sensor network developed to Bombaja UFSM

## The Purpose
**Baja SAE is a project developed by Automotive Engineering Society and has as main objective that engineering students
could apply on real life the knowledge acquired in universities and colleges.**
The engineering students must project and develop a mini baja prototype that attends the contest requirements, given by SAE.

**The competition have different phases, one theroretical**, when the students have to write a project report and present their car projects to contest judges (graduated engineers) and **one practical**, when the car is evaluated in different exams, each one aimed to stress one or more specific car parts. 

The last competition test is a **resistance race, where the car that executes more laps in the circuit wins the race.** </br>
The competition circuit have a lot of obstacles and its objective is to broke car parts. </br>
**Baja SAE competition is an endurance project and the students vehicles need to be prepared to overdue any obstacle.**

Bombaja UFSM is the team that carries **Federal University of Santa Maria name.** </br> 
The objective of this project is to **develop a sensor network to monitor the prototype in real time.**

## Development
The microcotroller used in project is a **XMEGA2560**. 

The Mega 2560 is a microcontroller board based on the ATmega2560. It has 54 digital input/output pins (of which 15 can be used as PWM outputs), 16 analog inputs, 4 UARTs (hardware serial ports), a 16 MHz crystal oscillator, a USB connection, a power jack, an ICSP header, and a reset button. </br>

It was used **Arduino IDE to develop software.** </br>
**It was chose Arduino platform because it has a big community, it is cheap and open source**.

The main project have the following sensors:

- **Fuel level** sensor
- **Temperature** sensor
- **Velocity** sensor
- **Motor Revolution per Minute (RPM)** sensor

In addition, it has a Real Time Clock (**RTC**), a Standard Drive (**SD**) card to record monitored data and a Graphical Liquid Crystal Display (**GLCD**) screen fixed in the steering wheel to made the information visible to car pilot.

The **RTC gives the TimeStamp, available in GLCD screen**. </br>
The **SD card receives car real time information every 2 seconds.** </br>
The **Fuel Sensor is a capacitive sensor and it monitors the fuel level in prototype's fuel tank.** </br>
The **velocity and RPM sensors are inductive sensors that detects pulses and send it to the microcontroller.** 

One new idea is to use two Radio Frequency (**RF**) modules to **send the monitored data to another microcontroller situated in team pit stop place.** </br>
The RF module needs to send information in equal time invervals, the same stored information available in SD card. </br>
Its goal is that the team can visualize acquired car physical measures in real time, facilitating the process of fault detection. 

## Utilization


## Copyrights
The project can **be reproduced with no problem.** </br>
However, I only ask you to **mantain original credits/references to the author.**


Enjoy!


**Hollweg**

