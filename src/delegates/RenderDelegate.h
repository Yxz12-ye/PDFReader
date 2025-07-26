#pragma once

#include "Delegate.h"
#include "model/DocumentModel.h"
#include <QObject>
#include <poppler/qt6/poppler-qt6.h>
#include <QImage>

class RenderDelegate : public QObject
{
    Q_OBJECT
private:
    DocumentModel* document;
    QList<QImage> _imageList;
public:

    RenderDelegate(DocumentModel* doc, QObject* parent = nullptr);
    ~RenderDelegate(){};
    void RenderToImage(QList<Poppler::Page*>& pageData);
signals:
    void RenderResult(int count, QList<QImage>& result);
};

