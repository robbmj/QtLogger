#include "logger.h"

#include <QBuffer>
#include <QDateTime>
#include <QtCore/QNoDebug>

namespace logger
{

using namespace std;

logger::Logger::Level Logger::level = Logger::Verbose;

Logger::Logger(string clazz, string func, int line, Level lvl, bool logif) :
    logif(logif || doLog(lvl))
{
   if (logif)
   {
        QString t(QDateTime::currentDateTime().toString(Qt::ISODate));
        QString c = QString::fromStdString(clazz);
        QString f = QString::fromStdString(func);
        QString l = QString::number(line);
        QString m = lvlName(lvl);
        msg = m + " {" + t + "} [" + c + "::" + f + "]#" + l;
   }
}

QDebug Logger::log()
{
    QDebug d(QtDebugMsg);
    d << msg;
    return d;
}

inline QString Logger::lvlName(Level level) const
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

inline bool Logger::doLog(Level level) const
{
    return Logger::level <= level;
}

}
