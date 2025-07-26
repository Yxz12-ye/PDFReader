#pragma once

#include "Delegate.h"
#include "model/DocumentModel.h"
#include <QFileDialog>

class OpenFileDelegate : public Delegate {
    Q_OBJECT

public:
    explicit OpenFileDelegate(DocumentModel* model,
                              QObject* parent = nullptr);

    void Implement(const QString& fileName) override;
    void Open();

private:
    DocumentModel* documentModel;

signals:
    void Opened();
};
