#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "juttu.h"

#include <QPushButton>
#include <QLayout>
#include <QStackedLayout>
#include <QCheckBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rb1(new QRadioButton(tr("QHBoxLayout"))),
    rb2(new QRadioButton(tr("QVBoxLayout"))),
    rb3(new QRadioButton(tr("QGridLayout"))),
    lawi(0),
    j1(new Juttu(tr("yellow"))),
    j2(new Juttu(tr("white"))),
    j3(new Juttu(tr("orange"))),
    j4(new Juttu(tr("cyan")))
{
    ui->setupUi(this);

    ui->w1->setLayout(new QHBoxLayout());
    ui->w1->layout()->addWidget(rb1);
    ui->w1->layout()->addWidget(rb2);
    ui->w1->layout()->addWidget(rb3);

    connect(rb1, SIGNAL(toggled(bool)), this, SLOT(tog(bool)));
    connect(rb2, SIGNAL(toggled(bool)), this, SLOT(tog(bool)));
    connect(rb3, SIGNAL(toggled(bool)), this, SLOT(tog(bool)));

    ui->w2->setLayout(new QVBoxLayout());
    ui->w2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    rb1->toggle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw(QLayout* layout)
{
    if (lawi) {
        j1->setParent(0);
        j2->setParent(0);
        j3->setParent(0);
        delete lawi;
    }

    lawi = new QWidget();

    if (layout->inherits("QGridLayout")) {
        QGridLayout* grid = qobject_cast<QGridLayout*>(layout);
        grid->addWidget(j1, 0, 0);
        grid->addWidget(j2, 0, 1);
        grid->addWidget(j3, 1, 0, 1, 2);
    }
    else if (layout->inherits("QBoxLayout")) {
        QBoxLayout* box = qobject_cast<QBoxLayout*>(layout);
        box->addWidget(j1);
        box->addWidget(j2);
        box->addWidget(j3);
    }
    else {
        Q_ASSERT(false);
    }

    lawi->setLayout(layout);

    ui->w2->layout()->addWidget(lawi);

    j1->updateStretch();
    j2->updateStretch();
    j3->updateStretch();
}

void MainWindow::tog(bool on)
{
    if (!on) {
        return;
    }

    if (rb1->isChecked()) {
        draw(new QHBoxLayout());
    }
    else if (rb2->isChecked()) {
        draw(new QVBoxLayout());
    }
    else if (rb3->isChecked()) {
        draw(new QGridLayout());
    }
}


