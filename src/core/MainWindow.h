#include "../delegates/OpenFileDelegate.h"
#include "../delegates/model/DocumentModel.h"
#include "../delegates/RenderDelegate.h"
#include <QMenu>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QImage>

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    OpenFileDelegate* file;
    DocumentModel* doc;
    RenderDelegate* rendering;
    QVBoxLayout *pdf;
    QList<QLabel*> pages;
    int currentPage;
public:
    MainWindow(/* args */);
    ~MainWindow(){};
    void addPage(int count);
public slots:
    void renderPage(int count, QList<QImage>& imageList);
};
