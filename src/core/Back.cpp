#include "Back.h"

Back::Back()
{

}

Back::~Back()
{
}

// void Back::openPDF(QString file)
// {
//     a = Poppler::Document::load(file);
//     qDebug()<<a.get()->numPages();
//     return ;
// }

void Back::openPDF(QString file)
{
    // 先释放所有现有资源
    a.reset(); // 重要：先释放文档对象
    
    // 重新加载文档
    std::unique_ptr<Poppler::Document> newDoc(Poppler::Document::load(file));
    if (!newDoc || newDoc->isLocked()) {
        qDebug() << "Failed to load document:" << file;
        return;
    }
    
    // 使用原子操作替换文档指针
    a = std::move(newDoc);
    qDebug() << "Loaded pages:" << a->numPages();
}

/*
void Back::convater(int page_index = 0) // 参数 page_index 0-indexed
{
    // 假设 a 是 std::unique_ptr<PDFDocument> 或类似
    if (!a) {
        qDebug() << "Error: PDF document 'a' is not loaded or is null.";
        return;
    }

    // 确保页码在有效范围内
    int num_pages = a.get()->numPages();
    if (num_pages == 0) {
        qDebug() << "Error: PDF document has no pages.";
        return;
    }

    // 将 0-indexed 的参数转换为 1-indexed 的页码
    int actual_page_number = page_index + 1;

    if (actual_page_number < 1 || actual_page_number > num_pages) {
        qDebug() << "Error: Invalid page index " << page_index << ". Document has " << num_pages << " pages.";
        return;
    }

    // 获取页面对象
    // 假设 a.get()->page() 接受 1-indexed 的页码，并返回一个智能指针或包装类
    auto page_wrapper = a.get()->page(actual_page_number);

    if (!page_wrapper) { // 检查返回的页面对象是否有效
        qDebug() << "Error: Failed to get page " << actual_page_number << ". Page object is null.";
        return;
    }

    // 获取原始页面指针（如果 page_wrapper 是智能指针）
    auto page_raw_ptr = page_wrapper.get();
    if (!page_raw_ptr) {
        qDebug() << "Error: Raw page pointer for page " << actual_page_number << " is null.";
        return;
    }

    static QImage image; // 仅初始化一次
    // 如果 convater 每次调用都应该重新渲染，则不应该使用 static QImage
    // 如果 static QImage 导致问题，可以先移除 static 关键字进行测试
    // 并且，如果每次调用都渲染不同页面，static QImage 也不合适
    // 考虑将其改为成员变量或每次都创建新对象
    if (image.isNull()) { // 第一次调用时初始化
         image = page_raw_ptr->renderToImage();
    }
    // 如果每次调用 convater 都希望渲染不同的页面，static QImage 是不合适的。
    // 应该每次都重新生成 QImage:
    // QImage current_image = page_raw_ptr->renderToImage();
    // emit render(current_image);


    emit render(image);
    return;
}
*/

void Back::convater(int page)
{
    if (!a) {
        qDebug() << "Error: PDF document 'a' is not loaded or is null.";
        return;
    }
    int num_pages = a->numPages();
    if (num_pages == 0) {
        qDebug() << "Error: PDF document has no pages.";
        return;
    }
    if (page < 0 || page >= num_pages) {
        qDebug() << "Error: Invalid page index " << page;
        return;
    }
    pageClass = a->page(page);
    if (!pageClass) {
        qDebug() << "Error: Page object is null.";
        return;
    }
    image = pageClass->renderToImage();
    emit render(image);
}
