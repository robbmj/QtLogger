QtLogger
========

A simple logger for Qt

To use this logger add it as an 
<a href="http://qt-project.org/doc/qtcreator-2.6/creator-project-qmake-libraries.html">
external library to your Qt project
</a>

Sample usages:

    #include <logger.h>
    // The class the message is being printed from
    #define __CLASS__ "Main"
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

    LOG_FATAL(bool logIf = true)     // the logger will not stop execution
    LOG_CRITICAL(bool logIf = true)
    LOG_WARNING(bool logIf = true)
    LOG_INFO(bool logIf = true)
    LOG_DEBUG(bool logIf = true)
    LOG_VERBOSE(bool logIf = true)

Each of the LOG_* calls optionaly takes exactly one bool. If the value is false the log message will not be printed.

Also you may configure logger to print to a QIODevice, this can be configured in the following way

    LoggerCfg *cfg = new LoggerCfg(new QFile("log.txt"));
    Logger::init(cfg);
    // run the application
    Logger::destroy();
    
logger takes responsibility for managing the memory allocated to the LoggerCfg object. Other configuration options include:

    // If false logger will not write to stdout
    bool logToConsole = true,
    // If set to false will only flush log messages when the buffer reaches its capasity
    bool flushImmediatly = true, 
    // The default log lvl. if level is set to Debug all Verbose messages will be ignored
    logger::Level logLvl = logger::Verbose,
    // If instantiated logger will write to the QIODevice
    QIODevice *logDest = NULL

Log lvl options:
    Fatal, Critical, Warning, Info, Debug, Verbose

In the example below logger will not print to stdout, it will not flush the buffer on each call, Verbose and Debug messages will be ignored and it will write to a file called log.txt.

    LoggerCfg *cfg = new LoggerCfg(false, false, Info, new QFile("log.txt"));
    Logger::init(cfg);
    // run the application
    Logger::destroy();
    
logger behaves in the same way as qDebug and is as easy to use.

    LOG_DEBUG() << "QPoint:" << qPoint << true << 1.1 << 'c';
    DEBUG {2014-01-09T08:20:09} [ClearBack::ClearBack]#25: QPoint: QPoint(500,112) true 1.1 c
    
Except now you get the log level that printed the message, the timestamp of when the message was printed, the class name, the method name and the line number from where the message was printed. 
