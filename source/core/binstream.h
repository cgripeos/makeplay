//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************

#ifndef MAKEPLAY_INC_BINSTREAM_H
#define MAKEPLAY_INC_BINSTREAM_H
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H

#ifndef MAKEPLAY_INC_CRC_H
#include "crc.h"
#endif // MAKEPLAY_INC_CRC_H

namespace makeplay { namespace core {

enum StreamError
{
    BINSTREAM_OK = 0,
    BINSTREAM_EOF,
    BINSTREAM_FAILOPP,
    BINSTREAM_UNKNOWN,
};


//-----------------------------------------------------------------------------
// ReadStream
//-----------------------------------------------------------------------------
class ReadStream
{
public: 
    virtual ~ReadStream() {}

    virtual bool        eof() = 0;
    virtual StreamError seek(size_t _pos) = 0;
    virtual StreamError read(void* _buffer, size_t _size) = 0;

    // TO-DO byte swapping for "different"-endian machines
    ReadStream& operator>> (bool& _val)        { read(&_val, sizeof(bool)); return *this; }
    ReadStream& operator>> (CRC& _val)         { read(&_val, sizeof(CRC)); return *this; }
    ReadStream& operator>> (char& _val)        { read(&_val, sizeof(char)); return *this; }
    ReadStream& operator>> (int8_t& _val)      { read(&_val, sizeof(int8_t)); return *this; }
    ReadStream& operator>> (uint8_t& _val)     { read(&_val, sizeof(uint8_t)); return *this; }
    ReadStream& operator>> (int16_t& _val)     { read(&_val, sizeof(int16_t)); return *this; }
    ReadStream& operator>> (uint16_t& _val)    { read(&_val, sizeof(uint16_t)); return *this; }
    ReadStream& operator>> (int32_t& _val)     { read(&_val, sizeof(int32_t)); return *this; }
    ReadStream& operator>> (uint32_t& _val)    { read(&_val, sizeof(uint32_t)); return *this; }
    ReadStream& operator>> (int64_t& _val)     { read(&_val, sizeof(int64_t)); return *this; }
    ReadStream& operator>> (uint64_t& _val)    { read(&_val, sizeof(uint64_t)); return *this; }
    ReadStream& operator>> (float& _val)       { read(&_val, sizeof(float)); return *this; }
    ReadStream& operator>> (double& _val)      { read(&_val, sizeof(double)); return *this; }
    ReadStream& operator>> (std::string& _val)
    { 
        int len;
        (*this) >> len;
        _val.resize(len);
        read(&(_val[0]), len);

        return *this;
    }
};

//-----------------------------------------------------------------------------
// WriteStream
//-----------------------------------------------------------------------------
class WriteStream
{
public: 
    virtual ~WriteStream() {}

    virtual StreamError write(void const* _buffer, size_t _size) = 0;

    // TO-DO byte swapping for "different"-endian machines
    WriteStream& operator<< (bool _val)          { write(&_val, sizeof(bool)); return *this; }
    WriteStream& operator<< (const CRC& _val)    { write(&_val, sizeof(CRC)); return *this; }
    WriteStream& operator<< (char _val)          { write(&_val, sizeof(char)); return *this; }
    WriteStream& operator<< (int8_t _val)        { write(&_val, sizeof(int8_t)); return *this; }
    WriteStream& operator<< (uint8_t _val)       { write(&_val, sizeof(uint8_t)); return *this; }
    WriteStream& operator<< (int16_t _val)       { write(&_val, sizeof(int16_t)); return *this; }
    WriteStream& operator<< (uint16_t _val)      { write(&_val, sizeof(uint16_t)); return *this; }
    WriteStream& operator<< (int32_t _val)       { write(&_val, sizeof(int32_t)); return *this; }
    WriteStream& operator<< (uint32_t _val)      { write(&_val, sizeof(uint32_t)); return *this; }
    WriteStream& operator<< (int64_t _val)       { write(&_val, sizeof(int64_t)); return *this; }
    WriteStream& operator<< (uint64_t _val)      { write(&_val, sizeof(uint64_t)); return *this; }
    WriteStream& operator<< (float _val)         { write(&_val, sizeof(float)); return *this; }
    WriteStream& operator<< (double _val)        { write(&_val, sizeof(double)); return *this; }
    WriteStream& operator<< (const char* _val)
    {
        size_t size = strlen(_val);
        (*this) << uint32_t(size);
        write(_val, size);
        return *this;
    }
    WriteStream& operator<< (std::string const& _val)
    { 
        (*this) << uint32_t(_val.length());
        write(_val.c_str(), _val.size()); 
        return *this; 
    }
};

                                 

}} // namespace makeplay::core


//-----------------------------------------------------------------------------
// Utils for revisioning object save/loads
//-----------------------------------------------------------------------------

#define DEF_REV(OBJ, REV)                                       \
    namespace namespace_##OBJ {                                 \
        void LoadRev(core::ReadStream&  _b, int& _lrev)      \
            { _b >> _lrev;  MP_ASSERT(_lrev <= REV); }          \
        void SaveRev(core::WriteStream& _b)                  \
            {_b << REV;}                                        \
    }

#define LOAD_REV(obj, b)   int rev; namespace_##obj::LoadRev(b, rev)                                            
#define SAVE_REV(obj, b)   namespace_##obj::SaveRev(b)     

//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_BINSTREAM_H

