/*! \file
    \brief The definition of tetengo2::gui::menu_item.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUITEM_H)
#define TETENGO2_GUI_MENUITEM_H

#include <cstddef>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Handle.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class template for a menu item.

        \tparam Id     A ID type. It must conform to
                       boost::UnsignedInteger<Id>.
        \tparam Handle A handle type. It must conform to
                       concept_tetengo2::gui::Handle<Handle>.
        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
   */
    template <typename Id, typename Handle, typename String>
    class menu_item : boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Id>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));


    public:
        // types

        //! The ID type.
        typedef Id id_type;

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
            \brief Returns whether the menu item is a menu separator.

            \retval true  The menu item is a menu separator.
            \retval false Otherwise.
        */
        virtual bool is_separator()
        const = 0;

        /*!
            \brief Returns the ID.

            \return The ID.
        */
        id_type id()
        const
        {
            return m_id;
        }

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
        const string_type& text()
        const
        {
            return m_text;
        }

        /*!
            \brief Sets the text.

            \param text A text.
        */
        void set_text(const string_type& text)
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
        m_id(get_and_increment_id()),
        m_text(text)
        {}


    private:
        // static functions

        static id_type get_and_increment_id()
        {
            static id_type id = 40001;

            return id++;
        }


        // variables

        id_type m_id;

        string_type m_text;


    };


}}

#endif
