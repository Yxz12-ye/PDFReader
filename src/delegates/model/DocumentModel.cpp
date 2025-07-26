#include "DocumentModel.h"
#include <QDebug>

DocumentModel::DocumentModel(QObject *parent) : QObject(parent) {}

void DocumentModel::openFile(const QString &path)
{
    qDebug() << tr("打开文件:") << path;

    // 这里可以放模型处理的具体实现（比如调用Poppler之类的）
    auto _document = Poppler::Document::load(path);
    if (_document)
    {
        document = std::move(_document);
        qDebug() << tr("打开成功");
        getPage();
        return;
    }
    qDebug() << tr("打开失败");
    return;
}

bool DocumentModel::isNULL()
{
    if (document)
        return false;
    return true;
}

void DocumentModel::getPage()
{
    int total = document->numPages();
    int renderNum = total < 10 ? total : 10;
    for (int i = 0; i < renderNum; ++i)
    {
        pageData.append(std::shared_ptr<Poppler::Page>(document->page(i).release()));
        // document->page(i)->renderToImage().save(QString::number(i)+".png"); 不报错代码
        // pageData[i]->renderToImage().save(QString::number(i)+".png"); 报错代码
    }
    emit startRender(pageData);
}

void DocumentModel::getImage(int count, QList<QImage> _imageList)
{
    image = _imageList;
    emit temp(count, image);
    return ;
}