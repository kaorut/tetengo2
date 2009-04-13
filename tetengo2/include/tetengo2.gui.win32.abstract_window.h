/*! \file
    \brief The definition of tetengo2::gui::win32::abstract_window.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ABSTRACTWINDOW_H)
#define TETENGO2_GUI_WIN32_ABSTRACTWINDOW_H

#include <cassert>
//#include <cstddef>
//#include <memory>
#include <stdexcept>

#include <boost/bind.hpp>
//#include <boost/concept_check.hpp>
#include <boost/signal.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.MainMenu.h"
#include "concept_tetengo2.gui.WindowObserver.h"
#include "concept_tetengo2.gui.Widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for an abstract window for Win32 platforms.
 
        \tparam Widget         A widget type. It must conform to
                               concept_tetengo2::gui::Widget<Widget>.
        \tparam MainMenu       A main menu type. It must conform to
                               concept_tetengo2::gui::MainMenu<MainMenu>.
        \tparam WindowObserver A abstract_window observer type. It must conform to
                               concept_tetengo2::gui::WindowObserver<WindowObserver>.
   */
    template <typename Widget, typename MainMenu, typename WindowObserver>
    class abstract_window : public Widget
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Widget<Widget>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MainMenu<MainMenu>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::WindowObserver<WindowObserver>
        ));


    public:
        // types

        //! The widget type.
        typedef Widget widget_type;

        //! The handle type.
        typedef typename widget_type::handle_type handle_type;

        //! The canvas type.
        typedef typename widget_type::canvas_type canvas_type;

        //! The alerting unary functor type.
        typedef typename widget_type::alert_type alert_type;

        //! The difference type.
        typedef typename widget_type::difference_type difference_type;

        //! The size type.
        typedef typename widget_type::size_type size_type;

        //! The position type.
        typedef typename widget_type::position_type position_type;

        //! The dimension type.
        typedef typename widget_type::dimension_type dimension_type;

        //! The string type.
        typedef typename widget_type::string_type string_type;

        //! The unary functor type for encoding from the native.
        typedef
            typename widget_type::encode_from_native_type
            encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef
            typename widget_type::encode_to_native_type
            encode_to_native_type;

        //! The font type.
        typedef typename widget_type::font_type font_type;

        //! The child type.
        typedef typename widget_type::child_type child_type;

        //! The paint observer type.
        typedef typename widget_type::paint_observer_type paint_observer_type;

        //! The mouse observer type.
        typedef typename widget_type::mouse_observer_type mouse_observer_type;

        //! The main menu type.
        typedef MainMenu main_menu_type;

        //! The abstract_window observer type.
        typedef WindowObserver window_observer_type;


        // constructors and destructor

        /*!
            \brief Destroys the abstract window.
        */
        virtual ~abstract_window()
        throw ()
        {}


        // functions

        /*!
            \brief Activates the abstract window.

            \throw std::runtime_error When the abstract window is already
                                      destroyed.
        */
        virtual void activate()
        {
            check_destroyed();

            ::BringWindowToTop(this->handle());
        }

        /*!
            \brief Returns true when the abstract window has a main menu.

            \retval true  When the abstract window has a main menu.
            \retval false Otherwise.

            \throw std::runtime_error When the abstract window is already
                                      destroyed.
        */
        virtual bool has_main_menu()
        const
        {
            check_destroyed();

            return m_p_main_menu.get() != NULL;
        }

        /*!
            \brief Returns the main menu.

            When the abstract window does not have a main menu, the result is
            undefined.

            \return The main menu.

            \throw std::runtime_error When the abstract window is already
                                      destroyed.
        */
        virtual main_menu_type& main_menu()
        {
            check_destroyed();

            assert(has_main_menu());

            return *m_p_main_menu;
        }

        /*!
            \brief Returns the main menu.

            When the abstract window does not have a main menu, the result is
            undefined.

            \return The main menu.

            \throw std::runtime_error When the abstract window is already
                                      destroyed.
        */
        virtual const main_menu_type& main_menu()
        const
        {
            check_destroyed();

            assert(has_main_menu());

            return *m_p_main_menu;
        }

        /*!
            \brief Sets a main menu.

            When p_main_menu is NULL, the currently associated main menu is
            destroyed.

            \param p_main_menu An auto pointer to a main menu.

            \throw std::runtime_error When the abstract window is already
                                      destroyed.
        */
        virtual void set_main_menu(std::auto_ptr<main_menu_type> p_main_menu)
        {
            check_destroyed();

            if (::SetMenu(this->handle(), NULL) == 0)
                throw std::runtime_error("Can't unset the main menu.");
            
            m_p_main_menu = p_main_menu;
            
            if (m_p_main_menu.get() != NULL)
            {
                if (::SetMenu(this->handle(), m_p_main_menu->handle()) == 0)
                    throw std::runtime_error("Can't set a main menu.");
                if (::DrawMenuBar(this->handle()) == 0)
                    throw std::runtime_error("Can't draw the main menu.");
            }
        }

        /*!
            \brief Adds an abstract window observer.

            \param p_window_observer An auto pointer to an abstract window observer.

            \throw std::runtime_error When the abstract window is already
                                      destroyed.
        */
        virtual void add_window_observer(
            std::auto_ptr<window_observer_type> p_window_observer
        )
        {
            check_destroyed();

            m_window_destroyed_handler.connect(
                boost::bind(
                    &typename window_observer_type::destroyed,
                    p_window_observer.get()
                )
            );

            m_window_observers.push_back(p_window_observer);
        }

        /*!
            \brief Closes the abstract window.

            \throw std::runtime_error When the abstract window is already
                                      destroyed.
        */
        virtual void close()
        {
            check_destroyed();

            const ::BOOL result =
                ::PostMessageW(this->handle(), WM_CLOSE, 0, 0);
            if (result == 0)
                throw std::runtime_error("Can't close the abstract window.");
        }


    protected:
        // static functions

        /*!
            \brief Returns whether the window class is registered.

            \param window_class_name A window class name.
            \param instance_handle   An instance handle.

            \retval true  When the window class is registered.
            \retval false Otherwise.
        */
        static bool window_class_is_registered(
            const string_type& window_class_name,
            const ::HINSTANCE  instance_handle
        )
        {
            ::WNDCLASSEXW window_class;
            const ::BOOL result = ::GetClassInfoExW(
                instance_handle, window_class_name.c_str(), &window_class
            );

            return result != 0;
        }

        // constructors

        /*!
            \brief Creates an abstract window.
        */
        abstract_window()
        :
        widget_type(),
        m_p_main_menu(),
        m_window_observers(),
        m_window_destroyed_handler()
        {}

        /*!
            \brief Creates an abstract window.

            \param parent A parent window.
        */
        abstract_window(const abstract_window& parent)
        :
        widget_type(parent),
        m_p_main_menu(),
        m_window_observers(),
        m_window_destroyed_handler()
        {}


        // functions

        /*!
            \brief Dispatches the abstract window messages.

            \param uMsg                       A message.
            \param wParam                     A word-sized parameter.
            \param lParam                     A long-sized parameter.
            \param p_default_window_procedure A pointer to a default abstract
                                              window procedure.

            \return The result code.
        */
        virtual ::LRESULT window_procedure(
            const ::UINT    uMsg,
            const ::WPARAM  wParam,
            const ::LPARAM  lParam,
            const ::WNDPROC p_default_window_procedure
        )
        {
            switch (uMsg)
            {
            case WM_COMMAND:
                {
                    const ::WORD source = HIWORD(wParam);
                    const ::WORD id = LOWORD(wParam);
                    if (source == 0)
                    {
                        if (!has_main_menu()) break;

                        typename main_menu_type::menu_item_type* const
                        p_found = main_menu().find_by_id(id);
                        if (p_found == NULL) break;
                        p_found->select();
                        return 0;
                    }

                    break;
                }
            case WM_INITMENUPOPUP:
                {
                    if (!has_main_menu()) break;

                    const ::HMENU handle = reinterpret_cast< ::HMENU>(wParam);
                    typename main_menu_type::menu_item_type* const
                    p_found = main_menu().find_by_handle(handle);
                    if (p_found == NULL) break;
                    p_found->select();
                    return 0;
                }
            case WM_DESTROY:
                {
                    if (m_window_observers.empty()) break;

                    m_window_destroyed_handler();
                    break;
                }
            }
            return this->widget_type::window_procedure(
                uMsg, wParam, lParam, p_default_window_procedure
            );
        }


    private:
        // variables

        std::auto_ptr<main_menu_type> m_p_main_menu;

        boost::ptr_vector<window_observer_type> m_window_observers;

        boost::signal<void ()> m_window_destroyed_handler;


    };


}}}

#endif
