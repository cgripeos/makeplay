//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************



#include "proto.h"
#include "crc.h"
#include "mt.h"
#include <string>

namespace makeplay { namespace core { 

CRC::StrTbl   CRC::s_strTbl;
const CRC CRC::s_crcINVALID("");




}} // namespace makeplay::core