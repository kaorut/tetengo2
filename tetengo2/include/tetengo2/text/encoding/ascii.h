/*! \file
    \brief The definition of tetengo2::text::encoding::ascii.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_ASCII_H)
#define TETENGO2_TEXT_ENCODING_ASCII_H

#include <memory>
#include <string>

#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2::text::encoding {
    /*!
        \brief The class for an ASCII encoding.
    */
    class ascii : public encoding<std::string>
    {
    public:
        // types

        //! The base type.
        using base_type = encoding<std::string>;

        //! The pivot type.
        using pivot_type = typename base_type::pivot_type;

        //! The string type.
        using string_type = base_type::string_type;


        // constructors and destructors

        /*!
            \brief Creates an ASCII encoding.
        */
        ascii();

        /*!
            \brief Destroys the ASCII encoding.
        */
        virtual ~ascii();


    private:
        // types

        class impl;


        // variables

        const std::shared_ptr<impl> m_p_impl;


        // virtual functions

        virtual const std::string& name_impl() const override;

        virtual string_type from_pivot_impl(pivot_type pivot) const override;

        virtual pivot_type to_pivot_impl(string_type string) const override;
    };
}


#endif
