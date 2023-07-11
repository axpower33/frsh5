
// CfRSH5Doc.cpp: реализация класса CCfRSH5Doc 
//

#include "pch.h"
#include "framework.h"
#include "frsh5View.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "fRSH5.h"
#endif

#include "fRSH5Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CfRSH5Doc

IMPLEMENT_DYNCREATE(CfRSH5Doc, CDocument)

BEGIN_MESSAGE_MAP(CfRSH5Doc, CDocument)
END_MESSAGE_MAP()

// Создание или уничтожение CCfRSH5Doc
double M_PI = 3.14;
double kk = 1.38E-23;
double E0 = 8.854E-14;
int E = 100;
double C_SI = 1 / (4 * M_PI * E0 * E);
double eQulon = 1.6E-19;
char getcd[128];
int Xmax = 640;
int Zmax = 640;
int Ymax = 480;
int sr = 0;

//CFrModInCndDlg FrModInCndDlg;

CfRSH5Doc::CfRSH5Doc() noexcept
{
    // TODO: добавьте код для одноразового вызова конструктора
    sr++;
    srand(sr);
    Rmax = 35e-7;
    Rmin = 25e-7;
    Rmid = 30e-7;
    MaxQ = 27e-19;
    Tmshft = 0.0001;
    DensAg = 10.5;
    Tk = 300;
    //mouse_event(MOUSEEVENTF_MOVE, 100, 100, 0, 1);
}

CfRSH5Doc::~CfRSH5Doc()
{
  
}


BOOL CfRSH5Doc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    else
    {
        needCharge = true;
        FrModInCndDlg.DoModal();
        N = FrModInCndDlg.m_Npat;
        dt= FrModInCndDlg.m_dt;
        
        t = 0;
        s = 1;
        xx = 0;
       
        MakeArray(N);
        InitParticle();
        InitAgr();
        return TRUE;
    }

    // TODO: добавьте код повторной инициализации
    // (Документы SDI будут повторно использовать этот документ)

    return TRUE;
}

// Сериализация CCfRSH5Doc

void CfRSH5Doc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar.Write(&N, sizeof(N));
        for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
            ar.Write(Pi, sizeof(Particle));
        ar.Write(&dt, sizeof(dt));
        ar.Write(&t, sizeof(t));
        ar.Write(CMass, (N / 2 + 1) * sizeof(*CMass));
        ar.Write(Pagregat, (N / 2 + 1) * sizeof(*Pagregat));
        ar.Write(ConPat, (N + 1) * sizeof(*ConPat));
        ar.Write(&s, sizeof(s));
        // TODO: добавьте код сохранения
    }
    else
    {
        ar.Read(&N, sizeof(N));
        MakeArray(N);
        TempP = new Particle;
        for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
        {
            TempP->next = Pi->next;
            TempP->pred = Pi->pred;
            ar.Read(Pi, sizeof(Particle));
            Pi->next = TempP->next;
            Pi->pred = TempP->pred;
        }
        delete TempP;
        ar.Read(&dt, sizeof(t));
        ar.Read(&t, sizeof(t));
        ar.Read(CMass, (N / 2 + 1) * sizeof(*CMass));
        ar.Read(Pagregat, (N / 2 + 1) * sizeof(*Pagregat));
        ar.Read(ConPat, (N + 1) * sizeof(*ConPat));
        ar.Read(&s, sizeof(s));
    }// TODO: добавьте код загрузки
}

void CfRSH5Doc::OnIdle()
{
    CDocument::OnIdle();
    if (xx == 1)  xx = 0; else xx = 1;
    if (FirstPat->q) CulonForces();

    for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
        for (Pj = Pi->next; Pj != NULL; Pj = Pj->next)
        {
            double dist_ij = pow(Pi->X - Pj->X, 2) + pow(Pi->Y - Pj->Y, 2) + pow(Pi->Z - Pj->Z, 2);
            if (dist_ij <= pow((5000000 * Pi->R + 5000000 * Pj->R), 2)) UnitPaticle(Pi, Pj);
        }
    AgrForces();
    MovePart();
    t = t + dt;
    SetModifiedFlag(xx);

   /* InvalidateRect(NULL, NULL, false);
    UpdateAllViews(NULL);
    
    if (xx == 0)
    {
        mouse_event(MOUSEEVENTF_WHEEL, 100, 100, 1000, 1); xx = 1;
    }
    else 
    {
        mouse_event(MOUSEEVENTF_HWHEEL, 100, 100, 1000, 1); xx = 0;
    }*/
}
    
        

