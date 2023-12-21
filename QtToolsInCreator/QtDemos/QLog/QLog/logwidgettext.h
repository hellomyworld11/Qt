#ifndef LOGWIDGETTEXT_H
#define LOGWIDGETTEXT_H

#include "logwidgetbase.h"
#include <QWidget>
namespace Ui {
class LogWidgettext;
}

class LogWidgettext : public LogWidgetBase {
    Q_OBJECT

public:
    explicit LogWidgettext(QWidget* parent = nullptr);
    ~LogWidgettext();
private slots:
    void on_btn_clear_clicked();

protected:
    void on_logData(LogMsg msg) override;
    void setMaxMumBlockCount(int maximum) override;

private:
    Ui::LogWidgettext* ui;
    QString m_logStyle;
};

#endif // LOGWIDGETTEXT_H
