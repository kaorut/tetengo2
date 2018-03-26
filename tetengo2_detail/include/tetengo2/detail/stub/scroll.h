/*! \file
    \brief The definition of tetengo2::detail::stub::scroll.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_SCROLL_H)
#define TETENGO2_DETAIL_STUB_SCROLL_H

#include <cstddef>
#include <memory>
#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>

#include <tetengo2/stdalt.h>


namespace tetengo2::detail::stub {
    /*!
        \brief The class for a detail implementation of a scroll.
    */
    class scroll : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = std::size_t;

        //! The range type.
        using range_type = std::pair<size_type, size_type>;

        //! The scroll bar details type.
        struct scroll_bar_details_type
        {
#if !defined(DOCUMENTATION)
            size_type                       position{};
            std::pair<size_type, size_type> range;
            size_type                       page_size{};
            bool                            enabled;

            scroll_bar_details_type(
                const size_type                   position,
                std::pair<size_type, size_type>&& range,
                const size_type                   page_size,
                const bool                        enabled)
            : position{ position }, range{ std::forward<std::pair<size_type, size_type>>(range) },
              page_size{ page_size }, enabled{ enabled }
            {}
#endif
        };

        //! The scroll bar details pointer type.
        using scroll_bar_details_ptr_type = std::unique_ptr<scroll_bar_details_type>;

        //! The style type.
        enum class style_type
        {
            vertical, //!< The vertical style.
            horizontal, //!< The horizontal style.
        };


        // static functions

        /*!
            \brief Creates a scroll bar.

            \tparam WidgetDetails A detail implementation type of a widget.

            \param widget_details A detail implementation of a widget.
            \param style          A style type.

            \return A unique pointer to a scroll bar.

            \throw std::system_error When a system cursor cannot be created.
        */
        template <typename WidgetDetails>
        static scroll_bar_details_ptr_type
        create_scroll_bar(const WidgetDetails& widget_details, const style_type style)
        {
            boost::ignore_unused(widget_details, style);

            return stdalt::make_unique<scroll_bar_details_type>(0, std::make_pair(0, 100), 10, true);
        }

        /*!
            \brief Returns the position.

            \param details A detail implementation of a scroll bar.

            \return The position.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        static size_type position(const scroll_bar_details_type& details)
        {
            return details.position;
        }

        /*!
            \brief Sets a position.

            \param details  A detail implementation of a scroll bar.
            \param position A position.

            \throw std::system_error When the scroll information cannot be set.
        */
        static void set_position(scroll_bar_details_type& details, const size_type position)
        {
            details.position = position;
        }

        /*!
            \brief Returns the range.

            \param details A detail implementation of a scroll bar.

            \return The range.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        static const range_type& range(const scroll_bar_details_type& details)
        {
            return details.range;
        }

        /*!
            \brief Sets a range.

            \tparam R A range type.

            \param details A detail implementation of a scroll bar.
            \param range   A range.

            \throw std::system_error When the scroll information cannot be set.
        */
        static void set_range(scroll_bar_details_type& details, range_type range)
        {
            details.range = std::move(range);
        }

        /*!
            \brief Returns the page size.

            \param details A detail implementation of a scroll bar.

            \return The page size.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        static size_type page_size(const scroll_bar_details_type& details)
        {
            return details.page_size;
        }

        /*!
            \brief Sets a page size.

            \param details   A detail implementation of a scroll bar.
            \param page_size A page size.

            \throw std::system_error When the scroll information cannot be set.
        */
        static void set_page_size(scroll_bar_details_type& details, const size_type page_size)
        {
            details.page_size = page_size;
        }

        /*!
            \brief Returns the enabled status.

            \param details A detail implementation of a scroll bar.

            \retval true  When the scroll bar is enabled.
            \retval false Otherwise.
        */
        static bool enabled(const scroll_bar_details_type& details)
        {
            return details.enabled;
        }

        /*!
            \brief Sets an enabled status.

            \param details A detail implementation of a scroll bar.
            \param enabled An enable status.
        */
        static void set_enabled(scroll_bar_details_type& details, const bool enabled)
        {
            details.enabled = enabled;
        }


    private:
        // static functions


        // forbidden operations

        scroll() = delete;
    };
}


#endif
