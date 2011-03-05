/*! \file
    \brief The definition of tetengo2::gui::win32::abstract_window.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ABSTRACTWINDOW_H)
#define TETENGO2_GUI_WIN32_ABSTRACTWINDOW_H

//#include <algorithm>
//#include <cassert>
//#include <cstddef>
//#include <stdexcept>
//#include <utility>

//#include <boost/bind.hpp>
//#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp0x.h"
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

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef widget<typename traits_type::base_type> base_type;

        //! The main menu type.
        typedef typename traits_type::main_menu_type main_menu_type;

        //! The window observer set type.
        typedef
            typename traits_type::window_observer_set_type
            window_observer_set_type;


        // constructors and destructor

        /*!
            \brief Destroys the abstract window.
        */
        virtual ~abstract_window()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Activates the abstract window.
        */
        void activate()
        {
            ::SetActiveWindow(handle());
        }

        /*!
            \brief Returns true when the abstract window has a main menu.

            \retval true  When the abstract window has a main menu.
            \retval false Otherwise.
        */
        bool has_main_menu()
        const
        {
            return m_p_main_menu.get() != NULL;
        }

        /*!
            \brief Returns the main menu.

            When the abstract window does not have a main menu, the result is
            undefined.

            \return The main menu.
        */
        main_menu_type& main_menu()
        {
            assert(has_main_menu());

            return *m_p_main_menu;
        }

        /*!
            \brief Returns the main menu.

            When the abstract window does not have a main menu, the result is
            undefined.

            \return The main menu.
        */
        const main_menu_type& main_menu()
        const
        {
            assert(has_main_menu());

            return *m_p_main_menu;
        }

        /*!
            \brief Sets a main menu.

            When p_main_menu is NULL, the currently associated main menu is
            destroyed.

            \param p_main_menu A unique pointer to a main menu.
        */
        void set_main_menu(
            typename cpp0x::unique_ptr<main_menu_type>::type p_main_menu
        )
        {
            if (::SetMenu(handle(), NULL) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't unset the main menu.")
                );
            }
            
            m_p_main_menu = std::move(p_main_menu);
            
            if (m_p_main_menu.get() != NULL)
            {
                assert(m_p_main_menu->details());
                if (
                    ::SetMenu(handle(), &*m_p_main_menu->details()->second) ==
                    0
                )
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't set a main menu.")
                    );
                }
                if (::DrawMenuBar(handle()) == 0)
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
        */
        const window_observer_set_type& window_observer_set()
        const
        {
            return m_window_observer_set;
        }

        /*!
            \brief Returns the window observer set.

            \return The window observer set.
        */
        window_observer_set_type& window_observer_set()
        {
            return m_window_observer_set;
        }

        /*!
            \brief Closes the abstract window.

            \throw std::runtime_error When the abstract window is already
                                      destroyed.
        */
        void close()
        {
            close_impl();
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

            \param message_handler_map A message handler map.
        */
        explicit abstract_window(
            message_handler_map_type&& message_handler_map
        )
        :
        base_type(
            make_message_handler_map(
                std::forward<message_handler_map_type>(message_handler_map)
            )
        ),
        m_p_main_menu(),
        m_window_observer_set()
        {}


    private:
        // static functions

        static bool same_menu(
            const typename main_menu_type::base_type::base_type& menu1,
            ::UINT                                               menu2_id
        )
        {
            return menu1.details()->first == menu2_id;
        }

        static bool same_popup_menu(
            const typename main_menu_type::base_type::base_type& menu1,
            ::HMENU                                              menu2_handle
        )
        {
            if (!menu1.details() || menu2_handle == NULL) return false;
            return &*menu1.details()->second == menu2_handle;
        }


        // variables

        typename cpp0x::unique_ptr<main_menu_type>::type m_p_main_menu;

        window_observer_set_type m_window_observer_set;


        // virtual functions

        virtual void close_impl()
        {
            const ::BOOL result = ::PostMessageW(handle(), WM_CLOSE, 0, 0);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't close the abstract window.")
                );
            }
        }


        // functions

        message_handler_map_type make_message_handler_map(
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            map[WM_COMMAND].push_back(
                boost::bind(&abstract_window::on_command, this, _1, _2)
            );
            map[WM_INITMENUPOPUP].push_back(
                boost::bind(&abstract_window::on_initmenupopup, this, _1, _2)
            );
            map[WM_DESTROY].push_back(
                boost::bind(&abstract_window::on_destroy, this, _1, _2)
            );

            return map;
        }

        boost::optional< ::LRESULT> on_command(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            const ::WORD source = HIWORD(wParam);
            const ::WORD id = LOWORD(wParam);
            if (source == 0)
            {
                if (!has_main_menu()) return boost::optional< ::LRESULT>();

                const typename main_menu_type::recursive_iterator
                found = std::find_if(
                    main_menu().recursive_begin(),
                    main_menu().recursive_end(),
                    boost::bind(same_menu, _1, id)
                );
                if (found == main_menu().recursive_end())
                    return boost::optional< ::LRESULT>();
                found->select();

                return boost::optional< ::LRESULT>(0);
            }

            return boost::optional< ::LRESULT>();
        }

        boost::optional< ::LRESULT> on_initmenupopup(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            const ::HMENU handle = reinterpret_cast< ::HMENU>(wParam);

            if (!has_main_menu()) return boost::optional< ::LRESULT>();

            const typename main_menu_type::recursive_iterator
            found = std::find_if(
                main_menu().recursive_begin(),
                main_menu().recursive_end(),
                boost::bind(same_popup_menu, _1, handle)
            );
            if (found == main_menu().recursive_end())
                return boost::optional< ::LRESULT>();
            found->select();

            return boost::optional< ::LRESULT>(0);
        }

        boost::optional< ::LRESULT> on_destroy(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            if (m_window_observer_set.destroyed().empty())
                return boost::optional< ::LRESULT>();

            m_window_observer_set.destroyed()();

            return boost::optional< ::LRESULT>();
        }


    };


}}}

#endif
