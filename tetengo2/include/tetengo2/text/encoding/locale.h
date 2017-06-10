/*! \file
    \brief The definition of tetengo2::text::encoding::locale.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_LOCALE_H)
#define TETENGO2_TEXT_ENCODING_LOCALE_H

#include <locale>
#include <memory>
#include <string>

#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2 { namespace text { namespace encoding
{
    /*!
        \brief The class template for an encoding based on a locale.

        \tparam String A string type.
    */
    template <typename String>
    class locale : public encoding<String>
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
            \brief Creates an encoding based on the current locale.
        */
        locale();

        /*!
            \brief Creates an encoding based on a locale.

            \param locale_based_on A locale based on.
        */
        locale(std::locale locale_based_on);

        /*!
            \brief Destroys the encoding based on a locale.
        */
        virtual ~locale();


        // functions

        /*!
            \brief Checks whether one encoding based on a locale is equal to another.

            \tparam S A string type.

            \param one     One encoding based on a locale.
            \param another Another encoding based on a locale.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename S>
        friend bool operator==(const locale<S>& one, const locale<S>& another);

        /*!
            \brief Checks whether one encoding based on a locale is not equal to another.

            \tparam S A string type.

            \param one     One encoding based on a locale.
            \param another Another encoding based on a locale.

            \retval true  When the one is not equal to the other.
            \retval false Otherwise.
        */
        template <typename S>
        friend bool operator!=(const locale<S>& one, const locale<S>& another);

        /*!
            \brief Returns the locale based on.

            \return The locale based on.
        */
        const std::locale& locale_based_on()
        const;


    private:
        // type

        class impl;


        // variables

        std::shared_ptr<impl> m_p_impl;


        // virtual functions

        virtual const std::string& name_impl()
        const override;

        virtual string_type from_pivot_impl(const pivot_type& pivot)
        const override;

        virtual pivot_type to_pivot_impl(const string_type& string)
        const override;


    };


}}}


#endif
