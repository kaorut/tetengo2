/*! \file
    \brief The definition of tetengo2::meta::assoc_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_META_ASSOCLIST_H)
#define TETENGO2_META_ASSOCLIST_H

#include <cstddef>

#include <boost/mpl/begin.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>


namespace tetengo2 { namespace meta
{
    /*!
        \brief The metaclass for a node of an associative list.

        This metaclass meets the following <a
        href="http://www.boost.org/doc/libs/1_43_0/libs/mpl/doc/index.html">Boost
        MPL</a> concepts:

        \arg <a
            href="http://www.boost.org/doc/libs/1_43_0/libs/mpl/doc/refmanual/forward-sequence.html">Forward
            Sequence</a>
        \arg <a
            href="http://www.boost.org/doc/libs/1_43_0/libs/mpl/doc/refmanual/associative-sequence.html">Associative
            Sequence</a>
        \arg <a
            href="http://www.boost.org/doc/libs/1_43_0/libs/mpl/doc/refmanual/extensible-associative-sequence.html">Extensible
            Associative Sequence</a>

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


    /*!
        \brief The metaclass for the end node of an associative list.
    */
    struct assoc_list_end
    {
        // types

        //! The category
        typedef boost::mpl::forward_iterator_tag category;


    };


#if !defined(DOCUMENTATION)
    namespace detail
    {
        template <typename AssocList, std::size_t Size>
        struct assoc_list_size
        {
            typedef
                typename assoc_list_size<
                    typename AssocList::next, Size + 1
                >::type
                type;
        };

        template <std::size_t Size>
        struct assoc_list_size<assoc_list_end, Size>
        {
            typedef boost::mpl::size_t<Size> type;
        };


    }
#endif


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

    template <>
    struct begin<tetengo2::meta::assoc_list_end>
    {
        typedef tetengo2::meta::assoc_list_end type;
    };

    // boost::mpl::end
    template <typename Value, typename Next>
    struct end<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef tetengo2::meta::assoc_list_end type;
    };

    template <>
    struct end<tetengo2::meta::assoc_list_end>
    {
        typedef tetengo2::meta::assoc_list_end type;
    };

    // boost::mpl::size
    template <typename Value, typename Next>
    struct size<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef
            typename tetengo2::meta::detail::assoc_list_size<
                tetengo2::meta::assoc_list<Value, Next>, 0
            >::type
            type;
    };

    template <>
    struct size<tetengo2::meta::assoc_list_end>
    {
        typedef boost::mpl::size_t<0> type;
    };

    // boost::mpl::empty
    template <typename Value, typename Next>
    struct empty<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef boost::mpl::bool_<false> type;
    };

    template <>
    struct empty<tetengo2::meta::assoc_list_end>
    {
        typedef boost::mpl::bool_<true> type;
    };


}}
#endif


#endif
