// (c) 2017 Jens Kallup
#include <stdio.h>

extern "C" {
    void clrscr(void);
    int  getcurx(void);
    int  getcury(void);
    int  getkey();
    void gotoxy(int,int);
};

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0005
#define KEY_DOWN    0x0006
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108

const int GAME_MAP_WIDTH  = 15;
const int GAME_MAP_HEIGHT = 10;

// 15x10
char game_map[GAME_MAP_HEIGHT][GAME_MAP_WIDTH] = {
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,3 },
{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,3 },
{ 1,2,2,8,2,2,2,2,2,2,2,2,2,2,3 },
{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,3 },
{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,3 },
{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,3 },
{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,3 },
{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,3 },
{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,3 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,3 }};

int main()
{
    int c,r,key;
    int xpos=0, ypos=0;
    
    clrscr();
    for (c = 0; c < GAME_MAP_HEIGHT; c++) {
    for (r = 0; r < GAME_MAP_WIDTH; r++) {
        if (game_map[c][r] == 4) break;
        if (game_map[c][r] == 1)      { printf("#"); }
        else if (game_map[c][r] == 8) {
            xpos = c;
            ypos = r;      printf("P");
        }
        else if (game_map[c][r] == 3) {
            printf("#\n");
            break;
        }
        else {
            printf(".");
        }
    }   }

    xpos += 2;
    gotoxy(xpos,ypos);
    
    // game loop
    while (1)
    {
        key = getkey();
        if (key > 0) {     
            if (key == 113 || key == KEY_ESCAPE) break;
            else if (key == '6') {
                // ------------------
                // player on wall ?
                // step over line ...
                // ------------------
                if (xpos > GAME_MAP_WIDTH-2 && ypos == GAME_MAP_HEIGHT-1) {
                    gotoxy(GAME_MAP_WIDTH-1,ypos);
                    printf(".");
                    xpos = 2;
                    ypos = 2;
                    gotoxy(xpos,ypos); printf("P");
                    gotoxy(xpos,ypos);
                    continue;
                }   else
                if (xpos >= 14) {
                    xpos = 1;
                    int sy = ypos;
                    if (++ypos == sy+1) {
                        gotoxy(GAME_MAP_WIDTH-1,sy);  printf(".");
                        gotoxy(1,ypos); printf("#");
                    }
                }
                gotoxy(++xpos  ,ypos); printf("P"); if (xpos > 2)
                gotoxy(  xpos-1,ypos); printf(".");
            }
            else if (key == '4')
            {
                int chr = '.';
                int pos = 1;
                if (xpos == 2 && ypos == 2) {
                    gotoxy(2,2); printf(".");
                    xpos = GAME_MAP_WIDTH;
                    ypos = GAME_MAP_HEIGHT - 1;
                    gotoxy(xpos+1,ypos);
                    printf("#");
                }   else
                if (xpos <= 2)   {
                    chr = '#';
                    pos =   0;
                    int sy = ypos;
                    int sx = xpos; xpos = GAME_MAP_WIDTH-1;
                    if (--ypos == sy-1) {
                        gotoxy(2,sy);    printf(".");
                        gotoxy(GAME_MAP_WIDTH-1,ypos); printf("P");
                        gotoxy(GAME_MAP_WIDTH-1,ypos);
                        continue;
                    }
                }
                gotoxy(--xpos    ,ypos); printf("P");
                gotoxy(  xpos+pos,ypos); printf("%c",chr);
            }
            else if (key == '8') {
                printf(".");
                if (ypos < 3) {
                    printf(".");
                    ypos = GAME_MAP_HEIGHT-1;
                    gotoxy(xpos,++ypos);
                }

                gotoxy(xpos,ypos); printf(".");
                gotoxy(xpos,--ypos); printf("P");
            }
            else if (key == '2') {
                gotoxy(xpos,  ypos); printf(".");
                gotoxy(xpos,++ypos); printf("P");
            }   gotoxy(  xpos  ,ypos);
        }
    }
}
