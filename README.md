SparkFun MicroMod Environmental Sensor Function Board
========================================

[![SparkFun MicroMod Environmental Sensor Function Board](https://cdn.sparkfun.com/assets/parts/1/8/1/4/8/18632-SparkFun_MicroMod_Environmental_Function_Board-01.jpg)](https://www.sparkfun.com/products/18632)

[*SparkFun MicroMod Environmental Sensor Function Board (SEN-18632)*](https://www.sparkfun.com/products/18632)

The SparkFun MicroMod Environmental Function Board adds additional sensing options to the MicroMod Processor Boards. This Function Board includes three sensors to monitor air quality (SGP40), humidity & temperature (SHTC3), and CO<sub>2</sub> concentrations (STC31) in your indoor environment. To make it even easier to use, all communication is over the MicroMod's I<sup>2</sup>C bus!

* The SGP40 measures the quality of the air in your room or house. The SGP40 uses a metal oxide (MOx) sensor with a temperature controlled micro hotplate and provides a humidity-compensated volatile organic compound (VOC) based indoor air quality signal. Both the sensing element and VOC Algorithm feature an unmatched robustness against contaminating gases present in real world applications enabling a unique long term stability as well as low drift and device to device variation.

* The SHTC3 is a highly accurate digital humidity and temperature sensor. The SHTC3 uses a capacitive humidity sensor with a relative humidity measurement range of 0 to 100% RH and bandgap temperature sensor with a temperature measurement range of -40&deg;C to 125&deg;C. The SHTC3 builds on the success of their SHTC1 sensor with higher accuracy (±2% RH, ±0.2&deg;C) than its predecessor, enabling greater flexibility.

* The STC31 measures CO<sub>2</sub> concentrations based on thermal conductivity and has two CO<sub>2</sub> measurement ranges: 0 to 25 vol%; and 0 to 100 vol%. The measurement repeatability is 0.2 vol%, with a stability of 0.025 vol% / °C. The measurement accuracy depends on the measurement range: 0.5 vol% + 3% measured value; 1 vol% + 3% measured value. Using measurements from the SHTC3, the STC31 is able to provide humidity-compensated measurements together with improved temperature compensation.  The STC31 can compensate for atmospheric pressure too - which is handy if, like us, you’re up in the mountains!

The outstanding performance of these three sensors is based on Sensirion’s patented CMOSens<sup>&reg;</sup> technology, which combines the sensor element, signal processing, and digital calibration on a small CMOS chip. The well-proven CMOS technology is perfectly suited for high-quality mass production and is the ideal choice for demanding and cost-sensitive OEM applications.

Utilizing our handy M.2 MicroMod connector, no soldering is required to connect it to your system. Simply match up the key on your processor and function board's beveled edge connector to their respective key on the M.2 connector, then secure them to the main board with screws. The MicroMod Environmental Function Board can then be read via the I<sup>2</sup>C port. The board is equipped with the AP2112 3.3V voltage regulator, I<sup>2</sup>C pull-up resistors, power LED, jumper to disable the LED, and jumpers for alternative STC31 addresses. 


Repository Contents
-------------------

* **/Firmware** - Arduino example code from the tutorial
* **/Hardware** - Eagle design files (.brd, .sch)
* **/Production** - Production panel files (.brd)

Documentation
--------------

* **[Installing an Arduino Library Guide](https://learn.sparkfun.com/tutorials/installing-an-arduino-library/all)** - Basic information on how to install an Arduino library.
* **Arduino Libraries**
  * **[SGP40](https://github.com/sparkfun/SparkFun_SGP40_Arduino_Library)**
  * **[SHTC3](https://github.com/sparkfun/SparkFun_SHTC3_Arduino_Library)**
  * **[STC3X](https://github.com/sparkfun/SparkFun_STC3x_Arduino_Library)**
* **[Hookup Guide](https://learn.sparkfun.com/tutorials/2001)** - Basic hookup guide


Product Versions
----------------

* [SEN-18632](https://www.sparkfun.com/products/18632)- Initial release


Version History
---------------

* v1.0 - Initial Release


License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. 

If you have any questions or concerns on licensing, please contact technical support on our [SparkFun forums](https://forum.sparkfun.com/viewforum.php?f=152).

Distributed as-is; no warranty is given.

- Your friends at SparkFun.

_<COLLABORATION CREDIT>_
