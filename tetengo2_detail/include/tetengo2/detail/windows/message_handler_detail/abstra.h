/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::abstract_window.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_ABSTRACTWINDOW_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_ABSTRACTWINDOW_H

#include <algorithm>
#include <string>
#include <system_error>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


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
            boost::ignore_unused(l_param);

            const ::WORD id = LOWORD(w_param);

            if (!abstract_window.has_menu_bar())
                return boost::none;

            using menu_bar_type = typename AbstractWindow::menu_bar_type;
            const typename menu_bar_type::recursive_iterator_type found =
                std::find_if(
                    abstract_window.menu_bar().recursive_begin(),
                    abstract_window.menu_bar().recursive_end(),
                    [id](const typename menu_bar_type::base_type::base_type& menu) { return menu.details().id == id; }
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
            boost::ignore_unused(l_param);

            const auto handle = reinterpret_cast< ::HMENU>(w_param);

            if (!abstract_window.has_menu_bar())
                return boost::none;

            using menu_bar_type = typename AbstractWindow::menu_bar_type;
            const auto found =
                std::find_if(
                    abstract_window.menu_bar().recursive_begin(),
                    abstract_window.menu_bar().recursive_end(),
                    [handle](const typename menu_bar_type::base_type::base_type& popup_menu)
                    {
                        if (!handle)
                            return false;
                        return popup_menu.details().handle.get() == handle;
                    }
                );
            if (found == abstract_window.menu_bar().recursive_end())
                return boost::none;
            found->select();

            return boost::make_optional< ::LRESULT>(0);
        }

        inline std::vector<boost::filesystem::path> make_paths(const ::HDROP drop_handle)
        {
            const auto count = ::DragQueryFileW(drop_handle, 0xFFFFFFFF, nullptr, 0);

            std::vector<boost::filesystem::path> paths{};
            paths.reserve(count);

            for (::UINT i = 0; i < count; ++i)
            {
                const auto length = ::DragQueryFileW(drop_handle, i, nullptr, 0);
                std::vector<wchar_t> path_string(length + 1, 0);

                const auto result =
                    ::DragQueryFileW(drop_handle, i, path_string.data(), static_cast< ::UINT>(path_string.size()));
                if (result == 0)
                {
                    BOOST_THROW_EXCEPTION((
                        std::system_error{
                            std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                            "Can't obtain the dropped file path."
                        }
                    ));
                }

                paths.emplace_back(std::wstring{ path_string.begin(), path_string.begin() + length });
            }

            return paths;
        }

        template <typename AbstractWindow>
        boost::optional< ::LRESULT> on_drop_files(
            AbstractWindow& abstract_window,
            const ::WPARAM  w_param,
            const ::LPARAM  l_param
        )
        {
            boost::ignore_unused(w_param, l_param);

            if (abstract_window.file_drop_observer_set().file_dropped().empty())
                return boost::none;

            const auto paths = make_paths(reinterpret_cast< ::HDROP>(w_param));
            abstract_window.file_drop_observer_set().file_dropped()(paths);
            return boost::make_optional< ::LRESULT>(0);
        }

        template <typename AbstractWindow>
        boost::optional< ::LRESULT> on_close(
            AbstractWindow& abstract_window,
            const ::WPARAM  w_param,
            const ::LPARAM  l_param
        )
        {
            boost::ignore_unused(w_param, l_param);

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
            boost::ignore_unused(w_param, l_param);

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
            boost::ignore_unused(w_param, l_param);

            if (abstract_window.window_observer_set().destroyed().empty())
                return boost::none;

            abstract_window.window_observer_set().destroyed()();

            return boost::none;
        }


    }


}}}}


#endif
#endif
