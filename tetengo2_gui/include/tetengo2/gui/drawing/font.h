/*! \file
    \brief The definition of tetengo2::gui::drawing::font.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_FONT_H)
#define TETENGO2_GUI_DRAWING_FONT_H

#include <boost/operators.hpp>


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a font.

        \tparam String         A string type.
        \tparam Size           A size type.
        \tparam DrawingDetails A detail implementation type of a drawing.
   */
    template <typename String, typename Size, typename DrawingDetails>
    class font : private boost::equality_comparable<font<String, Size, DrawingDetails>>
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The size type.
        using size_type = Size;

        //! The drawing details type.
        using drawing_details_type = DrawingDetails;


        // static functions

        /*!
            \brief Returns the dialog font.

            \return The dialog font.
        */
        static const font& dialog_font()
        {
            static const font singleton{ drawing_details_type::template make_dialog_font<font>() };
            return singleton;
        }


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
        font(
            string_type     family,
            const size_type size,
            const bool      bold,
            const bool      italic,
            const bool      underline,
            const bool      strikeout
        )
        :
        m_family(std::move(family)),
        m_size(size),
        m_bold(bold),
        m_italic(italic),
        m_underline(underline),
        m_strikeout(strikeout)
        {}


        // functions

        /*!
            \brief Checks whether one font is equal to another.

            \param one     One font.
            \param another Another font.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const font& one, const font& another)
        {
            return
                one.m_family == another.m_family &&
                one.m_size == another.m_size &&
                one.m_bold == another.m_bold &&
                one.m_italic == another.m_italic &&
                one.m_underline == another.m_underline &&
                one.m_strikeout == another.m_strikeout;
        }

        /*!
            \brief Returns the family.

            \return The family.
        */
        const string_type& family()
        const
        {
            return m_family;
        }

        /*!
            \brief Returns the size.

            \return The size.
        */
        size_type size()
        const
        {
            return m_size;
        }

        /*!
            \brief Returns whether this font is bold.

            \retval true  When this font is bold.
            \retval false Otherwise.
        */
        bool bold()
        const
        {
            return m_bold;
        }

        /*!
            \brief Returns whether this font is italic.

            \retval true  When this font is italic.
            \retval false Otherwise.
        */
        bool italic()
        const
        {
            return m_italic;
        }

        /*!
            \brief Returns whether this font is underlined.

            \retval true  When this font is underlined.
            \retval false Otherwise.
        */
        bool underline()
        const
        {
            return m_underline;
        }

        /*!
            \brief Returns whether this font is striked out.

            \retval true  When this font is striked out.
            \retval false Otherwise.
        */
        bool strikeout()
        const
        {
            return m_strikeout;
        }


    private:
        // variables

        string_type m_family;

        size_type m_size;

        bool m_bold;

        bool m_italic;

        bool m_underline;

        bool m_strikeout;


    };


}}}


#endif
