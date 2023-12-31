﻿#include "widget.h"
#include "logsavetxt.h"
#include "ui_widget.h"
#include <QComboBox>
#include <QDebug>
#include <QStringList>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("日志输出测试");

    QStringList types;
    types << "Log"
          << "Csv";

    ui->combox_FileType->addItems(types);
    ui->combox_FileType->setCurrentIndex(0);

    void (QComboBox::*fun)(int) = static_cast<void (QComboBox::*)(int)>(&QComboBox::activated);
    connect(ui->combox_FileType, fun,
        this, &Widget::on_combo_activate);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout,
        this, &Widget::on_timer);
    m_timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_timer()
{
    qDebug() << "debug信息";
    qInfo() << "Info信息";
    qWarning() << "Warning信息";
    qCritical() << "critical信息";
}

void Widget::on_combo_activate(int index)
{
    // qDebug() << "index: " << index;
    ((LogSaveTxt*)LogSaveTxt::getInstance())->setFileType((LogSaveTxt::FileType)index);
}
