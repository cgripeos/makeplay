//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


//#include "..\proto.h"
#include "..\filestream.h"
#include <iostream>
#include <fstream>
# include <windows.h>

namespace makeplay { namespace core {


Path::Path(const char* _path)
{
    m_syspath = _path;
    size_t found = m_syspath.find_first_of('\\');
    while (found != std::string::npos)
    {
        m_syspath[found] = '/';
        found = m_syspath.find('\\');
    }

}

bool Path::exists() const
{
    BOOL fOk;
    WIN32_FILE_ATTRIBUTE_DATA   fileInfo;

    fOk = GetFileAttributesExA(m_syspath.c_str(), GetFileExInfoStandard, (void*)&fileInfo);
    return fOk != 0;
}

bool Path::is_dir() const
{
    if (m_syspath.empty())
    {
        return false;
    }

    if (m_syspath[m_syspath.size()-1] == '\\')
    {
        return true;
    }
    return false;
}

bool Path::is_file() const
{
    return !is_dir();
}

size_t Path::file_size() const
{
    if (!is_file() || !exists())
        return 0;

    BOOL fOk;
    WIN32_FILE_ATTRIBUTE_DATA   fileInfo;

    fOk = GetFileAttributesExA(m_syspath.c_str(), GetFileExInfoStandard, (void*)&fileInfo);
    if (!fOk)
        return -1;
    if (0 == fileInfo.nFileSizeHigh)
    {
        return 0;
    }

    return (long)fileInfo.nFileSizeLow;
}


void Path::get_filename(std::string& _file)
{
    _file.clear();
    if (m_syspath.empty())
    {
        return;
    }

    if (is_file())
    {
        size_t found = m_syspath.find_last_of('\\');
        if ( std::string::npos != found)
        {
            _file.append(&m_syspath[found], m_syspath.size() - 1 - found);
        }
    }
}

void Path::get_ext(std::string& _ext)
{
    _ext.clear();
    if (m_syspath.empty())
    {
        return;
    }

    size_t found = m_syspath.size()-1;
    while (found)
    {
        char c = m_syspath[found--];
        if (c == '.')
        {
            m_syspath.append(&m_syspath[found], m_syspath.size() - 1 - found);
            return;
        }

        if (c == '\\')
        {
            return;
        }
    }
}




class FileReadStreamWin : public FileReadStream
{
public: 
    std::ifstream  m_file;

    FileReadStreamWin(const char* _filename)
    {
        m_file.open(_filename, std::ios::in|std::ios::binary);
    }

    ~FileReadStreamWin()
    {
        if (m_file.is_open())
        {
            m_file.close();
        }
    }

    virtual bool    FileReadStreamWin::eof()
    {
        return !m_file.is_open() || m_file.eof();
    }

    virtual StreamError read(void* _buffer, size_t _size)
    {
        if (m_file.is_open())
        {
            m_file.read((char*)_buffer, _size);
            return m_file.bad() ? BINSTREAM_FAILOPP: BINSTREAM_OK;
        }

        return BINSTREAM_FAILOPP;
    }
    
    virtual StreamError seek(size_t _pos)
    {
        if (m_file.is_open())
        {
            m_file.seekg(_pos, std::ios::beg);
            return m_file.bad() ? BINSTREAM_FAILOPP: BINSTREAM_OK;
        }
        return BINSTREAM_FAILOPP;
    }
};

// static 
FileReadStream*  FileReadStream::open_read(const Path& _path)
{
    return new FileReadStreamWin(_path.path().c_str());
}


class FileWriteStreamWin : public FileWriteStream
{
public: 
    std::ofstream  m_file;

    FileWriteStreamWin(const char* _filename, FileWriteOpp _opp)
    {
        m_file.open(_filename, std::ios::out|std::ios::binary  | ((_opp == FILE_APPEND) ? std::ios::app : 0));
    }

    ~FileWriteStreamWin()
    {
        if (m_file.is_open())
        {
            m_file.close();
        }
    }

    virtual StreamError write(void const* _buffer, size_t _size)
    {
        if (m_file.is_open())
        {
            m_file.write((char*)_buffer, _size);
            return m_file.bad() ? BINSTREAM_FAILOPP: BINSTREAM_OK;
        }
        return BINSTREAM_FAILOPP;
    }
};


// static 
FileWriteStream* FileWriteStream::open_write(const Path& _path, FileWriteOpp _opp)
{
    return new FileWriteStreamWin(_path.path().c_str(), _opp);
}


}} // namespace makeplay::core::file

