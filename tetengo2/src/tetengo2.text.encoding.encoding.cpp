/*! \file
    \brief The definition of tetengo2::text::encoding::encoding.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2 { namespace text { namespace encoding
{
    class encoding::impl : private boost::noncopyable
    {
    public:
        // types

        using encoding_details_type = typename encoding::encoding_details_type;

        using pivot_type = typename encoding::pivot_type;


        // constructors and destructor

        impl()
        {}


    };


    encoding::~encoding()
    = default;

    encoding::encoding()
    :
    m_p_impl(std::make_shared<impl>())
    {}


}}}
