#include "logprocess.h"
#include <QDebug>
#include <QMutex>
LogProcess* LogProcess::m_log = nullptr;
QtMessageHandler messageHandle;
LogProcess* LogProcess::GetInstance()
{
    if (nullptr == m_log) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (nullptr == m_log) {
            m_log = new LogProcess();
        }
    }
    return m_log;
}

void LogProcess::myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        break;
    case QtInfoMsg:
        break;
    case QtWarningMsg:
        break;
    case QtCriticalMsg:
        break;
    case QtFatalMsg:
        break;
    }
    if (!msg.isEmpty()) {
        // qDebug() << "recv" << msg;
        const char* file = context.file ? context.file : "";
        const char* function = context.function ? context.function : "";
        emit m_log->logData(LogMsg(context.line, type, QTime::currentTime(), file, function, msg));
    }
    messageHandle(type, context, msg); // 输出到控制台
}

LogProcess::LogProcess(QObject* parent)
    : QObject(parent)
{
    qRegisterMetaType<QtMsgType>("QtMsgType");
    qRegisterMetaType<LogMsg>("LogMsg");
    messageHandle = qInstallMessageHandler(LogProcess::myMessageOutput);
}

LogProcess::~LogProcess()
{
    qInstallMessageHandler(0); // 还原
}
