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
            \brief Checks whether one font and color is equal to another.

            \param one     One font and color.
            \param another Another font and color.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const font_color& one, const font_color& another)
        {
            return one.m_font == another.m_font && one.m_color == another.m_color;
        }

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

        \tparam FontColor A font and color type.
    */
    template <typename FontColor>
    class font_color_set : private boost::equality_comparable<font_color_set<FontColor>>
    {
    public:
        // types

        //! The font and color type.
        typedef FontColor font_color_type;


        // constructors and destructor

        /*!
            \brief Creates a font and color set.

            \tparam FC1 A font and color type #1.

            \param company_line_name A font and color set for the company and line names.
        */
        template <typename FC1>
        font_color_set(FC1&& company_line_name)
        :
        m_company_line_name(std::forward<FC1>(company_line_name))
        {}


        // functions

        /*!
            \brief Checks whether one font and color set is equal to another.

            \param one     One font and color set.
            \param another Another font and color set.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const font_color_set& one, const font_color_set& another)
        {
            return one.m_company_line_name == another.m_company_line_name;
        }

        /*!
            \brief Returns the font and color set for the company and line names.

            \return The font and color set for the company and line names.
        */
        const font_color_type& company_line_name()
        const
        {
            return m_company_line_name;
        }


    private:
        // variables

        font_color_type m_company_line_name;


    };


}}


#endif
