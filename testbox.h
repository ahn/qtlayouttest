#ifndef TESTBOX_H
#define TESTBOX_H

#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QSlider>
#include <QLabel>

class TestBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit TestBox(QString title);

    virtual QSize sizeHint() const;

    void updateStretch();
    
    virtual void resizeEvent(QResizeEvent* event);

signals:
    
public slots:

private slots:
    void policyActivated(int i);
    void sliderMoved(int);
    void stretchRequested(int);

private:
    void initSizeLabel();
    void initPolicyWidget();
    void initHintWidget();
    void initStretchWidget();

    QLabel* sizeLabel;
    QLabel* minSizeLabel;
    QComboBox* policy;
    QSlider* sliderH;
    QSlider* sliderV;
    QLabel* sizeH;
    QLabel* sizeV;
    QComboBox* stretch;
};

#endif // TESTBOX_H
