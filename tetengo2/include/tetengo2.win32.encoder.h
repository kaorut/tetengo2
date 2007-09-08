/*! \file
    \brief The definition of tetengo2::win32::encoder.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_WIN32_ENCODER_H)
#define TETENGO2_WIN32_ENCODER_H

#include <stdexcept>
#include <string>

#include <boost/concept_check.hpp>
#include <boost/scoped_array.hpp>

#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace win32
{
    /*!
        \brief The class for an encoder using the Win32 API.
    */
    class encoder
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates an encoder object.
        */
        encoder()
        {}

        /*!
            \brief Copies an encoder object.

            \param another Another encoder.
        */
        encoder(const encoder& another)
        {}

        /*!
            \brief Destroys the encoder object.
        */
        ~encoder()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps this for another.

            \param another Another encoder.
        */
        void swap(encoder& another)
        throw ()
        {}

        /*!
            \brief Assigns an encoder object.

            \param another Another encoder.
        */
        encoder& operator=(const encoder& another)
        {
            return *this;
        }

        /*!
            \brief Encodes a source string to a target string.

            \param Target A string type of the target. It must conform to
                          boost::ConvertibleConcept<Target, std::string>,
                          boost::ConvertibleConcept<Target, std::wstring>.
            \param Source A string type of the source. It must conform to
                          boost::ConvertibleConcept<Source, std::string>,
                          boost::ConvertibleConcept<Source, std::wstring>,
                          boost::CopyConstructible<Source>.

            \param string A string.

            \return The encoded string.
        */
        template <typename Target, typename Source>
        const Target encode(const Source& string)
        const;

        template <typename Target>
        const Target encode(const char* const& string)
        const
        {
            boost::function_requires<
                boost::ConvertibleConcept<const char*, std::string>
            >();

            return encode<Target, std::string>(string);
        }

        template <typename Target>
        const Target encode(const wchar_t* const& string)
        const
        {
            boost::function_requires<
                boost::ConvertibleConcept<const char*, std::wstring>
            >();

            return encode<Target, std::wstring>(string);
        }

        template <>
        const std::string encode(const std::string& string)
        const
        {
            boost::function_requires<
                boost::ConvertibleConcept<std::string, std::string>
            >();
            boost::function_requires<
                boost::ConvertibleConcept<std::string, std::string>
            >();

            return string;
        }

        template <>
        const std::wstring encode(const std::wstring& string)
        const
        {
            boost::function_requires<
                boost::ConvertibleConcept<std::wstring, std::wstring>
            >();
            boost::function_requires<
                boost::ConvertibleConcept<std::wstring, std::wstring>
            >();

            return string;
        }

        template <>
        const std::wstring encode(const std::string& string)
        const
        {
            boost::function_requires<
                boost::ConvertibleConcept<std::wstring, std::wstring>
            >();
            boost::function_requires<
                boost::ConvertibleConcept<std::string, std::string>
            >();

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
            boost::function_requires<
                boost::ConvertibleConcept<std::string, std::string>
            >();
            boost::function_requires<
                boost::ConvertibleConcept<std::wstring, std::wstring>
            >();

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
