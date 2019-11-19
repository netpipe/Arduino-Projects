#include <SWire.h>     // for I2C
 
#define eeprom_address 0x50    // device address 
byte d=0;
 
void setup()
{
  Serial.begin(115200); // Initialize the serial
  SWire.begin(4,5);
 
  //write data out
  Serial.println("Writing data.");
  for (int i=0; i<10; i++)
  {
    writeData(i,i);
  }
  Serial.println("Complete");
  //read data back
  Serial.println("Reading data.");
  for (int i=0; i<10; i++)
  {
    Serial.print(i);
    Serial.print(" : ");
    d=readData(i);
    Serial.println(d, DEC);
  }
  Serial.println("Complete");
 
}
 
// writes a byte of data in memory location eaddress
void writeData(unsigned int eaddress, byte data)
{
  SWire.beginTransmission(eeprom_address);
  // set the pointer position
  SWire.write((int)(eaddress >> 8));
  SWire.write((int)(eaddress & 0xFF));
  SWire.write(data);
  SWire.endTransmission();
  delay(10);
}
 
// reads a byte of data from memory location eaddress
byte readData(unsigned int eaddress)
{
  byte result;
  SWire.beginTransmission(eeprom_address);
  // set the pointer position
  SWire.write((int)(eaddress >> 8));
  SWire.write((int)(eaddress & 0xFF));
  SWire.endTransmission();
  SWire.requestFrom(eeprom_address,1); // get the byte of data
  result = SWire.read();
  return result;
}
 
void loop()
{
}
