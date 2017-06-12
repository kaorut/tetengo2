/*! \file
    \brief The definition of tetengo2::text::encoding::polymorphic.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_POLYMORPHIC_H)
#define TETENGO2_TEXT_ENCODING_POLYMORPHIC_H

#include <memory>
#include <string>

#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2 { namespace text { namespace encoding
{
    /*!
        \brief The class template for a polymorphic encoding holder.

        \tparam String A string type.
    */
    template <typename String>
    class polymorphic : public encoding<String>
    {
    public:
        // types

        //! The base type.
        using base_type = encoding<String>;

        //! The pivot type.
        using pivot_type = typename base_type::pivot_type;

        //! The string type.
        using string_type = typename base_type::string_type;


        // constructors and destructor

        /*!
            \brief Creates a polymorphic encoding holder.

            \param p_encoding A unique pointer to an encoding.
        */
        explicit polymorphic(std::unique_ptr<base_type> p_encoding);

        /*!
            \brief Destroys the encoding based on a polymorphic.
        */
        virtual ~polymorphic();


    private:
        // type

        class impl;


        // variables

        std::shared_ptr<impl> m_p_impl;


        // virtual functions

        virtual const std::string& name_impl()
        const override;

        virtual string_type from_pivot_impl(pivot_type pivot)
        const override;

        virtual pivot_type to_pivot_impl(string_type string)
        const override;


    };


}}}


#endif
