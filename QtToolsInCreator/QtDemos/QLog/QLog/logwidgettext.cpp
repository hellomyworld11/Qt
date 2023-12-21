#include "logwidgettext.h"
#include "ui_logwidgettext.h"
#include <QDebug>

LogWidgettext::LogWidgettext(QWidget* parent)
    : LogWidgetBase(parent)
    , ui(new Ui::LogWidgettext)
{
    ui->setupUi(this);

    ui->textEdit->moveCursor(QTextCursor::End);
    m_logStyle = "<span style='background:%1;'>%2 %3</span>"; // 日志的格式

    connect(ui->btn_clear, &QPushButton::clicked,
        this, &LogWidgettext::on_btn_clear_clicked);
}

LogWidgettext::~LogWidgettext()
{
    delete ui;
}

void LogWidgettext::on_btn_clear_clicked()
{
    ui->textEdit->clear();
}

void LogWidgettext::on_logData(LogMsg msg)
{
    Q_UNUSED(msg.file)
    Q_UNUSED(msg.function)
    Q_UNUSED(msg.line)

    QString strColor = "transparent";
    switch (msg.type) {
    case QtDebugMsg:
        if (!ui->cb_debug->isChecked())
            return;
        break;
    case QtInfoMsg:
        if (!ui->cb_info->isChecked())
            return;
        strColor = "rgb(134, 210, 250)";
        break;
    case QtWarningMsg:
        if (!ui->cb_warn->isChecked())
            return;
        strColor = "rgb(252, 175, 62)";
        break;
    case QtCriticalMsg:
        if (!ui->cb_critical->isChecked())
            return;
        strColor = "rgb(250, 48, 48)";
        break;
    case QtFatalMsg:
        break;
    }

    QString strLog = m_logStyle.arg(strColor).arg(msg.time.toString("HH:mm:ss")).arg(msg.msg);
    //qDebug() << "own :" << strLog;
    ui->textEdit->append(strLog);
}

void LogWidgettext::setMaxMumBlockCount(int maximum)
{
    ui->textEdit->document()->setMaximumBlockCount(maximum);
}
