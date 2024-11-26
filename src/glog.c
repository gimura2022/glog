#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glog.h>

static const char* default_format = GLOG_COLOR_DARK_GRAY "[" GLOG_COLOR_LIGHT_GRAY "%s" GLOG_COLOR_DARK_GRAY
	"][" GLOG_COLOR_LIGHT_GRAY "%s" GLOG_COLOR_DARK_GRAY "][" GLOG_COLOR_LIGHT_GRAY "%s"
	GLOG_COLOR_DARK_GRAY "] " GLOG_COLOR_LIGHT_GRAY "%s" GLOG_COLOR_RESET;

static const char* chaos_name       = GLOG_COLOR_DARK_LIGHT_BLUE "CHAOS" GLOG_COLOR_RESET;
static const char* trace_name       = GLOG_COLOR_LIGHT_BLUE "TRACE" GLOG_COLOR_RESET;
static const char* debug_name       = GLOG_COLOR_BLUE "DEBUG" GLOG_COLOR_RESET;
static const char* info_name        = GLOG_COLOR_GREEN "INFO" GLOG_COLOR_RESET;
static const char* warn_name        = GLOG_COLOR_DARK_YELLOW "WARN" GLOG_COLOR_RESET;
static const char* error_name       = GLOG_COLOR_RED "ERROR" GLOG_COLOR_RESET;
static const char* die_name         = GLOG_COLOR_DARK_RED "DIE" GLOG_COLOR_RESET;
static const char* unreachable_name = GLOG_COLOR_WHITE "UNREACHABLE" GLOG_COLOR_RESET;

struct glog__logging_level glog__chaos_level       = {0};
struct glog__logging_level glog__trace_level       = {0};
struct glog__logging_level glog__debug_level       = {0};
struct glog__logging_level glog__info_level        = {0};
struct glog__logging_level glog__warn_level        = {0};
struct glog__logging_level glog__error_level       = {0};
struct glog__logging_level glog__die_level         = {0};
struct glog__logging_level glog__unreachable_level = {0};

static void die_handler(void);
static void unreachable_handler(void);

void glog__init(void)
{
	glog__chaos_level       = (struct glog__logging_level) {.level = -300, .handler = NULL, .name                = chaos_name};
	glog__trace_level       = (struct glog__logging_level) {.level = -200, .handler = NULL, .name                = trace_name};
	glog__debug_level       = (struct glog__logging_level) {.level = -100, .handler = NULL, .name                = debug_name};
	glog__info_level        = (struct glog__logging_level) {.level = 0, .handler    = NULL, .name                = info_name};
	glog__warn_level        = (struct glog__logging_level) {.level = 100, .handler  = NULL, .name                = warn_name};
	glog__error_level       = (struct glog__logging_level) {.level = 200, .handler  = NULL, .name                = error_name};
	glog__die_level         = (struct glog__logging_level) {.level = 1000, .handler = die_handler, .name         = die_name};
	glog__unreachable_level = (struct glog__logging_level) {.level = 2000, .handler = unreachable_handler, .name = unreachable_name};
}

void glog__logger_from_prefix(struct glog__logger* logger, const char* prefix)
{
	*logger = (struct glog__logger) {
		.format           = default_format,
		.prefix           = prefix,
		.min_log_level    = -1000,
		.out_streams      = &stderr,
		.out_stream_count = 1
	};
}

void glog__putf(const struct glog__logger* logger, const struct glog__logging_level* level,
	const char* fmt, ...)
{
	if (logger == NULL || level == NULL) return;
	if (logger->min_log_level > level->level) return;

	va_list args;
	va_start(args, fmt);

	char msg[GLOG_MAX_MSG_BUF] = {0};
	vsnprintf(msg, sizeof(msg), fmt, args);

	va_end(args);

	time_t t = time(NULL);
	struct tm* lt = localtime(&t);

	char datetime[GLOG_MAX_DATE_BUF] = {0};
	strftime(datetime, sizeof(datetime), "%Y:%m:%d %H:%M:%S", lt);

	for (int i = 0; i < logger->out_stream_count; i++) {
		fprintf(logger->out_streams[i], logger->format, datetime, logger->prefix, level->name,
				msg);
	}

	if (level->handler != NULL) level->handler();
}

static void die_handler(void)
{
	fputs("Detected die message.\n", stderr);
	abort();
}

static void unreachable_handler(void)
{
	fputs("Detected unreachable situation.\n", stderr);
	abort();
}
