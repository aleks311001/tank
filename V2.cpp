#include "TXNetwork.h"
#include "TXLib.h"
#define SERVER_IP "10.0.2.204"  //IP �������  //10.0.2.205

struct C_Tank
    {
    double  x,  y ;
    double vx, vy;
    double r ;
    double D, l ;
    double x_d, y_d ;
    double XP;
    double max_XP;
    double lvl;
    COLORREF Tank, Dulo ;
    } ;

struct C_snaryad
    {
    double  x,  y ;
    double vx, vy ;
    double l ;
    double x0, y0 ;
    double lvl;
    COLORREF color ;
    } ;

struct C_Lvl_plus
    {
    double x, y;
    double vx, vy;
    double Xp;
    double lvl;
    double r;
    };

const int XWindow = GetSystemMetrics (SM_CXSCREEN), YWindow = GetSystemMetrics (SM_CYSCREEN) ;

void Draw_tank (C_Tank * tank, double SledX, double SledY) ;
void Draw_Snaryad (C_snaryad * s) ;
void Draw_LVL_plus (C_Lvl_plus * obj);
void Draw_XP (double xp) ;
void Vistrel (C_snaryad snaryad [], C_Tank tank [], int d);
void Prisv_zn_prot (C_Tank sopernik []);
//void Prisv_zn_sn_p (C_snaryad snaryad_p [][]);
void Prisv_zn_sn (C_snaryad snaryad []);
void Prisv_Zn_Per_data (int P_D [], C_Tank tank);
void Prisv_Zn_Tank_sop (C_Tank * tank,  int P_D []);
double atan_ (double x, double y) ;
double sqrt_ (double x) ;
double dist (double x1, double y1, double x2, double y2) ;
double rand_ (int a, int b);

