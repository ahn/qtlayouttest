#ifndef JUTTU_H
#define JUTTU_H

#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QSlider>
#include <QLabel>

class Juttu : public QGroupBox
{
    Q_OBJECT
public:
    explicit Juttu(QString title);

    virtual QSize sizeHint() const;

    void updateStretch();
    
signals:
    
public slots:

private slots:
    void policyActivated(int i);
    void sliderMoved(int);
    void resizeClicked();
    void stretchRequested(int);

private:
    void initPolicyWidget();
    void initHintWidget();
    void initStretchWidget();

    QComboBox* policy;
    QSlider* sliderH;
    QSlider* sliderV;
    QLabel* sizeH;
    QLabel* sizeV;
    QComboBox* stretch;
};

#endif // JUTTU_H
