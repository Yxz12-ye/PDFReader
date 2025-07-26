#pragma once

#include <QObject>
#include <QString>

class Delegate : public QObject { // 所有代理的基类
    Q_OBJECT

public:
    explicit Delegate(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Delegate() = default;

    virtual void Implement(const QString& data) = 0; // 实现函数的接口
};