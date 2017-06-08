/*! \file
    \brief The definition of tetengo2::text::encoding::cp932.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_CP932_H)
#define TETENGO2_TEXT_ENCODING_CP932_H

#include <memory>
#include <stdexcept>
#include <string>

#include <boost/operators.hpp>

#include <tetengo2/detail/base/encoding.h>
#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2 { namespace text { namespace encoding
{
    /*!
        \brief The class for a CP932 encoding.
    */
    class cp932 : public encoding<std::string>, private boost::equality_comparable<cp932>
    {
    public:
        // types

        //! The base type.
        using base_type = encoding<std::string>;

        //! The string type.
        using string_type = base_type::string_type;

        //! The encoding details type.
        using encoding_details_type = tetengo2::detail::base::encoding;


        // constructors and destructors

        /*!
            \brief Creates a CP932 encoding.
        */
        cp932();

        /*!
            \brief Destroys the ASCII encoding.
        */
        virtual ~cp932();


        // functions

        /*!
            \brief Checks whether one CP932 encoding is equal to another.

            \param one     One CP932 encoding.
            \param another Another CP932 encoding.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const cp932& one, const cp932& another);

        /*!
            \brief Translates a string from the pivot encoding.

            \param pivot A pivot string.

            \return A translated string.

            \throw std::invalid_argument When the string cannot be translated.
        */
        string_type from_pivot(const typename base_type::pivot_type& pivot)
        const;

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.

            \throw std::invalid_argument When the string cannot be translated.
        */
        typename base_type::pivot_type to_pivot(const string_type& string)
        const;


    private:
        // types

        class impl;


        // variables

        const std::shared_ptr<impl> m_p_impl;


    };


}}}


#endif
