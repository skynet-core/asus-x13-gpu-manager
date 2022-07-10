#ifndef egpu_x13_lib_system_h_
#define egpu_x13_lib_system_h_

#include <string>
#include <fcntl.h>

std::string resolve_kernel_version();

std::string &kernel_version();

int load_kern_module(int file_fd, int flags = 0);

int delete_kern_module(const std::string &name, unsigned int flags = O_NONBLOCK);

#endif