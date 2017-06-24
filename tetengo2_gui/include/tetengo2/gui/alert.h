/*! \file
    \brief The definition of tetengo2::gui::alert.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ALERT_H)
#define TETENGO2_GUI_ALERT_H

#include <exception>
#include <stdexcept>
#include <string>
#include <system_error>

#include <boost/core/noncopyable.hpp>
#include <boost/exception/all.hpp>

#include <tetengo2/detail/base/alert.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class for an alert.
    */
    class alert : private boost::noncopyable
    {
    public:
        // types

        //! The detail implemetation type of an alert.
        using alert_details_type = detail::base::alert;

        //! The widget handle type.
        using widget_handle_type = alert_details_type::widget_handle_type;


        // constructors and destructor

        /*!
            \brief Creates an alert.

            \param widget_handle A widget handle.
            \param alert_details A detail implementation of an alert.
        */
        alert(const widget_handle_type widget_handle, const alert_details_type& alert_details)
        :
        m_widget_handle(alert_details.root_ancestor_widget_handle(widget_handle)),
        m_alert_details(alert_details)
        {}

        /*!
            \brief Creates an alert.

            \param alert_details A detail implementation of an alert.
        */
        explicit alert(const alert_details_type& alert_details)
        :
        m_widget_handle(alert_details.root_ancestor_widget_handle(nullptr)),
        m_alert_details(alert_details)
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
                    m_alert_details.show_task_dialog(
                        m_widget_handle,
                        string_type{ TETENGO2_TEXT("Alert") },
                        string_type{ TETENGO2_TEXT("std::system_error") },
                        exception_encoder().decode(message),
                        p_file ?
                            exception_encoder().decode(*p_file) : string_type{ TETENGO2_TEXT("Unknown Source File") },
                        p_line ? *p_line : 0
                    );
                    return;
                }

                const std::exception* const p_std_exception = dynamic_cast<const std::exception*>(&exception);
                if (p_std_exception)
                {
                    m_alert_details.show_task_dialog(
                        m_widget_handle,
                        string_type{ TETENGO2_TEXT("Alert") },
                        exception_encoder().decode(typeid(*p_std_exception).name()),
                        exception_encoder().decode(p_std_exception->what()),
                        p_file ?
                            exception_encoder().decode(*p_file) : string_type{ TETENGO2_TEXT("Unknown Source File") },
                        p_line ? *p_line : 0
                    );
                    return;
                }

                m_alert_details.show_task_dialog(
                    m_widget_handle,
                    string_type{ TETENGO2_TEXT("Alert") },
                    exception_encoder().decode(typeid(exception).name()),
                    exception_encoder().decode(boost::diagnostic_information(exception)),
                    p_file ?
                        exception_encoder().decode(*p_file) : string_type{ TETENGO2_TEXT("Unknown Source File") },
                    p_line ? *p_line : 0
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
                m_alert_details.show_task_dialog(
                    m_widget_handle,
                    string_type{ TETENGO2_TEXT("Alert") },
                    exception_encoder().decode(typeid(exception).name()),
                    exception_encoder().decode(exception.what()),
                    string_type{ TETENGO2_TEXT("Unknown Source File") },
                    0
                );
            }
            catch (...)
            {}
        }


    private:
        // types

        using string_type = type_list::string_type;

        using exception_encoder_type =
            text::encoder<type_list::internal_encoding_type, text::encoding::locale<std::string>>;


        // static functions

        static const exception_encoder_type& exception_encoder()
        {
            static const exception_encoder_type singleton{
                type_list::internal_encoding_type{}, text::encoding::locale<std::string>{}
            };
            return singleton;
        }


        // variables

        const widget_handle_type m_widget_handle;

        const alert_details_type& m_alert_details;


    };


}}


#endif
