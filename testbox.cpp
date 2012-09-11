#include "testbox.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>


TestBox::TestBox(QString background) :
    QGroupBox(),
    sizeLabel(new QLabel()),
    minSizeLabel(new QLabel()),
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

    initSizeLabel();
    initPolicyWidget();
    initHintWidget();
    initStretchWidget();

    connect(sliderH, SIGNAL(valueChanged(int)), this, SLOT(sliderMoved(int)));
    connect(sliderV, SIGNAL(valueChanged(int)), this, SLOT(sliderMoved(int)));

    sliderH->setValue(200);
    sliderV->setValue(200);
}

QSize TestBox::sizeHint() const
{
    return QSize(sliderH->value(), sliderV->value());
}

void TestBox::updateStretch()
{
    stretchRequested(stretch->currentIndex());
    stretch->setEnabled(qobject_cast<QWidget*>(parent())->layout()->inherits("QBoxLayout"));
}

void TestBox::resizeEvent(QResizeEvent* event)
{
    QGroupBox::resizeEvent(event);
    int w = size().width();
    int h = size().height();
    sizeLabel->setText(tr("Current size: %1 x %2").arg(w).arg(h));
    int minW = minimumSizeHint().width();
    int minH = minimumSizeHint().height();
    minSizeLabel->setText(tr("Minimum size hint: %1 x %2").arg(minW).arg(minH));
}

void TestBox::initSizeLabel()
{
    QWidget* cont = new QWidget();
    cont->setLayout(new QVBoxLayout());
    cont->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    cont->layout()->addWidget(sizeLabel);
    cont->layout()->addWidget(minSizeLabel);
    layout()->addWidget(cont);
}

void TestBox::initPolicyWidget() {
    QWidget* cont = new QWidget();
    cont->setLayout(new QVBoxLayout());
    cont->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    layout()->addWidget(cont);

    cont->layout()->addWidget(new QLabel(tr("Size Policy:")));

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

    cont->layout()->addWidget(policy);

    connect(policy, SIGNAL(activated(int)), this, SLOT(policyActivated(int)));
}

void TestBox::initHintWidget()
{
    QWidget* cont = new QWidget();
    cont->setLayout(new QVBoxLayout());
    cont->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layout()->addWidget(cont);

    cont->layout()->addWidget(new QLabel(tr("Horizontal Size Hint:")));
    cont->layout()->addWidget(sizeH);

    sliderH->setRange(0, 500);
    cont->layout()->addWidget(sliderH);

    cont->layout()->addWidget(new QLabel(tr("Vertical Size Hint:")));
    cont->layout()->addWidget(sizeV);

    sliderV->setRange(0, 500);
    cont->layout()->addWidget(sliderV);
}

void TestBox::initStretchWidget() {
    QWidget* cont = new QWidget();
    cont->setLayout(new QVBoxLayout());
    cont->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    for (int i=0; i<=5; ++i) {
        stretch->addItem(tr("%1").arg(i), i);
    }
    cont->layout()->addWidget(new QLabel("Stretch (HBoxLayout only)"));
    cont->layout()->addWidget(stretch);
    layout()->addWidget(cont);

    connect(stretch, SIGNAL(activated(int)), this, SLOT(stretchRequested(int)));
}

void TestBox::policyActivated(int i)
{
   QSizePolicy po = policy->itemData(i).value<QSizePolicy>();
   setSizePolicy(po);
}

void TestBox::sliderMoved(int)
{
    sizeH->setText(QString("%1").arg(sliderH->value()));
    sizeV->setText(QString("%1").arg(sliderV->value()));
    updateGeometry();
}

void TestBox::stretchRequested(int i) {
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


