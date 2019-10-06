
#ifndef LOGO_H
#define LOGO_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>
#include <QObject>
#include "field.h"

class Logo: public QObject
{
    Q_OBJECT
public:
    Logo(FieldSetting stng);
    ~Logo();
    const GLfloat *constData() const { return m_data.constData(); }
    int count() const { return m_count; }
    int vertexCount() const { return m_count / 6; }
    void addTime(double inc) {t=t+inc;}
    Field *getField() {return m_field;}

private:
    void quad(GLfloat x1, GLfloat y1, GLfloat z1, float e1, GLfloat x2, GLfloat y2, GLfloat z2, float e2, GLfloat x3, GLfloat y3, GLfloat z3, float e3, GLfloat x4, GLfloat y4, GLfloat z4, float e4);
    void add(const QVector3D &v, float e);
    double t, delta;
    float Emax, Emin;
    QVector<GLfloat> m_data;
    int m_count;
    Field *m_field;

public slots:
       void refreshLogo();

signals:
    void finished();

};

#endif // LOGO_H
