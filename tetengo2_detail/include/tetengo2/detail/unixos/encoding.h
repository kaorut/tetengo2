/*! \file
    \brief The definition of tetengo2::detail::unixos::encoding.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_UNIXOS_ENCODING_H)
#define TETENGO2_DETAIL_UNIXOS_ENCODING_H

#include <memory>


namespace tetengo2 { namespace detail { namespace unixos
{
    /*!
        \brief The class for a detail implementation of an encoding.
    */
    class encoding : public base::encoding
    {
    public:
        // types

        //! The pivot type.
        using pivot_type = base::encoding::pivot_type;

        //! The UTF-8 string type.
        using utf8_string_type = base::encoding::utf8_string_type;

        //! The CP932 string type.
        using cp932_string_type = base::encoding::cp932_string_type;


        // static functions

        /*!
            \brief Returns the instance of the detail implementation.

            \return The instance.
        */
        static const encoding& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementaion.
        */
        virtual ~encoding();


    private:
        // types

        class impl;


        // constructors

        encoding();


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual utf8_string_type pivot_to_utf8_impl(const pivot_type& pivot)
        const override;

        virtual pivot_type utf8_to_pivot_impl(const utf8_string_type& string)
        const override;

        virtual cp932_string_type pivot_to_cp932_impl(const pivot_type& pivot)
        const override;

        virtual pivot_type cp932_to_pivot_impl(const cp932_string_type& string)
        const override;


    };


}}}


#endif