int main ()
    {
    _txWindowStyle &= ~ WS_CAPTION ;
    txCreateWindow (XWindow, YWindow) ;

    C_Tank tank     [2] = {{          100,           100, 0, 0, 40, 20, 90, 0, 0, 20, 30, 1, RGB (0, 0, 255), RGB (150, 150, 150)},
                           {XWindow - 100, YWindow - 100, 0, 0, 40, 20, 90, 0, 0, 15, 15, 1, RGB (255, 0, 0), RGB (150, 150, 150)}} ;
    //C_Tank sopernik [3] = {} ;

    C_Lvl_plus obj [5] = {};

    double Per_Obj_Nach [20] = {};

    int Per_Data_0 [14] = {};
    int Per_Data_1 [14] = {};

    C_snaryad snaryad_0 [10] = {} ;
    C_snaryad snaryad_1 [10] = {} ;

    double Per_sn_0 [20] = {};
    double Per_sn_1 [20] = {};

    double Per_Obj_s [20] = {};
    double Per_Obj_r [20] = {};

    //Prisv_zn_prot (sopernik);
    //Prisv_zn_sn_p (snaryad_p);

    Per_Data_1[12] = txMouseX ();
    Per_Data_1[13] = txMouseY ();

    Prisv_zn_sn   (snaryad_0);
    Prisv_zn_sn   (snaryad_1);

    int d = 0, d_prot = 0 ;
    int k_prot = 0 ;
    int t_p_prot[3] = {} ;

    TX_SOCKET client = txCreateSocket (TX_CLIENT, SERVER_IP);

    txRecvFrom (client, &Per_Obj_Nach,  sizeof (Per_Obj_Nach));

    for (int i = 0; i < 5; i++)
        {
        obj[i].x   = Per_Obj_Nach [i*4    ];
        obj[i].y   = Per_Obj_Nach [i*4 + 1];
        obj[i].lvl = Per_Obj_Nach [i*4 + 2];
        obj[i].Xp  = Per_Obj_Nach [i*4 + 3];
        }


    for (int i = 0, t_p = 0; !GetAsyncKeyState (VK_ESCAPE) && tank[0].XP > 0; i ++, t_p ++, tank[0].XP += 0.0025)
        {
        txBegin() ;

        txSetFillColor (TX_WHITE) ;
        txClear () ;
        if (GetAsyncKeyState ('W')) tank[0].vy = -8 ;
        if (GetAsyncKeyState ('A')) tank[0].vx = -8 ;
        if (GetAsyncKeyState ('S')) tank[0].vy =  8 ;
        if (GetAsyncKeyState ('D')) tank[0].vx =  8 ;

        tank[0].x += tank[0].vx;
        tank[0].y += tank[0].vy;

        if (tank[0].vx < -0.3) tank[0].vx += 0.2;
        if (tank[0].vy < -0.3) tank[0].vy += 0.2;
        if (tank[0].vx >  0.3) tank[0].vx -= 0.2;
        if (tank[0].vy >  0.3) tank[0].vy -= 0.2;
        if (tank[0].vy <   0.3 && tank[0].vy > -0.3) tank[0].vy = 0;
        if (tank[0].vx <   0.3 && tank[0].vx > -0.3) tank[0].vx = 0;

        if (tank[0].x <         - 500) tank[0].x =         - 500;
        if (tank[0].x > XWindow + 500) tank[0].x = XWindow + 500;
        if (tank[0].y <         - 500) tank[0].y =         - 500;
        if (tank[0].y > YWindow + 500) tank[0].y = YWindow + 500;

        Draw_tank (&tank [0], txMouseX (), txMouseY ()) ;
        Draw_tank (&tank [1], Per_Data_1[12], Per_Data_1 [13]) ;

        if (GetAsyncKeyState (VK_SPACE) && t_p >= 20)
            {
            Vistrel (snaryad_0, tank, d%10);
            d++;
            t_p = 0;
            }

        for (int i_ = 0; i_ < 10; i_++)
            {
            snaryad_0[i_].x += snaryad_0[i_].vx ;
            snaryad_0[i_].y += snaryad_0[i_].vy ;
            if (dist (snaryad_0[i_].x, snaryad_0[i_].y, snaryad_0[i_].x0, snaryad_0[i_].y0) >= 1200)
                {
                snaryad_0[i_].x = -50;
                snaryad_0[i_].y = -50;
                snaryad_0[i_].vx = 0;
                snaryad_0[i_].vy = 0;
                }

            Draw_Snaryad (&snaryad_0[i_]);
            Draw_Snaryad (&snaryad_1[i_]);

            for (int n = 0; n < 5; n++)
                {
                Draw_LVL_plus (&obj[n]);
                }

            for (int n = 0; n < 5; n++)
                {
                if (dist (snaryad_0[i_].x, snaryad_0[i_].y, obj[n].x, obj[n].y) < obj[n].r + 20)
                    {
                    snaryad_0[i_].y = -50;
                    if (obj[n].Xp > 1)
                        {
                        obj[n].Xp --;
                        obj[n].vx = snaryad_0[i_].vx/15;
                        obj[n].vy = snaryad_0[i_].vy/15;
                        }
                    else
                        {
                        obj[n].x   = rand_ (50, XWindow - 50);
                        obj[n].y   = rand_ (50, YWindow - 50);
                        obj[n].lvl = rand_ (1, 3);
                        obj[n].Xp  = (obj[n].lvl + 1) * 2;
                        tank [0].XP ++;
                        }
                    snaryad_0[i_].vx = 0;
                    snaryad_0[i_].vy = 0;
                    }
                }
            }

        if (tank[0].XP <= 0 || tank[1].XP <= 0)
            {
            //for (int b = 0;  b < 1000000000 && !GetAsyncKeyState (VK_ESCAPE);  b++) ;
            }

        if (tank[0].XP >= tank[0].max_XP) tank[0].XP = tank[0].max_XP;

        for (int n = 0; n < 10; n++)
            {
            Per_sn_0 [2 * n]     = snaryad_0[n].x;
            Per_sn_0 [2 * n + 1] = snaryad_0[n].y;
            }

        for (int n = 0; n < 5; n++)
            {
            Per_Obj_s [n*4    ] = obj[n].x;
            Per_Obj_s [n*4 + 1] = obj[n].y;
            Per_Obj_s [n*4 + 2] = obj[n].lvl;
            Per_Obj_s [n*4 + 3] = obj[n].Xp;
            }

        Prisv_Zn_Per_data (Per_Data_0, tank[0]);

        txSendTo   (client, &Per_Data_0, sizeof (Per_Data_0));
        txRecvFrom (client, &Per_Data_1, sizeof (Per_Data_1));
        txSendTo   (client, &Per_sn_0,   sizeof (Per_sn_0));
        txRecvFrom (client, &Per_sn_1,   sizeof (Per_sn_1));
        txSendTo   (client, &Per_Obj_s,  sizeof (Per_Obj_s));
        txRecvFrom (client, &Per_Obj_r,  sizeof (Per_Obj_r));

        Prisv_Zn_Tank_sop (&tank [1], Per_Data_1);

        for (int n = 0; n < 10; n++)
            {
            snaryad_1[n].x = Per_sn_1 [2 * n];
            snaryad_1[n].y = Per_sn_1 [2 * n + 1];
            if (dist (snaryad_0[n].x, snaryad_0[n].y, tank[1].x, tank[1].y) < tank[1].r + 20)
                {
                if (tank[1].XP > 1) tank[1].XP --;
                snaryad_0[n].y = -50;
                snaryad_0[n].vx = 0;
                snaryad_0[n].vy = 0;
                }

            if (dist (snaryad_1[n].x, snaryad_1[n].y, tank[0].x, tank[0].y) < tank[0].r + 20 && tank[0].XP > -1) tank[0].XP --;
            }

        for (int n = 0; n < 5; n++)
            {
            if (Per_Obj_r [n*4]     != Per_Obj_s [n*4    ]) obj[n].x   = Per_Obj_r [n*4];
            if (Per_Obj_r [n*4 + 1] != Per_Obj_s [n*4 + 1]) obj[n].y   = Per_Obj_r [n*4 + 1];
            obj[n].lvl = Per_Obj_r [n*4 + 2];
            obj[n].Xp  = Per_Obj_r [n*4 + 3];
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

    txSetColor (TX_BLACK);
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

    POINT XP_ [4] = {{tank->x - tank->r, tank->y - tank->r - 5},
                     {tank->x - tank->r, tank->y - tank->r - 10},
                     {tank->x - tank->r + tank->XP * 2 * tank->r / tank->max_XP, tank->y - tank->r - 10},
                     {tank->x - tank->r + tank->XP * 2 * tank->r / tank->max_XP, tank->y - tank->r - 5}};

    txSetColor (TX_BLACK);
    txSetFillColor (RGB (0, 240, 0));
    txPolygon (XP_, 4);
    }

void Draw_Snaryad (C_snaryad * s)
    {
    txSetColor (TX_BLACK) ;
    txSetFillColor (TX_BLACK) ;
    txCircle (s->x, s->y, 20) ;
    txSetFillColor (s->color) ;
    txCircle (s->x, s->y, 16) ;
    }

void Draw_LVL_plus (C_Lvl_plus * obj)
    {
    txSetFillColor (RGB (0, (obj->lvl + 2) * 50, 0));
    txSetColor     (RGB (0, (obj->lvl + 2) * 40, 0), 3);
    obj->r  = obj->lvl * 10;
    if (obj->vx <= -0.1) obj->vx += 0.05;
    if (obj->vy <= -0.1) obj->vy += 0.05;
    if (obj->vx >=  0.1) obj->vx -= 0.05;
    if (obj->vy >=  0.1) obj->vy -= 0.05;
    if (obj->vy <   0.1 && obj->vy > -0.1) obj->vy = 0;
    if (obj->vx <   0.1 && obj->vx > -0.1) obj->vx = 0;
    obj->x += obj->vx;
    obj->y += obj->vy;
    txCircle (obj->x, obj->y, obj->r);
    }

void Draw_XP (double xp)
    {
    POINT XP_ [4] = {{200, 30}, {200, 45}, {200 + xp * (XWindow - 400) / 15, 45}, {200 + xp * (XWindow - 400) / 15, 30}};
    txSetColor (TX_BLACK);
    txSetFillColor (RGB (0, 240, 0));
    txPolygon (XP_, 4);
    }

void Vistrel (C_snaryad snaryad [], C_Tank tank [], int d)
    {
    snaryad[d].x0 = tank[0].x_d ;
    snaryad[d].y0 = tank[0].y_d ;
    snaryad[d].x  = snaryad[d].x0 ;
    snaryad[d].y  = snaryad[d].y0 ;
    snaryad[d].vx = 30 * cos (atan_ (tank[0].y_d - tank[0].y , tank[0].x_d - tank[0].x)) ;
    snaryad[d].vy = 30 * sin (atan_ (tank[0].y_d - tank[0].y , tank[0].x_d - tank[0].x)) ;
    }

void Prisv_zn_prot (C_Tank sopernik [])
    {
    for (int i = 0; i < 3; i ++)
        {
        sopernik[i].x = rand_ (200 + i * (XWindow - 200) / 5, 200 + (i + 1) * (XWindow - 200) / 5) ;
        sopernik[i].y = rand_ (200, YWindow - 50) ;
        sopernik[i].r = 30 ;
        sopernik[i].D = 15 ;
        sopernik[i].l = 75 ;
        sopernik[i].XP = 2 ;
        sopernik[i].max_XP = 2;
        sopernik[i].lvl = 1;
        sopernik[i].Tank = RGB (255, 0, 0) ;
        sopernik[i].Dulo = RGB (130, 130, 130) ;
        }
    }

void Prisv_Zn_Per_data (int P_D [], C_Tank tank)
    {
    P_D [0]  = tank.x;
    P_D [1]  = tank.y;
    P_D [2]  = tank.vx;
    P_D [3]  = tank.vy;
    P_D [4]  = tank.r;
    P_D [5]  = tank.D;
    P_D [6]  = tank.l;
    P_D [7]  = tank.x_d;
    P_D [8]  = tank.y_d;
    P_D [9]  = tank.XP;
    P_D [11] = tank.lvl;
    P_D [12] = txMouseX ();
    P_D [13] = txMouseY ();
    }

void Prisv_Zn_Tank_sop (C_Tank * tank, int P_D [])
    {
    tank->x   = P_D [0];
    tank->y   = P_D [1];
    tank->vx  = P_D [2];
    tank->vy  = P_D [3];
    tank->r   = P_D [4];
    tank->D   = P_D [5];
    tank->l   = P_D [6];
    tank->x_d = P_D [7];
    tank->y_d = P_D [8];
    tank->XP  = P_D [9];
    tank->lvl = P_D [11];
    }

void Prisv_zn_sn (C_snaryad snaryad [])
    {
    for (int i = 0; i < 10; i ++)
        {
        snaryad[i].x = -50 ;
        snaryad[i].color = RGB (0, 0, 230) ;
        snaryad[i].lvl = 1;
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
    if (x <= 0) return 0.00001 ;
    return -1 ;
    }

double dist (double x1, double y1, double x2, double y2)
    {
    return sqrt ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) ;
    }

double rand_ (int a, int b)
    {
    return rand() % (b - a + 1) + a;
    }
