#ifndef LOGSAVEBASE_H
#define LOGSAVEBASE_H

#include "define.h"
#include <QObject>

class LogSaveBase : public QObject {
    Q_OBJECT
public:
    explicit LogSaveBase(QObject* parent = nullptr);
    ~LogSaveBase();

protected:

    virtual void on_logData(LogMsg msg) = 0;
    /**
     * @brief   打开新文件
     * @return  true：打开成功 false：打开失败
     */
    virtual bool openNewFile() = 0;

protected:
    QString m_strLogName; // 日志名
    static LogSaveBase* m_logSave; // 静态单例对象
};

#endif // LOGSAVEBASE_H
