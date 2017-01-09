/*! \file
    \brief The definition of tetengo2::detail::windows::shell.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_SHELL_H)
#define TETENGO2_DETAIL_WINDOWS_SHELL_H

#include <algorithm>

#include <boost/core/noncopyable.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/text.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a shell.
    */
    class shell : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a shell.
        */
        shell()
        {}


        // functions

        /*!
            \brief Executes a command.

            \tparam String       A string type.
            \tparam InpuIterator An input iterator type.
            \tparam Encoder      An encoder type.

            \param command         A command. When it is a path, the path is relative to the current directory.
            \param parameter_first The first iterator to parameters.
            \param parameter_last  The last iterator to parameters.
            \param encoder         An encoder.

            \retval true  When the command is executed successfully.
            \retval false Otherwise.
        */
        template <typename String, typename InputIterator, typename Encoder>
        bool execute(
            const String&       command,
            const InputIterator parameter_first,
            const InputIterator parameter_last,
            const Encoder&      encoder
        )
        const
        {
            const auto result =
                ::ShellExecuteW(
                    nullptr,
                    L"open",
                    encoder.encode(command).c_str(),
                    encoder.encode(concatenate_parameters<String>(parameter_first, parameter_last)).c_str(),
                    nullptr,
                    SW_SHOWNORMAL
                );
            return reinterpret_cast< ::UINT_PTR>(result) > 32;
        }


    private:
        // static functions

        template <typename String, typename InputIterator>
        static String concatenate_parameters(const InputIterator first, const InputIterator last)
        {
            String parameters;

            std::for_each(
                first,
                last,
                [&parameters](const String& parameter) { parameters += parameter + String{ TETENGO2_TEXT(" ") }; }
            );

            return parameters;
        }


    };


}}}


#endif
