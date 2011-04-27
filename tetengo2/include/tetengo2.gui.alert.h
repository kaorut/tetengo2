/*! \file
    \brief The definition of tetengo2::gui::alert.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ALERT_H)
#define TETENGO2_GUI_ALERT_H

#include <cstddef>
#include <exception>
#include <functional>
#include <stdexcept>

#include <boost/exception/all.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.text.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The unary functor class template for an alert.

        \tparam UiEncoder        An encoder type for the user interface.
        \tparam ExceptionEncoder An encoder type for the user interface.
        \tparam AlertDetails     A detail implementation type of an alert.
    */
    template <
        typename UiEncoder,
        typename ExceptionEncoder,
        typename AlertDetails
    >
    class alert :
        public std::unary_function<std::exception, void>
    {
    public:
        // types

        //! The encoder type for the user interface.
        typedef UiEncoder ui_encoder_type;

        //! The encoder type for exceptions.
        typedef ExceptionEncoder exception_encoder_type;

        //! The detail implemetation type of an alert.
        typedef AlertDetails alert_details_type;

        //! The widget handle type.
        typedef
            typename alert_details_type::widget_handle_type
            widget_handle_type;


        // constructors

        /*!
            \brief Creates an alert.

            \param widget_handle     A widget handle.
        */
        explicit alert(const widget_handle_type widget_handle = NULL)
        TETENGO2_CPP0X_NOEXCEPT
        :
        m_widget_handle(
            alert_details_type::root_ancestor_widget_handle(widget_handle)
        )
        {}


        // functions

        /*!
            \brief Alerts a fatal error.

            \param exception An exception.
        */
        void operator()(const boost::exception& exception)
        const
        TETENGO2_CPP0X_NOEXCEPT
        {
            try
            {
                const std::exception* const p_std_exception =
                    dynamic_cast<const std::exception*>(&exception);
                if (p_std_exception != NULL)
                {
                    const char* const* const p_file =
                        boost::get_error_info<boost::throw_file>(
                            exception
                        );
                    const int* const p_line =
                        boost::get_error_info<boost::throw_line>(
                            exception
                        );
                    const char* const* const p_function =
                        boost::get_error_info<boost::throw_function>(
                            exception
                        );
                    alert_details_type::show_task_dialog(
                        m_widget_handle,
                        string_type(TETENGO2_TEXT("Alert")),
                        exception_encoder().decode(
                            typeid(*p_std_exception).name()
                        ),
                        exception_encoder().decode(p_std_exception->what()),
                        p_file != NULL ?
                            exception_encoder().decode(*p_file) :
                            string_type(),
                        p_line != NULL ? *p_line : 0,
                        p_function != NULL ?
                            exception_encoder().decode(*p_function) :
                            string_type(),
                        ui_encoder()
                    );
                }
                else
                {
                    alert_details_type::show_task_dialog(
                        m_widget_handle,
                        string_type(TETENGO2_TEXT("Alert")),
                        exception_encoder().decode(typeid(exception).name()),
                        exception_encoder().decode(
                            boost::diagnostic_information(exception)
                        ),
                        string_type(),
                        0,
                        string_type(),
                        ui_encoder()
                    );
                }
            }
            catch (...)
            {}
        }

        /*!
            \brief Alerts a fatal error.

            \param exception An exception.
        */
        void operator()(
            const std::exception& exception =
                std::runtime_error("Unknown Error!")
        )
        const
        TETENGO2_CPP0X_NOEXCEPT
        {
            try
            {
                alert_details_type::show_task_dialog(
                    m_widget_handle,
                    string_type(TETENGO2_TEXT("Alert")),
                    ui_encoder().encode(
                        exception_encoder().decode(typeid(exception).name())
                    ),
                    ui_encoder().encode(
                        exception_encoder().decode(exception.what())
                    ),
                    string_type(),
                    0,
                    string_type(),
                    ui_encoder()
                );
            }
            catch (...)
            {}
        }


    private:
        // types

        typedef typename ui_encoder_type::internal_string_type string_type;


        // static functions

        static const ui_encoder_type& ui_encoder()
        {
            static const ui_encoder_type singleton;
            return singleton;
        }

        static const exception_encoder_type& exception_encoder()
        {
            static const exception_encoder_type singleton;
            return singleton;
        }


        // variables

        const widget_handle_type m_widget_handle;


    };


}}


#endif
