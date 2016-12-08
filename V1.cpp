#include "TXLib.h"

struct C_Tank
    {
    double  x,  y ;
    double vx, vy;
    double r ;
    double D, l ;
    double x_d, y_d ;
    COLORREF Tank, Dulo ;
    } ;

struct C_snaryad
    {
    double  x,  y ;
    double vx, vy ;
    double l ;
    double x0, y0 ;
    COLORREF color ;
    } ;

const double XWindow = GetSystemMetrics (SM_CXSCREEN), YWindow = GetSystemMetrics (SM_CYSCREEN) ;
double XP = 15;

void Draw_tank (C_Tank * tank, double SledX, double SledY) ;
void Draw_Snaryad (C_snaryad * s) ;
void Draw_XP () ;
void Vistrel (C_snaryad snaryad [], C_Tank tank [], int * d);
void Prisv_zn_prot (C_Tank sopernik []);
//void Prisv_zn_sn_p (C_snaryad snaryad_p [][]);
void Prisv_zn_sn (C_snaryad snaryad []);
double atan_ (double x, double y) ;
double sqrt_ (double x) ;
double dist (double x1, double y1, double x2, double y2) ;

int main ()
    {
    _txWindowStyle &= ~ WS_CAPTION ;
    txCreateWindow (XWindow, YWindow) ;

    C_Tank tank     [1] = {100, 100, 0, 0, 40, 20, 90, 0, 0, RGB (0, 0, 255), RGB (150, 150, 150)} ;
    C_Tank sopernik [3] = {} ;
    C_snaryad snaryad [10] = {} ;
    C_snaryad snaryad_p [3][40] = {} ;

    Prisv_zn_prot (sopernik);
    //Prisv_zn_sn_p (snaryad_p);
    for (int i = 0; i < 3; i ++)
        {
        for (int n = 0; n < 40; n++)
            {
            snaryad_p[i][n].x = -50 ;
            snaryad_p[i][n].color = RGB (230, 0, 0) ;
            }
        }
    Prisv_zn_sn   (snaryad);

    int d = 0, d_prot = 0 ;
    int k_prot = 0 ;
    int t_p_prot[3] = {} ;

    for (int i = 0, t_p = 0; !GetAsyncKeyState (VK_ESCAPE) && XP > 0; i ++, t_p ++)
        {
        txBegin() ;
        txSetFillColor (TX_WHITE) ;
        txClear () ;
        if (GetAsyncKeyState ('W')) tank[0].y-=3 ;
        if (GetAsyncKeyState ('A')) tank[0].x-=3 ;
        if (GetAsyncKeyState ('S')) tank[0].y+=3 ;
        if (GetAsyncKeyState ('D')) tank[0].x+=3 ;
        Draw_tank (&tank [0], txMouseX (), txMouseY ()) ;

        if (GetAsyncKeyState (VK_SPACE) && t_p >= 35)
            {
            Vistrel (snaryad, tank, &d);
            t_p = 0;
            }

        for (int i_ = 0; i_ < 10; i_++)
            {
            snaryad[i_].x += snaryad[i_].vx ;
            snaryad[i_].y += snaryad[i_].vy ;
            if (dist (snaryad[i_].x, snaryad[i_].y, snaryad[i_].x0, snaryad[i_].y0) >= 1200)
                {
                snaryad[i_].x = -50 ;
                snaryad[i_].y = -50 ;
                snaryad[i_].vx = 0 ;
                snaryad[i_].vy = 0 ;
                }
            Draw_Snaryad (&snaryad[i_]) ;
            for (int n = 0; n < 3; n++)
                {
                if (dist (snaryad[i_].x, snaryad[i_].y, sopernik[n].x, sopernik[n].y) < sopernik[n].r + 20)
                    {
                    sopernik[n].x = random (50, XWindow  - 50) ;
                    sopernik[n].y = random (50, YWindow  - 50) ;
                    snaryad[i_].y = -50 ;
                    snaryad[i_].vx = 0 ;
                    snaryad[i_].vy = 0 ;
                    }
                }
            }

        for (int i_ = 0; i_ < 3; i_++)
            {
            Draw_tank (&sopernik [i_], tank[0].x, tank[0].y) ;
            if (t_p_prot[i_] >= 60)
                {
                d_prot++ ;
                k_prot = d_prot%40 ;
                snaryad_p[i_][k_prot].x0 = sopernik[i_].x_d ;
                snaryad_p[i_][k_prot].y0 = sopernik[i_].y_d ;
                snaryad_p[i_][k_prot].x  = snaryad_p[i_][k_prot].x0 ;
                snaryad_p[i_][k_prot].y  = snaryad_p[i_][k_prot].y0 ;
                snaryad_p[i_][k_prot].vx = 10 * cos (atan_ (sopernik[i_].y_d - sopernik[i_].y , sopernik[i_].x_d - sopernik[i_].x)) ;
                snaryad_p[i_][k_prot].vy = 10 * sin (atan_ (sopernik[i_].y_d - sopernik[i_].y , sopernik[i_].x_d - sopernik[i_].x)) ;
                t_p_prot[i_] = 0 ;
                }

            for (int n = 0; n < 40; n++)
                {
                snaryad_p[i_][n].x += snaryad_p[i_][n].vx ;
                snaryad_p[i_][n].y += snaryad_p[i_][n].vy ;
                if (dist (snaryad_p[i_][n].x, snaryad_p[i_][n].y, snaryad_p[i_][n].x0, snaryad_p[i_][n].y0) >= 1200)
                    {
                    snaryad_p[i_][n].x = -50 ;
                    snaryad_p[i_][n].y = -50 ;
                    snaryad_p[i_][n].vx = 0 ;
                    snaryad_p[i_][n].vy = 0 ;
                    }
                Draw_Snaryad (&snaryad_p[i_][n]) ;

                if (dist (snaryad_p[i_][n].x, snaryad_p[i_][n].y, tank[0].x, tank[0].y) < tank[0].r + 20)
                    {
                    XP--;
                    snaryad_p[i_][n].y = -50 ;
                    snaryad_p[i_][n].vx = 0 ;
                    snaryad_p[i_][n].vy = 0 ;
                    }
                }

            t_p_prot [i_] ++ ;
            }

        for (int n = 0;  n < 3;  n++)
            {
            if (rand ()%100 == 1)
                {
                sopernik[n].vx = (rand()%100 - 50)/30 + 2.5 * cos (atan_ (tank[0].y_d - sopernik[n].y , tank[0].x_d - sopernik[n].x));
                sopernik[n].vy = (rand()%100 - 50)/30 + 2.5 * sin (atan_ (tank[0].y_d - sopernik[n].y , tank[0].x_d - sopernik[n].x));
                }
            sopernik[n].x += sopernik[n].vx;
            sopernik[n].y += sopernik[n].vy;
            }

        Draw_XP ();

        if (XP <= 0)
            {
            for (int b = 0;  b < 10000000000 && !GetAsyncKeyState (VK_ESCAPE);  b++) ;
            }

        txEnd() ;
        }
    }

