//====================================================
//     File data
//====================================================
/**
 * @file windows.cpp
 * @author Gianluca Bianco
 * (biancogianluca9@gmail.com)
 * @date 2022-06-06
 * @copyright Copyright (c) 2022 Gianluca Bianco
 * under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Windows headers
#ifdef _WIN32
#include <windows.h>
#endif

// My headers
#include <osmanip/utility/generic.hpp>
#include <osmanip/utility/iostream.hpp>
#include <osmanip/utility/windows.hpp>

// STD headers
#include <sstream>
#include <string>

namespace osm {
//====================================================
//     Macros
//====================================================
#ifdef _WIN32
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

//====================================================
//     Variables
//====================================================
#ifdef _WIN32
    static HANDLE stdoutHandle;
    static DWORD outModeInit;
#endif
    std::string old_chcp;

    //====================================================
    //     Functions
    //====================================================

    // enableANSI
    /**
     * @brief Function used to enable ANSI escape
     * sequences on Windows.
     *
     */
    void enableANSI() {
// Settings for Windows mode
#ifdef _WIN32

        DWORD outMode = 0;
        stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (stdoutHandle == INVALID_HANDLE_VALUE) {
            exit(GetLastError());
        }

        if (!GetConsoleMode(stdoutHandle, &outMode)) {
            exit(GetLastError());
        }

        outModeInit = outMode;

        // Enable ANSI escape codes
        outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        if (!SetConsoleMode(stdoutHandle, outMode)) {
            exit(GetLastError());
        }

#endif
    }

    // disableANSI
    void disableANSI()
    /**
     * @brief Function used to disable ANSI escape
     * sequences on Windows.
     *
     */
    {
        // Reset all styles and colors
        osm::cout << "\033[0m";

// Settings for Windows mode
#ifdef _WIN32

        // Reset console mode
        if (!SetConsoleMode(stdoutHandle, outModeInit)) {
            exit(GetLastError());
        }

#endif
    }

    // enableUNICODE
    /**
     * @brief Function used to enable UNICODE
     * characters (used for Windows only).
     *
     */
    void enableUNICODE() {
// Settings for Windows mode
#ifdef _WIN32

        std::string old_chcp_pre = osm::getCommandOut("chcp");
        old_chcp = osm::split_string(old_chcp_pre, " ").back();

        system("chcp 65001 > nul");

#endif
    }

    // disableUNICODE
    /**
     * @brief Function used to disable UNICODE
     * characters (used for Windows only).
     *
     */
    void disableUNICODE() {
// Settings for Windows mode
#ifdef _WIN32

        std::ostringstream oss;
        oss << "chcp " << old_chcp << " > nul";
        std::string return_chcp = oss.str();

        system(return_chcp.c_str());

#endif
    }
}  // namespace osm