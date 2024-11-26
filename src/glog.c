#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "glog.h"

static const char* default_format = "[%s][%s][%s] %s";

static const char* chaos_name       = "CHAOS";
static const char* trace_name       = "TRACE";
static const char* debug_name       = "DEBUG";
static const char* info_name        = "INFO";
static const char* warn_name        = "WARN";
static const char* error_name       = "ERROR";
static const char* die_name         = "DIE";
static const char* unreachable_name = "UNREACHABLE";

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

	char buf[GLOG_MAX_MSG_BUF] = {0};
	vsnprintf(buf, sizeof(buf), fmt, args);

	va_end(args);

	time_t t = time(NULL);
	struct tm* lt = localtime(&t);

	for (int i = 0; i < logger->out_stream_count; i++) {
		fprintf(logger->out_streams[i], logger->format, asctime(lt), logger->prefix, level->name,
				buf);
	}

	level->handler();
}

static void die_handler(void)
{
	fputs("Detected die message. Abort.", stderr);
	abort();
}

static void unreachable_handler(void)
{
	fputs("Detected unreachable situation. Abort.", stderr);
	abort();
}
