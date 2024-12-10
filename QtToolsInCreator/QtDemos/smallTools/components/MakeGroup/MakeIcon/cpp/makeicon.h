#ifndef MAKEICON_H
#define MAKEICON_H
#include <JQToolsLibrary>
#include <QImage>

#define MAKEICON_INITIALIZA                                                    \
    {                                                                          \
        qmlRegisterType<MakeIcon::Manage>("MakeIcon", 1, 0, "MakeIconManage"); \
    }

namespace MakeIcon {

class Manage : public AbstractTool {
    Q_OBJECT
    Q_DISABLE_COPY(Manage)
public:
    Manage();

    ~Manage() = default;
public slots:
    inline QString targetSavePath() const { return targetSavePath_; }

    inline QString sourceIconFilePath() const { return sourceIconFilePath_; }

    QString chooseSourceIconFilePath();

signals:
    void targetSavePathChanged();

    void sourceIconFilePathChanged();

private:
    QString targetSavePath_;

    QString sourceIconFilePath_;

    QImage sourceIconImage_;
};
}

#endif // MAKEICON_H