void CfRSH5Doc::MakeArray(int N)
{
    FirstPat = new Particle;
    FirstPat->pred = NULL;
    FirstPat->N = 1;
    LastPat = FirstPat;
    for (int i = 2; i != N + 1; i++)
    {
        LastPat->next = TempP = new Particle;
        TempP->pred = LastPat;
        TempP->next = NULL;
        TempP->N = i;
        LastPat = TempP;
    }
}


void CfRSH5Doc::DistroyArray()
{
    if (FirstPat == NULL) return;
    TempP = FirstPat->next;
    do
        delete FirstPat;
    while (FirstPat = TempP, TempP = TempP->next, FirstPat != NULL);
    FirstPat = NULL;

}


Particle* CfRSH5Doc::Npat(int Np)
{
    TempP = FirstPat;
    for (int i = 1; i < Np; i++) TempP = TempP->next;
    return (TempP);
}


void CfRSH5Doc::SizePatDistr()
{
    
    for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
        if (Pi->N <= N * 0.2) Pi->R = Rmin;
        else if (Pi->N <= N * 0.8) Pi->R = (Rmin + Rmax) / 2;
        else Pi->R = Rmax;

}

void CfRSH5Doc::SpontDstr()
{
    double Vel, alpha, theta;
    for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
    {
        Vel = 1.41 * sqrt(2 * kk * Tk / Pi->mass) * double(rand()) / RAND_MAX;
        alpha = 2 * M_PI * double(rand()) / RAND_MAX;
        theta = 2 * M_PI * double(rand()) / RAND_MAX;
        Pi->Vx = Vel * cos(theta) * sin(alpha);
        Pi->Vy = Vel * cos(theta) * cos(alpha);
        Pi->Vz = Vel * sin(theta);
    }
}


void CfRSH5Doc::zeroDstr()
{
    for (Pi = FirstPat; Pi != NULL; Pi = Pi->next) Pi->Vx = Pi->Vy = Pi->Vz = 0;
}

void CfRSH5Doc::MxwDstr()
{
    int Vminz = 0;
    double Vmax = 0.25;
    int kmax;
    if (N != 2) kmax = N / 3; else kmax = 1;
    int i, j;
    double F;
    double dN, V, Vel, dv, alpha, theta;
    int rdn;

    j = 0; i = 1;
    dv = (Vmax - Vminz) / kmax;

    Pj = FirstPat;

    for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
    {
        V = Vminz + dv * i;
        F = sqrt(Pi->mass / (2 * M_PI * kk * Tk));
        F = pow(F, 3);
        F = F * exp(-(Pi->mass * pow(V, 2)) / (2 * kk * Tk)) * 4 * M_PI * pow(V, 2);
        dN = N * F * dv;
        rdn = (int)(dN + 0.5);
        i++;
        if ((j + rdn) < N)
            while (rdn)
            {
                j++;
                Vel = V;
                alpha = 2 * M_PI * double(rand()) / RAND_MAX;
                theta = 2 * M_PI * double(rand()) / RAND_MAX;
                Pj->Vx = Vel * cos(theta) * sin(alpha);
                Pj->Vy = Vel * cos(theta) * cos(alpha);
                Pj->Vz = Vel * sin(theta);
                rdn--;
                Pj = Pj->next;
            }
    }
    int cnt = N - j;

    while (cnt--)
    {
        Vel = sqrt((8 * kk * Tk) / (M_PI * Pj->mass));
        alpha = 2 * M_PI * double(rand()) / RAND_MAX;
        theta = M_PI * double(rand()) / RAND_MAX;
        Pj->Vx = Vel * cos(theta) * sin(alpha);
        Pj->Vy = Vel * cos(theta) * cos(alpha);
        Pj->Vz = Vel * sin(theta);
        Pj = Pj->next;
    }
}

