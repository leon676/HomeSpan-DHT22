/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2020 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/
 
////////////////////////////////////////////////////////////
//                                                        //
//    HomeSpan: A HomeKit implementation for the ESP32    //
//    ------------------------------------------------    //
//                                                        //
////////////////////////////////////////////////////////////

#include "HomeSpan.h" 
#include "DEV_Identify.h"      
#include "DEV_Sensors.h"

void setup() {
  
  Serial.begin(115200);
  homeSpan.begin(Category::Sensors,"AZDelivery Temp Sensor");
      
  new SpanAccessory();                                                          
    new DEV_Identify("AZDelivery Temp Sensor","SmartHomeFactory","123-ABC","Sensor","0.9",0);
    new Service::HAPProtocolInformation();
      new Characteristic::Version("1.1.0");
    // Create a Temperature Sensor (see DEV_Sensors.h for definition)
    new DEV_TempSensor();                                                                
    
  new SpanAccessory();
    new DEV_Identify("AZDelivery Humidity Sensor","SmartHomeFactory","123-ABC","Sensor","0.9",0);
    new Service::HAPProtocolInformation();
      new Characteristic::Version("1.1.0");
    // Create a Humidity Sensor (see DEV_Sensors.h for definition)
    new DEV_HumSensor();                                                                
    
} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // end of loop()
