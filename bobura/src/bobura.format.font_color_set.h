/*! \file
    \brief The definition of bobura::format::font_color_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_FORMAT_FONTCOLORSET_H)
#define BOBURA_FORMAT_FONTCOLORSET_H

#include <utility>

#include <boost/operators.hpp>


namespace bobura { namespace format
{
    /*!
        \brief The class template for a font and color.

        \tparam Font  A font type.
        \tparam Color A color type.
    */
    template <typename Font, typename Color>
    class font_color : private boost::equality_comparable<font_color<Font, Color>>
    {
    public:
        // types

        //! The font type.
        typedef Font font_type;

        //! The color type.
        typedef Color color_type;


        // constructors and destructor

        /*!
            \brief Creates a font and color.

            \tparam F A font type.
            \tparam C A color type.

            \param font  A font.
            \param color A color.
        */
        template <typename F, typename C>
        font_color(F&& font, C&& color)
        :
        m_font(std::forward<F>(font)),
        m_color(std::forward<C>(color))
        {}


        // functions

        /*!
            \brief Returns the font.

            \return The font.
        */
        const font_type& font()
        const
        {
            return m_font;
        }

        /*!
            \brief Returns the color.

            \return The color.
        */
        const color_type& color()
        const
        {
            return m_color;
        }


    private:
        // variables

        font_type m_font;

        color_type m_color;


    };


    /*!
        \brief The class template for a font and color set.

        \tparam Font  A font type.
        \tparam Color A color type.
    */
    template <typename Font, typename Color>
    class font_color_set
    {
    public:
        // types

        //! The font type.
        typedef Font font_type;

        //! The color type.
        typedef Color color_type;


        // constructors and destructor

        /*!
            \brief Creates a font and color set.
        */
        font_color_set()
        {}


        // functions


    private:
        // types


        // variables


    };


}}


#endif
