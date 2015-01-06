/*! \file
    \brief The definition of tetengo2::gui::alert.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ALERT_H)
#define TETENGO2_GUI_ALERT_H

#include <exception>
#include <stdexcept>
#include <string>
#include <system_error>

#include <boost/exception/all.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for an alert.

        \tparam UiEncoder        An encoder type for the user interface.
        \tparam ExceptionEncoder An encoder type for the exception.
        \tparam AlertDetails     A detail implementation type of an alert.
    */
    template <typename UiEncoder, typename ExceptionEncoder, typename AlertDetails>
    class alert
    {
    public:
        // types

        //! The encoder type for the user interface.
        using ui_encoder_type = UiEncoder;

        //! The encoder type for exceptions.
        using exception_encoder_type = ExceptionEncoder;

        //! The detail implemetation type of an alert.
        using alert_details_type = AlertDetails;

        //! The widget handle type.
        using widget_handle_type = typename alert_details_type::widget_handle_type;


        // constructors and destructor

        /*!
            \brief Creates an alert.

            \param widget_handle     A widget handle.
        */
        explicit alert(const widget_handle_type widget_handle = nullptr)
        :
        m_widget_handle(alert_details_type::root_ancestor_widget_handle(widget_handle))
        {}


        // functions

        /*!
            \brief Alerts a fatal error.

            \param exception An exception.
        */
        void operator()(const boost::exception& exception)
        const
        {
            try
            {
                const char* const* const p_file = boost::get_error_info<boost::throw_file>(exception);
                const int* const p_line = boost::get_error_info<boost::throw_line>(exception);

                const std::system_error* const p_system_error = dynamic_cast<const std::system_error*>(&exception);
                if (p_system_error)
                {
                    const std::string what{ p_system_error->std::runtime_error::what() };
                    auto message = p_system_error->code().message();
                    if (!what.empty())
                        message += std::string{ ": " } +what;
                    alert_details_type::show_task_dialog(
                        m_widget_handle,
                        string_type{ TETENGO2_TEXT("Alert") },
                        string_type{ TETENGO2_TEXT("std::system_error") },
                        exception_encoder().decode(message),
                        p_file ?
                            exception_encoder().decode(*p_file) : string_type{ TETENGO2_TEXT("Unknown Source File") },
                        p_line ? *p_line : 0,
                        ui_encoder()
                    );
                    return;
                }

                const std::exception* const p_std_exception = dynamic_cast<const std::exception*>(&exception);
                if (p_std_exception)
                {
                    alert_details_type::show_task_dialog(
                        m_widget_handle,
                        string_type{ TETENGO2_TEXT("Alert") },
                        exception_encoder().decode(typeid(*p_std_exception).name()),
                        exception_encoder().decode(p_std_exception->what()),
                        p_file ?
                            exception_encoder().decode(*p_file) : string_type{ TETENGO2_TEXT("Unknown Source File") },
                        p_line ? *p_line : 0,
                        ui_encoder()
                    );
                    return;
                }

                alert_details_type::show_task_dialog(
                    m_widget_handle,
                    string_type{ TETENGO2_TEXT("Alert") },
                    exception_encoder().decode(typeid(exception).name()),
                    exception_encoder().decode(boost::diagnostic_information(exception)),
                    p_file ?
                        exception_encoder().decode(*p_file) : string_type{ TETENGO2_TEXT("Unknown Source File") },
                    p_line ? *p_line : 0,
                    ui_encoder()
                );
            }
            catch (...)
            {}
        }

        /*!
            \brief Alerts a fatal error.

            \param exception An exception.
        */
        void operator()(const std::exception& exception = std::runtime_error("Unknown Error!"))
        const
        {
            try
            {
                alert_details_type::show_task_dialog(
                    m_widget_handle,
                    string_type{ TETENGO2_TEXT("Alert") },
                    exception_encoder().decode(typeid(exception).name()),
                    exception_encoder().decode(exception.what()),
                    string_type{ TETENGO2_TEXT("Unknown Source File") },
                    0,
                    ui_encoder()
                );
            }
            catch (...)
            {}
        }


    private:
        // types

        using string_type = typename ui_encoder_type::internal_string_type;


        // static functions

        static const ui_encoder_type& ui_encoder()
        {
            static const ui_encoder_type singleton{};
            return singleton;
        }

        static const exception_encoder_type& exception_encoder()
        {
            static const exception_encoder_type singleton{};
            return singleton;
        }


        // variables

        const widget_handle_type m_widget_handle;


    };


}}


#endif
