/*! \file
    \brief The definition of tetengo2::win32::encoder.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_WIN32_ENCODER_H)
#define TETENGO2_WIN32_ENCODER_H

#include <string>

#include <boost/noncopyable.hpp>

#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace win32
{
    /*!
        \brief The class for an encoder using the Win32 API.
    */
    class encoder : private boost::noncopyable
    {
    public:
        // static functions

        static const encoder& instance()
        {
            static const encoder singleton;

            return singleton;
        }


        // constructors and destructor

        ~encoder()
        throw ()
        {}


        // functions

        /*!
            \brief Encodes a std::string string to a target string.

            \param Target A string type of the target.
            \param Source A string type of the source.

            \param string A string.

            \return The encoded string.
        */
        template <typename Target, typename Source>
        const Target encode(const Source& string)
        const;

        template <typename Target>
        const Target encode(const char* const string)
        const
        {
            return encode<Target, std::string>(string);
        }

        template <typename Target>
        const Target encode(const wchar_t* const string)
        const
        {
            return encode<Target, std::wstring>(string);
        }

        template <>
        const std::string encode(const std::string& string)
        const
        {
            return string;
        }

        template <>
        const std::wstring encode(const std::wstring& string)
        const
        {
            return string;
        }

        template <>
        const std::wstring encode(const std::string& string)
        const
        {
            return std::wstring();
        }

        template <>
        const std::string encode(const std::wstring& string)
        const
        {
            return std::string();
        }


    private:
        // constructors

        encoder()
        {}


    };
}}

#endif
