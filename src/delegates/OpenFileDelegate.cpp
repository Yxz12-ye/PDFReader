#include "OpenFileDelegate.h"

#include <QDebug>

OpenFileDelegate::OpenFileDelegate(
    DocumentModel* model,
    QObject* parent)
    : Delegate(parent)
    , documentModel(model) {}

void OpenFileDelegate::Implement(const QString& fileName) { // 这里是调用模型的实现，若不用模型则直接完善该函数接口即可
    if(documentModel)
    {
        documentModel->openFile(fileName); // 调用具体的处理函数
    }
}

void OpenFileDelegate::Open() { 
    QWidget a;
    QFileDialog file(&a);
    file.setFileMode(QFileDialog::AnyFile);
    file.setNameFilter(tr("PDFDocument (*.pdf)"));
    file.setViewMode(QFileDialog::Detail);
    QString path = file.getOpenFileName();
    if(!path.isNull()){
        documentModel->openFile(path);
    }
    if(!documentModel->isNULL()) emit Opened();
}