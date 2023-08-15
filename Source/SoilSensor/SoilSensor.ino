//#include <ESP8266WiFi.h>
#include "offset_memory.h"
#include "sensor.h"


void setup(void) {

  Serial.begin(115200);
  setup_sensor();
  read_offset();
}

void loop(void) {
  setup_sensor();
  read_offset();
dataRead_print();
  // Serial.print("PH => ");
  // Serial.println(phv_arr);

  // Serial.print("con => ");
  // Serial.println(con_arr);

  // Serial.print("tem => ");
  // Serial.println(tem_arr);

  // Serial.print("moi  => ");
  // Serial.println(moi_arr);

  delay(3000);
}
