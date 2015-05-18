/*! \file
    \brief The definition of tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TABFRAME_H)
#define TETENGO2_GUI_WIDGET_TABFRAME_H

#include <tetengo2/gui/widget/custom_control.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a tab frame.

        \tparam Traits              A traits type.
        \tparam DetailsTraits       A detail implementation type traits.
        \tparam MouseCaptureDetails A detail implementation type of a mouse capture.
    */
    template <
        typename Traits,
        typename DetailsTraits,
        typename MouseCaptureDetails
    >
    class tab_frame : public custom_control<Traits, DetailsTraits, MouseCaptureDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The mouse capture details type.
        using mouse_capture_details_type = MouseCaptureDetails;

        //! The base type.
        using base_type = custom_control<traits_type, details_traits_type, mouse_capture_details_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type::base_type;


        // constructors and destructor

        /*!
            \brief Creates a tab frame.

            \param parent A parent widget.
        */
        explicit tab_frame(widget_type& parent)
        :
        base_type(parent, false, base_type::scroll_bar_style_type::none)
        {
            initialize_tab_frame(*this);
        }

        /*!
            \brief Destroys the tab frame.
        */
        virtual ~tab_frame()
        = default;


    private:
        // static functions

        static void initialize_tab_frame(tab_frame& /*tab_frame_*/)
        {

        }


    };


}}}


#endif
