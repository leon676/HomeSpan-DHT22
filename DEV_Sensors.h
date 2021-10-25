/////////////////////////////////
//   DEVICE-SPECIFIC SERVICES //
////////////////////////////////
#include "DHT.h"

#define DHTPIN 17
#define DHTTYPE DHT22

// reference to the Sensor Objects
DHT dht(DHTPIN, DHTTYPE);

// A standalone Temperature sensor
struct DEV_TempSensor : Service::TemperatureSensor {     

  // reference to the Current Temperature Characteristic
  SpanCharacteristic *temp;                                       

  // constructor() method
  DEV_TempSensor() : Service::TemperatureSensor() {      

    // start dhttemp Object
    dht.begin();                                    

    // instantiate the Current Temperature Characteristic
    temp = new Characteristic::CurrentTemperature(-10.0);     
    // expand the range from the HAP default of 0-100 to -50 to 100 to allow for negative temperatures
    temp->setRange(-50, 100);                                 

    // initialization message
    Serial.print("Configuring Temperature Sensor");           
    Serial.print("\n");

  } // end constructor

  void loop() {

    // the temperature refreshes every 10 seconds by the elapsed time
    if (temp->timeVal() > 10000) {
      // read temperature from sensor dht22
      float temperature = dht.readTemperature();        
      // set the new temperature; this generates an Event Notification and also resets the elapsed time
      temp->setVal(temperature);                            

      LOG1("Temperature Update: ");
      LOG1(temperature);
      LOG1(" ; ");
    }
  } // loop
};

////////////////////////////////////

// A standalone Humidity sensor
struct DEV_HumSensor : Service::HumiditySensor {     

  // reference to the Current Humidity Characteristic
  SpanCharacteristic *hum;                                  

  // constructor() method
  DEV_HumSensor() : Service::HumiditySensor() {      

    // start dhthum Object
    dht.begin();                                  

    // instantiate the Current Temperature Characteristic
    hum = new Characteristic::CurrentRelativeHumidity(50);
    // expand the range to 30%-100% 
    hum->setRange(30, 100);                                

    // initialization message
    Serial.print("Configuring Humidity Sensor");           
    Serial.print("\n");

  } // end constructor

  void loop() {

    // the humidity refreshes every 10 seconds by the elapsed time
    if (hum->timeVal() > 10000) {
      // read humidity from sensor dht22
      float humidity = dht.readHumidity();  
      // set the new humidity; this generates an Event Notification and also resets the elapsed time        
      hum->setVal(humidity);                            

      LOG1("Humidity Update: ");
      LOG1(humidity);
      LOG1(" ; ");
    }
  } // loop
};

//////////////////////////////////
