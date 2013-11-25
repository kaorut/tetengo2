/*! \file
    \brief The definition of tetengo2::gui::widget::dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_DIALOG_H)
#define TETENGO2_GUI_WIDGET_DIALOG_H

//#include <cassert>

//#include <boost/predef.h>

#include "tetengo2.gui.widget.abstract_window.h"
#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a modal dialog.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class dialog : public abstract_window<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef
            abstract_window<typename traits_type::base_type, widget_details_type, message_handler_details_type>
            base_type;

        //! The position type.
        typedef typename base_type::position_type position_type;

        //! The dimension type.
        typedef typename base_type::dimension_type dimension_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The message loop type.
        typedef typename traits_type::message_loop_type message_loop_type;

        //! The message loop break type.
        typedef typename traits_type::message_loop_break_type message_loop_break_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;

        //! The result type.
        enum class result_type
        {
            undecided, //!< The result is not decided yet.
            accepted,  //!< The settings are accepted.
            canceled,  //!< The settings are canceled.
        };


        // constructors and destructor

        /*!
            \brief Creates a dialog.

            \param parent         A parent window.
            \param file_droppable Set true to enable file drop.
        */
        explicit dialog(base_type& parent, const bool file_droppable = false)
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            base_type::scroll_bar_style_type::none,
            file_droppable,
            message_handler_details_type::make_dialog_message_handler_map(*this, message_handler_map_type())
        ),
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        m_result(result_type::undecided),
        m_p_details(
            widget_details_type::template create_dialog<typename base_type::base_type>(&parent, file_droppable)
        )
        {
            initialize_dialog();
        }

        /*!
            \brief Destroys the dialog.
        */
        virtual ~dialog()
        TETENGO2_STDALT_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        result_type result()
        const
        {
            return m_result;
        }

        /*!
            \brief Sets the result.

            \param result A result.
        */
        void set_result(const result_type result)
        {
            if (result == result_type::accepted)
                set_result_impl();
            m_result = result;
        }

        /*!
            \brief Shows the dialog as modal.
        */
        void do_modal()
        {
            do_modal_impl();

            assert(this->has_parent());
            auto& parent_window = dynamic_cast<base_type&>(this->parent());
            parent_window.set_enabled(false);

            this->window_observer_set().destroyed().connect([]() { message_loop_break_type()(0); });
            this->set_position(widget_details_type::template dialog_position<position_type>(*this, parent_window));
            this->set_visible(true);

            message_loop_type(*this)();

            parent_window.set_enabled(true);
            parent_window.activate();
        }


    private:
        // types

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


        // variables

        result_type m_result;

        const details_ptr_type m_p_details;


        // virtual functions

        virtual void set_result_impl()
        {}

        virtual void do_modal_impl()
        {}

        virtual const details_type& details_impl()
        const override
        {
            assert(m_p_details);
            return *m_p_details;
        }

        virtual details_type& details_impl()
        override
        {
            assert(m_p_details);
            return *m_p_details;
        }


        // functions

        void initialize_dialog()
        {
            this->initialize(this);
        }


    };


}}}


#endif
