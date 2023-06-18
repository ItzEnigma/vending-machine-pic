### Industrial Vending Machine project based on PIC16F882 microcontroller developed in C-Language. Debugged and simulated using MPLAB X IDE _(v6.05)_ and Proteus Simulator 
---
## Specifications & Components
#### The Hardware components used for the implementation of the project,
* **PIC16F882 Microcontroller:** the microcontroller used to implement the project using a very limited 2 KB Flash for the program and 128 Bytes RAM
* **LCD Display Screen:** provides instructions and information to the user such as selected drink type, price, current balance and any change due
* **Push Buttons (3-PB):** simulate inputs required to drive the user interface for drink selection and also to simulate coin insertion
* **Potentiometer (VR2):** simulate the voltage output of an analogue tilt sensor used for anti-theft detection
* **LEDs (2-LEDs):** simulate control outputs to the drink and coin dispensing mechanisms
* **Alarm Buzzer:** under normal operation this mode is dormant. However, when the tilt sensor voltage exceeds 2V ... it will indicate theft.
---
## Details
#### The Project presents the software development of an Industrial Vending Machine that has <ins>6 fundamental modes</ins>:
* **Drink Selection Mode:** the initial state that provides a user interface through which the customer can select a drink and view the prices
* **Coin Insertion Mode:** must initially display the cost of the selected drink. Coin insertions are simulated by pushbuttons (SW0-2). After each coin insertion the display updates to show the outstanding balance
* **Dispense Drink Mode:** this is simulated by setting LED output RA0 HIGH for 5 seconds, Timer 0 is used to create the delay of 5 seconds and after time has elapsed RA0 is set to LOW
* **Dispense Change Mode:** this mode is <ins>**ONLY**</ins> active if the inserted coins exceeded the required balance for the selected drink, by using RA1 LED to simulate coin dispense
* **Drink Ready Mode:** this mode is the final one, where a message is displayed on the LCD for 5 seconds then the system resets to start over for the next customer
* **Alarm Mode:** if the voltage from VR2 exceeds 2V, simulating a tilt sensor, an alarm is activated (RA3).
>__Note__ that the buttons are functional at **Drink Selection Mode** and **Coin Insertion Mode**, where in Drink Selection Mode <ins>SW0</ins> moves to the next drink and <ins>SW1</ins> selects the currently displayed drink. and in Coin Insertion Mode all buttons are functional adding 10 - 20 - 50 coins respectively.
---
## Attachments
Simulation schematic and video illustrating the vending machine operation
![Vending Machine](https://github.com/ItzEnigma/vending-machine-pic/assets/97047710/9c033037-d026-4d85-b3ce-776fa5fcbda7)


https://github.com/ItzEnigma/vending-machine-pic/assets/97047710/f5d13f8b-7c1d-44ad-b11e-68b7536a56cc

