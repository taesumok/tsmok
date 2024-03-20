#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
enum { BLACK, DARK_BLUE, DARK_GREEN, DARK_SKY_BLUE, DARK_RED, DARK_VIOLET, DARK_YELLOW, GRAY, DARK_GRAY, BLUE, GREEN, SKY_BLUE, RED, VIOLET, YELLOW, WHITE};

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 22
#define CLOCKWISE           0
#define COUNTER_CLOCKWISE   1
#define MAX_BLOCK_LIST      5
#define LATENCY             200
typedef struct _TBlock{
    int type;
    int len;
    int state;
    COORD vector[4];
}TBlock;

int start_x = 1, start_y = 2;
char board_buffer[BOARD_HEIGHT][BOARD_WIDTH];
char board[BOARD_HEIGHT][BOARD_WIDTH];
TBlock block_list[MAX_BLOCK_LIST];
int statitics[7];
unsigned int gScore = 0;
unsigned int gLines = 0;

unsigned int gSpeed = 1000;
unsigned int gMoveDelay = 100;
unsigned int gRotateDelay = 80;
unsigned int gSpaceDelay = 220;
clock_t gLatency = 0;
int tspin_weight = 1;
bool tspin_opt = true;
bool rotation_opt = CLOCKWISE;
//clock_t gMovedBlock = 0;

enum { BLANK, I_BLOCK, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, T_BLOCK, Z_BLOCK};

