#include <QtWidgets>
#include "Back.h"
#include <QObject>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>

class UI : public QWidget
{
    Q_OBJECT
private:
    QPushButton a;
    QPushButton r;
    QLabel im;
    Back b;
public:
    UI(/* args */);
    ~UI();
    void func();
public slots:
    void rerending(QImage image);

signals:
    void si1(QString msg);
};