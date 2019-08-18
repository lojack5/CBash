#pragma once
#include <fstream>
#include <iostream>
#include <vector>

struct Log {
	std::ofstream* logFile = NULL;
	bool isHigherLevel = false;

	template <typename T>
	Log& operator<<(T const& obj) {
		if (logFile != NULL)
			(*logFile) << obj;

		if (isHigherLevel)
			std::cout << obj;

		return *this;
	}

	Log& operator<<(std::ostream& (*pf)(std::ostream&)) {
		if (logFile != NULL)
			(*logFile) << pf;

		if (isHigherLevel)
			std::cout << pf;

		return *this;
	}
};

class Logger {
private:
	int logLevel = 2; // Debug and above
	std::ofstream logFile;
	std::vector<Log> loggers;
	Logger() {}
public:
	~Logger();
	Logger(Logger& copy) {}
	static Logger& getInstance();
	void init(int argc, char * argv[]);
	Log* getLogger(int level);
};