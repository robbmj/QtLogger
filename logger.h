#ifndef LOGGER_H
#define LOGGER_H

#include "logger_global.h"

#include <QtCore>
#include <QTextStream>
#include <QIODevice>

namespace logger
{

#define MACRO_ROUTER(x, A, FUNC, ...)  FUNC


#define PRIVATE_LOG_FATAL_0()           (logger::Logger(__CLASS__, __func__, __LINE__, logger::Fatal, true)).log()
#define PRIVATE_LOG_FATAL_1(logIf)      (logger::Logger(__CLASS__, __func__, __LINE__, logger::Fatal, logIf)).log()
#define LOG_FATAL(...)                  MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_FATAL_1(__VA_ARGS__), PRIVATE_LOG_FATAL_0(__VA_ARGS__))


#define PRIVATE_LOG_CRITICAL_0()        (logger::Logger(__CLASS__, __func__, __LINE__, logger::Critical, true)).log()
#define PRIVATE_LOG_CRITICAL_1(logIf)   (logger::Logger(__CLASS__, __func__, __LINE__, logger::Critical, logIf)).log()
#define LOG_CRITICAL(...)               MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_CRITICAL_1(__VA_ARGS__), PRIVATE_LOG_CRITICAL_0(__VA_ARGS__))


#define PRIVATE_LOG_WARNING_0()         (logger::Logger(__CLASS__, __func__, __LINE__, logger::Warning, true)).log()
#define PRIVATE_LOG_WARNING_1(logIf)    (logger::Logger(__CLASS__, __func__, __LINE__, logger::Warning, logIf)).log()
#define LOG_WARNING(...)                MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_WARNING_1(__VA_ARGS__), PRIVATE_LOG_WARNING_0(__VA_ARGS__))


#define PRIVATE_LOG_INFO_0()            (logger::Logger(__CLASS__, __func__, __LINE__, logger::Info, true)).log()
#define PRIVATE_LOG_INFO_1(logIf)       (logger::Logger(__CLASS__, __func__, __LINE__, logger::Info, logIf)).log()
#define LOG_INFO(...)                   MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_INFO_1(__VA_ARGS__), PRIVATE_LOG_INFO_0(__VA_ARGS__))


#define PRIVATE_LOG_DEBUG_0()           (logger::Logger(__CLASS__, __func__, __LINE__, logger::Debug, true)).log()
#define PRIVATE_LOG_DEBUG_1(logIf)      (logger::Logger(__CLASS__, __func__, __LINE__, logger::Debug, logIf)).log()
#define LOG_DEBUG(...)                  MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_DEBUG_1(__VA_ARGS__), PRIVATE_LOG_DEBUG_0(__VA_ARGS__))


#define PRIVATE_LOG_VERBOSE_0()         (logger::Logger(__CLASS__, __func__, __LINE__, logger::Verbose, true)).log()
#define PRIVATE_LOG_VERBOSE_1(logIf)    (logger::Logger(__CLASS__, __func__, __LINE__, logger::Verbose, logIf)).log()
#define LOG_VERBOSE(...)                MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_VERBOSE_1(__VA_ARGS__), PRIVATE_LOG_VERBOSE_0(__VA_ARGS__))

enum Level {
    Fatal, Critical, Warning, Info, Debug, Verbose
};

typedef struct LoggerCfg
{
    bool logToConsole;
    bool flushImmediatly;
    logger::Level logLvl;
    QIODevice *logDest;
    QTextStream *logWriter;

    LoggerCfg(bool logToConsole, bool flushImmediatly, logger::Level logLvl, QIODevice *logDest) :
        logToConsole(logToConsole),
        flushImmediatly(flushImmediatly),
        logLvl(logLvl),
        logDest(logDest)
    {
        if (logDest->open(QIODevice::WriteOnly | QIODevice::Append))
        {
            logWriter = new QTextStream(logDest);
        }
        else
        {
            throw "Can't open log device";
        }
    }

    LoggerCfg() :
        logToConsole(true),
        flushImmediatly(true),
        logLvl(logger::Verbose),
        logDest(NULL),
        logWriter(NULL)
    {

    }

    ~LoggerCfg()
    {
        if (logWriter != NULL)
        {
            delete logWriter;
            logWriter = NULL;
        }
        if (logDest != NULL)
        {
            delete logDest;
            logDest = NULL;
        }
    }
} LoggerCfg;

class LOGGERSHARED_EXPORT Logger
{
    
public:

    Logger(const std::string &clazz, const std::string &func, int line, Level lvl, bool logif);
    QDebug log();

    static void init(LoggerCfg *loggerCgf = NULL);
    static void destroy();
    static void msgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    QString msg;
    QString dummyStr;
    bool logif;

    static QTextStream cout;
    static LoggerCfg *cfg;
    static inline QString lvlName(Level level);
    static inline bool doLog(Level level);

};

}

#endif // LOGGER_H
