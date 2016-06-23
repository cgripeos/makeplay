//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_ERROR_H
#define MAKEPLAY_INC_ERROR_H
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H

namespace makeplay { namespace core {

namespace error {
 
enum class LogType
{
    ERROR_LOG,
    ERROR_WARN,
    ERROR_FAIL,
};


const char* const g_LogTypeStr[3] = {"ERROR_LOG", "ERROR_WARN", "ERROR_FAIL"};



//void stack(std::vector<void*>& _stack);
//void stack(std::vector<std::string>& _stack);
void log(LogType _type, const char* _file, int _line, const char* _msg);

} // error


#ifdef MP_USE_FAIL
    #define MP_FAIL(_msg)               do { makeplay::core::error::log(makeplay::core::error::LogType::ERROR_FAIL, __FILE__, __LINE__, _msg); } while(0)
#else
    #define MP_FAIL(_msg)               do {} while(0)
#endif // MP_USE_FAIL

#ifdef MP_USE_ASSERT
    #define MP_ASSERT(_exp)             do { if (!(_exp)) makeplay::core::error::log(makeplay::core::error::LogType::ERROR_FAIL, __FILE__, __LINE__, ""); } while(0)
    #define MP_ASSERT_MSG(_exp, _msg)   do { if (!(_exp)) makeplay::core::error::log(makeplay::core::error::LogType::ERROR_FAIL, __FILE__, __LINE__, _msg); } while(0)
#else
    #define MP_ASSERT(_exp, _msg)       do {} while(0)
    #define MP_ASSERT_MSG(_exp, _msg)   do {} while(0)
#endif // MP_USE_ASSERT

#ifdef MP_USE_WARN
    #define MP_WARN(_msg)           do { makeplay::core::error::log(makeplay::core::error::LogType::ERROR_WARN, __FILE__, __LINE__, _msg); } while(0)
#else
    #define MP_WARN(_msg)           do {} while(0)
#endif // MP_WARN

#ifdef MP_USE_LOG 
    #define MP_LOG(_msg)            do { makeplay::core::error::log(makeplay::core::error::LogType::ERROR_LOG, __FILE__, __LINE__, _msg); } while(0)
#else
    #define MP_LOG(_msg)            do () {} while(0)
#endif // MP_USE_LOG

}} // namespace makeplay::core 


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_ERROR_H

