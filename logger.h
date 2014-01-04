#ifndef LOGGER_H
#define LOGGER_H

#include "logger_global.h"

#include <QDebug>

namespace logger
{

//#define LOG_FATAL(logif) Logger(__CLASS__, __func__, __LINE__, LOG_FATAL, logif).log()


//#define LOG_CRITICAL(logif) Logger(__CLASS__, __func__, __LINE__, LOG_CRITICAL, logif).log()
//#define LOG_WARNING(logif) Logger(__CLASS__, __func__, __LINE__, LOG_WARNING, logif).log()


#define LOG_INFO(...)                                                                                                       \
    bool _$_b_$_[] = { __VA_ARGS__ };                                                                                       \
    Logger(__CLASS__, __func__, __LINE__, logger::Logger::Info, ((sizeof _$_b_$_ == 0) ? true : _$_b_$_[0])).log()


//#define LOG_DEBUG(logif) Logger(__CLASS__, __func__, __LINE__, LOG_DEBUG, logif).log()
//#define LOG_VERBOSE(logif) Logger(__CLASS__, __func__, __LINE__, LOG_VERBOSE, logif).log()


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
    bool logif;
    static Level level;

    QString lvlName(Level level) const;
    inline bool doLog(Level level) const;
};

//Logger::init();

}

#endif // LOGGER_H
