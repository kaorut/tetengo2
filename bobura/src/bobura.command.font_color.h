/*! \file
    \brief The definition of bobura::command::font_color.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FONTCOLOR_H)
#define BOBURA_COMMAND_FONTCOLOR_H

//#include <memory>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a font and color command.
    */
    class font_color : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;

        //! The font and color dialog type.
        typedef boost::mpl::at<dialog_type_list, type::dialog::font_color_dialog>::type font_color_dialog_type;

        //! The dialog base type.
        typedef font_color_dialog_type::base_type dialog_base_type;

        //! The string type.
        typedef font_color_dialog_type::string_type string_type;

        //! The message catalog type.
        typedef font_color_dialog_type::message_catalog_type message_catalog_type;


        // constructors and destructor

        /*!
            \brief Create a font and color command.

            \param message_catalog A message catalog.
        */
        explicit font_color(const message_catalog_type& message_catalog);

        /*!
            \brief Destroys a font and color command.
        */
        ~font_color();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const;


    };


}}


#endif
