#include <QDesktopWidget>
#include <QDebug>
#include <QMessageBox>
#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "glwidget.h"
#include "field.h"


SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    setWindowTitle("FieldVisualisation");
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_BtnVizual_clicked()
{
    FieldSetting stngs;
    stngs.A=ui->SpinBoxA->value();
    stngs.B=ui->SpinBoxB->value();
    stngs.Z=ui->SpinBoxZ->value();
    stngs.eps=ui->SpinBoxEPS->value();
    stngs.mu=ui->SpinBoxMU->value();
    stngs.E0=ui->SpinBoxE0->value();
    stngs.H0=ui->SpinBoxH0->value();
    stngs.G_frequency=(ui->SpinBoxFREQ->value())*1000000000;

    Window *window = new Window(stngs);


    window->resize(window->sizeHint());

    int desktopArea = QApplication::desktop()->width() *
            QApplication::desktop()->height();
    int widgetArea = window->width() * window->height();

    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window->show();
    else
        window->showMaximized();
}

void SettingsWindow::on_actionExit_triggered()
{
    this->close();
}

void SettingsWindow::on_actionAbout_triggered()
{
    QMessageBox::about(0, "О приложении",
                       "FieldVisualization Ver. 1.0\n\n Autor Zhukov R.E.");
}
