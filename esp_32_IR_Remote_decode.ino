/*************************************************************************************
 *  Created By: Parthasarathi kundu
 *  Created On: 28 December, 2022
 *  
 *  https://www.youtube.com/channel/UCA5UPZuB3zHiS6a34iDLo6w
 *  
 *  *********************************************************************************
 *  Install the following libraries
 *  1. IRremote
 ***********************************************************************************/

#include <IRremote.h>
const byte IR_RECEIVE_PIN = 14;

void setup(){
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN); // Start the IR receiver
}
void loop(){
  if (IrReceiver.decode()) {
  String ir_code = String(IrReceiver.decodedIRData.command, HEX);
  if(ir_code.equals("0")) {IrReceiver.resume();return; }
  
  Serial.println(ir_code);
  IrReceiver.resume();
  }
  delay(1000);
}
