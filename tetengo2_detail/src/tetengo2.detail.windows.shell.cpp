/*! \file
    \brief The definition of tetengo2::detail::windows::shell.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/core/noncopyable.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/base/shell.h>
#include <tetengo2/detail/windows/shell.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/type_list.h>


namespace tetengo2::detail::windows {
    class shell::impl : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = base::shell::string_type;


        // static functions

        static const shell& instance()
        {
            static const shell singleton;
            return singleton;
        }


        // functions

        bool execute_impl(const string_type& command, const std::vector<string_type>& parameters) const
        {
            const auto result = ::ShellExecuteW(
                nullptr,
                L"open",
                encoder().encode(command).c_str(),
                encoder().encode(boost::join(parameters, string_type{ TETENGO2_TEXT(" ") })).c_str(),
                nullptr,
                SW_SHOWNORMAL);
            return reinterpret_cast<::UINT_PTR>(result) > 32;
        }


    private:
        // types

        using encoder_type = text::encoder<type_list::internal_encoding_type, text::encoding::locale<std::wstring>>;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }
    };


    const shell& shell::instance()
    {
        return impl::instance();
    }

    shell::~shell() = default;

    shell::shell() : m_p_impl{ std::make_unique<impl>() } {}

    bool shell::execute_impl(const string_type& command, const std::vector<string_type>& parameters) const
    {
        return m_p_impl->execute_impl(command, parameters);
    }
}
