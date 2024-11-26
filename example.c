#include <glog.h>

int main(int argc, char* argv[])
{
	glog__init();

	struct glog__logger main_logger = {0};
	glog__logger_from_prefix(&main_logger, "main");

	glog__chaos(&main_logger, "Hello, world!\n");
	glog__trace(&main_logger, "Hello, world!\n");
	glog__debug(&main_logger, "Hello, world!\n");
	glog__info(&main_logger, "Hello, world!\n");
	glog__warn(&main_logger, "Hello, world!\n");
	glog__error(&main_logger, "Hello, world!\n");
	glog__die(&main_logger, "Hello, world!\n");

	return 0;
}
