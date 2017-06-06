/*! \file
    \brief The definition of tetengo2::detail::base::encoding.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <string>
#include <utility>

#include <boost/predef.h>

#include <tetengo2/detail/base/encoding.h>


namespace tetengo2 { namespace detail { namespace base
{
    class encoding::pivot_type
    {
    public:
        // types

#if BOOST_OS_WINDOWS
        using string_type = std::wstring;
#elif BOOST_OS_UNIX
        using string_type = std::string;
#else
#   error Specify the pivot string type.
#endif


        // constructors and destructor

        explicit pivot_type(string_type string)
        :
        m_string(std::move(string))
        {}


        // functions

        const string_type& get()
        const
        {
            return m_string;
        }


    private:
        // variables

        string_type m_string;


    };


    encoding::encoding()
    = default;

    encoding::~encoding()
    = default;

    encoding::utf8_string_type encoding::pivot_to_utf8(const pivot_type& pivot)
    const
    {
        return pivot_to_utf8_impl(pivot);
    }

    encoding::pivot_type encoding::utf8_to_pivot(const utf8_string_type& string)
    const
    {
        return utf8_to_pivot_impl(string);
    }

    encoding::cp932_string_type encoding::pivot_to_cp932(const pivot_type& pivot)
    const
    {
        return pivot_to_cp932_impl(pivot);
    }

    encoding::pivot_type encoding::cp932_to_pivot(const cp932_string_type& string)
    const
    {
        return cp932_to_pivot_impl(string);
    }


}}}
