/*! \file
    \brief The definition of tetengo2::gui::menu_command.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUCOMMAND_H)
#define TETENGO2_GUI_MENUCOMMAND_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.String.h"
#include "tetengo2.gui.menu_item.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a menu command.

        \tparam String  A string type. It must conform to
                        concept_tetengo2::String<String>.
        \tparam Command A command type. It must conform to
                        concept_tetengo2::String<String>.
   */
    template <typename String, typename Command>
    class menu_command : public menu_item<String>
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<Command>));


    public:
        // types

        //! The command type
        typedef Command command_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command.

            \param text    A text.
            \param command A command.
        */
        menu_command(const string_type& text, const command_type& command)
        :
        menu_item(text),
        m_command(command)
        {}

        /*!
            \brief Destroys the menu command.
        */
        virtual ~menu_command()
        throw ()
        {}


        // functions

        // The document will be derived from
        // tetengo2::gui::menu_item::is_command.
        virtual bool is_command()
        const
        {
            return true;
        }

        // The document will be derived from
        // tetengo2::gui::menu_item::is_popup.
        virtual bool is_popup()
        const
        {
            return false;
        }

        /*!
            \brief Returns the command.

            \return The command.
        */
        virtual const command_type& command()
        const
        {
            return m_command;
        }

        /*!
            \brief Sets the command.

            \param text A command.
        */
        virtual void set_command(const command_type& command)
        {
            m_command = command;
        }


    private:
        // variables

        command_type m_command;


    };


}}

#endif
