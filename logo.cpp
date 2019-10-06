
#include "logo.h"
#include <qmath.h>
#include <iterator>
#include <algorithm>
#include <QDebug>
#include "field.h"

using namespace std;


Logo::Logo(FieldSetting stng) : m_count(0)
{
    m_field = new Field(stng);
    t=0;
    delta=0.4;  //0.4
    refreshLogo();
}

Logo::~Logo()
{

}

void Logo::add(const QVector3D &v, float e)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = (v.x()-(m_field->get_A()/2))/20.0;
    *p++ = (v.y()-(m_field->get_B()/2))/20.0;
    *p++ = (v.z()-(m_field->get_Z()/2))/20.0;
    float dln=(Emax - Emin);

    *p++= (e-Emin)/dln;         //R
    *p++= (1-((e-Emin)/dln));   //G
    *p++= 0.0;                  //B
    m_count += 9;
}

void Logo::quad(GLfloat x1, GLfloat y1, GLfloat z1, float e1, GLfloat x2, GLfloat y2, GLfloat z2, float e2, GLfloat x3, GLfloat y3, GLfloat z3, float e3, GLfloat x4, GLfloat y4, GLfloat z4, float e4)
{
    add(QVector3D(x1, y1, z1), e1);
    add(QVector3D(x4, y4, z4), e4);
    add(QVector3D(x2, y2, z2), e2);

    add(QVector3D(x3, y3, z3), e3);
    add(QVector3D(x2, y2, z2), e2);
    add(QVector3D(x4, y4, z4), e4);
}

void Logo::refreshLogo()
{
    m_field->do_E_in_volnovod(t,delta);
    list <E_point> E;
    E=m_field->get_E_polya();
    Emax = m_field->get_Emax();
    Emin = m_field->get_Emin();
    m_data.clear();
    m_count=0;
    m_data.resize(4501000 * 6);


    for (list<E_point>::iterator p=E.begin(); p!=E.end(); p++)
    {

        QVector3D v1 = QVector3D(p->x, p->y, p->z);
        float e1=p->E;
        p++;
        QVector3D v2 = QVector3D(p->x, p->y, p->z);
        float e2=p->E;
        p++;
        QVector3D v3 = QVector3D(p->x, p->y, p->z);
        float e3=p->E;
        p++;
        QVector3D v4 = QVector3D(p->x, p->y, p->z);
        float e4=p->E;

        quad(v1.x(), v1.y(), v1.z(), e1, v2.x(), v2.y(), v2.z(), e2, v3.x(), v3.y(), v3.z(), e3, v4.x(), v4.y(), v4.z(), e4);

    }
    t+=0.000000000006;

    emit finished();
}





