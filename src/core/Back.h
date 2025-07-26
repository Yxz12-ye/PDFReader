#pragma once
#include <poppler/qt6/poppler-qt6.h>
#include <poppler/qt6/poppler-converter.h>
#include <QUrl>
#include <QImage>
#include <QObject>

class Back : public QObject
{
    Q_OBJECT
private:
    std::unique_ptr<Poppler::Document> a;
    std::unique_ptr<Poppler::Page> pageClass;
    QImage image;
public:
    Back();
    ~Back();
    void convater(int page);

signals:
    void render(QImage image);

public slots:
    void openPDF(QString file);
};

