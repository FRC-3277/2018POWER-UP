#include <LumberJack.h>
INITIALIZE_EASYLOGGINGPP

LumberJack::LumberJack() {
	defaultConf.setToDefault();
	defaultLogger = el::Loggers::getLogger("default");
}

LumberJack::~LumberJack() {
}

void LumberJack::SetLoggingLevel(el::Level argSeverityLevel)
{
	severityLevelChosen = argSeverityLevel;
}

void LumberJack::SetConfig()
{
	// Values are always std::string
	defaultConf.set(severityLevelChosen, el::ConfigurationType::Format, "%datetime %level %msg");
	// default logger uses default configurations
	el::Loggers::reconfigureLogger("default", defaultConf);
}

void LumberJack::iLog(char* msg)
{
	LOG_IF(isInfoLoggingEnabled, INFO) << msg;
	//defaultLogger->info("%v\n", msg);
}

void LumberJack::dLog(char* msg)
{
	LOG_IF(isDebugLoggingEnabled, DEBUG) << msg;
	//defaultLogger->debug("%v\n", msg);
}

void LumberJack::eLog(char* msg)
{
	LOG_IF(isErrorLoggingEnabled, ERROR) << msg;
	//defaultLogger->error("%v\n", msg);
}

void LumberJack::wLog(char* msg)
{
	LOG_IF(isWarningLoggingEnabled, WARNING) << msg;
	//defaultLogger->warn("%v\n", msg);
}

void LumberJack::fLog(char* msg)
{
	LOG_IF(isFatalLoggingEnabled, FATAL) << msg;
	//defaultLogger->fatal("%v\n", msg);
}

void LumberJack::tLog(char* msg)
{
	LOG_IF(isTraceLoggingEnabled, TRACE) << msg;
	//defaultLogger->trace("%v\n", msg);
}

void LumberJack::iLog(const string& msg)
{
	LOG_IF(isInfoLoggingEnabled, INFO) << msg;
	//defaultLogger->info("%v\n", msg);
}

void LumberJack::dLog(const string& msg)
{
	LOG_IF(isDebugLoggingEnabled, DEBUG) << msg;
	//defaultLogger->debug("%v\n", msg);
}

void LumberJack::eLog(const string& msg)
{
	LOG_IF(isErrorLoggingEnabled, ERROR) << msg;
	//defaultLogger->error("%v\n", msg);
}

void LumberJack::wLog(const string& msg)
{
	LOG_IF(isWarningLoggingEnabled, WARNING) << msg;
	//defaultLogger->warn("%v\n", msg);
}

void LumberJack::fLog(const string& msg)
{
	LOG_IF(isFatalLoggingEnabled, FATAL) << msg;
	//defaultLogger->fatal("%v\n", msg);
}

void LumberJack::tLog(const string& msg)
{
	LOG_IF(isTraceLoggingEnabled, TRACE) << msg;
	//defaultLogger->trace("%v\n", msg);
}

/**
 * The log method puts "data"... information of interest from the subsystem
 * to the SmartDashboard. Useful in dashLog() methods.
 */
void LumberJack::dashLogData(llvm::StringRef key, Sendable* data)
{
	SmartDashboard::PutData(key, data);
}

/**
 * The log method puts Numerical information of interest from the subsystem
 * to the SmartDashboard. Useful in dashLog() methods.
 */
void LumberJack::dashLogNumber(llvm::StringRef key, double value)
{
	SmartDashboard::PutNumber(key, value);
}

/**
 * The log method puts String information of interest from the subsystem to
 * the SmartDashboard. Useful in dashLog() methods.
 */
void LumberJack::dashLogString(llvm::StringRef key, llvm::StringRef message)
{
	SmartDashboard::PutString(key, message);
}
