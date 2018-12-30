/*! \file
    \brief The definition of tetengo2::detail::windows::scroll.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_SCROLL_H)
#define TETENGO2_DETAIL_WINDOWS_SCROLL_H

#include <memory>

#include <tetengo2/detail/base/scroll.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of a scroll.
    */
    class scroll : public base::scroll
    {
    public:
        // types

        //! The size type.
        using size_type = base::scroll::size_type;

        //! The range type.
        using range_type = base::scroll::range_type;

        //! The scroll bar details type.
        using scroll_bar_details_type = base::scroll::scroll_bar_details_type;

        //! The scroll bar details pointer type.
        using scroll_bar_details_ptr_type = base::scroll::scroll_bar_details_ptr_type;

        //! The style type.
        using style_type = base::scroll::style_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const scroll& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~scroll();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        scroll();


        // virtual functions

        virtual scroll_bar_details_ptr_type
        create_scroll_bar_impl(const gui::widget::widget& widget, style_type style) const override;

        virtual size_type position_impl(const scroll_bar_details_type& details) const override;

        virtual void set_position_impl(scroll_bar_details_type& details, size_type position) const override;

        virtual range_type range_impl(const scroll_bar_details_type& details) const override;

        virtual void set_range_impl(scroll_bar_details_type& details, range_type range) const override;

        virtual size_type page_size_impl(const scroll_bar_details_type& details) const override;

        virtual void set_page_size_impl(scroll_bar_details_type& details, size_type page_size) const override;

        virtual bool enabled_impl(const scroll_bar_details_type& details) const override;

        virtual void set_enabled_impl(scroll_bar_details_type& details, bool enabled) const override;
    };
}


#endif
