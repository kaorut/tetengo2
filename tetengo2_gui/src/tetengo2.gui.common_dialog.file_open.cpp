/*! \file
    \brief The definition of tetengo2::gui::common_dialog::file_open.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/common_dialog/file_open.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::common_dialog {
    class file_open::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = file_open::string_type;

        using abstract_window_type = file_open::abstract_window_type;

        using file_filter_type = file_open::file_filter_type;

        using file_filters_type = file_open::file_filters_type;

        using details_type = file_open::details_type;


        // constructors and destructor

        impl(string_type title, file_filters_type file_filters, abstract_window_type& parent)
        : m_p_details{ detail::gui_detail_impl_set().common_dialog_().create_file_open_dialog(
              parent,
              std::move(title),
              std::move(file_filters)) },
          m_result{}
        {}


        // functions

        const tetengo2::stdalt::filesystem::path& result() const
        {
            return m_result;
        }

        bool do_modal()
        {
            const auto result = detail::gui_detail_impl_set().common_dialog_().show_file_open_dialog(*m_p_details);
            if (!result)
                return false;

            m_result = *result;
            return true;
        }

        const details_type& details() const
        {
            return *m_p_details;
        }

        details_type& details()
        {
            return *m_p_details;
        }


    private:
        // types

        using details_ptr_type = detail::base::common_dialog::file_open_dialog_details_ptr_type;


        // variables

        details_ptr_type m_p_details;

        tetengo2::stdalt::filesystem::path m_result;
    };


    file_open::file_open(string_type title, file_filters_type file_filters, abstract_window_type& parent)
    : m_p_impl{ std::make_unique<impl>(std::move(title), std::move(file_filters), parent) }
    {}

    file_open::~file_open() = default;

    const tetengo2::stdalt::filesystem::path& file_open::result() const
    {
        return m_p_impl->result();
    }

    bool file_open::do_modal()
    {
        return m_p_impl->do_modal();
    }

    const file_open::details_type& file_open::details() const
    {
        return m_p_impl->details();
    }

    file_open::details_type& file_open::details()
    {
        return m_p_impl->details();
    }
}
