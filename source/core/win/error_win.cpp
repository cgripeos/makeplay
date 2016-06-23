//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#include "..\error.h"
#include <vector>
#include <string>

namespace makeplay { namespace core { namespace error {


void stack(std::vector<void*>& _stack)
{
}


void stack(std::vector<std::string>& _stack)
{
}


void log(LogType _type, const char* _file, int _line, const char* _msg)
{
    char buf[1024] = "";
    sprintf_s(buf, "%s: %s (%d): %s\n", g_LogTypeStr[int(_type)], _file, _line, _msg);
    
    switch (_type)
    {
    case LogType::ERROR_LOG:
    case LogType::ERROR_WARN:
        OutputDebugStringA(buf);
        break;

    case LogType::ERROR_FAIL:
        OutputDebugStringA(buf);

        if (IsDebuggerPresent()) 
        {
            __debugbreak();
        }

        exit(-1);
        break;

    default:
        break;
    };

}


}}} // namespace makeplay::core::error

