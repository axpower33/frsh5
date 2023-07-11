
// fRSH5Doc.h: интерфейс класса CfRSH7Doc 
//

#pragma once

struct RPoint
{
    double X;
    double Y;
    double Z;
};
struct  Particle
{
    double X, Y, Z;
    double Vx, Vy, Vz;
    double Fx, Fy, Fz;
    double VanX, VanY, VanZ;
    double mass;
    double q;
    double R;
    int   N;
    int   agr;
    bool  stop;
    Particle* next;
    Particle* pred;
};

struct Agregat
{
    double X, Y, Z;
    double Vx, Vy, Vz;
    double Jx, Jy, Jz;
    double Mx, My, Mz;
};


//{{AFX_MSG(CFR3dDoc)
// Handlers within the section marked by {{AFX_MSG and }}AFX_MSG
// are maintained by ClassExpress.
//}}AFX_MSG


class CfRSH5Doc : public CDocument
{
protected: // создать только из сериализации
    CfRSH5Doc() noexcept;
    DECLARE_DYNCREATE(CfRSH5Doc)

    // Атрибуты
public:

    // Операции
public:

    // Переопределение
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    virtual void OnIdle();
#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent();
    virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

    // Реализация
public:
    virtual ~CfRSH5Doc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // fr3d functions
protected:
    void MakeArray(int N);
    void DistroyArray();
    Particle* Npat(int Np);
    void MxwDstr();
    void SizePatDistr();
    void SpontDstr();
    void zeroDstr();
    void InitParticle();
    void InitAgr();
    int sortOfZ(const void* a, const void* b);
    void CulonForces();
    bool IsPatInAgr(Particle* Pi, Particle* Pj);
    void MovePart();
    void AngleSpeed(int kk, RPoint& W);
    void ChangeCMass(int Nagr);
    double GetMass(int i);
    void SetAgrSpeed(Particle* Pi);
    void AddPattoAgr(Particle* Pi, Particle* Pj);
    void PushAway(Particle* Pi, Particle* Pj);
    void UnitPaticle(Particle* Pi, Particle* Pj);
    void AgrForces();
    int NumPatOutAgr();
    int NumPatInAgr();
public:
    int N;
    double dt;
    double Rmax;
    double Rmin;
    double Rmid;
    double Tmshft;
    double DensAg;
    int Tk;
    double MaxQ;
    double Xmax;
    double Ymax;
    double Zmax;
    int xx;
    Particle* FirstPat;
    Particle* PNp;
    Agregat dF[300];
    int Pagregat[150];
    Agregat CMass[150];
    int ConPat[150];
    int s;
    double t;
    Particle* LastPat;
    Particle* TempP;
    Particle* Pi;
    Particle* Pj;
    bool needCharge;
    double GetScX, GetScY;
    double GetmaxX, GetmaxY;
    double GetminX, GetminY;
    double rangeX;
    double rangeY;
    double rangeR;
    bool WorkShow;

    // Созданные функции схемы сообщений
protected:
    DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
    // Вспомогательная функция, задающая содержимое поиска для обработчика поиска
    void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};



