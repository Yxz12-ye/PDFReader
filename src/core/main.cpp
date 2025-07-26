#include "poppler/qt6/poppler-qt6.h"
#include <QApplication>
#include <QDebug>
#include "MainWindow.h"

int main(int argc, char** argv){
    QApplication w(argc, argv);
    MainWindow ui;
    ui.show();
    return w.exec();
}