void CfRSH5Doc::InitParticle()
{
    double TmPat[300];
    int sign = 0;
    //double sq;// , alpha;

    SizePatDistr();
    for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
    {

    m1: Pi->X = 640 * double(rand()) / RAND_MAX;
        Pi->Y = 480 * double(rand()) / RAND_MAX;
        Pi->Z = 640 * double(rand()) / RAND_MAX;

        for (Pj = FirstPat; Pj != Pi; Pj = Pj->next)
        {
            double dist_ij = pow(Pi->X - Pj->X, 2) + pow(Pi->Y - Pj->Y, 2) + pow(Pi->Z - Pj->Z, 2);
            if (dist_ij <= pow((5000000 * Pi->R + 5000000 * Pj->R), 2)) goto m1;
        }


        if (sign == 0) Pi->q = 0; else if (sign == 1) Pi->q = 27e-19; else if (sign == 2) Pi->q = -27e-19;
        sign++;
        if (sign == 3) sign = 0;

        Pi->mass = ((4 / 3) * M_PI * pow(Pi->R, 3)) / DensAg;
        TmPat[Pi->N] = Tmshft * double(rand()) / RAND_MAX;
        Pi->agr = 0;
        Pi->stop = false;
        Pi->Fx = 0;
        Pi->Fy = 0;
        Pi->Fz = 0;
    }
    MxwDstr();
    
}

void CfRSH5Doc::InitAgr()
{
    int c;
    for (c = 0; c != N / 2; c++) Pagregat[c] = 0;
    for (c = 0; c != N + 1; c++) ConPat[c] = 0;
}

bool CfRSH5Doc::IsPatInAgr(Particle* Pi, Particle* Pj)
{
    return  (bool)((Pi->agr != 0) && (Pi->agr == Pj->agr));
}

void CfRSH5Doc::CulonForces()
{
    //int Nagr;
    double Temp, dX, dY, dZ;
    for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
    {
        Pi->Fx = 0;
        Pi->Fy = 0;
        Pi->Fz = 0;
    }
    for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
    {
        for (Pj = Pi->next; Pj != NULL; Pj = Pj->next)
        {
            if (IsPatInAgr(Pi, Pj)) continue;
            dX = Pi->X - Pj->X;
            dY = Pi->Y - Pj->Y;
            dZ = Pi->Z - Pj->Z;
            Temp = Pi->q * Pj->q / pow(dX * dX + dY * dY + dZ * dZ, 1.5);
            Pj->Fx -= Temp * dX;
            Pj->Fy -= Temp * dY;
            Pj->Fz -= Temp * dZ;
            Pi->Fx += Temp * dX;
            Pi->Fy += Temp * dY;
            Pi->Fz += Temp * dZ;
        }
        Pi->Fx *= C_SI;
        Pi->Fy *= C_SI;
        Pi->Fz *= C_SI;
        //double U=Pi->Fx*dX+Pi->Fy*dY+Pi->Fz*dZ;
        //double Ek=Pi->mass*(pow(Pi->Vx,2)+pow(Pi->Vy,2)+pow(Pi->Vz,2))/2;
    }
}

#define Pprt(a) (*(Particle**)a)
int CfRSH5Doc::sortOfZ(const void* a, const void* b)
{
    if (Pprt(a)->Z > Pprt(b)->Z) return  1; else
        if (Pprt(a)->Z < Pprt(b)->Z) return -1; else
            return  0;
}


