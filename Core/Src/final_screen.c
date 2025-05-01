#include "final_screen.h"

extern uint16_t scoreR, scoreY;   
extern uint16_t roundtime;

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif

void LCD_Final_Screen(void) {
    int touchx, touchy;

    LCD_Clear(0, LCD_COLOR_WHITE);
    LCD_SetFont(&Font16x24);
    LCD_SetTextColor(LCD_COLOR_BLACK);

    LCD_DisplayChar(20,  60, 'R');
    LCD_DisplayChar(32,  60, 'e');
    LCD_DisplayChar(44,  60, 'd');
    LCD_DisplayChar(56,  60, ':');
    LCD_DisplayChar(80,  60, '0' + scoreR);

    LCD_DisplayChar(20, 100, 'Y');
    LCD_DisplayChar(32, 100, 'e');
    LCD_DisplayChar(44, 100, 'l');
    LCD_DisplayChar(56, 100, 'l');
    LCD_DisplayChar(68, 100, 'o');
    LCD_DisplayChar(80, 100, 'w');
    LCD_DisplayChar(92, 100, ':');
    LCD_DisplayChar(116, 100, '0' + scoreY);

    LCD_DisplayChar(20, 140, 'T');
    LCD_DisplayChar(32, 140, 'i');
    LCD_DisplayChar(44, 140, 'm');
    LCD_DisplayChar(56, 140, 'e');
    LCD_DisplayChar(68, 140, ':');
    LCD_DisplayChar(92, 140, '0' + roundtime);
    LCD_DisplayChar(104,140,'s');

    LCD_Draw_Circle_Fill(160, 200, 50, LCD_COLOR_GREEN);
    LCD_DisplayChar( 10, 192, 'R');
    LCD_DisplayChar( 20, 192, 'e');
    LCD_DisplayChar( 30, 192, 's');
    LCD_DisplayChar( 40, 192, 't');
    LCD_DisplayChar( 50, 192, 'a');
    LCD_DisplayChar( 60, 192, 'r');
    LCD_DisplayChar( 70, 192, 't');

#if COMPILE_TOUCH_FUNCTIONS == 1
    while (1) {
        if (returnTouchStateAndLocation(&StaticTouchData)
            == STMPE811_State_Pressed) 
        {
            touchx = StaticTouchData.x;
            touchy = StaticTouchData.y;
            if (touchx >= 110 && touchx <= 210 &&
                touchy >= 150 && touchy <= 250)
            {
                return;
            }
        }
        HAL_Delay(50);
    }
#endif
}