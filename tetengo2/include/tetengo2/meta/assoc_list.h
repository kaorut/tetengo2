/*! \file
    \brief The definition of tetengo2::meta::assoc_list.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_META_ASSOCLIST_H)
#define TETENGO2_META_ASSOCLIST_H

#include <cstddef>

#include <boost/mpl/at.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/key_type.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/value_type.hpp>
#include <boost/mpl/void.hpp>


namespace tetengo2 { namespace meta
{
    /*!
        \brief The tag for a node of an associative list.
    */
    struct assoc_list_tag;


    /*!
        \brief The metaclass for a node of an associative list.

        This metaclass meets the following <a href="http://www.boost.org/doc/libs/1_49_0/libs/mpl/doc/index.html">Boost
        MPL</a> concepts:


        \arg <a href="http://www.boost.org/doc/libs/1_49_0/libs/mpl/doc/refmanual/forward-sequence.html">Forward
             Sequence</a>
        \arg <a href="http://www.boost.org/doc/libs/1_49_0/libs/mpl/doc/refmanual/extensible-sequence.html">Extensible
            Sequence</a>
        \arg <a href="http://www.boost.org/doc/libs/1_49_0/libs/mpl/doc/refmanual/front-extensible-sequence.html">Front
            Extensible Sequence</a>
        \arg <a
            href="http://www.boost.org/doc/libs/1_49_0/libs/mpl/doc/refmanual/associative-sequence.html">Associative
            Sequence</a>
        \arg <a
            href="http://www.boost.org/doc/libs/1_49_0/libs/mpl/doc/refmanual/extensible-associative-sequence.html">Extensible
            Associative Sequence</a>

        \tparam Element An element.
        \tparam Next    A next node.
    */
    template <typename Element, typename Next>
    struct assoc_list
    {
        // types

        //! This type.
        using type = assoc_list;

        //! The element.
        using element = Element;

        //! The next node.
        using next = Next;

        //! The tag.
        using tag = assoc_list_tag;

        //! The category.
        using category = boost::mpl::forward_iterator_tag;


    };


    /*!
        \brief The metaclass for the end node of an associative list.
    */
    struct assoc_list_end
    {
        // types

        //! This type.
        using type = assoc_list_end;

        //! The tag.
        using tag = assoc_list_tag;

        //! The category.
        using category = boost::mpl::forward_iterator_tag;


    };


