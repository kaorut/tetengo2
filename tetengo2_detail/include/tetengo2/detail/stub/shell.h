/*! \file
    \brief The definition of tetengo2::detail::stub::shell.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_SHELL_H)
#define TETENGO2_DETAIL_STUB_SHELL_H

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>

#include <tetengo2/text.h>


namespace tetengo2::detail::stub {
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
        shell() {}


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
            const Encoder&      encoder) const
        {
            boost::ignore_unused(parameter_first, parameter_last, encoder);

            return command.find(TETENGO2_TEXT("fail")) == String::npos;
        }
    };
}


#endif
