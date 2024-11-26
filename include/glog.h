#ifndef _glog_h
#define _glog_h

#include <stdio.h>

#define GLOG_COLOR_RESET "\033[0m"
#define GLOG_COLOR_STANDART "\033[39m"
#define GLOG_COLOR_BLACK "\033[30m"
#define GLOG_COLOR_DARK_RED "\033[31m"
#define GLOG_COLOR_DARK_GREEN "\033[32m"
#define GLOG_COLOR_DARK_YELLOW "\033[33m"
#define GLOG_COLOR_DARK_BLUE "\033[34m"
#define GLOG_COLOR_DARK_PURPURE "\033[35m"
#define GLOG_COLOR_DARK_LIGHT_BLUE "\033[36m"
#define GLOG_COLOR_LIGHT_GRAY "\033[37m"
#define GLOG_COLOR_DARK_GRAY "\033[90m"
#define GLOG_COLOR_RED "\033[91m"
#define GLOG_COLOR_GREEN "\033[92m"
#define GLOG_COLOR_ORANGE "\033[93m"
#define GLOG_COLOR_BLUE "\033[94m"
#define GLOG_COLOR_PURPURE "\033[95m"
#define GLOG_COLOR_LIGHT_BLUE "\033[96m"
#define GLOG_COLOR_WHITE "\033[97m"

#define GLOG_MAX_MSG_BUF 1024 * 32
#define GLOG_MAX_DATE_BUF 128

struct glog__logger {
	FILE** out_streams;
	size_t out_stream_count;

	const char* prefix;
	const char* format;

	int min_log_level;
};

typedef void (*glog__logging_level_handler_t)(void);

struct glog__logging_level {
	const char* name;
	int level;

	glog__logging_level_handler_t handler;
};

void glog__init(void);
void glog__logger_from_prefix(struct glog__logger* logger, const char* prefix);

extern struct glog__logging_level glog__chaos_level;
extern struct glog__logging_level glog__trace_level;
extern struct glog__logging_level glog__debug_level;
extern struct glog__logging_level glog__info_level;
extern struct glog__logging_level glog__warn_level;
extern struct glog__logging_level glog__error_level;
extern struct glog__logging_level glog__die_level;
extern struct glog__logging_level glog__unreachable_level;

void glog__putf(const struct glog__logger* logger, const struct glog__logging_level* level,
	const char* fmt, ...);

#ifndef RELEASE
#	define glog__chaos(logger, fmt) glog__putf(logger, &glog__chaos_level, fmt)
#	define glog__trace(logger, fmt) glog__putf(logger, &glog__trace_level, fmt)
#	define glog__debug(logger, fmt) glog__putf(logger, &glog__debug_level, fmt)
#	define glog__unreachable(logger, fmt) glog__putf(logger, &glog__unreachable_level, fmt)

#	define glog__chaosf(logger, fmt, ...) glog__putf(logger, &glog__chaos_level, fmt, __VA_ARGS__)
#	define glog__tracef(logger, fmt, ...) glog__putf(logger, &glog__trace_level, fmt, __VA_ARGS__)
#	define glog__debugf(logger, fmt, ...) glog__putf(logger, &glog__debug_level, fmt, __VA_ARGS__)
#	define glog__unreachablef(logger, fmt, ...) glog__putf(logger, &glog__unreachable_level, fmt, \
		__VA_ARGS__)
#endif

#define glog__info(logger, fmt) glog__putf(logger, &glog__info_level, fmt)
#define glog__warn(logger, fmt) glog__putf(logger, &glog__warn_level, fmt)
#define glog__error(logger, fmt) glog__putf(logger, &glog__error_level, fmt)
#define glog__die(logger, fmt) glog__putf(logger, &glog__die_level, fmt)

#define glog__infof(logger, fmt, ...) glog__putf(logger, &glog__info_level, fmt, __VA_ARGS__)
#define glog__warnf(logger, fmt, ...) glog__putf(logger, &glog__warn_level, fmt, __VA_ARGS__)
#define glog__errorf(logger, fmt, ...) glog__putf(logger, &glog__error_level, fmt, __VA_ARGS__)
#define glog__dief(logger, fmt, ...) glog__putf(logger, &glog__die_level, fmt, __VA_ARGS__)

#endif