void CfRSH5Doc::MovePart()
{
    //int i, j;
    //char st[10];
    double dVx, dVy, dVz, dx, dy, dz;

    for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
        if (Pi->stop == false)
        {
            dVx = dt * Pi->Fx / Pi->mass;
            dVy = dt * Pi->Fy / Pi->mass;
            dVz = dt * Pi->Fz / Pi->mass;
            Pi->Vx += dVx;
            Pi->Vy += dVy;
            Pi->Vz += dVz;
            //RandWalk(TmPat[Pi->N],Pi->Vx,Pi->Vy,Pi->Vz);

            Pi->X += dx = 5000000 * dt * Pi->Vx;
            Pi->Y += dy = 5000000 * dt * Pi->Vy;
            Pi->Z += dz = 5000000 * dt * Pi->Vz;

            if ((Pi->X > 640) || (Pi->X < 0)) { Pi->Vx = -Pi->Vx; Pi->X -= dx; }
            if ((Pi->Y > 480) || (Pi->Y < 0)) { Pi->Vy = -Pi->Vy; Pi->Y -= dy; }
            if ((Pi->Z > 640) || (Pi->Z < 0)) { Pi->Vz = -Pi->Vz; Pi->Z -= dz; }
        }
}

void CfRSH5Doc::AngleSpeed(int kk, RPoint& W)
{
    // Џ®«­л© ¬®¬Ґ­в бЁ«, ¤Ґ©бвўгойЁ© ­   ЈаҐЈ в б® бв®а®­л ®бв «м­ле з бвЁж
    double Nx = 0; double Ny = 0; double Nz = 0;

    int i = Pagregat[kk];
    while (i)
    {
        Nx += (Pi->Y - CMass[kk].Y) * Pi->Fz - (Pi->Z - CMass[kk].Z) * Pi->Fy;
        Ny += (Pi->Z - CMass[kk].Z) * Pi->Fx - (Pi->X - CMass[kk].X) * Pi->Fz;
        Nz += (Pi->X - CMass[kk].X) * Pi->Fy - (Pi->Y - CMass[kk].Y) * Pi->Fx;
        i = ConPat[i];
    }
    CMass[kk].Mx += dt * Nx;
    CMass[kk].My += dt * Ny;
    CMass[kk].Mz += dt * Nz;

    W.X = CMass[kk].Mx / CMass[kk].Jx;
    W.Y = CMass[kk].My / CMass[kk].Jy;
    W.Z = CMass[kk].Mz / CMass[kk].Jz;
}

// ‚лзЁб«пҐв жҐ­ва ¬ бб, Ї®«­л© ¬®¬Ґ­в, ¬®¬Ґ­в Ё­ҐажЁЁ  ЈаҐЈ в  Nagr
void CfRSH5Doc::ChangeCMass(int Nagr)
{
    int Np = Pagregat[Nagr];
    double Mass = 0;
    CMass[Nagr].X = 0;
    CMass[Nagr].Y = 0;
    CMass[Nagr].Z = 0;

    CMass[Nagr].Vx = 0;
    CMass[Nagr].Vy = 0;
    CMass[Nagr].Vz = 0;
    // ‚лзЁб«Ґ­ЁҐ жҐ­ва  ¬ бб  ЈаҐЈ в  Nagr

    while (Np)
    {
        PNp = Npat(Np);
        Mass += PNp->mass;
        CMass[Nagr].X +=  PNp->mass * PNp->X;
        CMass[Nagr].Y +=  PNp->mass * PNp->Y;
        CMass[Nagr].Z +=  PNp->mass * PNp->Z;

        CMass[Nagr].Vx +=  PNp->mass * PNp->Vx;
        CMass[Nagr].Vy +=  PNp->mass * PNp->Vy;
        CMass[Nagr].Vz +=  PNp->mass * PNp->Vz;

        Np = ConPat[Np];
    }

    CMass[Nagr].X /= Mass;
    CMass[Nagr].Y /= Mass;
    CMass[Nagr].Z /= Mass;

    CMass[Nagr].Vx /= Mass;
    CMass[Nagr].Vy /= Mass;
    CMass[Nagr].Vz /= Mass;

    // ‚лзЁб«Ґ­ЁҐ Ї®«­®Ј® ¬®¬Ґ­в  M Ё ¬®¬Ґ­в  Ё­ҐажЁЁ J  ЈаҐЈ в  Nagr

    Np = Pagregat[Nagr];

    CMass[Nagr].Jx = CMass[Nagr].Jy = CMass[Nagr].Jz = 0;
    CMass[Nagr].Mx = CMass[Nagr].My = CMass[Nagr].Mz = 0;

    while (Np)
    {
        PNp = Npat(Np);
        CMass[Nagr].Jx += PNp->mass * ((pow(PNp->Z - CMass[Nagr].Z, 2) + pow(PNp->Y - CMass[Nagr].Y, 2)) + 0.4 * pow(5000000 * PNp->R, 2));
        CMass[Nagr].Jy += PNp->mass * ((pow(PNp->X - CMass[Nagr].X, 2) + pow(PNp->Z - CMass[Nagr].Z, 2)) + 0.4 * pow(5000000 * PNp->R, 2));
        CMass[Nagr].Jz += PNp->mass * ((pow(PNp->X - CMass[Nagr].X, 2) + pow(PNp->Y - CMass[Nagr].Y, 2)) + 0.4 * pow(5000000 * PNp->R, 2));

        CMass[Nagr].Mx += PNp->mass * ((PNp->Y - CMass[Nagr].Y) * (PNp->Vz - CMass[Nagr].Vz) - (PNp->Z - CMass[Nagr].Z) * (PNp->Vy - CMass[Nagr].Vy));
        CMass[Nagr].My += PNp->mass * ((PNp->Z - CMass[Nagr].Z) * (PNp->Vx - CMass[Nagr].Vx) - (PNp->X - CMass[Nagr].X) * (PNp->Vz - CMass[Nagr].Vz));
        CMass[Nagr].Mz += PNp->mass * ((PNp->X - CMass[Nagr].X) * (PNp->Vy - CMass[Nagr].Vy) - (PNp->Y - CMass[Nagr].Y) * (PNp->Vx - CMass[Nagr].Vx));

        Np = ConPat[Np];
    }
}

