#include "TXLib.h"

struct C_Tank
    {
    double x, y;
    double r;
    double D, l;
    COLORREF Tank, Dulo;
    };

void Draw_tank (C_Tank * tank);
double atan_ (double x, double y);
double sqrt_ (double x);

int main ()
    {
    txCreateWindow (1000, 1000);
    C_Tank tank [1] = {100, 100, 40, 20, 90, RGB (0, 0, 255), RGB (150, 150, 150)};

    for (int i = 0;!GetAsyncKeyState ('G'); i ++)
        {
        txBegin();
        txSetFillColor (TX_WHITE);
        txClear ();
        if (GetAsyncKeyState ('W')) tank[0].y--;
        if (GetAsyncKeyState ('A')) tank[0].x--;
        if (GetAsyncKeyState ('S')) tank[0].y++;
        if (GetAsyncKeyState ('D')) tank[0].x++;
        Draw_tank (&tank [0]);
        txEnd();
        }
    }

void Draw_tank (C_Tank * tank)
    {
    txSetFillColor (tank->Dulo);
    double X_m = txMouseX () - tank->x;
    double Y_m = txMouseY () - tank->y;
    POINT Dulo[4] = {{ tank->D * Y_m / sqrt_(X_m*X_m + Y_m*Y_m) + tank->x, -tank->D * X_m / sqrt_(X_m*X_m + Y_m*Y_m) + tank->y},
                     {-tank->D * Y_m / sqrt_(X_m*X_m + Y_m*Y_m) + tank->x,  tank->D * X_m / sqrt_(X_m*X_m + Y_m*Y_m) + tank->y},
                     {-tank->D * Y_m / sqrt_(X_m*X_m + Y_m*Y_m) + tank->l * cos (atan_ (Y_m , X_m)) + tank->x,
                       tank->D * X_m / sqrt_(X_m*X_m + Y_m*Y_m) + tank->l * sin (atan_ (Y_m , X_m)) + tank->y},
                     { tank->D * Y_m / sqrt_(X_m*X_m + Y_m*Y_m) + tank->l * cos (atan_ (Y_m , X_m)) + tank->x,
                      -tank->D * X_m / sqrt_(X_m*X_m + Y_m*Y_m) + tank->l * sin (atan_ (Y_m , X_m)) + tank->y}};
    txPolygon (Dulo, 4);
    txSetFillColor (TX_BLACK);
    txSetColor     (TX_BLACK);
    txCircle (tank->x, tank->y, tank->r + 5);

    txSetFillColor (tank->Tank);
    txSetColor     (TX_BLACK);
    txCircle (tank->x, tank->y, tank->r);
    }

void Snaryad ()
    {

    }

double atan_ (double x, double y)
    {
    if (x > 0) return  -atan (y/x) + txPI/2;
    if (x < 0) return  -atan (y/x) - txPI/2;
    if (y > 0) return   0;
    if (y < 0) return  txPI;
    return 0;
    }

double sqrt_ (double x)
    {
    if (x >  0) return sqrt (x);
    if (x == 0) return 0.00001;
    return -1;
    }
