#ifndef LOGWIDGETBASE_H
#define LOGWIDGETBASE_H

#include "define.h"
#include <QWidget>
#include <qdatetime.h>

class LogWidgetBase : public QWidget {
    Q_OBJECT
public:
    explicit LogWidgetBase(QWidget* parent = nullptr);

protected:
    virtual void on_logData(LogMsg msg) = 0;
    /**
     * @brief            设置日志最多显示行数
     * @param maximum
     */
    virtual void setMaxMumBlockCount(int maximum) = 0;
signals:
};

#endif // LOGWIDGETBASE_H
