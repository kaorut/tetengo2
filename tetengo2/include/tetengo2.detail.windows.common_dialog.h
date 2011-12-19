/*! \file
    \brief The definition of tetengo2::detail::windows::common_dialog.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H)
#define TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H

#include <algorithm>
#include <cstddef>
#include <iterator>
//#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
//#include <utility>
#include <vector>

#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <atlbase.h>
#include <ObjBase.h>
#include <ShObjIdl.h>
#include <ShTypes.h>

#include "tetengo2.cpp11.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        typedef std::pair<std::wstring, std::wstring> native_filter_type;

        typedef std::vector<native_filter_type> native_filters_type;


        // functions

        template <typename String, typename Encoder>
        native_filter_type to_native_filter(
            const std::pair<String, String>& filter,
            const Encoder&                   encoder
        )
        {
            return native_filter_type(
                encoder.encode(filter.first), encoder.encode(filter.second)
            );
        }

        template <typename String, typename Encoder>
        native_filters_type to_native_filters(
            const std::vector<std::pair<String, String>>& filters,
            const Encoder&                                encoder
        )
        {
            native_filters_type native_filters;
            native_filters.reserve(filters.size());

            std::transform(
                filters.begin(),
                filters.end(),
                std::back_inserter(native_filters),
                TETENGO2_CPP11_BIND(
                    to_native_filter<String, Encoder>,
                    tetengo2::cpp11::placeholders_1(),
                    tetengo2::cpp11::cref(encoder)
                )
            );

            return native_filters;
        }

        ::COMDLG_FILTERSPEC to_filterspec(
            const native_filter_type& native_filter
        )
        {
            ::COMDLG_FILTERSPEC filterspec = {};

            filterspec.pszName = native_filter.first.c_str();
            filterspec.pszSpec = native_filter.second.c_str();

            return filterspec;
        }

        std::vector< ::COMDLG_FILTERSPEC> to_filterspecs(
            const native_filters_type& native_filters
        )
        {
            std::vector< ::COMDLG_FILTERSPEC> filterspecs;
            filterspecs.reserve(native_filters.size());

            std::transform(
                native_filters.begin(),
                native_filters.end(),
                std::back_inserter(filterspecs),
                to_filterspec
            );

            return filterspecs;
        }


    }
#endif

    /*!
        \brief The class for a detail implementation of dialogs.
    */
    class common_dialog
    {
    public:
        // types

        //! The file open dialog details type.
        typedef
            std::tuple<
                ATL::CComPtr< ::IFileOpenDialog>,
                ::HWND,
                std::wstring,
                detail::native_filters_type
            >
            file_open_dialog_details_type;

        //! The file open dialog details pointer type.
        typedef std::unique_ptr<file_open_dialog_details_type>
            file_open_dialog_details_ptr_type;

        
        // static functions

        /*!
            \brief Creates a file open dialog.

            \tparam Widget  A widget type.
            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param parent  A parent widget.
            \param title   A title.
            \param filters A file filters.
                           Each element is a pair of a label and a file
                           pattern.
            \param encoder An encoder.

            \return A unique pointer to a file open dialog.
        */
        template <typename Widget, typename String, typename Encoder>
        static file_open_dialog_details_ptr_type create_file_open_dialog(
            Widget&                                       parent,
            const String&                                 title,
            const std::vector<std::pair<String, String>>& filters,
            const Encoder&                                encoder
        )
        {
            ATL::CComPtr< ::IFileOpenDialog> p_dialog;

            const ::HRESULT creation_result =
                p_dialog.CoCreateInstance(__uuidof(::FileOpenDialog));
            if (!SUCCEEDED(creation_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a file open dialog.")
                );
            }

            return tetengo2::make_unique<file_open_dialog_details_type>(
                p_dialog,
                parent.details()->first.get(),
                encoder.encode(title),
                detail::to_native_filters(filters, encoder)
            );
        }

        /*!
            \brief Shows a file open dialog and return a path.

            \tparam Path A path type.
            \tparam Encoder An encoder type.

            \param dialog  A file open dialog.
            \param encoder An encoder.

            \return The path.
        */
        template <typename Path, typename Encoder>
        static Path show_file_open_dialog(
            file_open_dialog_details_type& dialog,
            const Encoder&                 encoder
        )
        {
            std::get<0>(dialog)->SetTitle(std::get<2>(dialog).c_str());

            std::vector< ::COMDLG_FILTERSPEC> filterspecs =
                detail::to_filterspecs(std::get<3>(dialog));
            std::get<0>(dialog)->SetFileTypes(
                static_cast< ::UINT>(filterspecs.size()), filterspecs.data()
            );

            const ::HRESULT showing_result =
                std::get<0>(dialog)->Show(std::get<1>(dialog));
            if (!SUCCEEDED(showing_result))
                return Path();

            ATL::CComPtr< ::IShellItem> p_item;
            const ::HRESULT result_result =
                std::get<0>(dialog)->GetResult(&p_item);
            if (!SUCCEEDED(result_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get the result.")
                );
            }

            wchar_t* file_name = NULL;
            const ::HRESULT file_title_result =
                p_item->GetDisplayName(SIGDN_FILESYSPATH, &file_name);
            if (!SUCCEEDED(file_title_result))
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get the file path.")
                );
            }
            BOOST_SCOPE_EXIT((file_name))
            {
                ::CoTaskMemFree(file_name);
            } BOOST_SCOPE_EXIT_END;

            return Path(encoder.decode(file_name));
        }


    };


}}}


#endif
