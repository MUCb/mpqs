#ifndef LOG_H
#define LOG_H

#include <ostream>
using namespace std;
extern int showDebugMsg;

#define LOG(level) if(showDebugMsg >= level)

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

#endif
