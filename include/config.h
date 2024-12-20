#ifndef __CONFIG_H
#define __CONFIG_H

// If DEBUG is defined, it won't boot without a USB cable
#define DEBUG
// #define USE_GUI
// #define USE_NOTECARD

// From Demo
#define GC0308_ADDR  0x21 //Camera
#define LTR553_ADDR  0x23 //Ambient light sensor
#define AXP2101_ADDR 0x34 //Power management
#define AW88298_ADDR 0x36 //Audio Amp
#define FT6336_ADDR  0x38 //Cap Touch
#define ES7210_ADDR  0x40 //Audio ADC
#define BM8563_ADDR  0x51 //RTC
#define AW9523_ADDR  0x58 //IO Expander
#define BMI270_ADDR  0x69 //IMU
#define BMM150_ADDR  0x10 //Compass

//On EXT I2C Bus
#define NOTECARD_ADDR           0x17 //Not actually applied, but this is the default
#define MODULE_4IN8OUT_1_ADDR   0x45 
#define MODULE_4IN8OUT_2_ADDR   0x46
#define ADC_GAS_FLOW_ADDR       0x48
#define ADC_PH_ADDR             0x49
#define QUIIC_RELAY_ADDR        0x6C
#define MOTOR_FEATHERWING_ADDR  0x6F
#define M5_HBRIDGE_ADDR         0x20 // or 0x54?? something funny with powerup sequence...
#define M5_4_20MA_ADDR          0x55
#define M5_KMETER_ADDR          0x11


#define SYS_I2C_PORT 0
#define SYS_I2C_SDA  12
#define SYS_I2C_SCL  11

#define EXT_I2C_PORT 0

#define PORTA_PIN_0  1
#define PORTA_PIN_1  2
#define PORTB_PIN_0  8
#define PORTB_PIN_1  9
#define PORTC_PIN_0  18
#define PORTC_PIN_1  17

#define POWER_MODE_USB_IN_BUS_IN 0
#define POWER_MODE_USB_IN_BUS_OUT 1
#define POWER_MODE_USB_OUT_BUS_IN 2
#define POWER_MODE_USB_OUT_BUS_OUT 3

//Customised
#define PIN_SDA_I2C_SYS 12
#define PIN_SCL_I2C_SYS 11
#define PIN_SDA_I2C_EXT 2
#define PIN_SCL_I2C_EXT 1

#define PIN_RX_RS485 18
#define PIN_TX_RS485 17
#define PIN_DE_RS485 5

#define PIN_RX0 44
#define PIN_TX0 43

#define PIN_PULSE_COUNT 8
#define PIN_JACKET_RELAY 9

#define MOD_16RO_ID 1
#define NOTECARD_FETCH_INTERVAL_MS (10 * 1000)

#define NC_SYNC true
#define NC_MODE "continuous"
#define NC_INBOUND 1
#define NC_OUTBOUND 1

// defined in platformio.ini
// #define NC_UID "dwt.ac.uk.heatpump"
// #define NC_UID "dwt.ac.uk.septicsensor"
// #define NC_UID "dwt.ac.uk.gaslid"

#define RS485_BAUD 9600

#define FLOAT_DECIMALS 1

#define TERMINAL_LOG_LENGTH 512

#ifndef AUTO_VERSION
#define AUTO_VERSION "0.0.0"
#endif

#endif  // __CONFIG_H