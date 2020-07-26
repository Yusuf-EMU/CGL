#include <stdlib.h>
#include <string.h>
#include "include/logger.h"

logger_T* init_logger() {
    logger_T* LOGGER = calloc(1, sizeof(struct LOGGER));
}

void log_base(const char* prefix, const char* str, int mode, int target) {
    switch(mode) {
        case VERBOSE:
            fputs(prefix, target == STDOUT ? stdout : stderr);
            fputs(str, target == STDOUT ? stdout : stderr);
            fputs("\n", target == STDOUT ? stdout : stderr);
            break;
        case SILENT:
            return;
            break;
    }
}

void performance(logger_T* LOGGER, const char* str) {
    log_base("PERF: ", str, LOGGER->performance_mode, STDOUT);
}

void debug(logger_T* LOGGER, const char* str) {
    log_base("DEBG: ", str, LOGGER->debug_mode, STDOUT);
}

void info(logger_T* LOGGER, const char* str) {
    log_base("INFO: ", str, LOGGER->info_mode, STDOUT);
}

void warning(logger_T* LOGGER, const char* str) {
    log_base("WARN: ", str, LOGGER->warning_mode, STDERR);    
}

void error(logger_T* LOGGER, const char* str) {
    log_base("EROR: ", str, LOGGER->error_mode, STDERR);    
}

void fatal(logger_T* LOGGER, const char* str) {
    log_base("FATL: ", str, LOGGER->fatal_mode, STDERR);    
    exit(-1);
}