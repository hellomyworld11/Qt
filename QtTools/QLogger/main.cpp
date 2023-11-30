#include <QtWidgets/QApplication>
#include "Logger.h"
#include <QDebug>
#include <QTimer>
#include <iostream>
#include <chrono>
#include <vector>
#include <atomic>
#include <sstream>
#include <thread>
using namespace std;
const int N = 7;

//ԭ�Ӽ���������Ҫ����ͨ��int�����߳�����²�׼ȷ��
static atomic_int gCount(0);

static QString currentThreadId()
{
	std::stringstream ss;
	ss << this_thread::get_id();
	return QString::fromStdString(ss.str());
}
//���log�ĺ���������ӡһ����Ϣ
static void showSomeLogger()
{
	//���ļ�����ı�����utf-8��ǰ���£��������ַ�ʽ������ֱ��������ġ�
	//u8��c++11��׼֧�ֵ��ַ���������д�������Բο�https://zh.cppreference.com/w/cpp/language/string_literal
	//QStringLiteral��Qt���еĺ꣬�����ڱ����������ַ���������
	//QString::fromLocal8Bit���������й����У���̬���������ַ�����
	for (int i = 0; i < 1000; ++i)
	{
		gCount++;
		int count = gCount;
		LOG_DEBUG << currentThreadId() << u8"ɽ��ľ��ľ��֦�����þ������֪��";
		LOG_DEBUG << currentThreadId() << QStringLiteral("�ƺ�Զ�ϰ��Ƽ䣬һƬ�³�����ɽ��");
		LOG_DEBUG << currentThreadId() << QString::fromLocal8Bit("������ֻ�������������籯���ȡ�");
		LOG_INFO << currentThreadId() << u8"�������Ӱ��춹�������˼֪��֪��";
		LOG_WARN << currentThreadId() << u8"����ɴ���׷�䣬ֻ�ǵ�ʱ���Ȼ��";
		LOG_CRIT << currentThreadId() << u8"���ص����鷢���ˣ���Ʊ����!" << count;
		qApp->processEvents();  //�ó��򱣳���Ӧ
	}
}

static void logThread()
{
	vector<std::thread> threads;

	//����N���߳�
	for (unsigned long long i = 0; i < N; ++i) {
		threads.emplace_back(thread(showSomeLogger));
	}

	//join,���߳̽�����
	for (unsigned long long i = 0; i < N; ++i)
	{
		threads[i].join();
	}
	LOG_INFO << currentThreadId() << u8"���Խ���,�ܹ�������� " << gCount;

}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
	Logger::initLog();

	LOG_INFO << currentThreadId() << u8"��ʼ������־ϵͳ";

	//�ӳٴ��� logger
	//����һ��
	QTimer::singleShot(2000, [&]() {
		std::thread logger(logThread);
 		logger.detach();
	});

    return a.exec();
}
