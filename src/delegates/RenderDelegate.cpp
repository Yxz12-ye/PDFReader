#include "RenderDelegate.h"


RenderDelegate::RenderDelegate(DocumentModel *doc, QObject *parent)
    : QObject(parent), document(doc)
{
}

void RenderDelegate::RenderToImage(QList<std::shared_ptr<Poppler::Page>>& pageData)
{
    QImage temp;
    if(!_imageList.isEmpty()) _imageList.clear();
    for(int i = 0;i<pageData.size();++i){
        temp = pageData[i]->renderToImage();
        _imageList.append(temp);
    }
    emit RenderResult(pageData.size(),_imageList);
}
