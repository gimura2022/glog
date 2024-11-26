# libglog [![CodeFactor](https://www.codefactor.io/repository/github/gimura2022/libglog/badge)](https://www.codefactor.io/repository/github/gimura2022/libglog)
Small library for logging

## Install
To install library run
```
cc -o gnub gnub.c
sudo ./gnub
```
in your terminal.

## Quick example
```c
#include <glog.h>

int main(int argc, char* argv[])
{
	glog__init();

	struct glog__logger main_logger = {0};
	glog__logger_from_prefix(&main_logger, "main");

	glog__info(&main_logger, "Hello, world!\n");

	return 0;
}
```
and compile this with `cc -o example example.c -lglog`.
