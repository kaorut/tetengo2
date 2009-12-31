/*! \file
    \brief The definition of tetengo2::gui::win32::menu_item.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENUITEM_H)
#define TETENGO2_GUI_WIN32_MENUITEM_H

#include <cstddef>
#include <memory>
//#include <string>

#include <boost/bind.hpp>
//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuObserver.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a menu item.

        \tparam Id           A ID type. It must conform to
                             boost::UnsignedInteger<Id>.
        \tparam Handle       A handle type. It must conform to
                             concept_tetengo2::gui::Handle<Handle>.
        \tparam String       A string type. It must conform to
                             concept_tetengo2::String<String>.
        \tparam Encode       An encoding unary functor type. The types
                             Encode<String, std::wstring> and
                             Encode<std::wstring, String> must conform to
                             boost::UnaryFunction<Encode, String, std::wstring>
                             and
                             boost::UnaryFunction<Encode, std::wstring, String>.
        \tparam MenuObserver A menu observer type. It must conform to
                             concept_tetengo2::gui::MenuObserver<MenuObserver>.
   */
    template <
        typename Id,
        typename Handle,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename MenuObserver
    >
    class menu_item : boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Id>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<String, std::wstring> encode_from_native_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_from_native_type, String, native_string_type
                >
            ));
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_to_native_type, native_string_type, String
                >
            ));
        };
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuObserver<MenuObserver>
        ));


    public:
        // types

        //! The ID type.
        typedef Id id_type;

        //! The handle type.
        typedef Handle handle_type;

        //! The string type.
        typedef String string_type;

        //! The unary functor type for encoding from the native.
        typedef Encode<String, std::wstring> encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef Encode<std::wstring, String> encode_to_native_type;

        //! The menu observer type.
        typedef MenuObserver menu_observer_type;


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

            \retval true  When the menu item is a menu command.
            \retval false Otherwise.
        */
        virtual bool is_command()
        const = 0;

        /*!
            \brief Returns whether the menu item is a popup menu.

            \retval true  When the menu item is a popup menu.
            \retval false Otherwise.
        */
        virtual bool is_popup()
        const = 0;

        /*!
            \brief Returns whether the menu item is a menu separator.

            \retval true  When the menu item is a menu separator.
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

        /*!
            \brief Selects this menu item.
        */
        void select()
        {
            m_menu_selected_handler();
        }

        /*!
            \brief Adds a menu observer.

            \param p_menu_observer An auto pointer to a menu observer.
        */
        void add_menu_observer(
            std::auto_ptr<menu_observer_type> p_menu_observer
        )
        {
            m_menu_selected_handler.connect(
                boost::bind(
                    &menu_observer_type::selected,
                    p_menu_observer.get()
                )
            );

            m_menu_observers.push_back(p_menu_observer);
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
        m_text(text),
        m_menu_observers(),
        m_menu_selected_handler()
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

        boost::ptr_vector<menu_observer_type> m_menu_observers;

        boost::signal<void ()> m_menu_selected_handler;


    };


}}}

#endif
