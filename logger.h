#ifndef LOGGER_H
#define LOGGER_H

#include "logger_global.h"

#include <QtCore>

namespace logger
{

#define TOKEN_TO_STRING(TOK) # TOK
#define STRINGIZE_TOKEN(TOK) TOKEN_TO_STRING(TOK)

#define LOG_FATAL(...)                                                              \
    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Fatal,                    \
    ((QString(STRINGIZE_TOKEN(__VA_ARGS__)).isEmpty()) ? true : __VA_ARGS__)).log()


#define LOG_CRITICAL(...)                                                           \
    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Critical,                 \
    ((QString(STRINGIZE_TOKEN(__VA_ARGS__)).isEmpty()) ? true : __VA_ARGS__)).log()


#define LOG_WARNING(...)                                                            \
    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Warning,                  \
    ((QString(STRINGIZE_TOKEN(__VA_ARGS__)).isEmpty()) ? true : __VA_ARGS__)).log()


#define LOG_INFO(...)                                                               \
    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Info,                     \
    ((QString(STRINGIZE_TOKEN(__VA_ARGS__)).isEmpty()) ? true : __VA_ARGS__)).log()


#define LOG_DEBUG(...)                                                              \
    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Debug,                    \
    ((QString(STRINGIZE_TOKEN(__VA_ARGS__)).isEmpty()) ? true : __VA_ARGS__)).log()


#define LOG_VERBOSE(...)                                                            \
    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Verbose,                  \
    ((QString(STRINGIZE_TOKEN(__VA_ARGS__)).isEmpty()) ? true : __VA_ARGS__)).log()


class LOGGERSHARED_EXPORT Logger
{
    
public:

    enum Level {
        Fatal, Critical, Warning, Info, Debug, Verbose
    };

    Logger(std::string clazz, std::string func, int line, Level lvl, bool logif);
    QDebug log();

    static void setLogLevel(Level level = Verbose)
    {
        level = level;
    }

    static void init()
    {
        setLogLevel();
    }

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
