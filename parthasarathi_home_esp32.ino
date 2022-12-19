/*************************************************************************************************
 *  Created By: Parthasarathi kundu
 *  Created On: 28 Decenber, 2022
 *  
 *  https://www.youtube.com/channel/UCA5UPZuB3zHiS6a34iDLo6w
 *  My Channel: https://www.youtube.com/channel/UCA5UPZuB3zHiS6a34iDLo6w
 *  
 *  *********************************************************************************************
 *  Preferences--> Aditional boards Manager URLs : 
 *  For ESP32 (2.0.3):
 *  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
 *  *********************************************************************************************
 *  Install the following libraries :
 *  1. ezButton
 *  2. IRremote
 ***********************************************************************************************/


#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include <EEPROM.h>
//---------------------------------------------------
//install these libraries
#include <ezButton.h>
#include <IRremote.h>
//---------------------------------------------------
const char *service_name = "kundu_home";
const char *pop = "12345678";
//---------------------------------------------------
#define EEPROM_SIZE 8
const byte IR_RECEIVE_PIN = 35;
//---------------------------------------------------
// define the Device Names
char device1[] = "Switch1";
char device2[] = "Switch2";
char device3[] = "Switch3";
char device4[] = "Switch4";
char device5[] = "Switch5";
char device6[] = "Switch6";
char device7[] = "Switch7";
char device8[] = "Switch8";
//---------------------------------------------------
// define the GPIO connected with Relays and switches
static uint8_t RELAY_1 = 23;  //D23
static uint8_t RELAY_2 = 22;  //D22
static uint8_t RELAY_3 = 21;  //D21
static uint8_t RELAY_4 = 19;  //D19
static uint8_t RELAY_5 = 18;  //D18
static uint8_t RELAY_6 = 5;  //D5
static uint8_t RELAY_7 = 25;  //D25
static uint8_t RELAY_8 = 26;  //D26
//---------------------------------------------------
ezButton button1(13);
ezButton button2(12);
ezButton button3(14);
ezButton button4(27);
ezButton button5(33);
ezButton button6(32);
ezButton button7(15);
ezButton button8(4);
//---------------------------------------------------
static uint8_t WIFI_LED    = 2;   //D2
static uint8_t gpio_reset = 0;
//---------------------------------------------------
// Relay State
bool STATE_RELAY_1 = LOW;
bool STATE_RELAY_2 = LOW;
bool STATE_RELAY_3 = LOW;
bool STATE_RELAY_4 = LOW;
bool STATE_RELAY_5 = LOW;
bool STATE_RELAY_6 = LOW;
bool STATE_RELAY_7 = LOW;
bool STATE_RELAY_8 = LOW;
//---------------------------------------------------
//The framework provides some standard device types 
//like switch, lightbulb, fan, temperature sensor.
static Switch my_switch1(device1, &RELAY_1);
static Switch my_switch2(device2, &RELAY_2);
static Switch my_switch3(device3, &RELAY_3);
static Switch my_switch4(device4, &RELAY_4);
static Switch my_switch5(device5, &RELAY_5);
static Switch my_switch6(device6, &RELAY_6);
static Switch my_switch7(device7, &RELAY_7);
static Switch my_switch8(device8, &RELAY_8);
//---------------------------------------------------

/****************************************************************************************************
 * sysProvEvent Function
*****************************************************************************************************/
void sysProvEvent(arduino_event_t *sys_event)
{
    switch (sys_event->event_id) {      
        case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on BLE\n", service_name, pop);
        printQR(service_name, pop, "ble");
#else
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on SoftAP\n", service_name, pop);
        printQR(service_name, pop, "softap");
#endif        
        break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        Serial.printf("\nConnected to Wi-Fi!\n");
        digitalWrite(WIFI_LED, HIGH);
        break;
    }
}