// Џа®жҐ¤гал ¤«п а Ў®вл б  ЈаҐЈ в ¬Ё
double CfRSH5Doc::GetMass(int i)
{
    double ret = 0;
    if (Pi->stop)
    {
        i = Pagregat[Pi->agr];
        do
        {
            ret += Pi->mass;
            i = ConPat[i];
        } while (i != 0);
    }
    else ret = Pi->mass;
    return ret;
}

// “бв ­®ўЄ  «Ё­Ґ©­ле бЄ®а®бвҐ© г з бвЁж ў  ЈаҐЈ вҐ б®¤Ґа¦ йЁе i
void CfRSH5Doc::SetAgrSpeed(Particle* Pi)
{
    RPoint W;
    if (Pi->stop)
    {
        //‚лзЁб«Ґ­ЁҐ «Ё­Ґ©­®© бЄ®а®бвЁ з бвЁж ў  ЈаҐЈ вҐ }
        int i = Pagregat[Pi->agr];
        AngleSpeed(Pi->agr, W);
        do
        {
            Pi->Vx = CMass[Pi->agr].Vx + W.Y * (Pi->Z - CMass[Pi->agr].Z) - W.Z * (Pi->Y - CMass[Pi->agr].Y);
            Pi->Vy = CMass[Pi->agr].Vy + W.Z * (Pi->X - CMass[Pi->agr].X) - W.X * (Pi->Z - CMass[Pi->agr].Z);
            Pi->Vz = CMass[Pi->agr].Vz + W.X * (Pi->Y - CMass[Pi->agr].Y) - W.Y * (Pi->X - CMass[Pi->agr].X);
            i = ConPat[i];
        } while (i != 0);
    }
}

//  „®Ў ў«пҐв j з бвЁжг Є  ЈаҐЈ вг ­ зЁ­ ойҐ¬гбп б i з бвЁжл
void CfRSH5Doc::AddPattoAgr(Particle* Pi, Particle* Pj)
{
    Pj->agr = Pi->agr;
    int i = Pi->N; int j = Pj->N;
    while (ConPat[i]) i = ConPat[i];

    ConPat[i] = j;
    if (ConPat[j] != 0)
    {
        j = ConPat[j];
        while (j)
        {
            Pj = Npat(j);
            Pj->agr = Pi->agr;
            j = ConPat[j];
        }
    }
}

