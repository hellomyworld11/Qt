#ifndef WIDGETTEMP_H
#define WIDGETTEMP_H

#include <QWidget>
#include <QEvent>

class WidgetTemp : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetTemp(QWidget *parent = nullptr);

    void setToolBar(QWidget *toolBar);
private:
    void init();
    void thisEvent(QObject *watched, QEvent *event);
    void toolBarEvent(QObject *watched, QEvent *event);

#ifdef Q_OS_WIN
    bool winMouseEvent(MSG* msg,  long *result);          // 鼠标事件处理
#endif

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
signals:
    /**
     * @brief               窗口最大化、最小化、还原时发出
     * @param windowStates
     */
    void windowStateChanged(Qt::WindowStates windowStates);

private:
    QWidget* m_toolbar = nullptr;
};

#endif // WIDGETTEMP_H
