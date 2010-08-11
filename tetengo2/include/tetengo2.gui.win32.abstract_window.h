/*! \file
    \brief The definition of tetengo2::gui::win32::abstract_window.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ABSTRACTWINDOW_H)
#define TETENGO2_GUI_WIN32_ABSTRACTWINDOW_H

//#include <algorithm>
//#include <cassert>
//#include <cstddef>
#include <functional>
//#include <memory>
//#include <stdexcept>

#include <boost/bind.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>

#include "tetengo2.gui.win32.widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for an abstract window for Win32 platforms.
 
        \tparam Traits A traits type.
   */
    template <typename Traits>
    class abstract_window : public widget<typename Traits::base_type>
    {
    public:
        // types

        //! \return The traits type.
        typedef Traits traits_type;

        //! \return The base type.
        typedef widget<typename traits_type::base_type> base_type;

        //! \return The main menu type.
        typedef typename traits_type::main_menu_type main_menu_type;

        //! \return The window observer set type.
        typedef
            typename traits_type::window_observer_set_type
            window_observer_set_type;


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
            \brief Returns the window observer set.

            \return The window observer set.

            \throw std::runtime_error When the abstract window is already
                                      destroyed.
        */
        virtual const window_observer_set_type& window_observer_set()
        const
        {
            check_destroyed();

            return m_window_observer_set;
        }

        /*!
            \brief Returns the window observer set.

            \return The window observer set.

            \throw std::runtime_error When the abstract window is already
                                      destroyed.
        */
        virtual window_observer_set_type& window_observer_set()
        {
            check_destroyed();

            return m_window_observer_set;
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
        m_window_observer_set()
        {}

        /*!
            \brief Creates an abstract window.

            \param parent A parent window.
        */
        explicit abstract_window(abstract_window& parent)
        :
        base_type(parent),
        m_p_main_menu(),
        m_window_observer_set()
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
                    if (m_window_observer_set.destroyed().empty()) break;

                    m_window_observer_set.destroyed()();
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

        window_observer_set_type m_window_observer_set;


    };


}}}

#endif
