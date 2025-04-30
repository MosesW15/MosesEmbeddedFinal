#include "gameplay.h" 


#define RED 'R'
#define YELLOW 'Y'

extern RNG_HandleTypeDef hrng;
extern uint16_t scoreR, scoreY;   
extern uint16_t roundtime;

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS


static char board[COLS][ROWS];

static void initBoard(void){
    for(int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++){
            board[i][j] = '.';
        }
    }
}

static void drawGrid(void){
    LCD_Clear(0, LCD_COLOR_BLUE);
    for(int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++){
            LCD_Draw_Circle_Fill(25 + i*32, 80 + j*35, 15, LCD_COLOR_WHITE);
        }
    }
}

static int countDir(int i, int j, int movei, int movej, char piece) {
    int count = 0;
    for (int move = 0; move < 4; move++) {
        int currCol = i + movei * move;
        int currRow = j + movej * move;
        if (currCol < 0 || currCol >= COLS || currRow < 0 || currRow >= ROWS) {
            break;
        }
        if (board[currCol][currRow] != piece) {
            break;
        }
        count++;
    }
    return count;
}


static int checkWin(char piece) {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (board[i][j] != piece) continue;
            if ( countDir(i,j,1,0,piece) == 4 ) return 1;  
            if ( countDir(i,j,0,1,piece) == 4 ) return 1;  
            if ( countDir(i,j,1,1,piece) == 4 ) return 1;  
            if ( countDir(i,j,1,-1,piece)== 4 ) return 1; 
        }
    }
    return 0;
}

static int isDraw(void) {
    for (int i = 0; i < COLS; i++) {
        if (board[i][0] == '.') {
            return 0;
        }
    }
    return 1;
}

static int dropPiece(int i, char piece) {
    for (int j = ROWS - 1; j >= 0; j--) {
        if (board[i][j] == '.') {
            board[i][j] = piece;
            return 1;
        }
    }
    return 0;
}

void runGameplay(uint8_t gameMode){

    if(gameMode == 1){
        initBoard();
        drawGrid();

        int selcol = 3;
        int starttime = HAL_GetTick();

        while(1){
            int touchx, touchy;

            for(int c = 0; c < COLS; c++){
                for(int r = 0; r < ROWS; r++){
                    if(board[c][r] == RED){
                        LCD_Draw_Circle_Fill(25 + c*32, 80 + r*35, 15, LCD_COLOR_RED);
                    } else if(board[c][r] == YELLOW){
                        LCD_Draw_Circle_Fill(25 + c*32, 80 + r*35, 15, LCD_COLOR_YELLOW);
                    }
                }
            }

            LCD_Draw_Circle_Fill(25 + selcol*32, 40, 15, LCD_COLOR_RED);

            if(returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed){
                touchx = StaticTouchData.x;
                touchy = StaticTouchData.y;

                if(touchy < 80){
                    if(touchx < 160){
                        if(selcol < COLS - 1){
                            selcol++;
                        }
                    } else {
                        if(selcol > 0){
                            selcol--;
                        }
                    }
                }
                else {
                    if(dropPiece(selcol, RED)){
                        if(checkWin(RED) || isDraw()){
                            roundtime = (HAL_GetTick() - starttime) / 1000;
                            scoreR++;
                            break;
                        }
                        while(1){
                            uint32_t rnd = HAL_RNG_GetRandomNumber(&hrng);
                            int aiCol = rnd % COLS;
                            if(dropPiece(aiCol, YELLOW)) break;
                        }
                        if(checkWin(YELLOW) || isDraw()){
                            roundtime = (HAL_GetTick() - starttime) / 1000;
                            scoreY++;
                            break;
                        }
                    }
                }
            }
            HAL_Delay(100);
        }
    }
    if(gameMode == 2){
        initBoard();
        drawGrid();

        int selcol = 3;
        char currP = RED;
        int starttime = HAL_GetTick();

        while(1){
            int touchx, touchy;

            for(int c = 0; c < COLS; c++){
                for(int r = 0; r < ROWS; r++){
                    if(board[c][r] == RED){
                        LCD_Draw_Circle_Fill(25 + c*32, 80 + r*35, 15, LCD_COLOR_RED);
                    } else if(board[c][r] == YELLOW){
                        LCD_Draw_Circle_Fill(25 + c*32, 80 + r*35, 15, LCD_COLOR_YELLOW);
                    }
                }
            }
            if(currP == RED){
                LCD_Draw_Circle_Fill(25 + selcol*32, 40, 15, LCD_COLOR_RED);
            } else {
                LCD_Draw_Circle_Fill(25 + selcol*32, 40, 15, LCD_COLOR_YELLOW);
            }
            if(returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed){
                touchx = StaticTouchData.x;
                touchy = StaticTouchData.y;

                if(touchy < 80){
                    if(touchx < 160){
                        if(selcol < COLS - 1){
                            selcol++;
                        }
                    } else {
                        if(selcol > 0){
                            selcol--;
                        }
                    }
                }
                else {
                    if(dropPiece(selcol, currP)){
                        if(checkWin(currP) || isDraw()){
                            roundtime = (HAL_GetTick() - starttime) / 1000;
                            if(currP == RED){
                                scoreR++;
                            } else {
                                scoreY++;
                            }
                            break;
                        }
                        if(currP == RED){
                            currP = YELLOW;
                        } else {
                            currP = RED;
                        }
                    }
                }
            }
            HAL_Delay(100);
        }
    }
}