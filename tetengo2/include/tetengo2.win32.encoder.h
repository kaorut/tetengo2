/*! \file
    \brief The definition of tetengo2::win32::encoder.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_WIN32_ENCODER_H)
#define TETENGO2_WIN32_ENCODER_H

#include <stdexcept>
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>

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
            if (string.empty()) return std::wstring();
            
            const int length = ::MultiByteToWideChar(
                CP_ACP,
                MB_PRECOMPOSED, 
                string.c_str(),
                static_cast<int>(string.length()),
                NULL,
                0
            );
            if (length == 0)
            {
                throw std::invalid_argument(
                    "Can't convert std::string to std::wstring!"
                );
            }

            const boost::scoped_array<wchar_t> converted(new wchar_t[length]);
            ::MultiByteToWideChar(
                CP_ACP,
                MB_PRECOMPOSED,
                string.c_str(),
                static_cast<int>(string.length()),
                converted.get(),
                length
            );

            return std::wstring(converted.get(), converted.get() + length);
        }

        template <>
        const std::string encode(const std::wstring& string)
        const
        {
            if (string.empty()) return std::string();

            const int length = ::WideCharToMultiByte(
                CP_ACP,
                WC_NO_BEST_FIT_CHARS | WC_COMPOSITECHECK | WC_DEFAULTCHAR,
                string.c_str(),
                static_cast<int>(string.length()),
                NULL,
                0,
                NULL,
                NULL
            );
            if (length == 0)
            {
                throw std::invalid_argument(
                    "Can't convert std::wstring to std::string!"
                );
            }
            
            const boost::scoped_array<char> converted(new char[length]);
            ::WideCharToMultiByte(
                CP_ACP,
                WC_NO_BEST_FIT_CHARS | WC_COMPOSITECHECK | WC_DEFAULTCHAR,
                string.c_str(),
                static_cast<int>(string.length()),
                converted.get(),
                length,
                NULL,
                NULL
            );

            return std::string(converted.get(), converted.get() + length);
        }


    private:
        // constructors

        encoder()
        {}


    };
}}

#endif
