/*! \file
    \brief The definition of tetengo2::gui::menu_item.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUITEM_H)
#define TETENGO2_GUI_MENUITEM_H

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Handle.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class template for a menu item.

        \tparam Handle A handle type. It must conform to
                       concept_tetengo2::gui::Handle<Handle>.
        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
   */
    template <typename Handle, typename String>
    class menu_item : boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));


    public:
        // types

        //! The handle type
        typedef Handle handle_type;

        //! The string type
        typedef String string_type;


        // constructors and destructor

        /*!
            \brief Destroys the menu item.
        */
        virtual ~menu_item()
        throw ()
        {}


        // functions

        /*!
            \brief Returns whether the menu item is a menu command.

            \retval true  The menu item is a menu command.
            \retval false Otherwise.
        */
        virtual bool is_command()
        const = 0;

        /*!
            \brief Returns whether the menu item is a popup menu.

            \retval true  The menu item is a popup menu.
            \retval false Otherwise.
        */
        virtual bool is_popup()
        const = 0;

        /*!
            \brief Returns the handle.

            If the value of is_popup() is false, this function may return
            NULL.

            \return The handle.
        */
        virtual handle_type handle()
        const = 0;

        /*!
            \brief Returns the text.

            \return The text.
        */
        virtual const string_type& text()
        const
        {
            return m_text;
        }

        /*!
            \brief Sets the text.

            \param text A text.
        */
        virtual void set_text(const string_type& text)
        {
            m_text = text;
        }


    protected:
        // constructors

        /*!
            \brief Creates a menu item.

            \param text A text.
        */
        menu_item(const string_type& text)
        :
        m_text(text)
        {}


    private:
        // variables

        string_type m_text;


    };


}}

#endif
