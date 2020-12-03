/*
Author: Asif Azad
Created : 04.12.2020


Last Modified: 04.12.2020
*/




#include<bits/stdc++.h>
using namespace std;

# include "iGraphics.h"
#include "SudokuAlgo.h"
#define dbg(a) cout<<#a<<" ->->->-> "<<a<<"\n"



int scr_width = 1550, scr_height = 800;
int active_cell = 0, last_active = 1;
int btn_startX = 1200, btn_startY = 550, btn_len = 200, btn_width = 30, btn_spacing = 10;
int no_soln = 0;

typedef struct
{
    int r, g, b;
}rgb;


typedef struct       //Represent Each Square Cell
{
    double cx, cy, arm, tcx, tcy;
    rgb color;

} block;

block cells[81];

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{

    iClear();

    iSetColor(0, 0, 0);          //bg color
    iFilledRectangle(0, 0,scr_width, scr_height);

    cells[last_active].color = {255, 255, 255};
    cells[active_cell].color = {0, 255, 0};


    for(int i = 0; i < 81; i++)
    {
        int x = i/9, y = i%9;
        iSetColor(cells[i].color.r, cells[i].color.g, cells[i].color.b);
        iFilledRectangle(cells[i].cx, cells[i].cy, cells[i].arm, cells[i].arm);

        if(solve[x][y])
        {
            char ch[] = {char(solve[x][y] + '0')};

            iSetColor(0, 0, 0);
            iText(cells[i].tcx, cells[i].tcy, ch, GLUT_BITMAP_HELVETICA_18);
        }

    }


    iSetColor(255, 0, 0);

    btn_startX = 1200;
    btn_startY = 550;
    btn_len = 200;
    btn_width = 30;
    btn_spacing = 10;

    iRectangle(btn_startX, btn_startY, btn_len, btn_width);
    iText(btn_startX+10, btn_startY + 7, "Exit", GLUT_BITMAP_TIMES_ROMAN_24);
    btn_startY += (btn_width+btn_spacing);

    iRectangle(btn_startX, btn_startY, btn_len, btn_width);
    iText(btn_startX+10, btn_startY + 7, "Erase", GLUT_BITMAP_TIMES_ROMAN_24);
    btn_startY += (btn_width+btn_spacing);

    iRectangle(btn_startX, btn_startY, btn_len, btn_width);
    iText(btn_startX+10, btn_startY + 7, "Solve", GLUT_BITMAP_TIMES_ROMAN_24);

    if(no_soln)
        iText(1200, 700, "No Solution Exist!!", GLUT_BITMAP_TIMES_ROMAN_24);

    iText(670, 720, "SUDOKU!!", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(590, 20, "Press 'e' to erase a single cell.");

}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT && state == GLUT_DOWN)
    {
        btn_startX = 1200;
        btn_startY = 550;
        btn_len = 200;
        btn_width = 30;
        btn_spacing = 10;

        if(mx >= btn_startX && mx <= btn_startX + btn_len && my >= btn_startY && my <= btn_startY + btn_width)
            exit(0);

        btn_startY += (btn_width + btn_spacing);
        if(mx >= btn_startX && mx <= btn_startX + btn_len && my >= btn_startY && my <= btn_startY + btn_width)
            memset(solve, 0, sizeof(solve));


        btn_startY += (btn_width + btn_spacing);
        if(mx >= btn_startX && mx <= btn_startX + btn_len && my >= btn_startY && my <= btn_startY + btn_width)
        {
            if(solve_exit())
                sudoku();
            else
                no_soln = 1;

//            for(int i =0 ; i< 9;i++)
//                for(int j = 0; j< 9; j++)
//                    cout<<solve[i][j] <<" \n"[j == 8];


        }

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key >= '1' && key <= '9')
    {
        dbg(key);
        int digit = int(key - '0');
        solve[active_cell/9][active_cell%9] = digit;

        no_soln = 0;
//
//            for(int i =0 ; i< 9;i++)
//                for(int j = 0; j< 9; j++)
//                    cout<<solve[i][j] <<" \n"[j == 8];
    }

    if(key == 'e')
        solve[active_cell/9][active_cell%9] = 0;
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_UP)
    {
        if(active_cell + 9 < 81)
        {
            last_active = active_cell;
            active_cell  += 9;
        }
    }
    else if(key == GLUT_KEY_DOWN)
    {
        if(active_cell - 9 >= 0)
        {
            last_active = active_cell;
            active_cell -= 9;
        }
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        if(active_cell + 1 < 81)
        {
            last_active = active_cell;
            active_cell++;
        }
    }
    else if(key == GLUT_KEY_LEFT)
    {
        if(active_cell - 1 >= 0)
        {
            last_active = active_cell;
            active_cell--;
        }
    }
}


int main()
{
    int cur_x = 450, cur_y = 50, spacing = 10, side = 50;

    for(int i =0 ; i< 81;i++)
    {
        int x = i/9, y = i%9;
        if(y == 0)
        {
            cur_x = 450;
            cur_y += side + spacing;
            if(x == 3 || x == 6)
                cur_y += 10;
        }

        cells[i].arm = side;
        cells[i].cx = cur_x;
        cells[i].cy = cur_y;
        cells[i].tcx = cur_x + 20;
        cells[i].tcy = cur_y + 20;
        cells[i].color = {255, 255, 255};


//        dbg(i);
//        dbg(x);
//        dbg(y);
//        dbg(cur_x);
//        dbg(cur_y);

        cur_x += side + spacing;
        if(y == 2 || y == 5)
            cur_x += 10;
    }


    //place your own initialization codes here.
    iInitialize(scr_width, scr_height, "Sudoku!!");
    return 0;
}
