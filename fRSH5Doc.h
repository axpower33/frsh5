
// fRSH5Doc.h: интерфейс класса CfRSH7Doc 
//

#pragma once

struct RPoint
{
    float X;
    float Y;
    float Z;
};
struct  Particle
{
    float X, Y, Z;
    float Vx, Vy, Vz;
    float Fx, Fy, Fz;
    float VanX, VanY, VanZ;
    float mass;
    float q;
    float R;
    int   N;
    int   agr;
    bool  stop;
    Particle* next;
    Particle* pred;
};

struct Agregat
{
    float X, Y, Z;
    float Vx, Vy, Vz;
    float Jx, Jy, Jz;
    float Mx, My, Mz;
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
    void InitParticle();
    void InitAgr();
    void CulonForces();
    bool IsPatInAgr(Particle* Pi, Particle* Pj);
    void MovePart();
    void AngleSpeed(int kk, RPoint& W);
    void ChangeCMass(int Nagr);
    float GetMass(int i);
    void SetAgrSpeed(Particle* Pi);
    void AddPattoAgr(Particle* Pi, Particle* Pj);
    void PushAway(Particle* Pi, Particle* Pj);
    void UnitPaticle(Particle* Pi, Particle* Pj);
    void AgrForces();
public:
    int N;
    float dt;
    float Rmax;
    float Rmin;
    float Rmid;
    float Tmshft;
    float DensAg;
    int Tk;
    int MaxQ;
    float Xmax;
    float Ymax;
    float Zmax;
    Particle* FirstPat;
    Particle* PNp;
    Agregat* dF;
    int* Pagregat;
    Agregat* CMass;
    int* ConPat;
    int s;
    float t;
    Particle* LastPat;
    Particle* TempP;
    Particle* Pi;
    Particle* Pj;
    bool needCharge;
    float GetScX, GetScY;
    float GetmaxX, GetmaxY;
    float GetminX, GetminY;
    float rangeX;
    float rangeY;
    float rangeR;

    // Созданные функции схемы сообщений
protected:
    DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
    // Вспомогательная функция, задающая содержимое поиска для обработчика поиска
    void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};



