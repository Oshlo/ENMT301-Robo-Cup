//************************************
//         ps2controller.h    
//************************************

#ifndef PS2CONTROLLER_H_
#define PS2CONTROLLER_H_

#define PS2_CLOCK_ADDR 45
#define PS2_COMMAND_ADDR 43
#define PS2_ATTENTION_ADDR 44
#define PS2_DATA_ADDR 42

#define BUT_NUM 24

#include <PS2X_lib.h>
extern PS2X ps2x;

void ps2_init();
void ps2_update();
void button_logic_callback();
void serial_control_callback();

#endif
