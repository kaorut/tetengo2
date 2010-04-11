/*! \file
    \brief The definition of concept_tetengo2::IStream.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_ISTREAM_H)
#define CONCEPTTETENGO2_ISTREAM_H

#include <istream>

#include <boost/concept_check.hpp>


namespace concept_tetengo2
{
    /*!
        \brief The concept check class template for an input stream.

        \tparam Type A type.
    */
    template <typename Type>
    class IStream : private boost::Convertible<Type&, std::istream&>
    {};


}

#endif
