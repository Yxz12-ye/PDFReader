#include "MainWindow.h"

MainWindow::MainWindow()
{
    doc = new DocumentModel();
    file = new OpenFileDelegate(doc);
    rendering = new RenderDelegate(doc);
    QWidget *m = new QWidget;
    QMenuBar *menuBar = new QMenuBar;
    QMenu *menu = new QMenu(tr("File"));
    QVBoxLayout *Vlayout = new QVBoxLayout(this);
    QHBoxLayout *Hlayout = new QHBoxLayout(this);
    pdf = new QVBoxLayout(m);
    QAction *openAction = menu->addAction(tr("Open"));
    QAction *exitAction = menu->addAction(tr("Exit"));
    QList<QAction *> actionList;
    QScrollArea *pdfArea = new QScrollArea(this);

    pdfArea->setWidgetResizable(true);
    pdfArea->setWidget(m);
    pdfArea->setMinimumSize(100, 100);
    this->setMinimumSize(300, 300);

    actionList.append(openAction);
    actionList.append(exitAction);
    menu->addActions(actionList);
    menuBar->addMenu(menu);
    Hlayout->addWidget(menuBar);
    Vlayout->addLayout(Hlayout);
    Vlayout->addSpacing(10);
    Vlayout->addWidget(pdfArea);

    connect(openAction, &QAction::triggered, file, &OpenFileDelegate::Open);
    connect(doc,&DocumentModel::startRender,rendering,&RenderDelegate::RenderToImage);
    connect(rendering,&RenderDelegate::RenderResult,doc,&DocumentModel::getImage);
    connect(doc,&DocumentModel::temp,this,&MainWindow::renderPage);
    connect(exitAction, &QAction::triggered, this, [this]
            {
        qDebug("Exit");
        this->close(); });
}

void MainWindow::addPage(int count)
{
    for (int i = 0; i < count; ++i)
    {
        pages.append(new QLabel(QString::number(i)));
        pdf->addWidget(pages.back());
    }
}

void MainWindow::renderPage(int count, QList<QImage>& imageList)
{
    addPage(count);
    for(int i = 0 ;i<count;++i){
        pages[i]->setPixmap(QPixmap::fromImage(imageList[i]));
    }
}
