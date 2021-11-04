
/******************************************************************************

  WRITTEN BY: Ho Yun "Bobby" Chan
  @ SparkFun Electronics
  DATE: 10/19/2021
  GITHUB REPO: https://github.com/sparkfun/MicroMod_Environmental_Sensor_Function_Board
  DEVELOPMENT ENVIRONMENT SPECIFICS:
    Firmware developed using Arduino IDE v1.8.12

  ========== DESCRIPTION==========
  This example code combines example codes from the SHTC3, STC31, and SGP40 libraries.
  Most of the steps to obtain the measurements are the same as the example code.
  Generic object names were renamed (e.g. mySensor => mySGP40 and mySTC3x).

     Example 1: Basic Relative Humidity and Temperature Readings  w/ SHTC3; Written by Owen Lyke
     Example 2: PHT (SHTC3) Compensated CO2 Readings w/ STC31; Written by Paul Clark and based on earlier code by Nathan Seidle
     Example 1: Basic VOC Index w/ SGP40; Written by Paul Clark

  Open a Serial Monitor/Plotter at 115200 baud to view the readings!

  Note: You may need to wait about ~5 minutes after starting up the code before VOC index
  has any values.

  ========== HARDWARE CONNECTIONS ==========
  MicroMod Artemis Processor Board => MicroMod Main Board => MicroMod Environmental Function Board (with SHTC3, STC31, and SGP40)

  Feel like supporting open source hardware?
  Buy a board from SparkFun!
       MicroMod MicroMod Artemis Processor   | https://www.sparkfun.com/products/16401
       MicroMod Main Board - Single          | https://www.sparkfun.com/products/18575
       MicroMod Environmental Function Board | https://www.sparkfun.com/products/18632

  You can also get the sensors individually.
       SHTC3 | https://www.sparkfun.com/products/16467
       STC31 | https://www.sparkfun.com/products/18385
       SGP40 | https://www.sparkfun.com/products/17729

  LICENSE: This code is released under the MIT License (http://opensource.org/licenses/MIT)

******************************************************************************/



#include <Wire.h>

#include "SparkFun_SHTC3.h" //Click here to get the library: http://librarymanager/All#SparkFun_SHTC3
SHTC3 mySHTC3; // Create an object of the SHTC3 class

#include "SparkFun_STC3x_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_STC3x
STC3x mySTC3x; // Create an object of the STC3x class

#include "SparkFun_SGP40_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP40
SGP40 mySGP40; //Create an object of the SGP40 class

float RH = 0.00; // Variable to keep track of SHTC3 temperature compensation for the STC31
float temperature = 0.00; // Variable to keep track of SHTC3 relative humidity compensation for the STC31

//Debug mode, comment one of these lines out using a syntax
//for a single line comment ("//"):
#define DEBUG 0     //0 = Output for Serial Plotter, CSV
//#define DEBUG 1     //1 = Output for Serial Monitor



