#include "Logger.h"
#include <ctime>

Logger::~Logger() {
	if (logFile.is_open())
		logFile.close();
}

Logger& Logger::getInstance() {
	static Logger instance = Logger();
	return instance;
}

void Logger::init(int argc, char * argv[]) {
	if (logFile.is_open())
		return;

	if (argc < 4)
		return;

	std::string logFileName = argv[3];
	logFileName += "Logs_";
	std::time_t t = time(0);
	struct tm* now = localtime(&t);
	char buffer[20];
	strftime(buffer, 20, "%d.%m.%y_%H.%M.%S", now);
	logFileName += buffer;
	logFileName += ".txt";
	logFile.open(logFileName, std::ios::out | std::ios::trunc);
	if (!logFile) {
		std::cout << "Couldn't open log file\n";
		return;
	}

	if (argc > 4)
		logLevel = atoi(argv[4]);

	logFile << "Arguments: " << argv[1] << " " << argv[2] << " " << argv[3] << " " << logLevel << std::endl << std::endl;

	Log info;
	info.logFile = &logFile;
	info.isHigherLevel = (logLevel <= 0);
	loggers.push_back(info);

	Log warning;
	warning.logFile = &logFile;
	warning.isHigherLevel = (logLevel <= 1);
	loggers.push_back(warning);

	Log debug;
	debug.logFile = &logFile;
	debug.isHigherLevel = (logLevel <= 2);
	loggers.push_back(debug);

	Log error;
	error.logFile = &logFile;
	error.isHigherLevel = (logLevel <= 3);
	loggers.push_back(error);
}

Log* Logger::getLogger(int level) {
	return &loggers[level];
}