void setColor(int ForeColor, int BackColor)
{
    int color = ForeColor | (BackColor << 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void cursorToggle(BOOL _cursor)
{
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible=_cursor;
	curInfo.dwSize=1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void drawTile(int tile)
{
    static char fcolor_set[10] = {BLACK, RED, BLUE, WHITE, YELLOW, VIOLET, SKY_BLUE, GREEN };
    static char bcolor_set[10] = {BLACK, DARK_RED, DARK_BLUE, BLACK, DARK_YELLOW, DARK_VIOLET, BLACK, DARK_GREEN };
    setColor(fcolor_set[tile], bcolor_set[tile]);
    printf("¡á");
    setColor(GRAY, BLACK);
}
void drawScore(int x, int y){
    setColor(YELLOW,BLACK);
    gotoxy(x,y);
    printf("Score :%6d",gScore);
    gotoxy(x,y+2);
    printf("Lines :%6d",gLines);
}
void drawFrame()
{
    int x,y;
    setColor(WHITE,BLACK);
    for(y=0; y<BOARD_HEIGHT; y++){
        gotoxy(2*(start_x-1), y+start_y);
        printf("¦¢");
        gotoxy(2*(start_x+BOARD_WIDTH), y+start_y);
        printf("¦¢");
    }
    gotoxy(2*(start_x-1), y+start_y);
    printf("¦¦");
    gotoxy(2*(start_x+BOARD_WIDTH), y+start_y);
    printf("¦¥");
    for(x=0; x<BOARD_WIDTH; x++){
        gotoxy(2*(start_x+x), start_y+BOARD_HEIGHT);
        printf("¦¡");
    }
    setColor(WHITE, BLACK);
}
void drawInfo(){
    int x=44,y=6;
    gotoxy(x, y); printf("      T-spin : %s", tspin_opt?"possible":"impossible");
    gotoxy(x,y+1);printf("  rotatation : %s", rotation_opt?"conuter-clockwise":"clockwise");
    gotoxy(x,y+2);printf("       speed : %d", gSpeed);
    gotoxy(x,y+3);printf("     m-delay : %d", gMoveDelay);
    gotoxy(x,y+4);printf("     r-delay : %d", gRotateDelay);
    gotoxy(x,y+5);printf("     d-delay : %d", gSpaceDelay);
    gotoxy(x,y+6);printf("     latency : %d", LATENCY);
}
void drawDebug(char board[BOARD_HEIGHT][BOARD_WIDTH], int x_pos){
    int x,y;
    for(y=0; y<BOARD_HEIGHT; y++){
        gotoxy(2*(start_x+x)+x_pos+BOARD_WIDTH, start_y+y);
        for(x=0; x<BOARD_WIDTH; x++){
            if( board[y][x]!= BLANK )
                setColor(RED, BLACK);
            else
                setColor(GRAY, BLACK);
            printf("%02d", board[y][x]);
        }
    }
    setColor(GRAY, BLACK);
}
void drawBoard()
{
    int x,y;
    for(y=0; y<BOARD_HEIGHT; y++){
        for(x=0; x<BOARD_WIDTH; x++){
            if( board[y][x] != board_buffer[y][x] ){
                gotoxy(2*(start_x+x), start_y+y);
                drawTile(board_buffer[y][x]);
                board[y][x] = board_buffer[y][x];
            }
        }
    }
}

void drawBlock(TBlock *block)
{
    int x = block->vector[0].X, y = block->vector[0].Y;
    int i=0;
    gotoxy(2*(start_x+x),start_y+y);
    drawTile(block->type);
    for(i=1; i<block->len; i++){
        x = block->vector[0].X+block->vector[i].X;
        y = block->vector[0].Y+block->vector[i].Y;
        gotoxy(2*(start_x+x),start_y+y);
        drawTile(block->type);
    }
}

void eraseBlock(TBlock *block)
{
    int x = block->vector[0].X, y = block->vector[0].Y;
    int i=0;
    gotoxy(2*(start_x+x),start_y+y);
    drawTile(BLANK);
    for(i=1; i<block->len; i++){
        x = block->vector[0].X+block->vector[i].X;
        y = block->vector[0].Y+block->vector[i].Y;
        gotoxy(2*(start_x+x),start_y+y);
        drawTile(BLANK);
    }
}
void drawPreview(int n){

    TBlock block;
    int i=0;
    for(i=0; i<n; i++){
        eraseBlock(&block_list[i]);
        block_list[i].vector[0] = {BOARD_WIDTH+start_x+3, i*3};
        drawBlock(&block_list[i]);
    }
}
void makeBlock(int nBlock, TBlock *block)
{
    static COORD block_init[7][3] = {
        {   // I_BLOCK
            {-1,0},{1,0},{2,0},
        },
        {   // J_BLOCK
            {-1,0},{1,0},{1,1},
        },
        {   // L_BLOCK
            {-1,0},{1,0},{-1,1},
        },
        {   // O_BLOCK
            {1,0},{0,1},{1,1},
        },
        {   // S_BLOCK
            {1,0},{-1,1},{0,1},
        },
        {   // T_BLOCK
            {-1,0},{1,0},{0,1},
        },
        {   // Z_BLOCK
            {-1,0},{0,1},{1,1},
        },
    };
    int i=0;
    block->vector[0] = {2*(start_x+BOARD_WIDTH)+4, 7*3};
    block->len = 4;
    block->type = nBlock;
    for(i=0; i<3; i++){
        block->vector[i+1] = block_init[nBlock-1][i];
    }
}
void drawStatitic(void){

    static char fcolor_set[10] = {BLACK, RED, BLUE, WHITE, YELLOW, VIOLET, SKY_BLUE, GREEN };
    static char tetrinomix[7] = {'I','J','L','O','S','T','Z'};
    int i=1;
    for(i=0; i<7; i++){
        gotoxy(2*BOARD_WIDTH+6,17+i);
        setColor(fcolor_set[i+1],BLACK);
        printf("%c -%3d",tetrinomix[i],statitics[i]);
    }
}
void generate_block(TBlock *block)
{
    static TBlock buf[MAX_BLOCK_LIST];
    memcpy(buf,block_list,sizeof(TBlock)*MAX_BLOCK_LIST);
    *block = block_list[0];
    eraseBlock(block);
    block->vector[0] = {4, 2};
    statitics[block->type-1]++;
    memcpy(block_list,buf+1,sizeof(TBlock)*(MAX_BLOCK_LIST-1));
    makeBlock(rand()%7+1, &block_list[MAX_BLOCK_LIST-1]);
    drawStatitic();
}
void moveDown(int y, int n){
    memcpy( board_buffer[y+n], board_buffer[y], sizeof(char)*10 );
    memset( board_buffer[y], 0, sizeof(char)*10 );
}
void destoryLine(){
    static int line[4];
    int x,y;
    int score;
    static int n=0,i=0;
    bool flag = true;
    for(i=0; i<n; i++){
        gotoxy(2*(BOARD_WIDTH+start_x)+4,line[i]+start_y);
        printf(" ");
    }
    n=0;
    for(y=BOARD_HEIGHT-1; y>=0; y--){
        flag = true;
        for(x=0; x<BOARD_WIDTH; x++){
            if(board[y][x] == BLANK){
                flag = false;
                break;
            }
        }
        if(flag)
            line[n++] = y;
    }
    for(i=0; i<n; i++){
        gotoxy(2*(BOARD_WIDTH+start_x)+4,line[i]+start_y);
        printf("<");
    }
    for(i=n-1; i>=0; i--){
        for(y=line[i]; y>0; y--){
            moveDown(y-1,1);
        }
    }
    if(n){
        gLines += n;
        score = 100*n*tspin_weight+(n==4?600:0);
        gScore += score;
        drawScore(2*BOARD_WIDTH+18,18);
        setColor(RED,BLACK);
        gotoxy(2*BOARD_WIDTH+22,19); printf("(+%4d)",score);
    }
    tspin_weight = 1;
}

bool isCrash(TBlock block){
    int i=0;
    int x,y;
    x = block.vector[0].X;
    y = block.vector[0].Y;

    if( board_buffer[y][x] != BLANK ){
        gotoxy(45,1);printf("point :%2d,%2d",x,y);
        return true;
    }
    if( x<0 || x>=BOARD_WIDTH || y<0 || y>=BOARD_HEIGHT ){
        gotoxy(45,1);printf("point :%2d,%2d",x,y);
        return true;
    }
    for( i=1; i<block.len; i++){
        x = block.vector[0].X;
        y = block.vector[0].Y;
        x += block.vector[i].X;
        y += block.vector[i].Y;
        if( board_buffer[y][x] != BLANK ){
            gotoxy(45,1);printf("point :%2d,%2d",x,y);
            return true;
        }
        if( x<0 || x>=BOARD_WIDTH || y<0 || y>=BOARD_HEIGHT ){
            gotoxy(45,1);printf("point :%2d,%2d",x,y);
            return true;
        }
    }
    return false;
}
bool checkCrash(TBlock block, int dir){
    switch(dir){
    case VK_RIGHT:
        block.vector[0].X++;
        break;
    case VK_LEFT:
        block.vector[0].X--;
        break;
    case VK_DOWN:
        block.vector[0].Y++;
        break;
    }
    return isCrash(block);
}
int rotate(TBlock *block){
    static COORD block_rotate[7][4][3] = {
        {   // I_BLOCK
            {{-1,0},{1,0},{2,0}},
            {{0,-1},{0,1},{0,2}},
            {{-2,0},{-1,0},{1,0}},
            {{0,-2},{0,-1},{0,1}}
        },
        {   // J_BLOCK
            {{-1,0},{1,0},{1,1}},
            {{0,-1},{-1,1},{0,1}},
            {{-1,-1},{-1,0},{1,0}},
            {{0,-1},{1,-1},{0,1}}
        },
        {   // L_BLOCK
            {{-1,0},{1,0},{-1,1}},
            {{-1,-1},{0,-1},{0,1}},
            {{-1,0},{1,0},{1,-1}},
            {{0,-1},{0,1},{1,1}}
        },
        {   // O_BLOCK
            {{1,0},{0,1},{1,1}},
            {{1,0},{0,1},{1,1}},
            {{1,0},{0,1},{1,1}},
            {{1,0},{0,1},{1,1}}
        },
        {   // S_BLOCK
            {{1,0},{-1,1},{0,1}},
            {{-1,-1},{-1,0},{0,1}},
            {{1,0},{-1,1},{0,1}},
            {{-1,-1},{-1,0},{0,1}}
        },
        {   // T_BLOCK
            {{-1,0},{1,0},{0,1}},
            {{0,-1},{-1,0},{0,1}},
            {{0,-1},{-1,0},{1,0}},
            {{0,-1},{1,0},{0,1}}
        },
        {   // Z_BLOCK
            {{-1,0},{0,1},{1,1}},
            {{1,-1},{1,0},{0,1}},
            {{-1,0},{0,1},{1,1}},
            {{1,-1},{1,0},{0,1}}
        },
    };
    static int a = 0;
    TBlock blockBuf = *block;

    int state = (block->state+1)%4;
    int type = blockBuf.type;
    int i=0;
    for(i=1; i<blockBuf.len; i++){
        blockBuf.vector[i] = block_rotate[type-1][state][i-1];
    }
    if(!isCrash(blockBuf)){
        blockBuf.state = state;
        *block = blockBuf;
        gotoxy(27,0); printf("rotate : success");
        return 1;
    }
    else{
        blockBuf.state = state;
        gotoxy(27,0); printf("rotate : fail   ");

        if( type == T_BLOCK && checkCrash(blockBuf, VK_DOWN)){
            if( rotation_opt == CLOCKWISE && state == 3 ){
                blockBuf.vector[0].X--;
                blockBuf.vector[0].Y += 2;
            }
            else if( rotation_opt == CLOCKWISE && state == 2){
                blockBuf.vector[0].X--;
                blockBuf.vector[0].Y++;
            }
            else if( rotation_opt == COUNTER_CLOCKWISE && state == 1){
                blockBuf.vector[0].X++;
                blockBuf.vector[0].Y += 2;
            }
            else if( rotation_opt == COUNTER_CLOCKWISE && state == 2){
                blockBuf.vector[0].X++;
                blockBuf.vector[0].Y++;
            }
            if(!isCrash(blockBuf)){
                blockBuf.state = state;
                *block = blockBuf;
                setColor(RED,BLACK);
                gotoxy(25,0); printf("rotate : T-spin");
                tspin_weight = 3;
                setColor(GRAY,BLACK);
                return 1;
            }
        }

    }
    gotoxy(27,1); printf(" state : %d,%2d", state,a++);
    gLatency = LATENCY;
    return 0;
}
int key_handler(){
    static char *cKey[2]={"down","up  "};
    SHORT key;
    int nKey;
    static int vkey[] = {VK_ESCAPE,VK_SPACE,VK_LEFT,VK_RIGHT,VK_DOWN,VK_UP};
    for(nKey=0; nKey<6; nKey++){
        key = GetAsyncKeyState(vkey[nKey]);
        gotoxy(60,0); printf("key : %s",cKey  [(key&0x8000)>0?0:1]);
        if( 0x8000 & key ){
            return vkey[nKey];
        }
    }
    return 0;
}

int key_wait(){
    static clock_t moveCooldown = 0;
    static clock_t spaceCooldown = 0;
    static clock_t rotateCooldown = 0;
    static clock_t begin = clock();
    static clock_t end = clock();
    static clock_t latency = 0;
    int key = 0;
    gotoxy(45,2); printf("begin :%5d", begin);
    gotoxy(45,3); printf("  end :%5d", end);
    while( (end-begin) < gSpeed+gLatency ){
        end = clock();
        gotoxy(60,2); printf("time :%5d", (int)end);
        gotoxy(60,3); printf("tick :%5d ", (int)(end-begin));
        if( clock() - moveCooldown > gMoveDelay ){
            key = key_handler();
            moveCooldown = clock();
        }
        if( key == VK_UP ){
            if( clock() - rotateCooldown < gRotateDelay ){
                key = 0;
            }
            else{
                rotateCooldown = clock();
            }  
        }
        if( key == VK_SPACE ){
            begin = clock();
            end = clock();
            if( clock() - spaceCooldown < gSpaceDelay ){
                key = 0;
            }
            else{
                spaceCooldown = clock();
            }
        }
        if(key!=0){
            gLatency = 0;
            return key;
        }
    }
    begin = clock();
    end = clock();
    gLatency = 0;
    return VK_DOWN;
}
void solid(TBlock block){
    int x = block.vector[0].X, y = block.vector[0].Y;
    int i=0;
    int type = block.type;
    board_buffer[y][x] = type;
    for(i=1; i < block.len; i++){
        x = block.vector[0].X+block.vector[i].X;
        y = block.vector[0].Y+block.vector[i].Y;
        board_buffer[y][x] = type;
    }
}
void initBlockList(){
    int i=0;
    for(i=0; i<MAX_BLOCK_LIST; i++){
        makeBlock(rand()%7+1, &block_list[i]);
        block_list[i].vector[0] = {BOARD_WIDTH+start_x+3, i*3};
    }
}
void drawGhost(TBlock block){
    static TBlock ghost;
    ghost = block;
    while(!isCrash(ghost)){
        ghost.vector[0].Y++;
    }
    ghost.vector[0].Y--;
    int x = ghost.vector[0].X, y = ghost.vector[0].Y;
    int i=0;
    gotoxy(2*(start_x+x),start_y+y);
    setColor(GRAY, BLACK);
    printf("¡á");
    for(i=1; i<block.len; i++){
        x = ghost.vector[0].X+ghost.vector[i].X;
        y = ghost.vector[0].Y+ghost.vector[i].Y;
        gotoxy(2*(start_x+x),start_y+y);
        printf("¡á");
    }
}
void eraseGhost(TBlock block){
    static TBlock ghost;
    ghost = block;
    while(!isCrash(ghost)){
        ghost.vector[0].Y++;
    }
    ghost.vector[0].Y--;
    int x = ghost.vector[0].X, y = ghost.vector[0].Y;
    int i=0;
    gotoxy(2*(start_x+x),start_y+y);
    setColor(GRAY, BLACK);
    printf("  ");
    for(i=1; i<block.len; i++){
        x = ghost.vector[0].X+ghost.vector[i].X;
        y = ghost.vector[0].Y+ghost.vector[i].Y;
        gotoxy(2*(start_x+x),start_y+y);
        printf("  ");
    }
}
int main(int argc, char *argv[])
{
    int x, y;
    srand(time(NULL));
    drawFrame();
    drawInfo();
    initBlockList();
    cursorToggle(false);
    for(y=0; y<20; y++){
        for(x=0; x<10; x++){
            board_buffer[y][x]=BLANK;
            board[y][x]=BLANK;
        }
    }

    TBlock curBlock;
    SHORT key;
    drawScore(2*BOARD_WIDTH+18,18);
    drawPreview(5);
    generate_block(&curBlock);
    drawGhost(curBlock);
    drawBlock(&curBlock);
    while(1){

        if(isCrash(curBlock)){
            break;
        }
//        drawDebug(board,-5);
//        drawDebug(board_buffer,16);
        if((key = key_wait())){
            gotoxy(60,1); printf("key : 0x%X",key);
            if( checkCrash(curBlock, key) ){
                if( key == VK_DOWN ){
//                    if(clock()-gMovedBlock < 900) continue;
                    solid(curBlock);
                    drawBlock(&curBlock);
                    drawBoard();
                    destoryLine();
                    drawBoard();
                    drawPreview(5);
                    generate_block(&curBlock);
                    drawGhost(curBlock);
                }
                gotoxy(45,0); printf("crash  ");
                continue;
            }
            else{
                gotoxy(45,0); printf("movable");
            }
            switch(key){
            case VK_UP:
                eraseBlock(&curBlock);
                eraseGhost(curBlock);
                rotate(&curBlock);
//                gMovedBlock = clock();
                break;
            case VK_RIGHT:
                eraseBlock(&curBlock);
                eraseGhost(curBlock);
                curBlock.vector[0].X++;
//                gMovedBlock = clock();
                break;
            case VK_LEFT:
                eraseBlock(&curBlock);
                eraseGhost(curBlock);
                curBlock.vector[0].X--;
//                gMovedBlock = clock();
                break;
            case VK_DOWN:
                eraseBlock(&curBlock);
                eraseGhost(curBlock);
                curBlock.vector[0].Y++;
//                gMovedBlock = clock();
                break;
            case VK_SPACE:
                eraseBlock(&curBlock);
                while(!checkCrash(curBlock,VK_DOWN)){
                    curBlock.vector[0].Y++;
                }
                eraseGhost(curBlock);
                solid(curBlock);
                drawBlock(&curBlock);
                drawBoard();
                destoryLine();
                drawPreview(5);
                generate_block(&curBlock);
                break;
            }
            drawBoard();
            drawGhost(curBlock);
            drawBlock(&curBlock);
        }
    }

    gotoxy(30,1);
    setColor(YELLOW,BLACK);
    printf(" - game over - ");
    gotoxy(0,21);
    setColor(GRAY,BLACK);
    system("pause>nul");
}
