/*! \file
    \brief The definition of tetengo2::text::encoding::ascii.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_ASCII_H)
#define TETENGO2_TEXT_ENCODING_ASCII_H

#include <memory>
#include <stdexcept>
#include <string>

#include <boost/operators.hpp>

#include <tetengo2/detail/base/encoding.h>
#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2 { namespace text { namespace encoding
{
    /*!
        \brief The class for an ASCII encoding.
    */
    class ascii : public encoding<tetengo2::detail::base::encoding>, private boost::equality_comparable<ascii>
    {
    public:
        // types

        //! The base type.
        using base_type = encoding<tetengo2::detail::base::encoding>;

        //! The string type.
        using string_type = std::string;

        //! The encoding detail type.
        using encoding_details_type = tetengo2::detail::base::encoding;


        // constructors and destructors

        /*!
            \brief Creates an ASCII encoding.
        */
        ascii();

        /*!
            \brief Destroys the ASCII encoding.
        */
        virtual ~ascii();


        // functions

        /*!
            \brief Checks whether one ascii encoding is equal to another.

            \param one     One ASCII encoding.
            \param another Another ASCII encoding.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const ascii& one, const ascii& another);

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
