#pragma once

#include <QObject>
#include <QString>
#include <poppler/qt6/poppler-qt6.h>
#include <QImage>

class DocumentModel : public QObject {
    Q_OBJECT
public:
    explicit DocumentModel(QObject* parent = nullptr);
    void openFile(const QString& path);
    bool isNULL();
    void getPage();// 临时
private:
    std::unique_ptr<Poppler::Document> document;
    QList<std::shared_ptr<Poppler::Page>> pageData;
    QList<QImage> image;
signals:
    void startRender(QList<std::shared_ptr<Poppler::Page>>& pageData);
    void RenderingEnd();
    void temp(int count, QList<QImage>& a);
public slots:
    void getImage(int count, QList<QImage> _imageList);
};