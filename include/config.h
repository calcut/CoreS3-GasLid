#ifndef __CONFIG_H
#define __CONFIG_H

// If DEBUG is defined, it won't boot without a USB cable
#define DEBUG
#define USE_GUI
// #define USE_NOTECARD

// From Demo
#define GC0308_ADDR  0x21
#define LTR553_ADDR  0x23
#define AXP2101_ADDR 0x34
#define AW88298_ADDR 0x36
#define FT6336_ADDR  0x38
#define ES7210_ADDR  0x40
#define BM8563_ADDR  0x51
#define AW9523_ADDR  0x58
#define BMI270_ADDR  0x69
#define BMM150_ADDR  0x10

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

#define MOD_16RO_ID 1
#define NOTECARD_FETCH_INTERVAL_MS (10 * 1000)

#define NC_SYNC true
#define NC_MODE "continuous"
#define NC_INBOUND 1
#define NC_OUTBOUND 1
#define NC_UID "dwt.ac.uk.heatpump"

#define RS485_BAUD 9600

#define FLOAT_DECIMALS 1

#define TERMINAL_LOG_LENGTH 512



#endif  // __CONFIG_H