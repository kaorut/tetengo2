/*! \file
    \brief The definition of tetengo2::gui::common_dialog::font.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/common_dialog/font.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::common_dialog {
    class font::impl : private boost::noncopyable
    {
    public:
        // types

        using font_type = font::font_type;

        using abstract_window_type = font::abstract_window_type;

        using details_type = font::details_type;


        // constructors and destructor

        impl(const tetengo2::stdalt::optional<font_type>& font, abstract_window_type& parent)
        : m_p_details{ detail::gui_detail_impl_set().common_dialog_().create_font_dialog(parent, font) }, m_result{
              font ? *font : font_type::dialog_font()
          }
        {}


        // functions

        const font_type& result() const
        {
            return m_result;
        }

        bool do_modal()
        {
            const auto result = detail::gui_detail_impl_set().common_dialog_().show_font_dialog(*m_p_details);
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

        using details_ptr_type = detail::base::common_dialog::font_dialog_details_ptr_type;


        // variables

        details_ptr_type m_p_details;

        font_type m_result;
    };


    font::font(const tetengo2::stdalt::optional<font_type>& font, abstract_window_type& parent)
    : m_p_impl{ std::make_unique<impl>(font, parent) }
    {}

    font::~font() = default;

    const font::font_type& font::result() const
    {
        return m_p_impl->result();
    }

    bool font::do_modal()
    {
        return m_p_impl->do_modal();
    }

    const font::details_type& font::details() const
    {
        return m_p_impl->details();
    }

    font::details_type& font::details()
    {
        return m_p_impl->details();
    }
}
