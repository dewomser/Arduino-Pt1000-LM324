//----------------------------------------------------------------------------
// RTD Module Example Sketch
// Last revision 30 November 2009
// Licence: GNU GPL
// By Trystan Lea
//
// reduziert auf eine Messstelle von Stefan Höhn
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Load RTD library and create new instance
//----------------------------------------------------------------------------
#include "RTDModule.h"
RTDModule rtd;

//----------------------------------------------------------------------------
// Temperature variables
//----------------------------------------------------------------------------
double CYLB,CYLT,COL;

//----------------------------------------------------------------------------
// Setup
//----------------------------------------------------------------------------
void setup()
{
  rtd.setPins(4,5,2);                                //RTD PT1000 pins 4,5 are digital pins for multiplexer, 2 is analog input
  
  //rtd.calibration( input number, scaler, offset )
  rtd.calibration(0, 0.120270927, -15.066198679);   //INPUT 0 pin 12
  rtd.calibration(1, 0.120821076, -13.824162893);   //INPUT 1 pin 14
  rtd.calibration(2, 0.120400012, -14.91327759);    //INPUT 2 pin 15
      
  analogReference(INTERNAL);                        //Set reference to 1.1V ready for RTD measurements

  Serial.begin(9600);
}

//----------------------------------------------------------------------------
// Main loop Es wird  nur 1 Temp angezeigt
//----------------------------------------------------------------------------
void loop()
{
  //Get temperatures and pass through digital low pass filter
  COL = digitalLowPass(COL, rtd.getTemperature(0) ,0.90);
 CYLB = digitalLowPass(CYLB, rtd.getTemperature(1) ,0.90);
 CYLT = digitalLowPass(CYLT, rtd.getTemperature(2) ,0.90);
  
  //Print temperatures out to serial
  //Serial.print(COL);
  Serial.println(COL);
  //Serial.print(' ');
  //Serial.print(CYLB);
  //Serial.print(' ');
  //Serial.println(CYLT);
  
}
//----------------------------------------------------------------------------

//Digital low pass filter
double digitalLowPass(double last_smoothed, double new_value, double filterVal)
{
  double smoothed = (new_value * (1 - filterVal)) + (last_smoothed * filterVal);
  return smoothed;
}
