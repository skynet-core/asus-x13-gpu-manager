#ifndef egpu_x13_lib_module_file_h_
#define egpu_x13_lib_module_file_h_


#include <sys/types.h>
#include <string_view>


class module_file
{
public:
    explicit module_file(std::string_view name);
    
    ~module_file();

    bool is_ok() const;

    int get_fd() const;

    std::string error() const;

private:
    FILE *file_;
    int err_;
};


#endif