/****************************************************************************************************
 * write_callback Function
*****************************************************************************************************/
void write_callback(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device->getDeviceName();
    const char *param_name = param->getParamName();
    //----------------------------------------------------------------------------------
    if(strcmp(device_name, device1) == 0) {
      
      Serial.printf("Lightbulb1 = %s\n", val.val.b? "true" : "false");
      
      if(strcmp(param_name, "Power") == 0) {
        //Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        STATE_RELAY_1 = val.val.b;
        STATE_RELAY_1 = !STATE_RELAY_1;
        control_relay(1, RELAY_1, STATE_RELAY_1);
        //(STATE_RELAY_1 == false) ? digitalWrite(RELAY_1, HIGH) : digitalWrite(RELAY_1, LOW);
        //param->updateAndReport(val);
      }
    }
    //----------------------------------------------------------------------------------
    else if(strcmp(device_name, device2) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");

      if(strcmp(param_name, "Power") == 0) {
        //Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        STATE_RELAY_2 = val.val.b;
        STATE_RELAY_2 = !STATE_RELAY_2;
        control_relay(2, RELAY_2, STATE_RELAY_2);
        //(STATE_RELAY_2 == false) ? digitalWrite(RELAY_2, HIGH) : digitalWrite(RELAY_2, LOW);
        //param->updateAndReport(val);
      }
    }
    //----------------------------------------------------------------------------------
    else if(strcmp(device_name, device3) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");

      if(strcmp(param_name, "Power") == 0) {
        //Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        STATE_RELAY_3 = val.val.b;
        STATE_RELAY_3 = !STATE_RELAY_3;
        control_relay(3, RELAY_3, STATE_RELAY_3);        
        //(STATE_RELAY_3 == false) ? digitalWrite(RELAY_3, HIGH) : digitalWrite(RELAY_3, LOW);
        //param->updateAndReport(val);
      }
  
    }
    //----------------------------------------------------------------------------------
    else if(strcmp(device_name, device4) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");

      if(strcmp(param_name, "Power") == 0) {
        //Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        STATE_RELAY_4 = val.val.b;
        STATE_RELAY_4 = !STATE_RELAY_4;
        control_relay(4, RELAY_4, STATE_RELAY_4);
        //(STATE_RELAY_4 == false) ? digitalWrite(RELAY_4, HIGH) : digitalWrite(RELAY_4, LOW);
        //param->updateAndReport(val);
      } 
    }
    //----------------------------------------------------------------------------------
     else if(strcmp(device_name, device5) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");

      if(strcmp(param_name, "Power") == 0) {
        //Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        STATE_RELAY_5 = val.val.b;
        STATE_RELAY_5 = !STATE_RELAY_5;
        control_relay(5, RELAY_5, STATE_RELAY_5);
        //(STATE_RELAY_5 == false) ? digitalWrite(RELAY_5, HIGH) : digitalWrite(RELAY_5, LOW);
        //param->updateAndReport(val);
      } 
    }
    //----------------------------------------------------------------------------------
     else if(strcmp(device_name, device6) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");

      if(strcmp(param_name, "Power") == 0) {
        //Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        STATE_RELAY_6 = val.val.b;
        STATE_RELAY_6 = !STATE_RELAY_6;
        control_relay(6, RELAY_6, STATE_RELAY_6);
        //(STATE_RELAY_6 == false) ? digitalWrite(RELAY_6, HIGH) : digitalWrite(RELAY_6, LOW);
        //param->updateAndReport(val);
      } 
    }
    //----------------------------------------------------------------------------------
     else if(strcmp(device_name, device7) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");

      if(strcmp(param_name, "Power") == 0) {
        //Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        STATE_RELAY_7 = val.val.b;
        STATE_RELAY_7 = !STATE_RELAY_7;
        control_relay(7, RELAY_7, STATE_RELAY_7);
        //(STATE_RELAY_7 == false) ? digitalWrite(RELAY_7, HIGH) : digitalWrite(RELAY_7, LOW);
        //param->updateAndReport(val);
      } 
    }
    //----------------------------------------------------------------------------------
     else if(strcmp(device_name, device8) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");

      if(strcmp(param_name, "Power") == 0) {
        //Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        STATE_RELAY_8 = val.val.b;
        STATE_RELAY_8 = !STATE_RELAY_8;
        control_relay(8, RELAY_8, STATE_RELAY_8);
        //(STATE_RELAY_8 == false) ? digitalWrite(RELAY_8, HIGH) : digitalWrite(RELAY_8, LOW);
        //param->updateAndReport(val);
      } 
    }
    //---------------------------------------------------------------------------------- 
}

