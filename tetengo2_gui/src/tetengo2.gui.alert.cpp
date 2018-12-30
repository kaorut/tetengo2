/*!
    \brief The definition of tetengo2::gui::alert.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
#include <system_error>
#include <typeinfo>

#include <boost/core/noncopyable.hpp>
#include <boost/exception/all.hpp>

#include <tetengo2/detail/base/alert.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/alert.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui {
    class alert::impl : private boost::noncopyable
    {
    public:
        // types

        using widget_handle_type = alert::widget_handle_type;


        // constructors and destructor

        explicit impl(const widget_handle_type widget_handle)
        : m_widget_handle{ detail::gui_detail_impl_set().alert_().root_ancestor_widget_handle(widget_handle) }
        {}

        impl() : m_widget_handle{ detail::gui_detail_impl_set().alert_().root_ancestor_widget_handle(nullptr) } {}


        // functions

        void operator_paren(const boost::exception& exception) const
        {
            try
            {
                const char* const* const  p_file = boost::get_error_info<boost::throw_file>(exception);
                const integer_type* const p_line = boost::get_error_info<boost::throw_line>(exception);

                const std::system_error* const p_system_error = dynamic_cast<const std::system_error*>(&exception);
                if (p_system_error)
                {
                    const std::string what{ p_system_error->std::runtime_error::what() };
                    auto              message = p_system_error->code().message();
                    if (!what.empty())
                        message += std::string{ ": " } + what;
                    detail::gui_detail_impl_set().alert_().show_task_dialog(
                        m_widget_handle,
                        string_type{ TETENGO2_TEXT("Alert") },
                        string_type{ TETENGO2_TEXT("std::system_error") },
                        exception_encoder().decode(message),
                        p_file ? exception_encoder().decode(*p_file) :
                                 string_type{ TETENGO2_TEXT("Unknown Source File") },
                        p_line ? *p_line : 0);
                    return;
                }

                const std::exception* const p_std_exception = dynamic_cast<const std::exception*>(&exception);
                if (p_std_exception)
                {
                    detail::gui_detail_impl_set().alert_().show_task_dialog(
                        m_widget_handle,
                        string_type{ TETENGO2_TEXT("Alert") },
                        exception_encoder().decode(typeid(*p_std_exception).name()),
                        exception_encoder().decode(p_std_exception->what()),
                        p_file ? exception_encoder().decode(*p_file) :
                                 string_type{ TETENGO2_TEXT("Unknown Source File") },
                        p_line ? *p_line : 0);
                    return;
                }

                detail::gui_detail_impl_set().alert_().show_task_dialog(
                    m_widget_handle,
                    string_type{ TETENGO2_TEXT("Alert") },
                    exception_encoder().decode(typeid(exception).name()),
                    exception_encoder().decode(boost::diagnostic_information(exception)),
                    p_file ? exception_encoder().decode(*p_file) : string_type{ TETENGO2_TEXT("Unknown Source File") },
                    p_line ? *p_line : 0);
            }
            catch (...)
            {
            }
        }

        void operator_paren(const std::exception& exception) const
        {
            try
            {
                detail::gui_detail_impl_set().alert_().show_task_dialog(
                    m_widget_handle,
                    string_type{ TETENGO2_TEXT("Alert") },
                    exception_encoder().decode(typeid(exception).name()),
                    exception_encoder().decode(exception.what()),
                    string_type{ TETENGO2_TEXT("Unknown Source File") },
                    0);
            }
            catch (...)
            {
            }
        }


    private:
        // types

        using string_type = type_list::string_type;

        using integer_type = type_list::integer_type;

        using exception_encoder_type =
            text::encoder<type_list::internal_encoding_type, text::encoding::locale<std::string>>;


        // static functions

        static const exception_encoder_type& exception_encoder()
        {
            static const exception_encoder_type singleton{ type_list::internal_encoding_type{},
                                                           text::encoding::locale<std::string>{} };
            return singleton;
        }


        // variables

        const widget_handle_type m_widget_handle;
    };


    alert::alert(const widget_handle_type widget_handle) : m_p_impl{ std::make_unique<impl>(widget_handle) } {}

    alert::alert() : m_p_impl{ std::make_unique<impl>() } {}

    alert::~alert() = default;

    void alert::operator()(const boost::exception& exception) const
    {
        m_p_impl->operator_paren(exception);
    }

    void alert::operator()(const std::exception& exception /* = std::runtime_error("Unknown Error!") */) const
    {
        m_p_impl->operator_paren(exception);
    }
}