#include "juttu.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>


Juttu::Juttu(QString background) :
    QGroupBox(),
    policy(new QComboBox()),
    sliderH(new QSlider(Qt::Horizontal)),
    sliderV(new QSlider(Qt::Horizontal)),
    sizeH(new QLabel()),
    sizeV(new QLabel()),
    stretch(new QComboBox())
{
    setStyleSheet(tr("QGroupBox { border: 2px solid black; background: %1; }").arg(background));

    QLayout* la = new QVBoxLayout();
    setLayout(la);

    initPolicyWidget();

    initHintWidget();

    initStretchWidget();

    QPushButton* resizeButton = new QPushButton("Resize to SizeHint");
    connect(resizeButton, SIGNAL(clicked()), this, SLOT(resizeClicked()));
    layout()->addWidget(resizeButton);



    connect(sliderH, SIGNAL(valueChanged(int)), this, SLOT(sliderMoved(int)));
    connect(sliderV, SIGNAL(valueChanged(int)), this, SLOT(sliderMoved(int)));

    sliderH->setValue(200);
    sliderV->setValue(100);
}

QSize Juttu::sizeHint() const
{
    //return QGroupBox::sizeHint();
    return QSize(sliderH->value(), sliderV->value());
}

void Juttu::updateStretch()
{
    stretchRequested(stretch->currentIndex());
    stretch->setEnabled(qobject_cast<QWidget*>(parent())->layout()->inherits("QBoxLayout"));
}

void Juttu::initPolicyWidget() {
    QWidget* sp = new QWidget();
    sp->setLayout(new QVBoxLayout());
    sp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    layout()->addWidget(sp);

    sp->layout()->addWidget(new QLabel(tr("Size Policy:")));

    policy->addItem(tr("Preferred"),
                    QSizePolicy(QSizePolicy::Preferred,
                                QSizePolicy::Preferred));

    policy->addItem(tr("Fixed"),
                    QSizePolicy(QSizePolicy::Fixed,
                                QSizePolicy::Fixed));

    policy->addItem(tr("Minimum"),
                    QSizePolicy(QSizePolicy::Minimum,
                                QSizePolicy::Minimum));

    policy->addItem(tr("Maximum"),
                    QSizePolicy(QSizePolicy::Maximum,
                                QSizePolicy::Maximum));

    policy->addItem(tr("Expanding"),
                    QSizePolicy(QSizePolicy::Expanding,
                                QSizePolicy::Expanding));

    policy->addItem(tr("MinimumExpanding"),
                    QSizePolicy(QSizePolicy::MinimumExpanding,
                                QSizePolicy::MinimumExpanding));

    policy->addItem(tr("Ignored"),
                    QSizePolicy(QSizePolicy::Ignored,
                                QSizePolicy::Ignored));

    sp->layout()->addWidget(policy);

    connect(policy, SIGNAL(activated(int)), this, SLOT(policyActivated(int)));
}

void Juttu::initHintWidget()
{
    QWidget* sp = new QWidget();
    sp->setLayout(new QVBoxLayout());
    sp->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layout()->addWidget(sp);

    sp->layout()->addWidget(new QLabel(tr("Horizontal Size Hint:")));
    sp->layout()->addWidget(sizeH);

    sliderH->setRange(0, 400);
    sp->layout()->addWidget(sliderH);

    sp->layout()->addWidget(new QLabel(tr("Vertical Size Hint:")));
    sp->layout()->addWidget(sizeV);

    sliderV->setRange(0, 400);
    sp->layout()->addWidget(sliderV);
}

void Juttu::initStretchWidget() {
    QWidget* sp = new QWidget();
    sp->setLayout(new QVBoxLayout());
    sp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    for (int i=0; i<=5; ++i) {
        stretch->addItem(tr("%1").arg(i), i);
    }
    sp->layout()->addWidget(new QLabel("Stretch (HBoxLayout only)"));
    sp->layout()->addWidget(stretch);
    layout()->addWidget(sp);

    connect(stretch, SIGNAL(activated(int)), this, SLOT(stretchRequested(int)));
}

void Juttu::policyActivated(int i)
{
   QSizePolicy po = policy->itemData(i).value<QSizePolicy>();
   setSizePolicy(po);
}

void Juttu::sliderMoved(int)
{
    sizeH->setText(QString("%1").arg(sliderH->value()));
    sizeV->setText(QString("%1").arg(sliderV->value()));
    updateGeometry();
}

void Juttu::resizeClicked()
{
    int x = sliderH->value() ? sliderH->value() : 1;
    int y = sliderV->value() ? sliderV->value() : 1;
    resize(x, y);
}

void Juttu::stretchRequested(int i) {
    int val = stretch->itemData(i).value<int>();

    QObject* pa = parent();
    QWidget* parent = qobject_cast<QWidget*>(pa);
    if (parent->layout()->inherits("QBoxLayout")) {
        QBoxLayout* box = qobject_cast<QBoxLayout*>(parent->layout());
        box->setStretch(box->indexOf(this), val);
    }
    /*else if (parent->layout()->inherits("QGridLayout")) {
        QGridLayout* grid = qobject_cast<QGridLayout*>(parent->layout());
        int index = grid->indexOf(this);
        int row = index/2;
        int col = index%2;
        grid->setRowStretch(row, val);
        grid->setColumnStretch(col, val);
    }*/
}
