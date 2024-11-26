#ifndef _glog_h
#define _glog_h

#include <stdio.h>

#define GLOG_MAX_OUT_STREAMS 16

struct glog__logger {
	FILE* out_streams[GLOG_MAX_OUT_STREAMS];

	const char* prefix;
	const char* format;
};

typedef void (*glog__logging_level_handler_t)(void);

struct glog__logging_level {
	const char* name;
	int level;

	glog__logging_level_handler_t handler;
};

extern int glog__min_log_level;
void glog__init(void);

void glog__logger_from_prefix(struct glog__logger* logger, const char* prefix);

extern glog__logging_level glog__chaos_level;
extern glog__logging_level glog__trace_level;
extern glog__logging_level glog__debug_level;
extern glog__logging_level glog__info_level;
extern glog__logging_level glog__warn_level;
extern glog__logging_level glog__error_level;
extern glog__logging_level glog__die_level;
extern glog__logging_level glog__unreachable_level;

void glog__putf(const struct glog__logger* logger, const struct glog__logging_level* level,
	const char* fmt, ...);

#ifndef RELEASE
#	define glog__chaos(logger, fmt, ...) glog__putf(logger, glog__chaos_level, fmt, __VA_ARGS__)
#	define glog__trace(logger, fmt, ...) glog__putf(logger, glog__trace_level, fmt, __VA_ARGS__)
#	define glog__debug(logger, fmt, ...) glog__putf(logger, glog__debug_level, fmt, __VA_ARGS__)
#	define glog__unreachable(logger, fmt, ...) glog__putf(logger, glog__unreachable_level, fmt, __VA_ARGS__)
#endif

#define glog__info(logger, fmt, ...) glog__putf(logger, glog__info_level, fmt, __VA_ARGS__)
#define glog__warn(logger, fmt, ...) glog__putf(logger, glog__warn_level, fmt, __VA_ARGS__)
#define glog__error(logger, fmt, ...) glog__putf(logger, glog__error_level, fmt, __VA_ARGS__)
#define glog__die(logger, fmt, ...) glog__putf(logger, glog__die_level, fmt, __VA_ARGS__)

#endif
