
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAction>
#include "field.h"

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
QT_END_NAMESPACE

class GLWidget;
class SettingsWindow;

class Window : public QWidget
{
    Q_OBJECT
public:
    Window(FieldSetting stng);
    ~Window();
protected:
    virtual void contextMenuEvent(QContextMenuEvent *pe)
    {m_pmnu->exec(pe->globalPos());}
private slots:
    void SaveInformation(QAction* action);
private:
    GLWidget *glWidget;
    QMenu *m_pmnu;
};

#endif
