/*! \file
    \brief The definition of tetengo2::win32::encode.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_WIN32_ENCODE_H)
#define TETENGO2_WIN32_ENCODE_H

#include <functional>
#include <stdexcept>
#include <string>

#include <boost/concept_check.hpp>
#include <boost/scoped_array.hpp>

#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace win32
{
    /*!
        \brief The unary functor class for an encode using the Win32 API.

        \param Target A string type of the target. It must conform to
                      tetengo2::StringConcept<Target>.
        \param Source A string type of the source. It must conform to
                      tetengo2::StringConcept<Source>.
    */
    template <typename Target, typename Source>
    class encode :
        public std::unary_function<Source, Target>
    {
    public:
        // functions

        /*!
            \brief Encodes a source string to a target string.

            \param string A string.

            \return The encoded string.
        */
        const Target operator()(const Source& string)
        {
            return string;
        }
    };

    template <typename Target>
    class encode<Target, const char*> :
        public std::unary_function<const char*, Target>
    {
    public:
        // functions

        const Target operator()(const char* const& string)
        const
        {
            return encode<Target, std::string>(string);
        }
    };

    template <typename Target>
    class encode<Target, const wchar_t*> :
        public std::unary_function<const wchar_t*, Target>
    {
    public:
        // functions

        const Target operator()(const wchar_t* const& string)
        const
        {
            return encode<Target, std::wstring>(string);
        }
    };

    template <>
    class encode<std::wstring, std::string> :
        public std::unary_function<std::string, std::wstring>
    {
    public:
        // functions

        const std::wstring operator()(const std::string& string)
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
    };

    template <>
    class encode<std::string, std::wstring> :
        public std::unary_function<std::wstring, std::string>
    {
    public:
        // functions

        const std::string operator()(const std::wstring& string)
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
    };
}}


#endif
