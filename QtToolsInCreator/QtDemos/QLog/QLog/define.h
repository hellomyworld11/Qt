#ifndef DEFINE_H
#define DEFINE_H
#include <QString>
#include <QTime>

#define LOG_PATH "./Log/"

#include <QMetaType>
/**
     * @brief           日志信息
     * @param type      日志级别
     * @param time      日志时间
     * @param file      日志来源文件
     * @param function  日志来源函数
     * @param line      日志来源行
     * @param msg       日志信息
     */
typedef struct LogMsg {
    LogMsg() {}
    LogMsg(int tline,
        QtMsgType ttype,
        QTime ttime,
        QString tfile,
        QString tfun,
        QString tmsg)
        : line(tline)
        , time(ttime)
        , file(tfile)
        , function(tfun)
        , msg(tmsg)
        , type(ttype)

    {
    }
    int line;
    QtMsgType type;
    QTime time;
    QString file;
    QString function;
    QString msg;
};

//Q_DECLARE_METATYPE(LogMsg);

#endif // DEFINE_H
