#ifndef LOGGER_H
#define LOGGER_H

#include "logger_global.h"

#include <QtCore>


namespace logger
{

#define TOKEN_TO_STRING(TOK) # TOK
#define STRINGIZE_TOKEN(TOK) TOKEN_TO_STRING(TOK)

#define MACRO_ROUTER(x, A, FUNC, ...)  FUNC


#define LOG_FATAL_0()         Logger(__CLASS__, __func__, __LINE__, logger::Logger::Fatal).log()
#define LOG_FATAL_1(logIf)    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Fatal, logIf).log()
#define LOG_FATAL(...)                   \
    MACRO_ROUTER(,##__VA_ARGS__, LOG_FATAL_1(__VA_ARGS__), LOG_FATAL_0(__VA_ARGS__))


#define LOG_CRITICAL_0()         Logger(__CLASS__, __func__, __LINE__, logger::Logger::Critical).log()
#define LOG_CRITICAL_1(logIf)    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Critical, logIf).log()
#define LOG_CRITICAL(...)                   \
    MACRO_ROUTER(,##__VA_ARGS__, LOG_CRITICAL_1(__VA_ARGS__), LOG_CRITICAL_0(__VA_ARGS__))


#define LOG_WARNING_0()         Logger(__CLASS__, __func__, __LINE__, logger::Logger::Warning).log()
#define LOG_WARNING_1(logIf)    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Warning, logIf).log()
#define LOG_WARNING(...)                   \
    MACRO_ROUTER(,##__VA_ARGS__, LOG_WARNING_1(__VA_ARGS__), LOG_WARNING_0(__VA_ARGS__))


#define LOG_INFO_0()         Logger(__CLASS__, __func__, __LINE__, logger::Logger::Info).log()
#define LOG_INFO_1(logIf)    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Info, logIf).log()
#define LOG_INFO(...)                   \
    MACRO_ROUTER(,##__VA_ARGS__, LOG_INFO_1(__VA_ARGS__), LOG_INFO_0(__VA_ARGS__))


#define LOG_DEBUG_0()         Logger(__CLASS__, __func__, __LINE__, logger::Logger::Debug).log()
#define LOG_DEBUG_1(logIf)    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Debug, logIf).log()
#define LOG_DEBUG(...)                   \
    MACRO_ROUTER(,##__VA_ARGS__, LOG_DEBUG_1(__VA_ARGS__), LOG_DEBUG_0(__VA_ARGS__))


#define LOG_VERBOSE_0()         Logger(__CLASS__, __func__, __LINE__, logger::Logger::Verbose).log()
#define LOG_VERBOSE_1(logIf)    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Verbose, logIf).log()
#define LOG_VERBOSE(...)                   \
    MACRO_ROUTER(,##__VA_ARGS__, LOG_VERBOSE_1(__VA_ARGS__), LOG_VERBOSE_0(__VA_ARGS__))


class LOGGERSHARED_EXPORT Logger
{
    
public:

    enum Level {
        Fatal, Critical, Warning, Info, Debug, Verbose
    };

    Logger(std::string clazz, std::string func, int line, Level lvl, bool logif = true);
    QDebug log();

    static void setLogLevel(Level level = Verbose)
    {
        level = level;
    }

    static void myinit()
    {
        setLogLevel();
        qInstallMessageHandler(msgHandler);
    }

    static void msgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
private:
    QString msg;
    QString dummyStr;
    bool logif;

    static Level level;
    static inline QString lvlName(Level level);
    static inline bool doLog(Level level);
};

//Logger::init();

}

#endif // LOGGER_H
