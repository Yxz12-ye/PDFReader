#include "UI.h"

UI::UI():a(this),r(this),im(this){
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(&a);
    layout->addSpacing(20);
    layout->addWidget(&r);
    layout->addSpacing(20);
    layout->addWidget(&im);
    a.setText("open");
    r.setText("render to image");
    im.setMinimumSize(100,100);
    connect(&a,&QPushButton::clicked,this,&UI::func);
    connect(this,&UI::si1,&b,&Back::openPDF);
    connect(&r,&QPushButton::clicked,&b,&Back::convater);
    connect(&b,&Back::render,this,&UI::rerending,Qt::QueuedConnection);
}

UI::~UI()
{
}

void UI::func()
{
    qDebug()<<"clicked";
    // emit si1("C:\\Users\\30789\\Documents\\RFF_Recognition_Based_on_Adaptive_Signal_Transform_and_Weighted_Feature_Fusion.pdf");
    emit si1("C:\\Users\\30789\\Documents\\P020201223393493838369.pdf");
}

void UI::rerending(QImage image){
    im.setPixmap(QPixmap::fromImage(image));
}
