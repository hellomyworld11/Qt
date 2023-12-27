#ifndef LOGSAVETXT_H
#define LOGSAVETXT_H

#include "logconfig.h"
#include "logsavebase.h"
#include <QFile>
#include <QMutex>
#include <QTextStream>

class LogSaveTxt : public LogSaveBase {
public:
    Q_OBJECT
    //属性宏
    Q_PROPERTY(FileType m_type READ fileType WRITE setFileType)
public:
    enum FileType {
        Log,
        CSV,
    };

public:
    static void initLog(); // 初始化日志保存功能
    static LogSaveBase* getInstance(); // 获取单例对象
    void setFileType(FileType type);
    FileType fileType() { return m_type; }

protected:
    void on_logData(LogMsg msg) override;
    bool openNewFile() override;
    bool relyTime();
    bool relySize();
    bool relyRowNum();
    bool openFile(QString name);

private:
    LogSaveTxt(QObject* parent = nullptr);
    ~LogSaveTxt();

private:
    QFile m_file;
    QTextStream m_out;
    FileType m_type;
    QMutex m_mutex;
    QString m_strLogFormat; // 保存的日志内容格式
    QString m_strNameFormat; // 保存的日志文件名称格式
    QString m_strTimeNameFormat;
};

#endif // LOGSAVETXT_H
