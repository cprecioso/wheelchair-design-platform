# The hiking wheelchair (working title)

> [Carlos Precioso (@cprecioso)](https://github.com/cprecioso) and [Martina Pozzoni (@martypoz)](https://github.com/martypoz)

## Context
Most people walk in their day-to-day lives. To work, school, to a restaurant with some friends, or just to your friend’s desk a few steps over. As we think about it, walking is a purely functional endeavour, design to get you from A to B in the quickest, most efficient way. There is however another way of walking, one that more and more people are practicing every day. One where the important matter is not the destination but the journey: **hiking**.

Hiking is an enjoyable activity with both physical and mental benefits. Hiking outdoors is a stimulating activity that helps decreasing stress levels and increase creativity and happiness. But we want not for these benefits to be limited by the ability to walk. People who have movement disabilities and are wheelchair-bound nevertheless do have the ability to enjoy journeys through nature. With our project, we want to contribute to **make hiking more enjoyable and safe for these wheelchair-bound people, without the need to be accompanied by an able-bodied person**.

## Sensors

<table>
<thead>
<tr class="header">
<th><p>Sensor</p></th>
<th><p>Resulting variable(s)</p></th>
<th><p>Possible uses</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>GPS tracker</p></td>
<td><p>Latitude and longitude coordinates.</p></td>
<td><ul>
<li>Plan the hiking trail and make sure to follow a wheelchair accessible path</li>
<li>Track your results and progress in terms of distance and speed</li>
<li>Link data gathered through the other sensors with locations for later use (feedback or sharing with other users)</li>
</ul></td>
</tr>
<tr class="even">
<td><p>Heart rate sensor</p></td>
<td><p>Beats per minute.</p></td>
<td><ul>
<li>Keep track of your effort and fitness level</li>
<li>Gather data on the most intense parts of the path</li>
</ul></td>
</tr>
<tr class="odd">
<td><p>Accelerometer</p></td>
<td><p>Accelerations in 3 axes</p></td>
<td><ul>
<li>Detect falls and other sudden impacts which might have had an effect on the wheelchair user.</li>
</ul></td>
</tr>
<tr class="even">
<td><p>Gyroscope</p></td>
<td><p>Rotation in 3 axes</p></td>
<td><ul>
<li>Detect inclination and required balance in uneven stretches of the path.</li>
</ul></td>
</tr>
<tr class="odd">
<td><p>Humidity</p></td>
<td><p>Percentage of water content on a surface</p></td>
<td><ul>
<li>Measure water loss</li>
</ul></td>
</tr>
</tbody>
</table>

## Actuators
<table>
  <thead>
    <tr class="header">
      <th>Actuator</th>
      <th>Possible use(s)</th>
    </tr>
  </thead>
  <tbody>
    <tr class="odd">
      <td>
        LCD Display
      </td>
      <td>
        <p>Visualize direction arrows:</p>
        <ul>
          <li>straight</li>
          <li>left</li>
          <li>right</li>
          <li>stop</li>
          <li>turn back</li>
        </ul>
      </td>
    </tr>
    <tr class="even">
      <td>RGB Led</td>
      <td>
        <ul>
          <li>
            Show the current state of the user in the
            <a
              href="https://customercare.g%20eonaute.com/hc/en-gb/articles/205%20822622-WHAT-DO-THE-COLOUR-CARDIO-%20ZONES-MEAN-"
              >cardio chart</a
            >
          </li>
        </ul>
      </td>
    </tr>
    <tr class="odd">
      <td>2 continuous rotation servos</td>
      <td>
        <ul>
          <li>
            Compensate extreme inclinations through a counterweight system
          </li>
        </ul>
      </td>
    </tr>
    <tr class="even">
      <td>GSM Antenna</td>
      <td>
        <ul>
          <li>
            Automatically call emergency services when falls are detected, or
            the user requests it
          </li>
        </ul>
      </td>
    </tr>
  </tbody>
</table>


---

# Wheelchair Design Platform

Wheelchair Design Platform is a repository that contains some resources to help
designers and developers speak the same language, and work together towards
addressing relevant challenges for wheelchair users. It is a collection of 
workshop materials, code examples and also a compilation of resources to foster
a prospering research and design community around wheelchair users.


![IoT1 Exhibition](/docs/workshops/images/iot1_exhibition.jpg)

## Workshops

* [Getting started](/docs/workshops/GettingStarted.md)
* [Workshop 1: Building an Internet-Connected Wheelchair](/docs/workshops/Workshop1.md)
* [Workshop 2: Integrating and Visualising Sensor-Based Data](/docs/workshops/Workshop2.md)
* [Workshop 3: Developing Algorithms and Controlling Actuators](/docs/workshops/Workshop3.md)
* [Workshop 4: Developing and Conducting a Data Collection Campaign](/docs/workshops/Workshop4.md)
* [Workshop 5: Implementing a Machine Learning Pipeline](/docs/workshops/Workshop5.md)
* [Workshop 6: Developing a Product Analytics Dashboard](/docs/workshops/Workshop6.md)

## Resources

* This platform uses two programming languages, Python on computers and C on
micro-controllers. While descriptions and examples of code should help you
get started, you can find some additional resources
[here](/docs/resources/software.md "Python and C resources").

* Documentation of your project is key,
[here are some tips and examples](/docs/resources/documentation.md "Documentation tips and examples").

* [Git manipulation such as Pull Request](/docs/resources/git.md "Git manipulation").

## Main Components

__**Disclaimer:**__ the design of this platform focuses on flexibility and
technology exploration rather than optimisation.

The main design includes a Raspberry Pi 3 and an Arduino Mega 2560 on the wheelchair frame.

The Arduino Mega is the micro-controller of the platform. Fixed on the main frame of the wheelchair,
it can collect data from sensors (e.g. force sensors, accelerometers), and trigger actions from actuators
(e.g. LEDs, vibration motors).

More on the Arduino Mega can be found [here](/docs/resources/arduino.md "Arduino resources").

Raspberry Pi is a small computer. It is also fixed to the main frame of the wheelchair,
where it can:
* interact with the Arduino Mega via USB to receive data and transmit commands;
* interact with the Internet to transmit commands and receive data;
* store data locally in files;
* run (machine learning) algorithms.

More on the Raspberry Pi can be found [here](/docs/resources/raspberrypi.md "Raspberry Pi resources").

These components fit together as shown on the following diagram. A large powerbank
powers the Raspberry Pi. The Arduino Mega communicates and receives power from the
Raspberry Pi via USB. A Feather (Arduino-like development board) on the wheel connects to
the Raspberry Pi via Bluetooth to sense and actuate from the wheel.

![Main Wheelchair components](/docs/workshops/images/wheechair-components.png)

## List of suggested components:

On the frame:

* 1 Raspberry Pi 3B;
* 1 SD card (Some come directly with NOOBS installed);
* 1 Arduino Mega;
* 1 Large power bank;
* 1 large breadboard;
* 1 USB cable A/micro (Powerbank to Raspberry Pi);
* 1 USB cable A/B (Raspberry Pi to Arduino Mega).

On the wheel:

* 1 Feather (Bluetooth enabled);
* 1 small power bank;
* 1 small breadboard;
* 1 USB cable A/B (power bank to Arduino Uno).


## Contact and Existing projects

* [The hiking wheelchair](https://github.com/cprecioso/wheelchair-design-platform)
* [The EDU wheelchair](https://github.com/ctsai-1/wheelchair-design-platform)
* [Weelchair tracking for basketball players](https://github.com/FabianIDE/wheelchair-design-platform)
* [Disco Wheelchair](https://github.com/MatthijsBrem/wheelchair-design-platform)
* [Wheelchair Madness 2222](https://github.com/pherkan/wheelchair-design-platform/tree/master/wheelchair)
* [Who is sitting?](https://github.com/Rosanfoppen/wheelchair-design-platform/tree/master/wheelchair)
* [Magic Wheelchair](https://github.com/Yuciena/wheelchair-design-platform)


Feel free to contact us at jacky@datacentricdesign.org. We welcome feedback, pull requests
or links to your project.
