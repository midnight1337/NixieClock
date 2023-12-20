# Nixie Clock

## Overwiev

Retro style nixie clock, this is a project based on cool looking, gas filled, vintage nixie tubes. <br/>

Clock displays time in Hour::Minute format. If RTC somehow loses his time, user is able to change it with functional buttons. 

Inspired by GreatScott. Best advantage of that project is that it looks cool af. <br/>

### Technologies and Development
- Arduino Pro Mini
- C++

## UML
![UML](/images/uml.png)

## Schematic
...


## Project documentation

#### Testing nixie tubes:
Some of them that I had, were damaged, or cathodes were burned out.
![Tube Test](/images/tube_test.jpeg)


#### SN74141N Nixie Driver pinout:
![SN74141N](/images/SN74141N.png)

#### SN74141N truth table:
![SN74141N](/images/SN74141N_truth_table.png)

#### Nixie tube pinout:

Nixie tubes usually has common anode, and separated cathode, each responsible for every digit on tube.

![Tube](/images/nixie_tube_pinout.png)
