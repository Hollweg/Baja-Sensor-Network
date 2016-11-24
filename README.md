
# Baja Sensor Network
Baja sensor network developed to Bombaja UFSM

## The Purpose
**Baja SAE is a project developed by Automotive Engineering Society and has as main objective that engineering students
could apply on real life the knowledge acquired in universities and colleges classes.**
The engineering students must design and build a mini baja prototype that attends the contest requirements and statute, given by SAE.

**The competition have different phases, one theroretical**, when the students have to write a project report and present their car projects to contest judges (graduated engineers) and **one practical**, when the car is evaluated in different exams, each one aimed to stress one or more specific car parts. 

The last competition test is an endurance, basically a **resistance race, where the car that executes more laps in the circuit during 3 hours wins the race.** </br>
The competition circuit have a lot of obstacles, like tree trunks and big stones, and its objective is to break the car. </br>
**Baja SAE competition is an endurance project and the students vehicles need to be prepared to overdue any obstacle.**

Bombaja UFSM is the team that carries **Federal University of Santa Maria name.** </br> 
The objective of this project is to **develop a sensor network to monitor the prototype in real time.**
Use embedded electronical in this kind of vehicle is one of the most hard tasks for electrical engineerings because the enviroment is completely inhospitable, and the system needs to bear impacts, dust, water, mud and clay.

## Development
The microcotroller used in project is a **XMEGA2560**. 

The Mega 2560 is a microcontroller based on the ATmega2560. It has 54 digital input/output pins (of which 15 can be used as PWM outputs), 16 analog inputs, 4 UARTs (hardware serial ports), a 16 MHz crystal oscillator, a USB connection, a power jack, an ICSP header, and a reset button. </br>

It was used **Arduino IDE to develop software.** </br>
**It was chose Arduino platform because it has a big community, it is cheap and open source**.

The main project have the following sensors:

- **Fuel level** sensor
- **Temperature** sensor
- **Velocity** sensor
- **Motor Revolution per Minute (RPM)** sensor

In addition, it has a Real Time Clock (**RTC**), a Standard Drive (**SD**) card to record monitored data and a Graphical Liquid Crystal Display (**GLCD**) fixed in the steering wheel to made the information visible to the car pilot.

The **RTC gives the TimeStamp, and provides its information on GLCD screen**. </br>
The **SD card receives car real time information every 2 seconds.** </br>
The **Fuel Sensor is a capacitive sensor and it monitors the fuel level in prototype's fuel tank.** </br>
The **velocity and RPM sensors are inductive sensors that detects pulses and send it to the microcontroller.** 

The pilot can view two different screens in GLCD, swaped using a "Swap Screen" button, in the steering wheel. </br>
In the first screen it is shown Gearbox temperature, Velocity and motor RPM. </br>
In the second screen it is show the Timestamp and Fuel Tank status.

One new idea is to use two Radio Frequency (**RF**) modules to **send the monitored data to another microcontroller situated in team pit stop place.** </br>
The RF module needs to send information in equal time invervals, the same time when it is stored information in SD card. </br>
Its main goal is grant car physical measures acess to the whole team in real time, facilitating the process of fault detection and problem correction. 

###RPM + Velocity
To **improve inductive sensors (RPM + velocity) reliability** it is used **system interruption** to acquire sensor data. In addition, it is calculated an average every 10 times acquisition, to enhance precision. </br>

###Fuel
The **capacitive sensor** is positioned in the **fuel tank half bottom part**, assuring the detection of low fuel. To improve the sensor measure, after it detects the fuel fault, it enables a timer that is reseted if it is detected another signal of fuel presence. This way, **only if the sensor detects fuel fault during 20 consecutive seconds, the GLCD shows "Empty Fuel" warning.** This detection system using a timer avoids fake detections. </br>

###Temperature
The **temperatue** is measured using a **Type K Thermocouple**, that is tied in in the gearbox. To read its signal with perfection it is used an **AD595 integrated circuit**, responsible for Cold Junction Compensation and precision improvement. After this singal conditioning, the temperature is sended via analog ports to microcontroller. </br>

To enchance car embedded system it is planned to develop the same software **using a different and better microcontroller**, with a better IDE, like **Texas Instruments MSP430** board or **Freescale FRDM K-22F**, that uses Kinetis Design Studio and a Cortex ARM chip. </br>
Moreover, the **thermocouple, inductive and capacitive sensors will be swaped by automotive sensors.** </br>
To improve pilot visibility while driving it will be developed an **analogic automotive panel to show RPM + Velocity**.

The prototype electhroncical system counts too with a LED headlight pair and a horn. </br>
The whole system is protected by a 1A fuse and powered by a 1000mAh Zippy battery, used mainly in aeromodelling projects. ;)

## Copyrights
The project can **be reproduced with no problem.** </br>
However, I only ask you to **mantain original credits/references to the author.**


Enjoy!


**Hollweg**

