/*! \file
    \brief The definition of bobura::font_color_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_FONTCOLORDIALOG_H)
#define BOBURA_FONTCOLORDIALOG_H

#include <memory>
#include <stdexcept>
#include <utility>

#include <tetengo2.cpp11.h>


namespace bobura
{
    /*!
        \brief The class template for the font and color dialog.

        \tparam Dialog         A dialog type.
        \tparam MessageCatalog A message catalog type.
        \tparam IntSize        An integer size type.
        \tparam Font           A font type.
        \tparam PointSize      A point size type.
        \tparam Color          A color type.
    */
    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    class font_color_dialog : public Dialog
    {
    public:
        // types

        //! The base type.
        typedef Dialog base_type;

        //! The abstract window type.
        typedef typename base_type::base_type abstract_window_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The integer size type.
        typedef IntSize int_size_type;

        //! The font type.
        typedef Font font_type;

        //! The point size type.
        typedef PointSize point_size_type;

        //! The color type.
        typedef Color color_type;

        //! The font and color type.
        typedef std::pair<const font_type&, const color_type&> font_color_type;


        // constructors and destructor

        /*!
            \brief Creates a font and color dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        font_color_dialog(abstract_window_type& parent, const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the font and color dialog.
        */
        virtual ~font_color_dialog()
        TETENGO2_CPP11_NOEXCEPT;


        // functions

        /*!
            \brief Returns the color of the background.

            \return The color of the background.

            \throw std::logic_error When the color has not been set.
        */
        const color_type& background()
        const;

        /*!
            \brief Sets a color of the background.

            \param color A color.
        */
        void set_background(const color_type& color);

        /*!
            \brief Returns the font and color of the company and the line names.

            \return The font and color of the company and the line names.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type company_line_name()
        const;

        /*!
            \brief Sets a font and color of the company and the line names.

            \param font  A font.
            \param color A color.
        */
        void set_company_line_name(const font_type& font, const color_type& color);

        /*!
            \brief Returns the font and color of the note.

            \return The font and color of the note.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type note()
        const;

        /*!
            \brief Sets a font and color of the note.

            \param font  A font.
            \param color A color.
        */
        void set_note(const font_type& font, const color_type& color);

        /*!
            \brief Returns the font and color of the time lines.

            \return The font and color of the time lines.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type time_line()
        const;

        /*!
            \brief Sets a font and color of the time lines.

            \param font  A font.
            \param color A color.
        */
        void set_time_line(const font_type& font, const color_type& color);

        /*!
            \brief Returns the font and color of the local stations.

            \return The font and color of the local stations.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type local_station()
        const;

        /*!
            \brief Sets a font and color of the local stations.

            \param font  A font.
            \param color A color.
        */
        void set_local_station(const font_type& font, const color_type& color);

        /*!
            \brief Returns the font and color of the principal stations.

            \return The font and color of the principal stations.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type principal_station()
        const;

        /*!
            \brief Sets a font and color of the principal stations.

            \param font  A font.
            \param color A color.
        */
        void set_principal_station(const font_type& font, const color_type& color);

        /*!
            \brief Returns the font and color of the local terminal stations.

            \return The font and color of the local terminal stations.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type local_terminal_station()
        const;

        /*!
            \brief Sets a font and color of the local terminal stations.

            \param font  A font.
            \param color A color.
        */
        void set_local_terminal_station(const font_type& font, const color_type& color);

        /*!
            \brief Returns the font and color of the principal terminal stations.

            \return The font and color of the principal terminal stations.

            \throw std::logic_error When the font and color have not been set.
        */
        font_color_type principal_terminal_station()
        const;

        /*!
            \brief Sets a font and color of the principal terminal stations.

            \param font  A font.
            \param color A color.
        */
        void set_principal_terminal_station(const font_type& font, const color_type& color);

        /*!
            \brief Returns the font of the train names.

            \return The font of the train names.

            \throw std::logic_error When the font has not been set.
        */
        const font_type& train_name()
        const;

        /*!
            \brief Sets a font of the train names.

            \param font  A font.
        */
        void set_train_name(const font_type& font);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void do_modal_impl()
        override;


    };


}


#endif
