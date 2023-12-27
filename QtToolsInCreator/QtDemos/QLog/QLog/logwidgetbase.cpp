#include "logwidgetbase.h"
#include "logprocess.h"
#include "logsavetxt.h"

LogWidgetBase::LogWidgetBase(QWidget* parent)
    : QWidget(parent)
{
    LogSaveTxt::initLog(); // 初始化日志保存功能
    connect(LogProcess::GetInstance(), &LogProcess::logData, this, &LogWidgetBase::on_logData, Qt::QueuedConnection);
}