/****************************************************************************************************
 * setup Function
*****************************************************************************************************/
void setup(){
  //------------------------------------------------------------------------------
  uint32_t chipId = 0;
  Serial.begin(115200);
  //------------------------------------------------------------------------------
  // initialize EEPROM with predefined size
  EEPROM.begin(EEPROM_SIZE);
  //------------------------------------------------------------------------------
  IrReceiver.begin(IR_RECEIVE_PIN); // Start the IR receiver
  //------------------------------------------------------------------------------
  // Set the Relays GPIOs as output mode
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
  pinMode(RELAY_5, OUTPUT);
  pinMode(RELAY_6, OUTPUT);
  pinMode(RELAY_7, OUTPUT);
  pinMode(RELAY_8, OUTPUT);
  //------------------------------------------------------------------------------
  // set debounce time to 100 milliseconds
  button1.setDebounceTime(100);
  button2.setDebounceTime(100);
  button3.setDebounceTime(100);
  button4.setDebounceTime(100);
  button5.setDebounceTime(100);
  button6.setDebounceTime(100);
  button7.setDebounceTime(100);
  button8.setDebounceTime(100);
  //------------------------------------------------------------------------------
  pinMode(gpio_reset, INPUT);
  pinMode(WIFI_LED, OUTPUT);
  digitalWrite(WIFI_LED, LOW);
  //------------------------------------------------------------------------------
  // Write to the GPIOs the default state on booting
  button1.setDebounceTime(100);
  button2.setDebounceTime(100);
  button3.setDebounceTime(100);
  button4.setDebounceTime(100);
  button5.setDebounceTime(100);
  button6.setDebounceTime(100);
  button7.setDebounceTime(100);
  button8.setDebounceTime(100);
  //------------------------------------------------------------------------------
  Node my_node;    
  my_node = RMaker.initNode("Kundu_homes");
  //------------------------------------------------------------------------------
  //Standard switch device
  my_switch1.addCb(write_callback);
  my_switch2.addCb(write_callback);
  my_switch3.addCb(write_callback);
  my_switch4.addCb(write_callback);
  my_switch5.addCb(write_callback);
  my_switch6.addCb(write_callback);
  my_switch7.addCb(write_callback);
  my_switch8.addCb(write_callback);
  //------------------------------------------------------------------------------
  //Add switch device to the node   
  my_node.addDevice(my_switch1);
  my_node.addDevice(my_switch2);
  my_node.addDevice(my_switch3);
  my_node.addDevice(my_switch4);
  my_node.addDevice(my_switch5);
  my_node.addDevice(my_switch6);
  my_node.addDevice(my_switch7);
  my_node.addDevice(my_switch8);
  //------------------------------------------------------------------------------
  //This is optional 
  RMaker.enableOTA(OTA_USING_PARAMS);
  //If you want to enable scheduling, set time zone for your region using setTimeZone(). 
  //The list of available values are provided here https://rainmaker.espressif.com/docs/time-service.html
  // RMaker.setTimeZone("Asia/Shanghai");
  // Alternatively, enable the Timezone service and let the phone apps set the appropriate timezone
  RMaker.enableTZService();
  RMaker.enableSchedule();
  //------------------------------------------------------------------------------
  //Service Name
  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  Serial.printf("\nChip ID:  %d Service Name: %s\n", chipId, service_name);
  //------------------------------------------------------------------------------
  Serial.printf("\nStarting ESP-RainMaker\n");
  RMaker.start();
  //------------------------------------------------------------------------------
  WiFi.onEvent(sysProvEvent);
  #if CONFIG_IDF_TARGET_ESP32
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
  #else
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
  #endif
  //------------------------------------------------------------------------------
  STATE_RELAY_1 = EEPROM.read(0);
  STATE_RELAY_2 = EEPROM.read(1);
  STATE_RELAY_3 = EEPROM.read(2);
  STATE_RELAY_4 = EEPROM.read(3);
  STATE_RELAY_5 = EEPROM.read(4);
  STATE_RELAY_6 = EEPROM.read(5);
  STATE_RELAY_7 = EEPROM.read(6);
  STATE_RELAY_8 = EEPROM.read(7);
  
  digitalWrite(RELAY_1, STATE_RELAY_1);
  digitalWrite(RELAY_2, STATE_RELAY_2);
  digitalWrite(RELAY_3, STATE_RELAY_3);
  digitalWrite(RELAY_4, STATE_RELAY_4);
  digitalWrite(RELAY_5, STATE_RELAY_5);
  digitalWrite(RELAY_6, STATE_RELAY_6);
  digitalWrite(RELAY_7, STATE_RELAY_7);
  digitalWrite(RELAY_8, STATE_RELAY_8);
  
  my_switch1.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_1);
  my_switch2.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_2);
  my_switch3.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_3);
  my_switch4.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_4);
  my_switch5.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_5);
  my_switch6.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_6);
  my_switch7.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_7);
  my_switch8.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_8);

  Serial.printf("Relay1 is %s \n", STATE_RELAY_1? "ON" : "OFF");
  Serial.printf("Relay2 is %s \n", STATE_RELAY_2? "ON" : "OFF");
  Serial.printf("Relay3 is %s \n", STATE_RELAY_3? "ON" : "OFF");
  Serial.printf("Relay4 is %s \n", STATE_RELAY_4? "ON" : "OFF");
  Serial.printf("Relay5 is %s \n", STATE_RELAY_5? "ON" : "OFF");
  Serial.printf("Relay6 is %s \n", STATE_RELAY_6? "ON" : "OFF");
  Serial.printf("Relay7 is %s \n", STATE_RELAY_7? "ON" : "OFF");
  Serial.printf("Relay8 is %s \n", STATE_RELAY_8? "ON" : "OFF");
  //------------------------------------------------------------------------------
}

