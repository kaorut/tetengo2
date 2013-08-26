/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::abstract_window.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_ABSTRACTWINDOW_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_ABSTRACTWINDOW_H

#include <algorithm>

#include <boost/optional.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.utility.h"


namespace tetengo2 { namespace detail { namespace windows { namespace message_handler_detail
{
    namespace abstract_window
    {
        template <typename AbstractWindow>
        boost::optional< ::LRESULT> on_command(
            AbstractWindow& abstract_window,
            const ::WPARAM  w_param,
            const ::LPARAM  l_param
        )
        {
            suppress_unused_variable_warning(l_param);

            const ::WORD id = LOWORD(w_param);

            if (!abstract_window.has_menu_bar())
                return boost::none;

            typedef typename AbstractWindow::menu_bar_type menu_bar_type;
            const typename menu_bar_type::recursive_iterator_type found =
                std::find_if(
                    abstract_window.menu_bar().recursive_begin(),
                    abstract_window.menu_bar().recursive_end(),
                    [id](const typename menu_bar_type::base_type::base_type& menu) { return menu.details()->id == id; }
                );
            if (found == abstract_window.menu_bar().recursive_end())
                return boost::none;
            found->select();

            return boost::make_optional< ::LRESULT>(0);
        }

        template <typename AbstractWindow>
        boost::optional< ::LRESULT> on_initmenupopup(
            AbstractWindow& abstract_window,
            const ::WPARAM  w_param,
            const ::LPARAM  l_param
        )
        {
            suppress_unused_variable_warning(l_param);

            const auto handle = reinterpret_cast< ::HMENU>(w_param);

            if (!abstract_window.has_menu_bar())
                return boost::none;

            typedef typename AbstractWindow::menu_bar_type menu_bar_type;
            const auto found =
                std::find_if(
                    abstract_window.menu_bar().recursive_begin(),
                    abstract_window.menu_bar().recursive_end(),
                    [handle](const typename menu_bar_type::base_type::base_type& popup_menu)
                    {
                        if (!popup_menu.details() || !handle)
                            return false;
                        return popup_menu.details()->handle.get() == handle;
                    }
                );
            if (found == abstract_window.menu_bar().recursive_end())
                return boost::none;
            found->select();

            return boost::make_optional< ::LRESULT>(0);
        }

        template <typename AbstractWindow>
        boost::optional< ::LRESULT> on_drop_files(
            AbstractWindow& abstract_window,
            const ::WPARAM  w_param,
            const ::LPARAM  l_param
        )
        {
            suppress_unused_variable_warning(w_param, l_param);

            if (abstract_window.file_drop_observer_set().file_dropped().empty())
                return boost::none;

            abstract_window.file_drop_observer_set().file_dropped();
            return boost::make_optional< ::LRESULT>(0);
        }

        template <typename AbstractWindow>
        boost::optional< ::LRESULT> on_close(
            AbstractWindow& abstract_window,
            const ::WPARAM  w_param,
            const ::LPARAM  l_param
        )
        {
            suppress_unused_variable_warning(w_param, l_param);

            if (abstract_window.window_observer_set().closing().empty())
                return boost::none;

            auto cancel = false;
            abstract_window.window_observer_set().closing()(cancel);
            return boost::make_optional< ::LRESULT>(cancel, 0);
        }

        template <typename AbstractWindow>
        boost::optional< ::LRESULT> on_query_end_session(
            AbstractWindow& abstract_window,
            const ::WPARAM  w_param,
            const ::LPARAM  l_param
        )
        {
            suppress_unused_variable_warning(w_param, l_param);

            if (abstract_window.window_observer_set().closing().empty())
                return boost::none;

            auto cancel = false;
            abstract_window.window_observer_set().closing()(cancel);
            return boost::make_optional< ::LRESULT>(cancel, FALSE);
        }

        template <typename AbstractWindow>
        boost::optional< ::LRESULT> on_destroy(
            AbstractWindow& abstract_window,
            const ::WPARAM  w_param,
            const ::LPARAM  l_param
        )
        {
            suppress_unused_variable_warning(w_param, l_param);

            if (abstract_window.window_observer_set().destroyed().empty())
                return boost::none;

            abstract_window.window_observer_set().destroyed()();

            return boost::none;
        }


    }


}}}}


#endif
#endif
