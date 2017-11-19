#ifndef LOG_H
#define LOG_H

#include <ostream>
using namespace std;
extern int showDebugMsg;

#define ERROR(fmt, arg...)  fprintf(stderr, "ERROR: " fmt "\n", ##arg);

#define DEBUG(level, fmt, arg...)                       \
    { if(showDebugMsg>=level) {                         \
        fprintf(stdout, fmt"", ##arg);       \
    } }
        // fprintf(stdout, "DEBUG: "fmt"", ##arg);       \


#define WARN(level, fmt, arg...)                       \
    { if(showDebugMsg>=level) {                         \
        fprintf(stdout, fmt" WARN:", ##arg);       \
    } }

enum Level {
	debug1, debug2, debug3, error, warning, info
};

struct Logger {
	std::ostream* stream;  // set this in a constructor to point
	                        // either to a file or console stream
	Level debug_level;
	Level current_level;
	public:
	Logger( std::ostream* dest, Level level ) : stream( dest) , debug_level(level) {}
	Logger& operator<<(const std::string& msg)
	{
		*stream << msg; // also print the level etc.
		return *this;
	}
	
	friend Logger& log(Logger& logger, Level n)
	{
		logger.current_level = n;
		return logger;
	}
};

#endif
