#ifndef LOGPROCESS_H
#define LOGPROCESS_H

#include "define.h"
#include <QObject>

class LogProcess : public QObject {
    Q_OBJECT
public:
    static LogProcess* GetInstance();

    static void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);
signals:
    void logData(LogMsg msg);

private:
    explicit LogProcess(QObject* parent = nullptr);
    ~LogProcess();
    static LogProcess* m_log;
};

#endif // LOGPROCESS_H
