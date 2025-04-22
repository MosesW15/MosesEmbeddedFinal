#include "gameplay.h" 


void runGameplay(uint8_t gameMode){

if(gameMode == 1){
    
   static char board[7][6];
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 6; j++){
            board[i][j] = '.';
        }
    }
    
    LCD_Clear(0, LCD_COLOR_BLUE);
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 6; j++){
            LCD_Draw_Circle_Fill(25 + i*32, 80 + j*35, 15, LCD_COLOR_WHITE);
        }
    }

}
if(gameMode == 2){
   
   static char board[7][6];
   for(int i = 0; i < 7; i++){
       for(int j = 0; j < 6; j++){
           board[i][j] = '.';
       }
   }
  
   LCD_Clear(0, LCD_COLOR_BLUE);
   for(int i = 0; i < 7; i++){
       for(int j = 0; j < 6; j++){
           LCD_Draw_Circle_Fill(25 + i*32, 80 + j*35, 15, LCD_COLOR_WHITE);
       }
   }
}
while(1){

}
}