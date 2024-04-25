#pragma once

#include <string>

namespace gmv {
    class DebugWarn {
    public:
        static void ShowDebugWarn(std::string message, std::string fileName, int lineNum);

        inline static std::string LogStr;
    };

#define DBG_LOG(warning)   \
        warning += std::string("\n"); \
        gmv::DebugWarn::LogStr += warning; \

#define LOG_RETURN_VOID(condition, warning)   \
    if (!(condition)) {    \
        gmv::DebugWarn::ShowDebugWarn(warning, __FILE__, __LINE__);   \
        return;  \
    } \

#define DBG_WARN_RETURN_FALSE(condition, warning)  \
    if (!(condition)) {            \
        gmv::DebugWarn::ShowDebugWarn(warning, __FILE__, __LINE__); \
        return false;   \
    } \

} // namespace gmv
