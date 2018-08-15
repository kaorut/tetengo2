/*! \file
    \brief The definition of tetengo2::detail::base::scroll.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_SCROLL_H)
#define TETENGO2_DETAIL_BASE_SCROLL_H

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a scroll.
    */
    class scroll : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = type_list::size_type;

        //! The range type.
        using range_type = std::pair<size_type, size_type>;

        //! The scroll bar details type.
        struct scroll_bar_details_type
        {
            /*!
                \brief Destroys the scroll bar details.
            */
            virtual ~scroll_bar_details_type();
        };

        //! The scroll bar details pointer type.
        using scroll_bar_details_ptr_type = std::unique_ptr<scroll_bar_details_type>;

        //! The style type.
        enum class style_type
        {
            vertical, //!< The vertical style.
            horizontal, //!< The horizontal style.
        };


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~scroll();


        // functions

        /*!
            \brief Creates a scroll bar.

            \param widget A widget.
            \param style  A style.

            \return A unique pointer to a scroll bar.

            \throw std::system_error When a system cursor cannot be created.
        */
        scroll_bar_details_ptr_type create_scroll_bar(const gui::widget::widget& widget, style_type style) const;

        /*!
            \brief Returns the position.

            \param details A detail implementation of a scroll bar.

            \return The position.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        size_type position(const scroll_bar_details_type& details) const;

        /*!
            \brief Sets a position.

            \param details  A detail implementation of a scroll bar.
            \param position A position.

            \throw std::system_error When the scroll information cannot be set.
        */
        void set_position(scroll_bar_details_type& details, size_type position) const;

        /*!
            \brief Returns the range.

            \param details A detail implementation of a scroll bar.

            \return The range.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        range_type range(const scroll_bar_details_type& details) const;

        /*!
            \brief Sets a range.

            \param details A detail implementation of a scroll bar.
            \param range   A range.

            \throw std::system_error When the scroll information cannot be set.
        */
        void set_range(scroll_bar_details_type& details, range_type range) const;

        /*!
            \brief Returns the page size.

            \param details A detail implementation of a scroll bar.

            \return The page size.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        size_type page_size(const scroll_bar_details_type& details) const;

        /*!
            \brief Sets a page size.

            \param details   A detail implementation of a scroll bar.
            \param page_size A page size.

            \throw std::system_error When the scroll information cannot be set.
        */
        void set_page_size(scroll_bar_details_type& details, size_type page_size) const;

        /*!
            \brief Returns the enabled status.

            \param details A detail implementation of a scroll bar.

            \retval true  When the scroll bar is enabled.
            \retval false Otherwise.
        */
        bool enabled(const scroll_bar_details_type& details) const;

        /*!
            \brief Sets an enabled status.

            \param details A detail implementation of a scroll bar.
            \param enabled An enable status.
        */
        void set_enabled(scroll_bar_details_type& details, bool enabled) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        scroll();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual scroll_bar_details_ptr_type
        create_scroll_bar_impl(const gui::widget::widget& widget, style_type style) const = 0;

        virtual size_type position_impl(const scroll_bar_details_type& details) const = 0;

        virtual void set_position_impl(scroll_bar_details_type& details, size_type position) const = 0;

        virtual range_type range_impl(const scroll_bar_details_type& details) const = 0;

        virtual void set_range_impl(scroll_bar_details_type& details, range_type range) const = 0;

        virtual size_type page_size_impl(const scroll_bar_details_type& details) const = 0;

        virtual void set_page_size_impl(scroll_bar_details_type& details, size_type page_size) const = 0;

        virtual bool enabled_impl(const scroll_bar_details_type& details) const = 0;

        virtual void set_enabled_impl(scroll_bar_details_type& details, bool enabled) const = 0;
    };
}


#endif