void Draw_tank (C_Tank * tank, double SledX, double SledY)
    {
    double X_m = SledX - tank->x ;
    double Y_m = SledY - tank->y ;
    double k1 = tank->D * Y_m / sqrt_(X_m*X_m + Y_m*Y_m) ;
    double k2 = tank->D * X_m / sqrt_(X_m*X_m + Y_m*Y_m) ;
    POINT Dulo[4] = {{ k1 + tank->x,
                      -k2 + tank->y},
                     {-k1 + tank->x,
                       k2 + tank->y},
                     {-k1 + tank->l * cos (atan_ (Y_m , X_m)) + tank->x,
                       k2 + tank->l * sin (atan_ (Y_m , X_m)) + tank->y},
                     { k1 + tank->l * cos (atan_ (Y_m , X_m)) + tank->x,
                      -k2 + tank->l * sin (atan_ (Y_m , X_m)) + tank->y}} ;

    txSetFillColor (tank->Dulo) ;
    txPolygon (Dulo, 4) ;
    txSetFillColor (TX_BLACK) ;
    txSetColor     (TX_BLACK) ;
    txCircle (tank->x, tank->y, tank->r + 5) ;

    txSetFillColor (tank->Tank) ;
    txSetColor     (TX_BLACK) ;
    txCircle (tank->x, tank->y, tank->r) ;
    tank->x_d = tank->l * cos (atan_ (Y_m , X_m)) + tank->x ;
    tank->y_d = tank->l * sin (atan_ (Y_m , X_m)) + tank->y ;
    }

