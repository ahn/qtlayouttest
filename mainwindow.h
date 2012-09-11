#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QCheckBox>

#include "juttu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    void draw(QLayout* layout);

    Ui::MainWindow *ui;

    QRadioButton* rb1;
    QRadioButton* rb2;
    QRadioButton* rb3;

    QWidget* lawi;

    Juttu* j1;
    Juttu* j2;
    Juttu* j3;
    Juttu* j4;



private slots:
    void tog(bool on);
};

#endif // MAINWINDOW_H