#if !defined(DOCUMENTATION)
    namespace detail
    {
        template <typename AssocList, typename Key, std::size_t Count>
        struct assoc_list_count
        {
            using type = typename assoc_list_count<typename AssocList::next, Key, Count>::type;
        };

        template <typename AssocList, std::size_t Count>
        struct assoc_list_count<
            AssocList, typename AssocList::element::first, Count
        >
        {
            using type =
                typename assoc_list_count<
                    typename AssocList::next, typename AssocList::element::first, Count + 1
                >::type;
        };

        template <typename Key, std::size_t Count>
        struct assoc_list_count<assoc_list_end, Key, Count>
        {
            using type = boost::mpl::integral_c<std::size_t, Count>;
        };

        template <typename AssocList, typename Key, std::size_t Order>
        struct assoc_list_order
        {
            using type = typename assoc_list_order<typename AssocList::next, Key, Order + 1>::type;
        };

        template <typename AssocList, std::size_t Order>
        struct assoc_list_order<
            AssocList, typename AssocList::element::first, Order
        >
        {
            using type = boost::mpl::integral_c<std::size_t, Order>;
        };

        template <typename Key, std::size_t Order>
        struct assoc_list_order<assoc_list_end, Key, Order>
        {
            using type = boost::mpl::void_;
        };

        template <typename AssocList, typename RangeFirst, typename RangeLast, typename Inserted>
        struct assoc_list_insert_range
        {
            using type =
                typename assoc_list_insert_range<
                    typename AssocList::next, RangeFirst, RangeLast, assoc_list<typename AssocList::element, Inserted>
                >::type;
        };

        template <typename RangeFirst, typename RangeLast, typename Inserted>
        struct assoc_list_insert_range<assoc_list_end, RangeFirst, RangeLast, Inserted>
        {
            using type =
                typename assoc_list_insert_range<
                    assoc_list_end,
                    typename boost::mpl::next<RangeFirst>::type,
                    RangeLast,
                    assoc_list<typename boost::mpl::deref<RangeFirst>::type, Inserted>
                >::type;
        };

        template <typename RangeLast, typename Inserted>
        struct assoc_list_insert_range<assoc_list_end, RangeLast, RangeLast, Inserted>
        {
            using type = Inserted;
        };

        template <typename AssocList, typename Key, typename Erased>
        struct assoc_list_erase_key
        {
            using type =
                typename assoc_list_erase_key<
                    typename AssocList::next,
                    Key,
                    typename boost::mpl::insert<Erased, typename AssocList::element>::type
                >::type;
        };

        template <typename AssocList, typename Erased>
        struct assoc_list_erase_key<AssocList, typename AssocList::element::first, Erased>
        {
            using type =
                typename assoc_list_erase_key<
                    typename AssocList::next, typename AssocList::element::first, Erased
                >::type;
        };

        template <typename Key, typename Erased>
        struct assoc_list_erase_key<assoc_list_end, Key, Erased>
        {
            using type = Erased;
        };

        template <typename Range>
        struct assoc_list_reverse
        {
            using type = typename boost::mpl::reverse<Range>::type;
        };

        template <typename Element, typename Next>
        struct assoc_list_reverse<assoc_list<Element, Next>>
        {
            using type =
                typename assoc_list_erase_key<assoc_list<Element, Next>, boost::mpl::na, assoc_list_end>::type;
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
    struct deref<tetengo2::meta::assoc_list<Element, Next>>
    {
        using type = Element;
    };


    // boost::mpl::begin

    template <>
    struct begin_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList>
        struct apply
        {
            using type = AssocList;
        };
    };


    // boost::mpl::end

    template <>
    struct end_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList>
        struct apply
        {
            using type = tetengo2::meta::assoc_list_end;
        };
    };


    // boost::mpl::has_key

    template <>
    struct has_key_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename Key>
        struct apply
        {
            using type = typename apply<typename AssocList::next, Key>::type;
        };

        template <typename AssocList>
        struct apply<AssocList, typename AssocList::element::first>
        {
            using type = boost::mpl::integral_c<bool, true>;
        };

        template <typename Key>
        struct apply<tetengo2::meta::assoc_list_end, Key>
        {
            using type = boost::mpl::integral_c<bool, false>;
        };

    };


    // boost::mpl::count

    template <>
    struct count_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename Key>
        struct apply
        {
            using type = typename tetengo2::meta::detail::assoc_list_count<AssocList, Key, 0>::type;
        };

    };


    // boost::mpl::order

    template <>
    struct order_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename Key>
        struct apply
        {
            using type = typename tetengo2::meta::detail::assoc_list_order<AssocList, Key, 0>::type;
        };
    };


    // boost::mpl::at

    template <>
    struct at_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename Key>
        struct apply
        {
            using type = typename at<typename AssocList::next, Key>::type;
        };

        template <typename AssocList>
        struct apply<AssocList, typename AssocList::element::first>
        {
            using type = typename AssocList::element::second;
        };

        template <typename Key>
        struct apply<tetengo2::meta::assoc_list_end, Key>
        {
            using type = boost::mpl::void_;
        };
    };


    // boost::mpl::key_type

    template <>
    struct key_type_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename Element>
        struct apply
        {
            using type = typename Element::first;
        };
    };


    // boost::mpl::value_type

    template <>
    struct value_type_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename Element>
        struct apply
        {
            using type = typename Element::second;
        };
    };


    // boost::mpl::insert

    template <>
    struct insert_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename PositionOrNewElement, typename NewElement>
        struct apply
        {
            using type = tetengo2::meta::assoc_list<NewElement, AssocList>;
        };

        template <typename AssocList, typename NewElement>
        struct apply<AssocList, NewElement, boost::mpl::na>
        {
            using type = tetengo2::meta::assoc_list<NewElement, AssocList>;
        };
    };


    // boost::mpl::insert_range

    template <>
    struct insert_range_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename Position, typename Range>
        struct apply
        {
            using type =
                typename tetengo2::meta::detail::assoc_list_insert_range<
                    typename tetengo2::meta::detail::assoc_list_reverse<AssocList>::type,
                    typename boost::mpl::begin<typename tetengo2::meta::detail::assoc_list_reverse<Range>::type>::type,
                    typename boost::mpl::end<typename tetengo2::meta::detail::assoc_list_reverse<Range>::type>::type,
                    tetengo2::meta::assoc_list_end
                >::type;
        };
    };


    // boost::mpl::erase_key

    template <>
    struct erase_key_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename Key>
        struct apply
        {
            using type =
                typename tetengo2::meta::detail::assoc_list_reverse<
                    typename tetengo2::meta::detail::assoc_list_erase_key<
                        AssocList, Key, tetengo2::meta::assoc_list_end
                    >::type
                >::type;
        };
    };


    // boost::mpl::erase

    template <>
    struct erase_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename Position, typename Ignored>
        struct apply
        {
            using type = typename erase_key<AssocList, typename deref<Position>::type::first>::type;
        };

        template <typename AssocList, typename Ignored>
        struct apply<AssocList, tetengo2::meta::assoc_list_end, Ignored>
        {
            using type = AssocList;
        };
    };


    // boost::mpl::clear

    template <>
    struct clear_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList>
        struct apply
        {
            using type = tetengo2::meta::assoc_list_end;
        };
    };


    // boost::mpl::push_front

    template <>
    struct push_front_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList, typename NewElement>
        struct apply
        {
            using type = typename insert<AssocList, NewElement>::type;
        };
    };


    // boost::mpl::pop_front

    template <>
    struct pop_front_impl<tetengo2::meta::assoc_list_tag>
    {
        template <typename AssocList>
        struct apply
        {
            using type = typename AssocList::next;
        };
    };


}}
#endif


#endif
