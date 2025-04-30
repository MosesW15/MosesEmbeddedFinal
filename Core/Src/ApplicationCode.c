/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */


extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#endif // COMPILE_TOUCH_FUNCTIONS
}

void LCD_Visual_Demo(void)
{
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}
#endif // COMPILE_TOUCH_FUNCTIONS

#if COMPILE_TOUCH_FUNCTIONS == 1
int LCD_First_Screen()
{
	LCD_Clear(0,LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	
	while (1) {
		LCD_DisplayChar(0,50,'1');
//		LCD_DisplayChar(5,50,'   ');
		LCD_DisplayChar(10,50,'P');
		LCD_DisplayChar(20,50,'l');
		LCD_DisplayChar(30,50,'a');
		LCD_DisplayChar(40,50,'y');
		LCD_DisplayChar(50,50,'e');
		LCD_DisplayChar(60,50,'r');
		LCD_DisplayChar(70,50,':');
		LCD_Draw_Circle_Fill(160,60,50,LCD_COLOR_BLUE);
	
		LCD_DisplayChar(0,230,'2');
//		LCD_DisplayChar(5,230,'   ');
		LCD_DisplayChar(10,230,'P');
		LCD_DisplayChar(20,230,'l');
		LCD_DisplayChar(30,230,'a');
		LCD_DisplayChar(40,230,'y');
		LCD_DisplayChar(50,230,'e');
		LCD_DisplayChar(60,230,'r');
		LCD_DisplayChar(70,230,':');
		LCD_Draw_Circle_Fill(160,240,50,LCD_COLOR_YELLOW);

LCD_DisplayChar(0, 140, 'W');
LCD_DisplayChar(5,140,' ');
LCD_DisplayChar(10, 140, 'e');
LCD_DisplayChar(20, 140, 'l');
LCD_DisplayChar(30, 140, 'c');
LCD_DisplayChar(40, 140, 'o');
LCD_DisplayChar(50, 140, 'm');
LCD_DisplayChar(60, 140, 'e');
LCD_DisplayChar(70, 140, ' ');
LCD_DisplayChar(80, 140, 'T');
LCD_DisplayChar(90, 140, 'o');
LCD_DisplayChar(100, 140, ' ');
LCD_DisplayChar(110, 140, 'C');
LCD_DisplayChar(120, 140, 'o');
LCD_DisplayChar(130, 140, 'n');
LCD_DisplayChar(135,140,' ');
LCD_DisplayChar(140, 140, 'n');
LCD_DisplayChar(150, 140, 'e');
LCD_DisplayChar(160, 140, 'c');
LCD_DisplayChar(170, 140, 't');
LCD_DisplayChar(180, 140, ' ');
LCD_DisplayChar(190, 140, 'F');
LCD_DisplayChar(200, 140, 'o');
LCD_DisplayChar(210, 140, 'u');
LCD_DisplayChar(220, 140, 'r');
LCD_DisplayChar(230, 140, '!');
		
	if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			int x = StaticTouchData.x;
			int y = StaticTouchData.y;
			if(x >= 110 && x <= 210 && y >= 190  && y <= 290){
				return 1;
			}
			if(x >= 110 && x <= 210 && y >= 10 && y <= 110){
				return 2;
			}
			HAL_Delay(1000);
		}
	}
}
#endif
