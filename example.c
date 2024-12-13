#include <glog.h>

int main(int argc, char* argv[])
{
	glog__init();

	struct glog__logger main_logger = {0};
	glog__logger_from_prefix(&main_logger, "main");

	glog__chaos(&main_logger, "Hello, world!");
	glog__trace(&main_logger, "Hello, world!");
	glog__debug(&main_logger, "Hello, world!");
	glog__info(&main_logger, "Hello, world!");
	glog__warn(&main_logger, "Hello, world!");
	glog__error(&main_logger, "Hello, world!");
	glog__die(&main_logger, "Hello, world!");

	return 0;
}