void Draw_Snaryad (C_snaryad * s)
    {
    txSetColor (TX_BLACK) ;
    txSetFillColor (TX_BLACK) ;
    txCircle (s->x, s->y, 20) ;
    txSetFillColor (s->color) ;
    txCircle (s->x, s->y, 16) ;
    }

void Draw_XP ()
    {
    POINT XP_ [4] = {{200, 30}, {200, 45}, {200 + XP * (XWindow - 400) / 15, 45}, {200 + XP * (XWindow - 400) / 15, 30}};
    txSetColor (TX_BLACK);
    txSetFillColor (RGB (0, 240, 0));
    txPolygon (XP_, 4);
    }

void Vistrel (C_snaryad snaryad [], C_Tank tank [], int * d)
    {
    *d++ ;
    int k = *d%10 ;
    snaryad[k].x0 = tank[0].x_d ;
    snaryad[k].y0 = tank[0].y_d ;
    snaryad[k].x  = snaryad[k].x0 ;
    snaryad[k].y  = snaryad[k].y0 ;
    snaryad[k].vx = 15 * cos (atan_ (tank[0].y_d - tank[0].y , tank[0].x_d - tank[0].x)) ;
    snaryad[k].vy = 15 * sin (atan_ (tank[0].y_d - tank[0].y , tank[0].x_d - tank[0].x)) ;
    }

void Prisv_zn_prot (C_Tank sopernik [])
    {
    for (int i = 0; i < 3; i ++)
        {
        sopernik[i].x = random (200 + i * (XWindow - 200) / 5, 200 + (i + 1) * (XWindow - 200) / 5) ;
        sopernik[i].y = random (200, YWindow - 50) ;
        sopernik[i].r = 30 ;
        sopernik[i].D = 15 ;
        sopernik[i].l = 75 ;
        sopernik[i].Tank = RGB (255, 0, 0) ;
        sopernik[i].Dulo = RGB (130, 130, 130) ;
        }
    }

/*void Prisv_zn_sn_p (C_snaryad snaryad_p[][])
    {
    for (int i = 0; i < 3; i ++)
        {
        for (int n = 0; n < 40; n++)
            {
            snaryad_p[i][n].x = -50 ;
            snaryad_p[i][n].color = RGB (230, 0, 0) ;
            }
        }
    } */

void Prisv_zn_sn (C_snaryad snaryad [])
    {
    for (int i = 0; i < 10; i ++)
        {
        snaryad[i].x = -50 ;
        snaryad[i].color = RGB (0, 0, 230) ;
        }
    }

double atan_ (double x, double y)
    {
    if (x > 0) return  -atan (y/x) + txPI/2 ;
    if (x < 0) return  -atan (y/x) - txPI/2 ;
    if (y > 0) return   0 ;
    if (y < 0) return  txPI ;
    return 0 ;
    }

double sqrt_ (double x)
    {
    if (x >  0) return sqrt (x) ;
    if (x == 0) return 0.00001 ;
    return -1 ;
    }

double dist (double x1, double y1, double x2, double y2)
    {
    return sqrt ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) ;
    }
