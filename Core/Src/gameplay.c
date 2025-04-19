#include "gameplay.h"
#include "lcd_driver.h"    

#include <stdint.h>

void runGameplay(uint8_t gameMode){
if(gameMode == 1){
    LCD_Clear(0, LCD_COLOR_GREEN);
}
if(gameMode == 2){
    LCD_Clear(0, LCD_COLOR_RED);
}
HAL_Delay(1000);
}