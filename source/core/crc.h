//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_CRC_H
#define MAKEPLAY_INC_CRC_H
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H

#include <string>
#include <map>

namespace makeplay { namespace core { 


// Shift-Add-XOR hash
#define MP_CRCFUNC(x,h)  (h ^ ((h << 5) + (h >> 2) + x))
#define MP_CRC1(x)     MP_CRCFUNC(x[0], 0)
#define MP_CRC2(x)     MP_CRCFUNC(x[1], MP_CRCFUNC(x[0], 0))
#define MP_CRC3(x)     MP_CRCFUNC(x[2], MP_CRCFUNC(x[1], MP_CRCFUNC(x[0],0)))
#define MP_CRC4(x)     MP_CRCFUNC(x[3], MP_CRCFUNC(x[2], MP_CRCFUNC(x[1], MP_CRCFUNC(x[0],0))))
#define MP_CRC5(x)     MP_CRCFUNC(x[4], MP_CRCFUNC(x[3], MP_CRCFUNC(x[2], MP_CRCFUNC(x[1], MP_CRCFUNC(x[0],0)))))
#define MP_CRC6(x)     MP_CRCFUNC(x[5], MP_CRCFUNC(x[4], MP_CRCFUNC(x[3], MP_CRCFUNC(x[2], MP_CRCFUNC(x[1], MP_CRCFUNC(x[0],0))))))
#define MP_CRC7(x)     MP_CRCFUNC(x[6], MP_CRCFUNC(x[5], MP_CRCFUNC(x[4], MP_CRCFUNC(x[3], MP_CRCFUNC(x[2], MP_CRCFUNC(x[1],MP_CRCFUNC(x[0],0)))))))
#define MP_CRC8(x)     MP_CRCFUNC(x[7], MP_CRCFUNC(x[6], MP_CRCFUNC(x[5], MP_CRCFUNC(x[4], MP_CRCFUNC(x[3], MP_CRCFUNC(x[2], MP_CRCFUNC(x[1],MP_CRCFUNC(x[0],0))))))))

//-----------------------------------------------------------------------------
// CRC
//-----------------------------------------------------------------------------
class CRC 
{
    typedef std::map<CRC, std::string> StrTbl;

public:
    CRC() : m_crc(s_crcINVALID) 
    {
    }

    CRC(int _value) : m_crc(_value)
    {
    }

    CRC(const char * _str) : m_crc(to_crc(_str)) 
    {
        SCOPED_MEM_HEAP(MEMHEAP_CRCTBL);
        s_strTbl[m_crc] = _str;
    }
    
    operator unsigned int() const
    { 
        return int(m_crc); 
    }

    std::string const& to_str() const 
    { 
        StrTbl::const_iterator i = s_strTbl.find(m_crc);
        if (i != s_strTbl.end())
        {
            return s_strTbl[m_crc]; 
        }
        else
        {
            static const std::string str;
            return str;
        }
    }

    CRC      operator+(const char* _str)   
    { 
        CRC crc(to_crc(_str, m_crc)); 

        SCOPED_MEM_HEAP(MEMHEAP_CRCTBL);
        s_strTbl[crc] = s_strTbl[m_crc];
        s_strTbl[crc] += _str;

        return crc;
    }

    CRC&     operator+=(const char* _str)  
    { 
        CRC crc = to_crc(_str, m_crc); 

        SCOPED_MEM_HEAP(MEMHEAP_CRCTBL);
        s_strTbl[crc] = s_strTbl[m_crc];
        s_strTbl[crc] += _str;

        m_crc = crc;

        return *this;
    }

    static const CRC&   invalid()   { return s_crcINVALID; }

    // Shift-Add-XOR hash
    static int to_crc(const char *str, int h = 0)
    {
        const char *p = str;
        size_t len = strlen(p);
        if (len > 0)
        {
            for (size_t i = 0; i < len; i++, p++)
            {
                char value = *p;
                h = MP_CRCFUNC(value, h);
            }
        }

        return h;
    }

protected:
    int m_crc;

    static const CRC s_crcINVALID;
    static StrTbl    s_strTbl;
};

}} // namespace makeplay::core


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_CRC_H


