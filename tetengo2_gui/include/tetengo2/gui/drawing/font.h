/*! \file
    \brief The definition of tetengo2::gui::drawing::font.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_FONT_H)
#define TETENGO2_GUI_DRAWING_FONT_H

#include <memory>

#include <boost/operators.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a font.
   */
    class font : private boost::equality_comparable<font>
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The size type.
        using size_type = tetengo2::type_list::size_type;


        // static functions

        /*!
            \brief Returns the dialog font.

            \return The dialog font.
        */
        static const font& dialog_font();


        // constructors and destructor

        /*!
            \brief Creates a font.

            When family is not installed, the family of the dialog font is set instead.

            \param family    A family.
            \param size      A size.
            \param bold      Whether this font is bold.
            \param italic    Whether this font is italic.
            \param underline Whether this font is underlined.
            \param strikeout Whether this font is striked out.
        */
        font(string_type family, size_type size, bool bold, bool italic, bool underline, bool strikeout);

        /*!
            \brief Copies a font.

            \param another Another font.
        */
        font(const font& another);

        /*!
            \brief Moves a font.

            \param another Another font.
        */
        font(font&& another);

        /*!
            \brief Destroys the font.
        */
        ~font();


        // functions

        /*!
            \brief Checks whether one font is equal to another.

            \param one     One font.
            \param another Another font.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const font& one, const font& another);

        /*!
            \brief Assigns another font.

            \param another Another font.

            \return This object.
        */
        font& operator=(const font& another);

        /*!
            \brief Assigns another font.

            \param another Another font.

            \return This object.
        */
        font& operator=(font&& another);

        /*!
            \brief Returns the family.

            \return The family.
        */
        const string_type& family() const;

        /*!
            \brief Returns the size.

            \return The size.
        */
        size_type size() const;

        /*!
            \brief Returns whether this font is bold.

            \retval true  When this font is bold.
            \retval false Otherwise.
        */
        bool bold() const;

        /*!
            \brief Returns whether this font is italic.

            \retval true  When this font is italic.
            \retval false Otherwise.
        */
        bool italic() const;

        /*!
            \brief Returns whether this font is underlined.

            \retval true  When this font is underlined.
            \retval false Otherwise.
        */
        bool underline() const;

        /*!
            \brief Returns whether this font is striked out.

            \retval true  When this font is striked out.
            \retval false Otherwise.
        */
        bool strikeout() const;


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;
    };
}


#endif
