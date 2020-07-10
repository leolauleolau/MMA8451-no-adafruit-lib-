#include<Wire.h>

const int mmw_addr = 0x1C; // 0x1c for accelerometer address


void setup() {
  Wire.begin();
  Wire.beginTransmission(mmw_addr);
  Wire.write(0x2A); //wake the device at REGL_CTR
  Wire.write(1);   //set it 1 to be awake as from the ref data sheet
  Wire.endTransmission(true);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(mmw_addr);
  Wire.write(0x01);  //The address of the x-axis data stored
  Wire.endTransmission(false);
  Wire.requestFrom(mmw_addr, 6, true);
  
  int x = Wire.read(); x <<= 8; x |= Wire.read(); x >>= 2;
  int y = Wire.read(); y <<= 8; y |= Wire.read(); y >>= 2;
  int z = Wire.read(); z <<= 8; z |= Wire.read(); z >>= 2;
  Serial.print("x: "); Serial.print("\t"); Serial.println((float)x/4096); //2g range is divided by 4096
  Serial.print("y: "); Serial.print("\t");   Serial.println((float)y/4096);
  Serial.print("z: "); Serial.print("\t");   Serial.println((float)z/4096);
  Serial.println();
  delay(500);
}
