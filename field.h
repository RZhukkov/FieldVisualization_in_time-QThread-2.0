#ifndef FIELD_H
#define FIELD_H

#include <list>

double const C_skor_sveta = 29979245800;

using namespace std;

struct mody
{
    int m;
    int n;
    double omega_krit;  //Критическая астота
};

struct E_point
{
    float x;    //координа точки X
    float y;    //координа точки Y
    float z;    //координа точки Z
    double E;   //напряженность в точке
};

struct FieldSetting
{
    double G_frequency;      //Частота поля
    double E0=10;           //Мощность генератора
    double H0=10;           //Мощность генератора
    float eps;              //Диэлектрическая проницаемость
    float mu;               //Магнитная проницаемость
    float A, B, Z;          //Геометрические размеры волновода
};

class Field
{
    /* -----Парраментры поля------ */
    double G_frequency;   //Частота поля
    double E0;            //Мощность генератора
    double H0;            //Мощность генератора

    /* -----Парраментры волновода------ */
    float eps;               //
    float mu;                //
    float A, B, Z;           //

   /* -----Расчетные данные------ */
    double k0;              //Коэффициент k0
    double omega;
    double  Emin, Emax;
    bool    maxmin;
    list <mody> omega_krit; //Критические частоты
    list <E_point> E_polya; //Напряжнность поля в точках

public:
    Field(FieldSetting stng);
    void set_frequency(double f){G_frequency=f;}
    void do_omega_krit ();
    void do_E_in_volnovod(float t, float delta);
    double get_E_in_point(float x, float y, float z, float t);
    float get_eps() {return eps;}
    float get_mu() {return mu;}
    float get_A() {return A;}
    float get_B() {return B;}
    float get_Z() {return Z;}
    double get_Emax () {return Emax;}
    double get_Emin () {return Emin;}
    double get_freq () {return G_frequency;}
    double get_E0 () {return E0;}
    double get_H0 () {return H0;}
    list <mody> & get_omega_krit () {return omega_krit;}
    list <E_point> & get_E_polya () {return E_polya;}
};

#endif // FIELD_H
