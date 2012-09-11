#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QCheckBox>

#include "testbox.h"

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

    QRadioButton* rbHoriz;
    QRadioButton* rbVert;
    QRadioButton* rbGrid;

    QWidget* testBoxContainer;

    TestBox* tb1;
    TestBox* tb2;
    TestBox* tb3;



private slots:
    void changeLayout(bool on);
};

#endif // MAINWINDOW_H
