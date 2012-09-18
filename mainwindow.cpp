#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QLayout>
#include <QStackedLayout>
#include <QCheckBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rbHoriz(new QRadioButton("QHBoxLayout")),
    rbVert(new QRadioButton("QVBoxLayout")),
    rbGrid(new QRadioButton("QGridLayout")),
    testBoxContainer(0),
    tb1(new TestBox("white")),
    tb2(new TestBox("yellow")),
    tb3(new TestBox("orange"))
{
    ui->setupUi(this);

    ui->layoutSelectWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->layoutSelectWidget->setLayout(new QHBoxLayout());
    ui->layoutSelectWidget->layout()->addWidget(new QLabel("Layout: "));
    ui->layoutSelectWidget->layout()->addWidget(rbHoriz);
    ui->layoutSelectWidget->layout()->addWidget(rbVert);
    ui->layoutSelectWidget->layout()->addWidget(rbGrid);

    connect(rbHoriz, SIGNAL(toggled(bool)), this, SLOT(changeLayout(bool)));
    connect(rbVert, SIGNAL(toggled(bool)), this, SLOT(changeLayout(bool)));
    connect(rbGrid, SIGNAL(toggled(bool)), this, SLOT(changeLayout(bool)));

    ui->mainArea->setLayout(new QVBoxLayout());
    ui->mainArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    rbHoriz->toggle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw(QLayout* layout)
{
    if (testBoxContainer) {
        tb1->setParent(0);
        tb2->setParent(0);
        tb3->setParent(0);
        delete testBoxContainer;
    }

    testBoxContainer = new QWidget();

    if (layout->inherits("QGridLayout")) {
        QGridLayout* grid = qobject_cast<QGridLayout*>(layout);
        grid->addWidget(tb1, 0, 0);
        grid->addWidget(tb2, 0, 1);
        grid->addWidget(tb3, 1, 0, 1, 2);
    }
    else if (layout->inherits("QBoxLayout")) {
        QBoxLayout* box = qobject_cast<QBoxLayout*>(layout);
        box->addWidget(tb1);
        box->addWidget(tb2);
        box->addWidget(tb3);
    }
    else {
        Q_ASSERT(false);
    }

    testBoxContainer->setLayout(layout);

    ui->mainArea->layout()->addWidget(testBoxContainer);

    tb1->updateStretch();
    tb2->updateStretch();
    tb3->updateStretch();
}

void MainWindow::changeLayout(bool on)
{
    if (!on) {
        return;
    }

    if (rbHoriz->isChecked()) {
        draw(new QHBoxLayout());
    }
    else if (rbVert->isChecked()) {
        draw(new QVBoxLayout());
    }
    else if (rbGrid->isChecked()) {
        draw(new QGridLayout());
    }
}


