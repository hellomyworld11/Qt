#ifndef LOGSAVETXT_H
#define LOGSAVETXT_H

#include "logconfig.h"
#include "logsavebase.h"
#include <QFile>
#include <QTextStream>

class LogSaveTxt : public LogSaveBase {
public:
    Q_OBJECT

    LogSaveTxt(QObject* parent = nullptr);
};

#endif // LOGSAVETXT_H
