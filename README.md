# Nixie Clock

## Overwiev

Nixie clock is a retro style clock based on cool looking, vintage Nixie Tubes. <br/>

This project is inspired by GreatScott, however I've written my own code for driving this device, and did some changes in board by adding microswitches that allows user to change time manually.

Clock displays time in Hour::Minute segments. Board contains a RTC module that can track time with no power supply.

DS3231 clock library made by https://www.jarzebski.pl/arduino/komponenty/zegar-czasu-rzeczywistego-rtc-ds3231.html,
however I had to do some modifications for my needs.

![Overwiev](/images/nixie_overwiev.jpg)

### Technologies and Development
- Arduino Pro Mini
- C++
- Electrical Engineering

## UML
![UML](/images/uml.png)

## Schematic
...


## Project documentation

#### Testing nixie tubes:
At the beginning of my project I had to choose working Tubes by building simple driver circuit and running each digit from 0 to 9. As you may know they are very old and well worn. Some of them that I had, were damaged, or cathodes were burned out.
![Tube Test](/images/tube_test.jpeg)


#### Prototype:
First power up with everything on board.
![Prototype](/images/clock-prototype.jpeg)

#### SN74141N Nixie Driver pinout:
![SN74141N](/images/SN74141N.png)

#### SN74141N truth table:
![SN74141N](/images/SN74141N_truth_table.png)

#### Nixie tube pinout:
Usually nixie tube structure has common anode and separted cathodes for each digit.
![Tube](/images/nixie_tube_pinout.png)
