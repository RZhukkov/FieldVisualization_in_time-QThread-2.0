#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include "window.h"
#include <list>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();
private slots:
    void on_BtnVizual_clicked();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
