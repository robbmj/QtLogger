#include "logger.h"

#include <QBuffer>
#include <QDateTime>

#include <QtCore/QDebug>

#include <iostream>

namespace logger
{

using namespace std;

logger::Logger::Level Logger::level = Logger::Verbose;
//Logger::myinit();

Logger::Logger(string clazz, string func, int line, Level lvl, bool logif) :
    logif(logif && doLog(lvl))
{
    //qDebug() << "this->logif is:" << this->logif << "logif is:" << logif << "dolog is:" << doLog(lvl);
   if (this->logif)
   {
        QString t(QDateTime::currentDateTime().toString(Qt::ISODate));
        QString c = QString::fromStdString(clazz);
        QString f = QString::fromStdString(func);
        QString l = QString::number(line);
        QString m = lvlName(lvl);
        msg = m + " {" + t + "} [" + c + "::" + f + "]#" + l;
   }
}

void Logger::msgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(type);
    Q_UNUSED(context);
    Q_UNUSED(msg);
    std::cout << "I am here" << endl;
}

QDebug Logger::log()
{
    if (logif)
    {
        QDebug writer(QtDebugMsg);
        writer << msg;
        return writer;
    }
    else
    {
        QDebug d(&dummyStr);
        return d;
    }
}

inline QString Logger::lvlName(Level level)
{
    switch(level)
    {
        case Fatal: return QString("FATAL");
        case Critical: return QString("CRITICAL");
        case Warning: return QString("WARNING");
        case Info: return QString("INFO");
        case Debug: return QString("DEBUG");
        case Verbose: return QString("VERBOSE");
        default: return QString("DEBUG");
    }
}

inline bool Logger::doLog(Level level)
{
    return level <= Logger::level;
}


}
