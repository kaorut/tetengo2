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
        // types

        //! The string type of the target.
        typedef Target target_type;

        //! The string type of the source.
        typedef Source source_type;


        // functions

        /*!
            \brief Encodes a source string to a target string.

            \param string A string.

            \return The encoded string.
        */
        const target_type operator()(const source_type& string)
        {
            return string;
        }
    };

#if !defined(DOCUMENTATION)
    // A specialized template.
    template <>
    class encode<std::wstring, std::string> :
        public std::unary_function<std::string, std::wstring>
    {
    public:
        // types

        typedef std::wstring target_type;

        typedef std::string source_type;


        // functions

        const target_type operator()(const source_type& string)
        const
        {
            if (string.empty()) return target_type();
            
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

            const boost::scoped_array<target_type::value_type> converted(
                new target_type::value_type[length]
            );
            ::MultiByteToWideChar(
                CP_ACP,
                MB_PRECOMPOSED,
                string.c_str(),
                static_cast<int>(string.length()),
                converted.get(),
                length
            );

            return target_type(converted.get(), converted.get() + length);
        }
    };

    // A specialized template.
    template <>
    class encode<std::string, std::wstring> :
        public std::unary_function<std::wstring, std::string>
    {
    public:
        // types

        typedef std::string target_type;

        typedef std::wstring source_type;


        // functions

        const target_type operator()(const source_type& string)
        const
        {
            if (string.empty()) return target_type();

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
            
            const boost::scoped_array<target_type::value_type> converted(
                new target_type::value_type[length]
            );
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

            return target_type(converted.get(), converted.get() + length);
        }
    };
#endif
}}


#endif
