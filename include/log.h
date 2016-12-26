#ifndef LOG_H
#define LOG_H


extern int showDebugMsg;

#define ERROR(fmt, arg...)  fprintf(stdout, "ERROR: " fmt "\n", ##arg);

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