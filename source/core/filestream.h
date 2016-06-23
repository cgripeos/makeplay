//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_FILESTREAM_H
#define MAKEPLAY_INC_FILESTREAM_H
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H

#ifndef MAKEPLAY_INC_BINSTREAM_H
#include "binstream.h"
#endif // MAKEPLAY_INC_BINSTREAM_H

#include <string>


namespace makeplay { namespace core { 

class Path;
class FileReadStream;
class FileWriteStream;

//-----------------------------------------------------------------------------
// Path
//-----------------------------------------------------------------------------
class Path
{
public:
    Path(const char* _path);

    bool   exists() const;
    bool   is_dir() const;
    bool   is_file() const;
    size_t file_size() const;

    void get_filename(std::string& _file);
    void get_ext(std::string& _ext);

    const std::string& path() const { return m_syspath; };

private:
    std::string m_syspath;
};



//-----------------------------------------------------------------------------
// FileReadStream
//-----------------------------------------------------------------------------
class FileReadStream : public ReadStream
{
public: 
    static FileReadStream*  open_read(const Path& _path);

             FileReadStream() {}
    virtual ~FileReadStream() {}

    virtual bool        eof() = 0;
    virtual StreamError read(void* _buffer, size_t _size) = 0;
    virtual StreamError seek(size_t _pos) = 0;
};


enum FileWriteOpp
{
    FILE_CLEAR,
    FILE_APPEND,
};


//-----------------------------------------------------------------------------
// FileWriteStream
//-----------------------------------------------------------------------------
class FileWriteStream : public WriteStream
{
public: 
    static FileWriteStream* open_write(const Path& _path, FileWriteOpp _opp);

             FileWriteStream() {}
    virtual ~FileWriteStream() {}

    virtual StreamError write(void const* _buffer, size_t _size) = 0;
};


}} // namespace makeplay::core


//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_FILESTREAM_H

