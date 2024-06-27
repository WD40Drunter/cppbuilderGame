//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


#define Sx 900
#define Sy 500
#define N 20
int started1 = 0;
int started2 = 0;
int started3 = 0;
int started4 = 0; 
int started5 = 0;
int zegar = 0;
int reload = 0;
int score = 0;

TForm1* Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
         KeyPreview = True;
         this->OnKeyDown = FormKeyDown;
}
//---------------------------------------------------------------------------

__fastcall TPocisk::TPocisk(TComponent* Owner)
    : TShape(Owner)
{
    Width = 5;
    Height = 10;
    Shape = stRectangle;
    Brush->Color = clRed; 
}

void TPocisk::Ruch()
{
    Top -= 10;
}

__fastcall TPlayerShape::TPlayerShape(TComponent* Owner)
    : TShape(Owner)
{
}

void __fastcall TPlayerShape::Paint()
{
    TRect rect = this->ClientRect;
    int centerX = (rect.Left + rect.Right) / 2;
    int bottomY = rect.Bottom;
    int topY = rect.Top;

    TPoint points[3] = {
        TPoint(centerX, topY),        // wierzcho³ek trójk¹ta
        TPoint(rect.Left, bottomY),   // lewy dolny róg
        TPoint(rect.Right, bottomY)   // prawy dolny róg
    };

    Canvas->Pen = this->Pen;
    Canvas->Brush = this->Brush;
    Canvas->Polygon(points, 2);
}


class czastka
{
public:
    int x0, y0, vx, vy;
    double masa, q;

    TShape* ksz1;
    void ruch(void);
    void smierc(void);
    czastka(void);
    ~czastka(void);
};




czastka* tw1[N];   //   globalna tablica czastek
czastka* tw2[N];
czastka* tw3[N];
czastka* tw4[N];
czastka* tw5[N];
TPocisk* pociski[10];
int ile_poc = 10;


czastka::czastka()
{
    x0 = random(Sx);
    y0 = random(Sy);
    while ((vx = random(7) - 3) == 0);
    while ((vy = random(7) - 3) == 0);

    ksz1 = new TShape(Form1);
    ksz1->Parent = Form1;
    ksz1->Left = x0;
    ksz1->Top = y0;
    ksz1->Width = 5;
    ksz1->Height = 5;
    ksz1->Shape = stCircle;  // tu dodatkowo ustawiamy na kó³ko
}

czastka::~czastka()
{    // tu wyjatkowo nie trzeba robi delete ksz     (jest to robione automatycznie w bibliotece VCL)
}



void czastka::ruch()
{
    if (this != NULL)
    {
        x0 += vx;
        y0 += vy;
        if (x0 >= Sx) { vx = -vx; x0 = Sx - 1; }
        if (x0 < 0) { vx = -vx; x0 = 0; }
        if (y0 >= Sy) { vy = -vy; y0 = Sy - 1; }
        if (y0 < 0) { vy = -vy; y0 = 0; }
        ksz1->Left = x0;
        ksz1->Top = y0;
    }
}


void czastka::smierc()
{
    if (this != NULL)
    {
        delete ksz1;
    }
}



  
void __fastcall TForm1::Button1Click(TObject* Sender)
{       //public:
}
//---------------------------------------------------------------------------

void TForm1::SprawdzKolizje()
{
    czastka** czastkiGrup[] = {tw1, tw2, tw3, tw4, tw5};

    for (int i = 0; i < ile_poc; ++i)
    {
        if (pociski[i] != NULL)
        {
            TRect pociskRect = pociski[i]->BoundsRect;

            for (int g = 0; g < 5; ++g)
            {
                for (int j = 0; j < N; ++j)
                {
                    if (czastkiGrup[g][j] != NULL && czastkiGrup[g][j]->ksz1 != NULL)
                    {
                        TRect czastkaRect = czastkiGrup[g][j]->ksz1->BoundsRect;

                        TRect intersection;
                        if (IntersectRect(&intersection, &pociskRect, &czastkaRect))
                        {
                            delete pociski[i];
                            pociski[i] = NULL;

                            czastkiGrup[g][j]->smierc();
                            delete czastkiGrup[g][j];
                            czastkiGrup[g][j] = NULL;
                            score += 100;
                            Label1->Caption = "Score: " + IntToStr(score);
                        }
                    }
                }
            }
        }
    }
}


