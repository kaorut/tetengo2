/*! \file
    \brief The definition of tetengo2::gui::widget::dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_DIALOG_H)
#define TETENGO2_GUI_WIDGET_DIALOG_H

#include <cassert>

#include <boost/predef.h>

#include <tetengo2/detail/base/widget.h>
#include <tetengo2/detail/stub/message_handler.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/message/dialog_message_loop.h>
#include <tetengo2/gui/message/message_loop_break.h>
#include <tetengo2/gui/message/window_observer_set.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a modal dialog.
    */
    class dialog : public abstract_window
    {
    public:
        // types

        //! The message loop type.
        using message_loop_type = gui::message::dialog_message_loop;

        //! The message loop break type.
        using message_loop_break_type = gui::message::message_loop_break;

        //! The result type.
        enum class result_type
        {
            undecided, //!< The result is not decided yet.
            accepted, //!< The settings are accepted.
            canceled, //!< The settings are canceled.
        };


        // constructors and destructor

        /*!
            \brief Creates a dialog.

            \param parent         A parent window.
            \param file_droppable Set true to enable file drop.
        */
        explicit dialog(abstract_window& parent, const bool file_droppable = false)
        :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
          abstract_window{ abstract_window::scroll_bar_style_type::none,
                           file_droppable,
                           message_handler_details_type::instance().make_dialog_message_handler_map(
                               *this,
                               message_handler_map_type{}) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
          m_result{ result_type::undecided }, m_p_details{ widget_details().create_dialog(&parent, file_droppable) }
        {
            initialize_dialog();

            parent.child_observer_set().created()(*this);
        }

        /*!
            \brief Destroys the dialog.
        */
        virtual ~dialog() noexcept
        {
            try
            {
                if (this->has_parent())
                    this->parent().child_observer_set().destroying()(*this);
            }
            catch (...)
            {
            }
        }


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        result_type result() const
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
            auto& parent_window = dynamic_cast<abstract_window&>(this->parent());
            parent_window.set_enabled(false);

            this->window_observer_set().closing().connect([this](bool& cancel) { this->on_close_impl(cancel); });
            this->window_observer_set().destroyed().connect([]() { message_loop_break_type{}(0); });
            this->set_position(widget_details().dialog_position(*this, parent_window));
            this->set_visible(true);

            message_loop_type{ *this }();

            parent_window.set_enabled(true);
            parent_window.activate();
        }


    protected:
        // functions

        /*!
            \brief Initializes the dialog.

            This function must be called in the constructor and only in the constructor.
        */
        void initialize_dialog()
        {
            abstract_window::initialize(this);
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        result_type m_result;

        const typename widget_details_type::widget_details_ptr_type m_p_details;


        // virtual functions

        virtual void set_result_impl() {}

        virtual void do_modal_impl() {}

        virtual void on_close_impl(bool&) {}

        virtual const details_type& details_impl() const override
        {
            assert(m_p_details);
            return *static_cast<const details_type*>(m_p_details.get());
        }

        virtual details_type& details_impl() override
        {
            assert(m_p_details);
            return *static_cast<details_type*>(m_p_details.get());
        }
    };
}


#endif
