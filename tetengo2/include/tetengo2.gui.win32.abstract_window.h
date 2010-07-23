/*! \file
    \brief The definition of tetengo2::gui::win32::abstract_window.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ABSTRACTWINDOW_H)
#define TETENGO2_GUI_WIN32_ABSTRACTWINDOW_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>

#include <boost/bind.hpp>
#include <boost/signal.hpp>
#include <boost/throw_exception.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for an abstract window for Win32 platforms.
 
        \tparam Widget         A widget type.
        \tparam MainMenu       A main menu type.
        \tparam WindowObserver A abstract_window observer type.
   */
    template <typename Widget, typename MainMenu, typename WindowObserver>
    class abstract_window : public Widget
    {
    public:
        // types

        //! \return The base type.
        typedef Widget base_type;

        //! \copydoc tetengo2::gui::win32::widget::handle_type
        typedef typename base_type::handle_type handle_type;

        //! \copydoc tetengo2::gui::win32::widget::canvas_type
        typedef typename base_type::canvas_type canvas_type;

        //! \copydoc tetengo2::gui::win32::widget::alert_type
        typedef typename base_type::alert_type alert_type;

        //! \copydoc tetengo2::gui::win32::widget::difference_type
        typedef typename base_type::difference_type difference_type;

        //! \copydoc tetengo2::gui::win32::widget::size_type
        typedef typename base_type::size_type size_type;

        //! \copydoc tetengo2::gui::win32::widget::position_type
        typedef typename base_type::position_type position_type;

        //! \copydoc tetengo2::gui::win32::widget::dimension_type
        typedef typename base_type::dimension_type dimension_type;

        //! \copydoc tetengo2::gui::win32::widget::string_type
        typedef typename base_type::string_type string_type;

        //! \copydoc tetengo2::gui::win32::widget::encoder_type
        typedef typename base_type::encoder_type encoder_type;

        //! \copydoc tetengo2::gui::win32::widget::font_type
        typedef typename base_type::font_type font_type;

        //! \copydoc tetengo2::gui::win32::widget::child_type
        typedef typename base_type::child_type child_type;

        //! \copydoc tetengo2::gui::win32::widget::paint_observer_type
        typedef typename base_type::paint_observer_type paint_observer_type;

        //! \copydoc tetengo2::gui::win32::widget::mouse_observer_type
        typedef typename base_type::mouse_observer_type mouse_observer_type;

        //! \return The main menu type.
        typedef MainMenu main_menu_type;

        //! \return The abstract window observer type.
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
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't unset the main menu.")
                );
            }
            
            m_p_main_menu = p_main_menu;
            
            if (m_p_main_menu.get() != NULL)
            {
                if (::SetMenu(this->handle(), m_p_main_menu->handle()) == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't set a main menu.")
                    );
                }
                if (::DrawMenuBar(this->handle()) == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't draw the main menu.")
                    );
                }
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
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't close the abstract window.")
                );
            }
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
        base_type(),
        m_p_main_menu(),
        m_window_observers(),
        m_window_destroyed_handler()
        {}

        /*!
            \brief Creates an abstract window.

            \param parent A parent window.
        */
        explicit abstract_window(abstract_window& parent)
        :
        base_type(parent),
        m_p_main_menu(),
        m_window_observers(),
        m_window_destroyed_handler()
        {}


        // functions

        //! \copydoc tetengo2::gui::win32::widget::window_procedure
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

                        const typename main_menu_type::recursive_iterator
                        found = std::find_if(
                            main_menu().recursive_begin(),
                            main_menu().recursive_end(),
                            boost::bind(
                                std::equal_to<
                                    typename main_menu_type::id_type
                                >(),
                                boost::bind(
                                    &main_menu_type::base_type::id, _1
                                ),
                                id
                            )
                        );
                        if (found == main_menu().recursive_end()) break;
                        found->select();

                        return 0;
                    }

                    break;
                }
            case WM_INITMENUPOPUP:
                {
                    const ::HMENU handle = reinterpret_cast< ::HMENU>(wParam);

                    if (!has_main_menu()) break;

                    const typename main_menu_type::recursive_iterator
                    found = std::find_if(
                        main_menu().recursive_begin(),
                        main_menu().recursive_end(),
                        boost::bind(
                            std::equal_to<
                                typename main_menu_type::handle_type
                            >(),
                            boost::bind(
                                &main_menu_type::base_type::base_type::handle,
                                _1
                            ),
                            handle
                        )
                    );
                    if (found == main_menu().recursive_end()) break;
                    found->select();

                    return 0;
                }
            case WM_DESTROY:
                {
                    if (m_window_observers.empty()) break;

                    m_window_destroyed_handler();
                    break;
                }
            }
            return this->base_type::window_procedure(
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
