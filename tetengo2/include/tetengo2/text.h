/*! \file
    \brief The definition of tetengo2::text.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_H)
#define TETENGO2_TEXT_H


namespace tetengo2 {
    /*!
        \brief The class template for a text value holder.

        \tparam Multibyte A multibyte value type.
        \tparam Wide      A wide value type.
    */
    template <typename Multibyte, typename Wide>
    class text_value_holder
    {
    public:
        // types

        //! The multibyte value type.
        using multibyte_type = Multibyte;

        //! The wide value type.
        using wide_type = Wide;


        // constructors and destructor

        /*!
            \brief Creates a text value holder.

            \param multibyte A multibyte value.
            \param wide      A wide value.
        */
        text_value_holder(const multibyte_type multibyte, const wide_type wide)
        : m_multibyte{ multibyte }, m_wide{ wide }
        {}


        // functions

        /*!
            \brief Returns the multibyte value.

            \return The multibyte value.
        */
        operator multibyte_type() const
        {
            return m_multibyte;
        }

        /*!
            \brief Returns the wide value.

            \return The wide value.
        */
        operator wide_type() const
        {
            return m_wide;
        }


    private:
        // variables

        multibyte_type m_multibyte;

        wide_type m_wide;
    };


    /*!
        \brief Makes a text value holder.

        \tparam Multibyte A multibyte value type.
        \tparam Wide      A wide value type.

        \param multibyte A multibyte value.
        \param wide      A wide value.

        \return A text value holder.
    */
    template <typename Multibyte, typename Wide>
    text_value_holder<Multibyte, Wide> make_text_value_holder(const Multibyte multibyte, const Wide wide)
    {
        return text_value_holder<Multibyte, Wide>{ multibyte, wide };
    }
}


/*!
    \brief Calls tetengo2::make_text_value_holder(). (For internal)

    \param VALUE A value.

    \return A text value holder.
*/
#define TETENGO2_TEXT_(VALUE) tetengo2::make_text_value_holder(VALUE, L##VALUE)

/*!
    \brief Calls tetengo2::make_text_value_holder().

    \param VALUE A value.

    \return A text value holder.
*/
#define TETENGO2_TEXT(VALUE) TETENGO2_TEXT_(VALUE)


#endif