//      ђa§¤ўЁЈ Ґв ¤ўҐ з бвЁжл
void CfRSH5Doc::PushAway(Particle* Pi, Particle* Pj)
{
    double dX, dY, dZ, R;

    R = 5000000 * (Pi->R + Pj->R);
    dX = Pj->X - Pi->X;
    dY = Pj->Y - Pi->Y;
    dZ = Pj->Z - Pi->Z;

    double dist_ij = sqrt(dX * dX + dY * dY + dZ * dZ);

    dX *= (R - dist_ij) / dist_ij;
    dY *= (R - dist_ij) / dist_ij;
    dZ *= (R - dist_ij) / dist_ij;

    if (Pj->agr != 0)
    {
        CMass[Pj->agr].X += dX;
        CMass[Pj->agr].Y += dY;
        CMass[Pj->agr].Z += dZ;
        int j = Pagregat[Pj->agr];
        while (j)
        {
            Pj = Npat(j);
            Pj->X += dX;
            Pj->Y += dY;
            Pj->Z += dZ;

            j = ConPat[j];
        }
    }
    else
    {
        Pj->X += dX;
        Pj->Y += dY;
        Pj->Z += dZ;
    }
}

void CfRSH5Doc::UnitPaticle(Particle* Pi, Particle* Pj)
{
    int l, kk, m;
    int i = Pi->N;
    int j = Pj->N;

    Particle* Pm; Particle* Pl;

    if (IsPatInAgr(Pi, Pj)) return;

    PushAway(Pi, Pj);

    SetAgrSpeed(Pi);
    SetAgrSpeed(Pj);


    if (Pi->stop == false)
    {
        if (Pj->stop == false)
        {

            Pagregat[s] = Pi->N;
            Pi->agr = s;
            Pj->agr = s;
            s++;
            ConPat[i] = j;

        }
        else AddPattoAgr(Pj, Pi);
    }
    else
        if (Pj->stop == false)
            AddPattoAgr(Pi, Pj);
        else
        {
            kk = Pi->agr;
            l = Pagregat[kk];
            s--;
            Pagregat[kk] = Pagregat[s];
            Pagregat[s] = 0;
            CMass[kk] = CMass[s];
            CMass[s].X = CMass[s].Y = CMass[s].Z =
                CMass[s].Vx = CMass[s].Vy = CMass[s].Vz =
                CMass[s].Mx = CMass[s].My = CMass[s].Mz =
                CMass[s].Jx = CMass[s].Jy = CMass[s].Jz = 0;
            m = Pagregat[kk];
            while (m)
            {
                Pm = Npat(m);
                Pm->agr = kk;
                m = ConPat[m];
            }
            Pl = Npat(l);
            AddPattoAgr(Pj, Pl);
        }

    // Џ®¬ҐвЁвм i Ё j Є Є ЇаЁ­ ¤«Ґ¦ йЁҐ Є  ЈаҐЈ в ¬
    Pi->stop = true;
    Pj->stop = true;
    ChangeCMass(Pj->agr);
}

