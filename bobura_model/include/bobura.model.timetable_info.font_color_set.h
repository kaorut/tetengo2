/*! \file
    \brief The definition of bobura::model::timetable_info::font_color_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_FONTCOLORSET_H)
#define BOBURA_MODEL_TIMETABLEINFO_FONTCOLORSET_H

#include <utility>

#include <boost/operators.hpp>


namespace bobura { namespace model { namespace timetable_info
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

            \param font  A font.
            \param color A color.
        */
        font_color(font_type font, color_type color)
        :
        m_font(std::move(font)),
        m_color(std::move(color))
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

        //! The font type.
        typedef typename font_color_type::font_type font_type;

        //! The color type.
        typedef typename font_color_type::color_type color_type;


        // static functions

        /*!
            \brief Returns the default font and color set.

            \return The default font and color set.
        */
        static const font_color_set& default_()
        {
            static auto singleton = make_default();
            return singleton;
        }


        // constructors and destructor

        /*!
            \brief Creates a font and color set.

            \param background                 A color for the background.
            \param company_line_name          A font and color for the company and line names.
            \param note                       A font and color for the note.
            \param time_line                  A font and color for the time line.
            \param local_station              A font and color for the local station.
            \param principal_station          A font and color for the principal station.
            \param local_terminal_station     A font and color for the local terminal station.
            \param principal_terminal_station A font and color for the principal terminal station.
            \param train_name                 A font for the train name.
        */
        font_color_set(
            color_type      background,
            font_color_type company_line_name,
            font_color_type note,
            font_color_type time_line,
            font_color_type local_station,
            font_color_type principal_station,
            font_color_type local_terminal_station,
            font_color_type principal_terminal_station,
            font_type       train_name
        )
        :
        m_background(std::move(background)),
        m_company_line_name(std::move(company_line_name)),
        m_note(std::move(note)),
        m_time_line(std::move(time_line)),
        m_local_station(std::move(local_station)),
        m_principal_station(std::move(principal_station)),
        m_local_terminal_station(std::move(local_terminal_station)),
        m_principal_terminal_station(std::move(principal_terminal_station)),
        m_train_name(std::move(train_name))
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
            return
                one.m_background == another.m_background &&
                one.m_company_line_name == another.m_company_line_name &&
                one.m_note == another.m_note &&
                one.m_time_line == another.m_time_line &&
                one.m_local_station == another.m_local_station &&
                one.m_principal_station == another.m_principal_station &&
                one.m_local_terminal_station == another.m_local_terminal_station &&
                one.m_principal_terminal_station == another.m_principal_terminal_station &&
                one.m_train_name == another.m_train_name;
        }

        /*!
            \brief Returns the color set for the background.

            \return The color set for the background.
        */
        const color_type& background()
        const
        {
            return m_background;
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

        /*!
            \brief Returns the font and color for the note.

            \return The font and color for the note.
        */
        const font_color_type& note()
        const
        {
            return m_note;
        }

        /*!
            \brief Returns the font and color for the time line.

            \return The font and color for the time line.
        */
        const font_color_type& time_line()
        const
        {
            return m_time_line;
        }

        /*!
            \brief Returns the font and color for the local station.

            \return The font and color for the local station.
        */
        const font_color_type& local_station()
        const
        {
            return m_local_station;
        }

        /*!
            \brief Returns the font and color for the principal station.

            \return The font and color for the principal station.
        */
        const font_color_type& principal_station()
        const
        {
            return m_principal_station;
        }

        /*!
            \brief Returns the font and color for the local terminal station.

            \return The font and color for the local terminal station.
        */
        const font_color_type& local_terminal_station()
        const
        {
            return m_local_terminal_station;
        }

        /*!
            \brief Returns the font and color for the principal terminal station.

            \return The font and color for the principal terminal station.
        */
        const font_color_type& principal_terminal_station()
        const
        {
            return m_principal_terminal_station;
        }

        /*!
            \brief Returns the font for the train name.

            \return The font for the train name.
        */
        const font_type& train_name()
        const
        {
            return m_train_name;
        }


    private:
        // static functions

        static font_color_set make_default()
        {
            auto default_font = font_type::dialog_font();
            font_type default_line_name_font(
                default_font.family(),
                default_font.size() * 2,
                default_font.bold(),
                default_font.italic(),
                default_font.underline(),
                default_font.strikeout()
            );

            color_type default_back_color(0xF8, 0xFF, 0xF0);

            font_color_type default_line_name_font_color(
                std::move(default_line_name_font), color_type(0x40, 0x40, 0x40)
            );
            font_color_type default_note_font_color(default_font, color_type(0x40, 0x40, 0x40));
            font_color_type default_time_line_font_color(default_font, color_type(0x80, 0x80, 0x80));
            font_color_type default_local_station_font_color(default_font, color_type(0xA0, 0xA0, 0xA0));
            font_color_type default_principal_station_font_color(default_font, color_type(0x40, 0x40, 0xA0));
            font_color_type default_local_terminal_station_font_color(
                default_font, color_type(0xA0, 0x40, 0x40)
            );
            font_color_type default_principal_terminal_station_font_color(
                default_font, color_type(0x00, 0x00, 0x00)
            );

            return
                font_color_set(
                    std::move(default_back_color),
                    std::move(default_line_name_font_color),
                    std::move(default_note_font_color),
                    std::move(default_time_line_font_color),
                    std::move(default_local_station_font_color),
                    std::move(default_principal_station_font_color),
                    std::move(default_local_terminal_station_font_color),
                    std::move(default_principal_terminal_station_font_color),
                    std::move(default_font)
                );
        }


        // variables

        color_type m_background;

        font_color_type m_company_line_name;

        font_color_type m_note;

        font_color_type m_time_line;

        font_color_type m_local_station;

        font_color_type m_principal_station;

        font_color_type m_local_terminal_station;

        font_color_type m_principal_terminal_station;

        font_type m_train_name;


    };


}}}


#endif
