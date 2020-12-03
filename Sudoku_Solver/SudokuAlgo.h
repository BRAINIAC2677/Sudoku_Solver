#ifndef SUDOKUALGO_H_INCLUDED
#define SUDOKUALGO_H_INCLUDED

int solve[9][9];


int find_next(int& cx, int& cy)
{
    for(cx = 0; cx < 9; cx++)
        for(cy = 0; cy < 9; cy++)
            if(solve[cx][cy] == 0)
                return 1;
    return 0;
}

int safe(int x, int y, int iccha)
{
    for(int i = 0; i< 9; i++)
    {
        if(solve[i][y] == iccha || solve[x][i] == iccha)
            return 0;
    }

    for(int i = x/3*3; i < x/3*3 + 3; i++)
        for(int j = y/3*3; j < y/3*3 + 3; j++)
            if(solve[i][j] == iccha)
                return 0;
    return 1;
}

int solve_exit()
{
    for(int i = 0;i < 9; i++)
    {
        for(int j = 0; j< 9; j++)
        {
            if(solve[i][j] == 0)
                continue;
            int temp = solve[i][j];
            solve[i][j] = 0;
            if(!safe(i, j, temp))
            {
                solve[i][j] = temp;
                return 0;
            }
            solve[i][j] = temp;
        }
    }
    return 1;
}

int sudoku()
{
    int cx, cy;
    if(!find_next(cx, cy))
        return 1;

    for(int i = 1; i<= 9; i++)
    {
        if(safe(cx, cy, i))
        {
            solve[cx][cy] = i;

            if(sudoku())
                return 1;

            solve[cx][cy] = 0;
        }
    }

    return 0;
}

#endif // SUDOKUALGO_H_INCLUDED
