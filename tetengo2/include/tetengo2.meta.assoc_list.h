/*! \file
    \brief The definition of tetengo2::meta::assoc_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_META_ASSOCLIST_H)
#define TETENGO2_META_ASSOCLIST_H //!< !! Include Guard !!

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/void.hpp>


namespace tetengo2 { namespace meta
{
    /*!
        \brief The metaclass for a node of an associative list.

        \tparam Value A value.
        \tparam Next  A next node.
    */
    template <typename Value, typename Next>
    struct assoc_list
    {
        // types

        //! The value.
        typedef Value value;

        //! The next node.
        typedef Next next;

        //! The category.
        typedef boost::mpl::forward_iterator_tag category;

    };


}}

#if !defined(DOCUMENTATION)
namespace boost { namespace mpl
{
    // functions

    // boost::mpl::deref
    template <typename Value, typename Next>
    struct deref<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef Value type;
    };

    // boost::mpl::next
    template <typename Value, typename Next>
    struct next<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef Next type;
    };

    // boost::mpl::begin
    template <typename Value, typename Next>
    struct begin<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef tetengo2::meta::assoc_list<Value, Next> type;
    };

    // boost::mpl::end
    template <typename Value, typename Next>
    struct end<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef boost::mpl::void_ type;
    };


}}
#endif


#endif
