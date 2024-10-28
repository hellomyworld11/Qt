﻿#include "textgroup.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <WelcomeGroup>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    WELCOMEGROUP_INITIALIZA
    TEXTGROUP_INITIALIZA

    engine.load(url);

    return app.exec();
}
