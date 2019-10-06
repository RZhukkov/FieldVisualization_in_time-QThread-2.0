
#include <math.h>
#include <list>
#include <iostream>
#include <iterator>
#include <QDebug>
#include "field.h"


using namespace std;



Field::Field(FieldSetting stng)
{
    G_frequency=stng.G_frequency;
    k0=2*M_PI*stng.G_frequency/C_skor_sveta;
    omega=2*M_PI*stng.G_frequency;
    eps=stng.eps;
    mu=stng.mu;
    A=stng.A;
    B=stng.B;
    Z=stng.Z;
    H0=stng.H0;
    E0=stng.E0;
    do_omega_krit();
    maxmin=false;
}

void Field::do_omega_krit ()
{
    omega_krit.clear();
    int m(0);
    double omega;
    bool vihod=false;
    while (!vihod)
    {
        mody temp_mod;
        double kapa;
        int n(0);
        while (1)
        {
            if ((m==0)&&(n==0)) {n++; continue;}
            kapa=hypot(((m*M_PI)/A),((n*M_PI)/B));
            omega=(C_skor_sveta/sqrt(eps*mu))*kapa;
            if (((omega/(2*M_PI))>=G_frequency)&&(n==0))
            {vihod=true; break;}
            if ((omega/(2*M_PI))>=G_frequency) break;
            temp_mod.m=m;
            temp_mod.n=n;
            temp_mod.omega_krit=omega;
            Field::omega_krit.push_back(temp_mod);
            ++n;
        }++m;
    }
}

void Field::do_E_in_volnovod(float t, float delta)
{
    E_polya.clear();
    E_point temp;
    double E;

    //z=0, z=Z
    for (float y=0; y<B; y+=delta)
    {
        for (float x=0; x<A;x+=delta)
        {
            float z=0;
            E=get_E_in_point(x,y,z,t);
            if (!maxmin) {Emin=E; Emax=E; maxmin=true;}
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+delta,y,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+delta;
            temp.y=y;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+delta,y+delta,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+delta;
            temp.y=y+delta;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x,y+delta,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y+delta;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x,y,z+Z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y;
            temp.z=z+Z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x,y+delta,z+Z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y+delta;
            temp.z=z+Z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+delta,y+delta,z+Z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+delta;
            temp.y=y+delta;
            temp.z=z+Z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+delta,y,z+Z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+delta;
            temp.y=y;
            temp.z=z+Z;
            temp.E=E;
            E_polya.push_back(temp);
        }
    }


    //x=0, x=A
    for (float z=0; z<Z; z+=delta)
    {
        for (float y=0; y<B;y+=delta)
        {
            float x=0;
            E=get_E_in_point(x,y,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x,y+delta,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y+delta;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x,y+delta,z+delta,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y+delta;
            temp.z=z+delta;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x,y,z+delta,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y;
            temp.z=z+delta;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+A,y,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+A;
            temp.y=y;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+A,y,z+delta,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+A;
            temp.y=y;
            temp.z=z+delta;
            temp.E=E;
            E_polya.push_back(temp);


            E=get_E_in_point(x+A,y+delta,z+delta,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+A;
            temp.y=y+delta;
            temp.z=z+delta;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+A,y+delta,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+A;
            temp.y=y+delta;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);
        }
    }

    //y=0, y=B
    for (float z=0; z<Z; z+=delta)
    {
        for (float x=0; x<A;x+=delta)
        {
            float y=0;
            E=get_E_in_point(x,y,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x,y,z+delta,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y;
            temp.z=z+delta;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+delta,y,z+delta,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+delta;
            temp.y=y;
            temp.z=z+delta;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+delta,y,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+delta;
            temp.y=y;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            //            y=B;
            E=get_E_in_point(x,y+B,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y+B;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+delta,y+B,z,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+delta;
            temp.y=y+B;
            temp.z=z;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x+delta,y+B,z+delta,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x+delta;
            temp.y=y+B;
            temp.z=z+delta;
            temp.E=E;
            E_polya.push_back(temp);

            E=get_E_in_point(x,y+B,z+delta,t);
            if (E>Emax) Emax=E;
            if (E<Emin) Emin=E;
            temp.x=x;
            temp.y=y+B;
            temp.z=z+delta;
            temp.E=E;
            E_polya.push_back(temp);
        }
    }
}

double Field::get_E_in_point(float x, float y, float z, float t)
{   //cout<<"--------------------  X="<<x<<" Y="<<y<<" Z="<<z<<" ------------------------"<<endl;
    double Eztm, Extm, Eytm, Exte, Eyte, Ez=0, Ex=0, Ey=0, Erez;    //Напряженности поля составляющие и результирующая
    double kapa, h;
    int m, n;
    list <mody> ::iterator IT;
    for (IT=omega_krit.begin(); IT!=omega_krit.end(); IT++)
    {    m=IT->m; n=IT->n;
        /*  ----Составляющая поля TM----*/
        if ((m!=0)&&(n!=0))
        {   kapa=hypot((m*M_PI/A),(n*M_PI/B));
            h=sqrt(k0*k0*eps*mu-kapa*kapa);
            Extm=-(h/(k0*eps*mu))*E0*(m*M_PI/A)*cos(m*M_PI*x/A)*sin(n*M_PI*y/B)*cos(omega*t-h*z);
            Ex+=Extm;
            Eytm=-(h/(k0*eps*mu))*E0*(n*M_PI/B)*sin(m*M_PI*x/A)*cos(n*M_PI*y/B)*cos(omega*t-h*z);
            Ey+=Eytm;
            Eztm=(kapa*kapa/(k0*eps*mu))*E0*sin(m*M_PI*x/A)*sin(n*M_PI*y/B)*sin(omega*t-h*z);
            Ez+=Eztm;
        }
        /*  ----Составляющая поля TE----*/  //Ezte - всегда равна нулю
        Exte=(1/eps)*H0*(n*M_PI/B)*cos(m*M_PI*x/A)*sin(n*M_PI*y/B)*cos(omega*t-h*z);
        Ex+=Exte;
        Eyte=-(1/eps)*H0*(m*M_PI/A)*sin(m*M_PI*x/A)*cos(n*M_PI*y/B)*cos(omega*t-h*z);
        Ey+=Eyte;
    }
    /*  ----Результирующая напряженность в точке----*/
    Erez=sqrt(Ez*Ez+Ex*Ex+Ey*Ey);
    //cout<<" E="<<Erez<<endl;
    return Erez;
}
