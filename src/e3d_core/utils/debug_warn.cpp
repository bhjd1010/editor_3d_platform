#include "debug_warn.h"

#ifdef _WIN32

#include <windows.h>

#endif

namespace gmv {
    void DebugWarn::ShowDebugWarn(std::string message, std::string fileName, int lineNum) {
#ifdef _WIN32
        std::string totalMsg = message + "  In File: " + fileName + "  Line: " + std::to_string(lineNum);
        MessageBox(NULL, TEXT(totalMsg.c_str()), TEXT("Warning Message \n "), MB_OK | MB_OKCANCEL);

#endif
    }
} // namespace gmv