void CfRSH5Doc::AgrForces()
{
    int i, kk;
    double mass, dVx, dVy, dVz, dX, dY, dZ;// , M1;
    for (kk = 1; kk < s; kk++)
    {
        i = Pagregat[kk];
        dF[kk].X = dF[kk].Y = dF[kk].Z = mass = 0;

        while (i)
        {
            Pi = Npat(i);
            dF[kk].X += Pi->Fx;
            dF[kk].Y += Pi->Fy;
            dF[kk].Z += Pi->Fz;
            mass += Pi->mass;
            i = ConPat[i];
        }
        if ((CMass[kk].X > 640) || (CMass[kk].X < 0))  CMass[kk].Vx = -CMass[kk].Vx;
        if ((CMass[kk].Y > 480) || (CMass[kk].Y < 0))  CMass[kk].Vy = -CMass[kk].Vy;
        if ((CMass[kk].Z > 640) || (CMass[kk].Z < 0))  CMass[kk].Vz = -CMass[kk].Vz;

        dVx = dt * dF[kk].X / mass;
        dVy = dt * dF[kk].Y / mass;
        dVz = dt * dF[kk].Z / mass;
        CMass[kk].Vx += dVx;
        CMass[kk].Vy += dVy;
        CMass[kk].Vz += dVz;
        CMass[kk].X += 5000000 * dt * CMass[kk].Vx;
        CMass[kk].Y += 5000000 * dt * CMass[kk].Vy;
        CMass[kk].Z += 5000000 * dt * CMass[kk].Vz;

        //-------- ‚лзЁб«Ґ­ЁҐ гЈ«  Phi --------//
        RPoint phi;
        AngleSpeed(kk, phi);
        phi.X = 5000000*dt * phi.X;
        phi.Y = 5000000 * dt * phi.Y;
        phi.Z = 5000000 * dt * phi.Z;
        //  ‚а йҐ­ЁҐ  ЈаҐЈ в  Ї®баҐ¤бвў®¬ ЇаҐ®Ўа §®ў ­Ёп Є®®а¤Ё­ в б Ї®¬®ймо---//
                             //---- ¬ ваЁжл ўа йҐ­Ёп ---//

        i = Pagregat[kk];
        while (i)
        {
            Pi = Npat(i);
            Pi->X += 5000000 * dt * (CMass[kk].Vx + dVx);
            Pi->Y += 5000000 * dt * (CMass[kk].Vy + dVy);
            Pi->Z += 5000000 * dt * (CMass[kk].Vz + dVz);
            dX = Pi->X - CMass[kk].X;
            dY = Pi->Y - CMass[kk].Y;
            Pi->X = CMass[kk].X + dX * cos(phi.Z) - dY * sin(phi.Z);
            Pi->Y = CMass[kk].Y + dY * cos(phi.Z) + dX * sin(phi.Z);
            dY = Pi->Y - CMass[kk].Y;
            dZ = Pi->Z - CMass[kk].Z;
            Pi->Y = CMass[kk].Y + dY * cos(phi.X) - dZ * sin(phi.X);
            Pi->Z = CMass[kk].Z + dZ * cos(phi.X) + dY * sin(phi.X);

            dX = Pi->X - CMass[kk].X;
            dZ = Pi->Z - CMass[kk].Z;
            Pi->X = CMass[kk].X + dX * cos(phi.Y) - dZ * sin(phi.Y);
            Pi->Z = CMass[kk].Z + dZ * cos(phi.Y) + dX * sin(phi.Y);
            i = ConPat[i];
        }
    }
}


int CfRSH5Doc::NumPatOutAgr()
{
    int i = 0;
    for (Pi = FirstPat; Pi != NULL; Pi = Pi->next)
        if (!Pi->stop) i++;
    return i;
}
int CfRSH5Doc::NumPatInAgr()
{
    return N - NumPatOutAgr();
}
//
// CfRSH5Doc commands
//

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CfRSH5Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
    // Измените этот код для отображения данных документа
    dc.FillSolidRect(lprcBounds, RGB(0, 0, 255));

    CString strText = _T("TODO: implement thumbnail drawing here");
    LOGFONT lf;

    CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
    pDefaultGUIFont->GetLogFont(&lf);
    lf.lfHeight = 36;

    CFont fontDraw;
    fontDraw.CreateFontIndirect(&lf);

    CFont* pOldFont = dc.SelectObject(&fontDraw);
    dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
    dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CfRSH5Doc::InitializeSearchContent()
{
    CString strSearchContent;
    // Задание содержимого поиска из данных документа.
    // Части содержимого должны разделяться точкой с запятой ";"

    // Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
    SetSearchContent(strSearchContent);
}

void CfRSH5Doc::SetSearchContent(const CString& value)
{
    if (value.IsEmpty())
    {
        RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
    }
    else
    {
        CMFCFilterChunkValueImpl* pChunk = nullptr;
        ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
        if (pChunk != nullptr)
        {
            pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
            SetChunkValue(pChunk);
        }
    }
}

#endif // SHARED_HANDLERS

// Диагностика CfRSH5Doc

#ifdef _DEBUG
void CfRSH5Doc::AssertValid() const
{
    CDocument::AssertValid();
}

void CfRSH5Doc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CCfRSH5Doc
