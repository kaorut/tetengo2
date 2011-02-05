/*! \file
    \brief The definition of C++0x keywords for tetengo2.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CPP0XKEYWORD_H)
#define TETENGO2_CPP0XKEYWORD_H

#include <boost/interprocess/smart_ptr/unique_ptr.hpp>
#include <boost/utility.hpp>


//! The alternative to the C++0x keyword noexcept.
#define TETENGO2_CPP0X_NOEXCEPT throw ()


namespace tetengo2 { namespace cpp0x
{
    /*!
        \brief The class template for the alternate of std::unique_ptr.

        \tparam T       A type.
        \tparam Deleter A deleter type.
    */
    template <typename T, typename Deleter = boost::checked_deleter<T>>
    struct unique_ptr
    {
        //! The alternate type of std::unique_ptr.
        typedef boost::interprocess::unique_ptr<T, Deleter> type;


    };


}}


#endif
