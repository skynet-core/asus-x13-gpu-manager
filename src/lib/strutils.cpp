#include "strutils.h"

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace strutils
            {
                namespace
                {
                    const std::string WHITESPACE = " \n\r\t\f\v";
                }

                std::string ltrim(const std::string &s)
                {
                    size_t start = s.find_first_not_of(WHITESPACE);
                    return (start == std::string::npos) ? "" : s.substr(start);
                }

                std::string rtrim(const std::string &s)
                {
                    size_t end = s.find_last_not_of(WHITESPACE);
                    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
                }

                std::string trim(const std::string &s)
                {
                    return rtrim(ltrim(s));
                }

                std::string to_lower(const std::string_view s)
                {
                    std::string orig{s};
                    std::transform(orig.begin(), orig.end(), orig.begin(),
                                   [](unsigned char c)
                                   { return std::tolower(c); });
                    return orig;
                }
            }
        }
    }
}