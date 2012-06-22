/*! \file
    \brief The definition of bobura::view::scale_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_SCALELIST_H)
#define BOBURA_VIEW_SCALELIST_H

#include <vector>

#include <boost/noncopyable.hpp>


namespace bobura { namespace view
{
    /*!
        \brief The class template for a view scale list.

        \tparam Scale  A scale type.
        \tparam Size   A size type.
        \tparam String A string type.
    */
    template <typename Scale, typename Size, typename String>
    class scale_list : boost::noncopyable
    {
    public:
        // types

        //! The scale type.
        typedef Scale scale_type;

        //! The size type.
        typedef Size size_type;

        //! The string type.
        typedef String string_type;


    };


}}


#endif
