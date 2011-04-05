/*! \file
    \brief The definition of tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DIALOG_H)
#define TETENGO2_GUI_WIN32_DIALOG_H

//#include <cassert>
//#include <stdexcept>

#include <boost/bind.hpp>
//#include <boost/optional.hpp>
#include <boost/scope_exit.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.win32.abstract_window.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a modal dialog.
 
        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a
                                      widget.
        \tparam MessageHandlerDetails A detail implementation type of a
                                      message handler.
   */
    template <
        typename Traits,
        typename WidgetDetails,
        typename MessageHandlerDetails
    >
    class dialog :
        public abstract_window<
            typename Traits::base_type, WidgetDetails, MessageHandlerDetails
        >
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
            abstract_window<
                typename traits_type::base_type,
                widget_details_type,
                message_handler_details_type
            > base_type;

        //! The message loop type.
        typedef typename traits_type::message_loop_type message_loop_type;

        //! The message loop break type.
        typedef
            typename traits_type::message_loop_break_type
            message_loop_break_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;


        //! The result type.
        enum result_type
        {
            result_undecided,   //!< The result is not decided yet.
            result_accepted,    //!< The settings are accepted.
            result_canceled,    //!< The settings are canceled.
        };


        // constructors and destructor

        /*!
            \brief Creates a dialog.

            \param parent A parent window.

            \throw std::runtime_error When a dialog cannot be created.
        */
        explicit dialog(base_type& parent)
        :
        base_type(
            message_handler_details_type::make_dialog_message_handler_map(
                *this, message_handler_map_type()
            )
        ),
        m_result(result_undecided),
        m_p_details(
            widget_details_type::create_dialog<typename base_type::base_type>(
                parent
            )
        )
        {
            initialize(this);
        }

        /*!
            \brief Destroys the dialog.
        */
        virtual ~dialog()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Sets the result.

            \param result A result.
        */
        void set_result(const result_type result)
        {
            m_result = result;
        }

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
            \brief Shows the dialog as modal.

            \return The result.
        */
        result_type do_modal()
        {
            assert(has_parent());
            base_type& parent_window = dynamic_cast<base_type&>(parent());
            parent_window.set_enabled(false);
            BOOST_SCOPE_EXIT((&parent_window))
            {
                parent_window.set_enabled(true);
                parent_window.activate();
            } BOOST_SCOPE_EXIT_END;

            window_observer_set().destroyed().connect(
                boost::bind(message_loop_break_type(), 0)
            );
            set_visible(true);

            message_loop_type()();

            return result();
        }


    private:
        // variables

        result_type m_result;

        const details_ptr_type m_p_details;


        // virtual functions

        virtual boost::optional<details_type&> details_impl()
        {
            return boost::optional<details_type&>(*m_p_details);
        }

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return boost::optional<const details_type&>(*m_p_details);
        }


    };


}}}

#endif
