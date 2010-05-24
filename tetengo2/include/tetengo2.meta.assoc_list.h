/*! \file
    \brief The definition of tetengo2::meta::assoc_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_META_ASSOCLIST_H)
#define TETENGO2_META_ASSOCLIST_H

#include <cstddef>

#include <boost/mpl/at.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/key_type.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/order.hpp>
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

        \tparam Element An element.
        \tparam Next    A next node.
    */
    template <typename Element, typename Next>
    struct assoc_list
    {
        // types

        //! The element.
        typedef Element element;

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

        template <typename AssocList, typename Key, std::size_t Count>
        struct assoc_list_count
        {
            typedef
                typename assoc_list_count<
                    typename AssocList::next, Key, Count
                >::type
                type;
        };

        template <typename AssocList, std::size_t Count>
        struct assoc_list_count<
            AssocList, typename AssocList::element::first, Count
        >
        {
            typedef
                typename assoc_list_count<
                    typename AssocList::next,
                    typename AssocList::element::first,
                    Count + 1
                >::type
                type;
        };

        template <typename Key, std::size_t Count>
        struct assoc_list_count<assoc_list_end, Key, Count>
        {
            typedef boost::mpl::size_t<Count> type;
        };

        template <typename AssocList, typename Key, std::size_t Order>
        struct assoc_list_order
        {
            typedef
                typename assoc_list_order<
                    typename AssocList::next, Key, Order + 1
                >::type
                type;
        };

        template <typename AssocList, std::size_t Order>
        struct assoc_list_order<
            AssocList, typename AssocList::element::first, Order
        >
        {
            typedef boost::mpl::size_t<Order> type;
        };

        template <typename Key, std::size_t Order>
        struct assoc_list_order<assoc_list_end, Key, Order>
        {
            typedef boost::mpl::void_ type;
        };


    }
#endif


}}

#if !defined(DOCUMENTATION)
namespace boost { namespace mpl
{
    // functions

    // boost::mpl::deref
    template <typename Element, typename Next>
    struct deref<tetengo2::meta::assoc_list<Element, Next> >
    {
        typedef Element type;
    };

    // boost::mpl::next
    template <typename Element, typename Next>
    struct next<tetengo2::meta::assoc_list<Element, Next> >
    {
        typedef Next type;
    };

    // boost::mpl::begin
    template <typename Element, typename Next>
    struct begin<tetengo2::meta::assoc_list<Element, Next> >
    {
        typedef tetengo2::meta::assoc_list<Element, Next> type;
    };

    template <>
    struct begin<tetengo2::meta::assoc_list_end>
    {
        typedef tetengo2::meta::assoc_list_end type;
    };

    // boost::mpl::end
    template <typename Element, typename Next>
    struct end<tetengo2::meta::assoc_list<Element, Next> >
    {
        typedef tetengo2::meta::assoc_list_end type;
    };

    template <>
    struct end<tetengo2::meta::assoc_list_end>
    {
        typedef tetengo2::meta::assoc_list_end type;
    };

    // boost::mpl::size
    template <typename Element, typename Next>
    struct size<tetengo2::meta::assoc_list<Element, Next> >
    {
        typedef
            typename tetengo2::meta::detail::assoc_list_size<
                tetengo2::meta::assoc_list<Element, Next>, 0
            >::type
            type;
    };

    template <>
    struct size<tetengo2::meta::assoc_list_end>
    {
        typedef boost::mpl::size_t<0> type;
    };

    // boost::mpl::empty
    template <typename Element, typename Next>
    struct empty<tetengo2::meta::assoc_list<Element, Next> >
    {
        typedef boost::mpl::bool_<false> type;
    };

    template <>
    struct empty<tetengo2::meta::assoc_list_end>
    {
        typedef boost::mpl::bool_<true> type;
    };

    // boost::mpl::front
    template <typename Element, typename Next>
    struct front<tetengo2::meta::assoc_list<Element, Next> >
    {
        typedef Element type;
    };

    // boost::mpl::has_key
    template <typename Element, typename Next, typename Key>
    struct has_key<tetengo2::meta::assoc_list<Element, Next>, Key>
    {
        typedef typename has_key<Next, Key>::type type;
    };

    template <typename Element, typename Next>
    struct has_key<
        tetengo2::meta::assoc_list<Element, Next>, typename Element::first
    >
    {
        typedef boost::mpl::bool_<true> type;
    };

    template <typename Key>
    struct has_key<tetengo2::meta::assoc_list_end, Key>
    {
        typedef boost::mpl::bool_<false> type;
    };

    // boost::mpl::count
    template <typename Element, typename Next, typename Key>
    struct count<tetengo2::meta::assoc_list<Element, Next>, Key>
    {
        typedef
            typename tetengo2::meta::detail::assoc_list_count<
                tetengo2::meta::assoc_list<Element, Next>, Key, 0
            >::type
            type;
    };

    template <typename Key>
    struct count<tetengo2::meta::assoc_list_end, Key>
    {
        typedef boost::mpl::size_t<0> type;
    };

    // boost::mpl::order
    template <typename Element, typename Next, typename Key>
    struct order<tetengo2::meta::assoc_list<Element, Next>, Key>
    {
        typedef
            typename tetengo2::meta::detail::assoc_list_order<
                tetengo2::meta::assoc_list<Element, Next>, Key, 0
            >::type
            type;
    };

    template <typename Key>
    struct order<tetengo2::meta::assoc_list_end, Key>
    {
        typedef boost::mpl::void_ type;
    };

    // boost::mpl::at

    template <typename Element, typename Next, typename Key>
    struct at<tetengo2::meta::assoc_list<Element, Next>, Key>
    {
        typedef typename at<Next, Key>::type type;
    };

    template <typename Element, typename Next>
    struct at<
        tetengo2::meta::assoc_list<Element, Next>, typename Element::first
    >
    {
        typedef typename Element::second type;
    };

    template <typename Key>
    struct at<tetengo2::meta::assoc_list_end, Key>
    {
        typedef boost::mpl::void_ type;
    };

    // boost::mpl::key_type

    template <typename Element, typename Next>
    struct key_type<tetengo2::meta::assoc_list<Element, Next>, Element>
    {
        typedef typename Element::first type;
    };

    template <typename Element>
    struct key_type<tetengo2::meta::assoc_list_end, Element>
    {
        typedef typename Element::first type;
    };


}}
#endif


#endif
