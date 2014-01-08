#include "logger.h"

#include <QBuffer>
#include <QDateTime>

#include <QtCore/QDebug>

#include <iostream>

namespace logger
{

using namespace std;

logger::LoggerCfg *Logger::cfg = new LoggerCfg();
QTextStream Logger::cout(stdout, QIODevice::WriteOnly);

Logger::Logger(const string &clazz, const string &func, int line, Level lvl, bool logif) :
    logif(logif && doLog(lvl))
{
   if (this->logif)
   {
        //QString t(QDateTime::currentDateTime().toString(Qt::ISODate));
        //QString c = QString::fromStdString(clazz);
        //QString f = QString::fromStdString(func);
        //QString l = QString::number(line);
        //QString m = lvlName(lvl);

       // the log level name
       msg = lvlName(lvl) +

               // the current date time
               " {" + QDateTime::currentDateTime().toString(Qt::ISODate) + "}" +

               // class name
               "[" + QString::fromStdString(clazz) +

               // the function name
               "::" + QString::fromStdString(func) + "]#" +

               // the line number
               QString::number(line);
   }
}

void Logger::msgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(type);
    Q_UNUSED(context);


        if (cfg->logToConsole)
        {
            cout << msg << "\n";
            if (cfg->flushImmediatly)
            {
                cout.flush();
            }
        }

        if (cfg->logWriter != NULL && cfg->logDest != NULL)
        {
            *cfg->logWriter << msg << "\n";
        }

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
        QDebug writer(&dummyStr);
        writer << msg;
        return writer;
    }
}

inline QString Logger::lvlName(Level level)
{
    switch(level)
    {
        case Fatal: return QString("***FATAL***");
        case Critical: return QString("**CRITICAL**");
        case Warning: return QString("*WARNING*");
        case Info: return QString("INFO");
        case Debug: return QString("DEBUG");
        case Verbose: return QString("VERBOSE");
        default: return QString("DEBUG");
    }
}

inline bool Logger::doLog(Level level)
{
    return level <= cfg->logLvl;
}

void Logger::init(LoggerCfg *loggerCgf)
{
    if (loggerCgf != NULL)
    {
        destroy();
        Logger::cfg = loggerCgf;
    }

    qInstallMessageHandler(msgHandler);
}

void Logger::destroy()
{
    if (Logger::cfg != NULL)
    {
        delete Logger::cfg;
        Logger::cfg = NULL;
    }
}

}
