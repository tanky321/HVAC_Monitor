#include <sdpsensor.h>
#include <Adafruit_MAX31856.h>

class HVACPCB : public PollingComponent, public Sensor {
 public:
  // constructor
  SDP8XXSensor sdp;
  Adafruit_MAX31856 maxthermo1 = Adafruit_MAX31856(14);
  Adafruit_MAX31856 maxthermo2 = Adafruit_MAX31856(27);
  Adafruit_MAX31856 maxthermo3 = Adafruit_MAX31856(15);
   
  Sensor *SDP1Temperature = new Sensor();
  Sensor *SDP1Pressure = new Sensor();
  Sensor *TC1_Sensor = new Sensor();
  Sensor *TC2_Sensor = new Sensor();
  Sensor *TC3_Sensor = new Sensor();
  
  HVACPCB() : PollingComponent(5000) {}

  void setup() override {
	  
	Wire.begin();
	delay(1000);
	 int ret = sdp.init(); 
	Wire.beginTransmission(0x70);
	Wire.write(1);
	Wire.endTransmission();
	
	maxthermo1.begin();
	maxthermo1.setThermocoupleType(MAX31856_TCTYPE_K);
	maxthermo2.begin();
	maxthermo2.setThermocoupleType(MAX31856_TCTYPE_K);
	maxthermo3.begin();
	maxthermo3.setThermocoupleType(MAX31856_TCTYPE_K);
	
  }
  void update() override {
    // This will be called every "update_interval" milliseconds.
  int ret = sdp.readSample();
  float Pressure;
  float Temperature;
  
  if (ret == 0) {
    Pressure = sdp.getDifferentialPressure();
	Pressure = Pressure * 0.00401865;

	Temperature = sdp.getTemperature();
  } else {
    Serial.print("Error in readSample(), ret = ");
    Serial.println(ret);
  }

	SDP1Temperature->publish_state(Temperature);
	SDP1Pressure->publish_state(Pressure);
	 
	//Get TC#1 Temperature and state
	float TC1 = maxthermo1.readThermocoupleTemperature();
	uint8_t fault1 = maxthermo1.readFault();
	if (fault1){
		TC1 = NAN;
		if (fault1 & MAX31856_FAULT_CJRANGE) ESP_LOGI("custom", "TC1 - Cold Junction Range Fault");
		if (fault1 & MAX31856_FAULT_TCRANGE) ESP_LOGI("custom", "TC1 - Thermocouple Range Fault");
		if (fault1 & MAX31856_FAULT_CJHIGH)  ESP_LOGI("custom", "TC1 - Cold Junction High Fault");
		if (fault1 & MAX31856_FAULT_CJLOW)   ESP_LOGI("custom", "TC1 - Cold Junction Low Fault");
		if (fault1 & MAX31856_FAULT_TCHIGH)  ESP_LOGI("custom", "TC1 - Thermocouple High Fault");
		if (fault1 & MAX31856_FAULT_TCLOW)   ESP_LOGI("custom", "TC1 - Thermocouple Low Fault");
		if (fault1 & MAX31856_FAULT_OVUV)    ESP_LOGI("custom", "TC1 - Over/Under Voltage Fault");
		if (fault1 & MAX31856_FAULT_OPEN)    ESP_LOGI("custom", "TC1 - Thermocouple Open Fault");}
	//Get TC#2 Temperature and state
	float TC2 = maxthermo2.readThermocoupleTemperature();
	uint8_t fault2 = maxthermo2.readFault();
	if (fault2){
		TC2 = NAN;
		if (fault2 & MAX31856_FAULT_CJRANGE) ESP_LOGI("custom", "TC2 - Cold Junction Range Fault");
		if (fault2 & MAX31856_FAULT_TCRANGE) ESP_LOGI("custom", "TC2 - Thermocouple Range Fault");
		if (fault2 & MAX31856_FAULT_CJHIGH)  ESP_LOGI("custom", "TC2 - Cold Junction High Fault");
		if (fault2 & MAX31856_FAULT_CJLOW)   ESP_LOGI("custom", "TC2 - Cold Junction Low Fault");
		if (fault2 & MAX31856_FAULT_TCHIGH)  ESP_LOGI("custom", "TC2 - Thermocouple High Fault");
		if (fault2 & MAX31856_FAULT_TCLOW)   ESP_LOGI("custom", "TC2 - Thermocouple Low Fault");
		if (fault2 & MAX31856_FAULT_OVUV)    ESP_LOGI("custom", "TC2 - Over/Under Voltage Fault");
		if (fault2 & MAX31856_FAULT_OPEN)    ESP_LOGI("custom", "TC2 - Thermocouple Open Fault");}		 
	//Get TC#2 Temperature and state 
	float TC3 = maxthermo3.readThermocoupleTemperature();
	uint8_t fault3 = maxthermo3.readFault();
	if (fault3){
		TC3 = NAN;
		if (fault3 & MAX31856_FAULT_CJRANGE) ESP_LOGI("custom", "TC3 - Cold Junction Range Fault");
		if (fault3 & MAX31856_FAULT_TCRANGE) ESP_LOGI("custom", "TC3 - Thermocouple Range Fault");
		if (fault3 & MAX31856_FAULT_CJHIGH)  ESP_LOGI("custom", "TC3 - Cold Junction High Fault");
		if (fault3 & MAX31856_FAULT_CJLOW)   ESP_LOGI("custom", "TC3 - Cold Junction Low Fault");
		if (fault3 & MAX31856_FAULT_TCHIGH)  ESP_LOGI("custom", "TC3 - Thermocouple High Fault");
		if (fault3 & MAX31856_FAULT_TCLOW)   ESP_LOGI("custom", "TC3 - Thermocouple Low Fault");
		if (fault3 & MAX31856_FAULT_OVUV)    ESP_LOGI("custom", "TC3 - Over/Under Voltage Fault");
		if (fault3 & MAX31856_FAULT_OPEN)    ESP_LOGI("custom", "TC3 - Thermocouple Open Fault");}
	 
	TC1_Sensor->publish_state(TC1);
	TC2_Sensor->publish_state(TC2);
	TC3_Sensor->publish_state(TC3);	
	 
  }
};