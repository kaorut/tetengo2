/*! \file
    \brief The definition of tetengo2::win32::encode.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_WIN32_ENCODE_H)
#define TETENGO2_WIN32_ENCODE_H

#include <cstddef>
#include <functional>
#include <stdexcept>
//#include <string>

#include <boost/concept_check.hpp>
#include <boost/scoped_array.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.StringConcept.h"


namespace tetengo2 { namespace win32
{
    /*!
        \brief The unary functor class template for an encode using the Win32
               API.

        \tparam Target A string type of the target. It must conform to
                       tetengo2::StringConcept<Target>.
        \tparam Source A string type of the source. It must conform to
                       tetengo2::StringConcept<Source>.
    */
    template <typename Target, typename Source>
    class encode :
        public std::unary_function<Source, Target>
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((tetengo2::StringConcept<Target>));
        BOOST_CONCEPT_ASSERT((tetengo2::StringConcept<Source>));


    public:
        // types

        //! The string type of the target.
        typedef result_type target_type;

        //! The string type of the source.
        typedef argument_type source_type;


        // functions

        /*!
            \brief Encodes a source string to a target string.

            \param string A string.

            \return The encoded string.

            \throw std::invalid_argument When the string cannot be encoded.
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
    private:
        // concept checks

        struct concept_check_Target
        {
            typedef std::wstring target_type;
            BOOST_CONCEPT_ASSERT((tetengo2::StringConcept<target_type>));
        };
        struct concept_check_Source
        {
            typedef std::string source_type;
            BOOST_CONCEPT_ASSERT((tetengo2::StringConcept<source_type>));
        };


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
    private:
        // concept checks

        struct concept_check_Target
        {
            typedef std::string target_type;
            BOOST_CONCEPT_ASSERT((tetengo2::StringConcept<target_type>));
        };
        struct concept_check_Source
        {
            typedef std::wstring source_type;
            BOOST_CONCEPT_ASSERT((tetengo2::StringConcept<source_type>));
        };

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