void setup() {

  Serial.begin(115200);
  while (!Serial) ; // Wait for Serial Monitor/Plotter to open for Processors with Native USB (i.e. SAMD51)


#if DEBUG
  Serial.println(F("Initializing Combined Example w/ SGP40, SHTC3, and STC31."));
#else
  Serial.println(F("RH,degF,degC,SHTC3_Valid,RH_Compensate_Valid,degC_Compensate_Valid,CO2%,STC31_Valid,VOC_Index"));
#endif

  Wire.begin();

  //mySTC3x.enableDebugging(); // Uncomment this line to get helpful debug messages on Serial
  //mySGP40.enableDebugging(); // Uncomment this line to print useful debug messages to Serial



  if (mySHTC3.begin() != SHTC3_Status_Nominal)
  {
#if DEBUG
    Serial.println(F("SHTC3 not detected. Please check wiring. Freezing..."));
#endif
    while (1)
      ; // Do nothing more
  }

  if (mySTC3x.begin() == false)
  {
#if DEBUG
    Serial.println(F("STC3x not detected. Please check wiring. Freezing..."));
#endif
    while (1)
      ; // Do nothing more
  }

  if (mySGP40.begin() == false)
  {
#if DEBUG
    Serial.println(F("SGP40 not detected. Check connections. Freezing..."));
#endif
    while (1)
      ; // Do nothing more
  }



  //We need to tell the STC3x what binary gas and full range we are using
  //Possible values are:
  //  STC3X_BINARY_GAS_CO2_N2_100   : Set binary gas to CO2 in N2.  Range: 0 to 100 vol%
  //  STC3X_BINARY_GAS_CO2_AIR_100  : Set binary gas to CO2 in Air. Range: 0 to 100 vol%
  //  STC3X_BINARY_GAS_CO2_N2_25    : Set binary gas to CO2 in N2.  Range: 0 to 25 vol%
  //  STC3X_BINARY_GAS_CO2_AIR_25   : Set binary gas to CO2 in Air. Range: 0 to 25 vol%
  if (mySTC3x.setBinaryGas(STC3X_BINARY_GAS_CO2_AIR_25) == false)
  {
#if DEBUG
    Serial.println(F("Could not set the binary gas! Freezing..."));
#endif
    while (1)
      ; // Do nothing more
  }



  //We can compensate for temperature and relative humidity using the readings from the SHTC3

  if (mySHTC3.update() != SHTC3_Status_Nominal) // Request a measurement
  {
#if DEBUG
    Serial.println(F("Could not read the RH and T from the SHTC3! Freezing..."));
#endif
    while (1)
      ; // Do nothing more
  }

  //In case the ‘Set temperature command’ has been used prior to the measurement command,
  //the temperature value given out by the STC31 will be that one of the ‘Set temperature command’.
  //When the ‘Set temperature command’ has not been used, the internal temperature value can be read out.
  temperature = mySHTC3.toDegC(); // "toDegC" returns the temperature as a floating point number in deg C
#if DEBUG
  Serial.print(F("Setting STC3x temperature to "));
  Serial.print(temperature, 2);
  Serial.print(",");
  Serial.print(F("C was "));
#endif

  if (mySTC3x.setTemperature(temperature) == false) {
#if DEBUG
    Serial.print(F("not "));
#endif
  }
#if DEBUG
  Serial.println(F("successful"));
#endif

  RH = mySHTC3.toPercent(); // "toPercent" returns the percent humidity as a floating point number

#if DEBUG
  Serial.print(F("Setting STC3x RH to "));
  Serial.print(RH, 2);
  Serial.print(",");
  Serial.print(F("% was "));
#endif

  if (mySTC3x.setRelativeHumidity(RH) == false) {
#if DEBUG
    Serial.print(F("not "));
#endif
  }
#if DEBUG
  Serial.println(F("successful"));
#endif



  //If we have a pressure sensor available, we can compensate for ambient pressure too.
  //As an example, let's set the pressure to 840 mbar (== SF Headquarters)
  uint16_t pressure = 840;

#if DEBUG
  Serial.print(F("Setting STC3x pressure to "));
  Serial.print(pressure);
  Serial.print(F("mbar was "));
#endif

  if (mySTC3x.setPressure(pressure) == false) {
#if DEBUG
    Serial.print(F("not "));
#endif
  }
#if DEBUG
  Serial.println(F("successful"));

  Serial.println(F("Note: Relative humidity and temperature compensation for the STC31 will be updated frequently in the main loop() function."));
#endif

} //end setup()





