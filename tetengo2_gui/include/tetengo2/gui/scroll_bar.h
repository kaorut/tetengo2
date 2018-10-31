/*! \file
    \brief The definition of tetengo2::gui::scroll_bar.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_SCROLLBAR_H)
#define TETENGO2_GUI_SCROLLBAR_H

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/scroll_bar_observer_set.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::gui {
    /*!
        \brief The class for a scroll bar.
    */
    class scroll_bar : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = tetengo2::type_list::size_type;

        //! The range type.
        using range_type = std::pair<size_type, size_type>;

        //! The scroll bar observer set type.
        using scroll_bar_observer_set_type = gui::message::scroll_bar_observer_set;

        //! The style type.
        enum class style_type
        {
            vertical, //!< The vertical style.
            horizontal, //!< The horizontal style.
        };


        // constructors and destructor

        /*!
            \brief Creates a scroll bar.

            \param widget A widget.
            \param style  A style.
        */
        scroll_bar(const gui::widget::widget& widget, style_type style);

        /*!
            \brief Destroys the scroll bar.
        */
        ~scroll_bar();


        // functions

        /*!
            \brief Returns the position.

            \return The position.
        */
        size_type position() const;

        /*!
            \brief Sets a position

            The position must be inside the range; i.e., range().first <= position < range().second.

            \param position A position.

            \throw std::out_of_range When the position is outside the range.
        */
        void set_position(size_type position);

        /*!
            \brief Returns the tracking position.

            \return The tracking position.
        */
        size_type tracking_position() const;

        /*!
            \brief Returns the range.

            \return The range.
        */
        range_type range() const;

        /*!
            \brief Sets a range

            The range.first must be smaller than the range.second, and the position must be inside the range;
            i.e., range.first <= position() <= range.second.

            \param range A range.

            \throw std::out_of_range When the position is outside the range.
        */
        void set_range(range_type range);

        /*!
            \brief Returns the page size.

            \return The page size.
        */
        size_type page_size() const;

        /*!
            \brief Sets a page size

            The page size may be larger than the size of the range.

            \param page_size A page size.
        */
        void set_page_size(size_type page_size);

        /*!
            \brief Returns the enabled status.

            \retval true  When the scroll bar is enabled.
            \retval false Otherwise.
        */
        bool enabled() const;

        /*!
            \brief Sets an entabled status.

            \param enabled An enabled status.
        */
        void set_enabled(bool enabled);

        /*!
            \brief Returns the scroll bar observer set.

            \return The scroll bar observer set.
        */
        const scroll_bar_observer_set_type& scroll_bar_observer_set() const;

        /*!
            \brief Returns the scroll bar observer set.

            \return The scroll bar observer set.
        */
        scroll_bar_observer_set_type& scroll_bar_observer_set();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