void __fastcall TForm1::Timer1Timer(TObject* Sender)
{
    int i;
    for (i = 0; i < N; i++)    //  petla po obiektach
    {
        tw1[i]->ruch();
        tw2[i]->ruch();
        tw3[i]->ruch();
        tw4[i]->ruch();
        tw5[i]->ruch();
        // narodziny
        // ....
    }
    if (started1 == 1)
    {
        if (zegar<250)
        {
            zegar+=1;
        }
        if (zegar == 50)
        {
            for (i = 0; i < N; i++)    //  petla po obiektach
            {
                tw2[i] = new czastka;
                started2 = 1;
                // narodziny
                // ....
            }
        }
        if (zegar == 100)
        {
            for (i = 0; i < N; i++)    //  petla po obiektach
            {
                tw3[i] = new czastka;
                started3 = 1;
                // narodziny
                // ....
            }
        }
        if (zegar == 150)
        {
            for (i = 0; i < N; i++)    //  petla po obiektach
            {
                tw4[i] = new czastka;
                started4 = 1;
                // narodziny
                // ....
            }
        }
        if (zegar == 200)
        {
            for (i = 0; i < N; i++)    //  petla po obiektach
            {
                tw5[i] = new czastka;
                started5 = 1;
                // narodziny
                // ....
            }
        }
    }
    for (int i = 0; i < ile_poc; ++i)
    {
        if (pociski[i] != NULL)
        {
            pociski[i]->Ruch();
            if (pociski[i]->Top < 0)
            {
                delete pociski[i];
                pociski[i] = NULL;
            }
        }
    }
    SprawdzKolizje();
    if (reload!=0)
    {
        reload -= 1;
    }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject* Sender)
{
    int i, j;
    Timer1->Enabled = false;
    if (started1 == 1)
    {
        for (j = 0; j < N; j++)    //  petla po obiektach
        {
            if (tw1[j] != NULL)
            {
                tw1[j]->smierc();
                delete tw1[j];
                tw1[j] = NULL;
            }
        }
        if (started2 == 1)
        {
            for (j = 0; j < N; j++)    //  petla po obiektach
            {
                if (tw2[j] != NULL)
                {
                    tw2[j]->smierc();
                    delete tw2[j];
                    tw2[j] = NULL;
                }
            }
            if (started3 == 1)
            {
                for (j = 0; j < N; j++)    //  petla po obiektach
                {
                    if (tw3[j] != NULL)
                    {
                        tw3[j]->smierc();
                        delete tw3[j];
                        tw3[j] = NULL;
                    }
                }
                if (started4 == 1)
                {
                    for (j = 0; j < N; j++)    //  petla po obiektach
                    {
                        if (tw4[j] != NULL)
                        {
                            tw4[j]->smierc();
                            delete tw4[j];
                            tw4[j] = NULL;
                        }
                    }
                    if (started5 == 1)
                    {
                        for (j = 0; j < N; j++)    //  petla po obiektach
                        {
                            if (tw5[j] != NULL)
                            {
                                tw5[j]->smierc();
                                delete tw5[j];
                                tw5[j] = NULL;
                            }
                        }
                    }
                }
            }
        }
    }
    for (j = 0; j < ile_poc; j++)
            {
                if (pociski[j] != NULL)
                {
                    delete pociski[j];
                    pociski[j] = NULL;
                }
            }
    for (i = 0; i < N; ++i)
        tw1[i] = new czastka;
    Timer1->Enabled = 1;
    if (player == NULL)
    {
        player = new TPlayerShape(this);
        player->Parent = this;
        player->Width = 20;
        player->Height = 20;
        player->Left = (Sx / 2) - (player->Width / 2);
        player->Top = Sy - player->Height + 5;
    }
    started1 = 1;
    zegar = 0;
    score = 0;
    Label1->Caption = "Score: " + IntToStr(score);
}

//---------------------------------------------------------------------------
int step = 10;
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (player != NULL)
{
    if (Key == 'A' && player->Left > 0)
    {
        player->Left = player->Left - step;
    }
    else if (Key == 'D' && player->Left < (Sx - player->Width))
    {
        player->Left = player->Left + step;
    }
    else if (Key == 'W')
    {
        int i;
        for(i=0;i<ile_poc;i++)
        {
             if(pociski[i] == NULL && reload == 0)
             {
                     pociski[i]=new TPocisk(this);
                     pociski[i]->Parent = this;
                     pociski[i]->Left = player->Left + player->Width / 2 - pociski[i]->Width / 2;
                     pociski[i]->Top = player->Top - pociski[i]->Height;
                     reload = 2;
                     break;
             }
        }
    }
}
}
//---------------------------------------------------------------------------