/****************************************************************************************************
 * loop Function
*****************************************************************************************************/
void loop()
{
  //------------------------------------------------------------------------------
  // Read GPIO0 (external button to reset device
  if(digitalRead(gpio_reset) == LOW) { //Push button pressed
    Serial.printf("Reset Button Pressed!\n");
    // Key debounce handling
    delay(100);
    int startTime = millis();
    while(digitalRead(gpio_reset) == LOW) delay(50);
    int endTime = millis();
    //_______________________________________________________________________
    if ((endTime - startTime) > 10000) {
      // If key pressed for more than 10secs, reset all
      Serial.printf("Reset to factory.\n");
      RMakerFactoryReset(2);
    } 
    //_______________________________________________________________________
    else if ((endTime - startTime) > 3000) {
      Serial.printf("Reset Wi-Fi.\n");
      // If key pressed for more than 3secs, but less than 10, reset Wi-Fi
      RMakerWiFiReset(2);
    }
    //_______________________________________________________________________
  }
  //------------------------------------------------------------------------------
  delay(100);
  
  if (WiFi.status() != WL_CONNECTED){
    //Serial.println("WiFi Not Connected");
    digitalWrite(WIFI_LED, LOW);
  }
  else{
    //Serial.println("WiFi Connected");
    digitalWrite(WIFI_LED, HIGH);
  }
  //------------------------------------------------------------------------------
  button_control();
  remote_control();
}

/*******************************************************************************
 * button_control function:
 ******************************************************************************/
void button_control(){
    button1.loop();
    if(button1.isPressed()){
      control_relay(1, RELAY_1, STATE_RELAY_1);
      my_switch1.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_1);
    }
    button2.loop();
    if(button2.isPressed()){
      control_relay(2, RELAY_2, STATE_RELAY_2);
      my_switch2.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_2);
    }
    button3.loop();
    if(button3.isPressed()){
      control_relay(3, RELAY_3, STATE_RELAY_3);
      my_switch3.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_3);
    }
    button4.loop();
    if(button4.isPressed()){
      control_relay(4, RELAY_4, STATE_RELAY_4);
      my_switch4.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_4);
    }
    button5.loop();
    if(button5.isPressed()){
      control_relay(5, RELAY_5, STATE_RELAY_5);
      my_switch5.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_5);
    }
    button6.loop();
    if(button6.isPressed()){
      control_relay(6, RELAY_6, STATE_RELAY_6);
      my_switch6.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_6);
    }
    button7.loop();
    if(button7.isPressed()){
      control_relay(7, RELAY_7, STATE_RELAY_7);
      my_switch7.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_7);
    }
    button8.loop();
    if(button8.isPressed()){
      control_relay(8, RELAY_8, STATE_RELAY_8);
      my_switch8.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_8);
    }
}

/****************************************************************************************************
 * control_relay Function
*****************************************************************************************************/
void control_relay(int relay_no, int relay_pin, boolean &status){
  status = !status;
  digitalWrite(relay_pin, status);
  EEPROM.write(relay_no-1, status);
  EEPROM.commit();
  String text = (status)? "ON" : "OFF";
  Serial.println("Relay"+String(relay_no)+" is "+text);
}

/****************************************************************************************************
 * remote_control Function
*****************************************************************************************************/
void remote_control()
{
   if (IrReceiver.decode()) {
      String ir_code = String(IrReceiver.decodedIRData.command, HEX);
      if(ir_code.equals("0")) {IrReceiver.resume();return; }
      
      Serial.println(ir_code);
      
      if(ir_code == "a"){
        control_relay(1, RELAY_1, STATE_RELAY_1);
        my_switch1.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_1);
      }
      else if(ir_code == "1b"){
        control_relay(2, RELAY_2, STATE_RELAY_2);
        my_switch2.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_2);
      }
      else if(ir_code == "1f"){
        control_relay(3, RELAY_3, STATE_RELAY_3);
        my_switch3.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_3);
      }
      else if(ir_code == "c"){
        control_relay(4, RELAY_4, STATE_RELAY_4);
        my_switch4.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_4);
      }
      else if(ir_code == "d"){
        control_relay(5, RELAY_5, STATE_RELAY_5);
        my_switch5.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_5);
      }
      else if(ir_code == "e"){
        control_relay(6, RELAY_6, STATE_RELAY_6);
        my_switch6.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_6);
      }
      else if(ir_code == "12"){
        control_relay(7, RELAY_7, STATE_RELAY_7);
        my_switch7.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_7);
      }
      else if(ir_code == "f"){
        control_relay(8, RELAY_8, STATE_RELAY_8);
        my_switch8.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, STATE_RELAY_8);
      }
      
        
      IrReceiver.resume();
   }
}
