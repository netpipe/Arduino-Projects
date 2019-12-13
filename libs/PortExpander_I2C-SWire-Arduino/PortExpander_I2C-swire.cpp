// blog.iharder.net
// Robert Harder
// Thanks to DFRobot.com for the LiquidCrystal_I2C code that helped me understand a lot
// August 2014


#include "PortExpander_I2C-swire.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif



/**
 * Creates a new PortExpander_I2C object with the given I2C address.
 */
PortExpander_I2C::PortExpander_I2C(uint8_t i2c_addr,uint8_t SDA1,uint8_t SCL1){
  _Addr = i2c_addr;
SDA=SDA1;
SCL=SCL1;
}

void PortExpander_I2C::init(){
	init_priv();
}

void PortExpander_I2C::init_priv(){
	_portValues = 0x00;
	SWire.begin(SDA,SCL);
    digitalWriteAll(0x00);
}


/**
 * Sets a port low (ground) or high (Vcc).
 * Port is a value 0-7 referring to the 8 ports on the expander.
 * "Low" is zero; "High" is anything else.
 */
void PortExpander_I2C::digitalWrite( uint8_t port, uint8_t level ){
    if( level == LOW ){ // LOW. 
        _portValues &= ~(1 << port);    // Clear the bit.
    } else {  // HIGH. 
        _portValues |= (0x01 << port);  // Set the bit.
    }
	i2cWrite(_portValues);              // Write to I2C
}

/**
 * Sets all the ports high or low according to the bitmask given,
 * where a 0 is low and a 1 is high. Internally this is how all
 * writes are sent to the port expander, so the single-port
 * digitalWrite command messes with the individual bits.
 */
void PortExpander_I2C::digitalWriteAll( uint8_t levels ){
    _portValues = levels;
	i2cWrite(_portValues);
}

/**
 * Convenience method for flipping the state of an output pin.
 */
void PortExpander_I2C::digitalToggle( uint8_t port ){
    _portValues ^= (1 << port );
	i2cWrite(_portValues);
}

/**
 * Sets a pin to INPUT or OUTPUT mode. Default is output. 
 * The TI PCF8574 port expander for which this library is built
 * requires a pin to be set HIGH before it can be read; that is
 * pin is able to detect a change when pulled low. If you need
 * a circuit that detects when a pin goes high, you'll need a 
 * transistor or something else to flip the signal. Setting a
 * a pin to input mode is the same as calling digitalWrite(x,HIGH).
 */
void PortExpander_I2C::pinMode( uint8_t port, uint8_t mode ){
    if( mode == INPUT ){
        digitalWrite(port, HIGH); // Set chip high and wait for being pulled to ground
    }
}

/**
 * Input pins are HIGH by default and they can be pulled to ground
 * to indicate a changed state.
 */
uint8_t PortExpander_I2C::digitalRead( uint8_t port ){
    SWire.requestFrom(_Addr,(uint8_t)1);
    uint8_t resp = SWire.read();
    return (resp & (1 << port)) > 0 ? HIGH : LOW;
}

/**
 * Returns a bit set with all pins represented.
 * Pins that were not set high will have meaningless values.
 */
uint8_t PortExpander_I2C::digitalReadAll(){
    SWire.requestFrom(_Addr,(uint8_t)1);
    uint8_t resp = SWire.read();
    return resp;
}

/**
 * Internal function to handle the I2C writing of data.
 */
void PortExpander_I2C::i2cWrite(uint8_t _data){                                        
	SWire.beginTransmission(_Addr);
	//printIIC((int)(_data) );//| _backlightval);
    SWire.write(_data);
	SWire.endTransmission();   
}


	
