#include "logsavebase.h"
#include "logprocess.h"

#include <QDir>
#include <qmutex.h>

LogSaveBase* LogSaveBase::m_logSave = nullptr;
LogSaveBase::LogSaveBase(QObject* parent)
    : QObject(parent)
{
    QDir dir;
    if (!dir.exists(LOG_PATH)) {
        dir.mkpath(LOG_PATH);
    }
    connect(LogProcess::GetInstance(), &LogProcess::logData, this, &LogSaveBase::on_logData, Qt::QueuedConnection);
}

LogSaveBase::~LogSaveBase()
{
    disconnect(LogProcess::GetInstance(), &LogProcess::logData, this, &LogSaveBase::on_logData);
}