void loop() {


  //==============================
  //======DEBUG TURNED ON=========
  //==============================
#if DEBUG
  //==============================
  //==========READ SHTC3==========
  //==============================
  //minimum update rate = ~100Hz

  SHTC3_Status_TypeDef result = mySHTC3.update();           // Call "update()" to command a measurement, wait for measurement to complete, and update the RH and T members of the object

  RH = mySHTC3.toPercent();                                 // "toPercent" returns the percent humidity as a floating point number
  Serial.print(F("RH = "));
  Serial.print(RH);

  Serial.print(F("%, T = "));
  Serial.print(mySHTC3.toDegF());                           // "toDegF" return the temperature as a flaoting point number in deg F
  Serial.print(F(" deg F, "));

  temperature = mySHTC3.toDegC();                           // "toDegC" returns the temperature as a floating point number in deg C
  Serial.print(temperature);
  Serial.print(F(" deg C"));

  if (mySHTC3.lastStatus == SHTC3_Status_Nominal)           // You can also assess the status of the last command by checking the ".lastStatus" member of the object
  {
    Serial.println("");                                         //Sample data good, no need to output a message
  }
  else {
    Serial.print(F(",     Update failed, error: "));        //notify user if there is an error
    errorDecoder(mySHTC3.lastStatus);
    Serial.println("");
  }



  //==============================
  //==========READ STC31==========
  //==============================
  //minimum update rate = 1Hz


  if (mySTC3x.setRelativeHumidity(RH) == false)
    Serial.print(F("Unable to set STC31 Relative Humidity with SHTC3."));

  if (mySTC3x.setTemperature(temperature) == false)
    Serial.println(F("Unable to set STC31 Temperature with SHTC3."));


  Serial.print(F("CO2(%): "));

  if (mySTC3x.measureGasConcentration())                   // measureGasConcentration will return true when fresh data is available
  {
    Serial.println(mySTC3x.getCO2(), 2);
  }
  else
  {
    Serial.print(mySTC3x.getCO2(), 2);
    Serial.println(F(",     (old STC3 sample reading, STC31 was not able to get fresh data yet)"));  //output this note to indicate  when we are not able to obtain a new measurement
  }



  //==============================
  //==========READ SGP40==========
  //==============================
  //minimum update rate = 1Hz

  Serial.print(F("VOC Index is: "));
  Serial.println(mySGP40.getVOCindex()); //Get the VOC Index using the default RH (50%) and T (25C)





  //==============================
  //=====DEBUG TURNED OFF=========
  //==============================
#else
  //==============================
  //==========READ SHTC3==========
  //==============================
  //minimum update rate = ~100Hz

  SHTC3_Status_TypeDef result = mySHTC3.update();           // Call "update()" to command a measurement, wait for measurement to complete, and update the RH and T members of the object

  RH = mySHTC3.toPercent();
  Serial.print(RH);
  Serial.print(",");
  Serial.print(mySHTC3.toDegF());
  Serial.print(",");
  temperature = mySHTC3.toDegC();                           // "toDegC" returns the temperature as a floating point number in deg C
  Serial.print(temperature);
  Serial.print(",");

  if (mySHTC3.lastStatus == SHTC3_Status_Nominal)           // You can also assess the status of the last command by checking the ".lastStatus" member of the object
  {
    Serial.print("1");                                         //Sample data good, no need to output a message
    Serial.print(",");
  }
  else
  {
    Serial.print("0");                                         //Sample data bad, no need to output a message
    Serial.print(",");
  }



  //==============================
  //==========READ STC31==========
  //==============================
  //minimum update rate = 1Hz


  if (mySTC3x.setRelativeHumidity(RH) == false)
  {
    //Serial.print(F("Unable to set STC31 Relative Humidity with SHTC3."));
    Serial.print("0");
    Serial.print(",");
  }
  else
  {
    Serial.print("1");
    Serial.print(",");
  }

  if (mySTC3x.setTemperature(temperature) == false)
  {
    //Serial.println(F("Unable to set STC31 Temperature with SHTC3."));
    Serial.print("0");
    Serial.print(",");
  }
  else
  {
    Serial.print("1");
    Serial.print(",");
  }

  if (mySTC3x.measureGasConcentration())                   // measureGasConcentration will return true when fresh data is available
  {
    Serial.print(mySTC3x.getCO2(), 2);
    Serial.print(",");
    Serial.print("1");                                     //Fresh Data
    Serial.print(",");
  }
  else
  {
    Serial.print(mySTC3x.getCO2(), 2);
    Serial.print(",");
    Serial.print("0");                                     //Data not fresh
    Serial.print(",");
  }



  //==============================
  //==========READ SGP40==========
  //==============================
  //minimum update rate = 1Hz

  Serial.println(mySGP40.getVOCindex()); //Get the VOC Index using the default RH (50%) and T (25C)

#endif



  //================================
  //=========SPACE & DELAY==========
  //================================
  //Serial.println("");// Uncomment this line to add some space between readings for the Serial Monitor
  delay(1000); //Wait 1 second - the Sensirion VOC algorithm expects a sample rate of 1Hz

}//end loop()





void errorDecoder(SHTC3_Status_TypeDef message)                             // The errorDecoder function prints "SHTC3_Status_TypeDef" resultsin a human-friendly way
{
  switch (message)
  {
    case SHTC3_Status_Nominal : Serial.print("Nominal"); break;
    case SHTC3_Status_Error : Serial.print("Error"); break;
    case SHTC3_Status_CRC_Fail : Serial.print("CRC Fail"); break;
    default : Serial.print("Unknown return code"); break;
  }
}
