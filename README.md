QtLogger
========

A simple logger for Qt

To use this logger add it as an external library to your Qt project. 

Sample usages:

    #include <logger.h>
    #define __CLASS__ "ClearBack"
    using namespace logger;

    int main(int argc, char *argv[])
    {
        Logger::init();
    
        LOG_VERBOSE() << "STARTING EXECUTION";
    
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        int r = a.exec();
        Logger::destroy(); // after calling destroy() no more log messages will be printed
        return r;
    }

The log level options are:

    LOG_FATEL(bool logIf = true)     // the logger will not stop execution
    LOG_CRITICAL(bool logIf = true)
    LOG_WARNING(bool logIf = true)
    LOG_INFO(bool logIf = true)
    LOG_DEBUG(bool logIf = true)
    LOG_VERBOSE(bool logIf = true)

Each of the LOG_* calls optionaly takes exactly one bool. If the value is false the log message will not be printed.

Also you may configure logger to print to an QIODevice, this can be configured in the following way

    LoggerCfg *cfg = new LoggerCfg(new QFile("log.txt"));
    Logger::init(cfg);
    // run the application
    Logger::destroy();
    
logger takes responsibility for managing the memory allocated to the LoggerCfg object. Other configuration options include:

    // If false logger will not write to stdout. Defaults to true
    bool logToConsole,
    // If set to false will only flush log messages when the buffer reaches its capasity. Defaults to true
    bool flushImmediatly, 
    // The default log lvl. if level is set to Debug all Verbose messages will be ignored. Defaults to verbose
    logger::Level logLvl,
    // If instantiated logger will write to the QIODevice. Defaults to NULL
    QIODevice *logDest

Log lvl options:
    Fatel, Critical, Warning, Info, Debug, Verbose

In the example below logger will not print to stdout, it will not flush the buffer on each call, Verbose and Debug messages will be ignored and it will write to a file called log.txt.

    LoggerCfg *cfg = new LoggerCfg(false, false, Info, new QFile("log.txt"));
    Logger::init(cfg);
    // run the application
    Logger::destroy();
