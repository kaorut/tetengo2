/*! \file
    \brief The definition of tetengo2::gui::common_dialog::color.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/common_dialog/color.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::common_dialog {
    class color::impl : private boost::noncopyable
    {
    public:
        // types

        using color_type = gui::drawing::color;

        using abstract_window_type = gui::widget::abstract_window;

        using details_type = detail::base::common_dialog::color_dialog_details_type;


        // constructors and destructor

        impl(const tetengo2::stdalt::optional<color_type>& color, abstract_window_type& parent)
        : m_p_details{ detail::gui_detail_impl_set().common_dialog_().create_color_dialog(parent, color) }, m_result{
              color ? *color : color_type{ 0, 0, 0 }
          }
        {}


        // functions

        const color_type& result() const
        {
            return m_result;
        }

        bool do_modal()
        {
            const auto result = detail::gui_detail_impl_set().common_dialog_().show_color_dialog(*m_p_details);
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

        using details_ptr_type = detail::base::common_dialog::color_dialog_details_ptr_type;


        // variables

        details_ptr_type m_p_details;

        color_type m_result;
    };


    color::color(const tetengo2::stdalt::optional<color_type>& color, abstract_window_type& parent)
    : m_p_impl{ std::make_unique<impl>(color, parent) }
    {}

    color::~color() = default;

    const color::color_type& color::result() const
    {
        return m_p_impl->result();
    }

    bool color::do_modal()
    {
        return m_p_impl->do_modal();
    }

    const color::details_type& color::details() const
    {
        return m_p_impl->details();
    }

    color::details_type& color::details()
    {
        return m_p_impl->details();
    }
}
