/*! \file
    \brief Test of class tetengo2::meta::assoc_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/mpl/begin.hpp>
//#include <boost/mpl/bool.hpp>
//#include <boost/mpl/clear.hpp>
//#include <boost/mpl/count.hpp>
//#include <boost/mpl/deref.hpp>
//#include <boost/mpl/empty.hpp>
//#include <boost/mpl/end.hpp>
//#include <boost/mpl/erase.hpp>
//#include <boost/mpl/erase_key.hpp>
//#include <boost/mpl/front.hpp>
//#include <boost/mpl/has_key.hpp>
//#include <boost/mpl/insert.hpp>
#include <boost/mpl/int.hpp>
//#include <boost/mpl/iterator_tags.hpp>
//#include <boost/mpl/key_type.hpp>
//#include <boost/mpl/next.hpp>
//#include <boost/mpl/order.hpp>
#include <boost/mpl/pair.hpp>
//#include <boost/mpl/size.hpp>
//#include <boost/mpl/value_type.hpp>
//#include <boost/mpl/void.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.meta.assoc_list.h"


namespace
{
    // types

    typedef tetengo2::meta::assoc_list_end assoc_list0;

    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000> >,
        tetengo2::meta::assoc_list_end
        >
        assoc_list1;

    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<2000> >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<2001> >,
        tetengo2::meta::assoc_list_end
        > >
        assoc_list2;

    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<3000> >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<3001> >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<3100> >,
        tetengo2::meta::assoc_list_end
        > > >
        assoc_list3;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(meta)
BOOST_AUTO_TEST_SUITE(assoc_list)
    // test cases

    BOOST_AUTO_TEST_CASE(is_sequence)
    {
        {
            typedef boost::mpl::is_sequence<assoc_list0>::type is_sequence;

            BOOST_MPL_ASSERT((is_sequence));
        }
        {
            typedef boost::mpl::is_sequence<assoc_list1>::type is_sequence;

            BOOST_MPL_ASSERT((is_sequence));
        }
        {
            typedef boost::mpl::is_sequence<assoc_list2>::type is_sequence;

            BOOST_MPL_ASSERT((is_sequence));
        }
    }

    BOOST_AUTO_TEST_CASE(deref)
    {
        {
            typedef boost::mpl::deref<assoc_list1>::type dereferenced;

            BOOST_MPL_ASSERT((
                boost::is_same<
                    dereferenced,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<1000>
                    >
                >
            ));
        }
        {
            typedef boost::mpl::deref<assoc_list2>::type dereferenced;

            BOOST_MPL_ASSERT((
                boost::is_same<
                    dereferenced,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<2000>
                    >
                >
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        {
            typedef boost::mpl::next<assoc_list1>::type next;

            BOOST_MPL_ASSERT((boost::is_same<next, assoc_list1::next>));
        }
        {
            typedef boost::mpl::next<assoc_list2>::type next;

            BOOST_MPL_ASSERT((boost::is_same<next, assoc_list2::next>));

            typedef boost::mpl::next<next>::type next2;

            BOOST_MPL_ASSERT((
                boost::is_same<next2, assoc_list2::next::next>
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(category)
    {
        {
            typedef assoc_list1::category category;

            BOOST_MPL_ASSERT((
                boost::is_convertible<
                    category, boost::mpl::forward_iterator_tag
                >
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(begin)
    {
        {
            typedef boost::mpl::begin<assoc_list0>::type begin;

            BOOST_MPL_ASSERT((boost::is_same<begin, assoc_list0>));
        }
        {
            typedef boost::mpl::begin<assoc_list1>::type begin;

            BOOST_MPL_ASSERT((boost::is_same<begin, assoc_list1>));
            BOOST_MPL_ASSERT((
                boost::is_same<
                    boost::mpl::deref<begin>::type,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<1000>
                    >
                >
            ));
        }
        {
            typedef boost::mpl::begin<assoc_list2>::type begin;

            BOOST_MPL_ASSERT((boost::is_same<begin, assoc_list2>));
            BOOST_MPL_ASSERT((
                boost::is_same<
                    boost::mpl::deref<begin>::type,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<2000>
                    >
                >
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(end)
    {
        {
            typedef boost::mpl::end<assoc_list0>::type end;

            BOOST_MPL_ASSERT((
                boost::is_same<end, tetengo2::meta::assoc_list_end>
            ));
        }
        {
            typedef boost::mpl::end<assoc_list1>::type end;

            BOOST_MPL_ASSERT((boost::is_same<end, assoc_list1::next>));
        }
        {
            typedef boost::mpl::end<assoc_list2>::type end;

            BOOST_MPL_ASSERT((boost::is_same<end, assoc_list2::next::next>));
        }
    }

    BOOST_AUTO_TEST_CASE(size)
    {
        {
            typedef boost::mpl::size<assoc_list0>::type size;

            BOOST_MPL_ASSERT_RELATION(size::value, ==, 0);
        }
        {
            typedef boost::mpl::size<assoc_list1>::type size;

            BOOST_MPL_ASSERT_RELATION(size::value, ==, 1);
        }
        {
            typedef boost::mpl::size<assoc_list2>::type size;

            BOOST_MPL_ASSERT_RELATION(size::value, ==, 2);
        }
    }

    BOOST_AUTO_TEST_CASE(empty)
    {
        {
            typedef boost::mpl::empty<assoc_list0>::type empty;

            BOOST_MPL_ASSERT((empty));
        }
        {
            typedef boost::mpl::empty<assoc_list1>::type empty;

            BOOST_MPL_ASSERT_NOT((empty));
        }
        {
            typedef boost::mpl::empty<assoc_list2>::type empty;

            BOOST_MPL_ASSERT_NOT((empty));
        }
    }

    BOOST_AUTO_TEST_CASE(front)
    {
        {
            typedef boost::mpl::front<assoc_list1>::type front;

            BOOST_MPL_ASSERT((
                boost::is_same<
                    front,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<1000>
                    >
                >
            ));
        }
        {
            typedef boost::mpl::front<assoc_list2>::type front;

            BOOST_MPL_ASSERT((
                boost::is_same<
                    front,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<2000>
                    >
                >
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(has_key)
    {
        {
            typedef
                boost::mpl::has_key<assoc_list0, boost::mpl::int_<0> >::type
                has_key;

            BOOST_MPL_ASSERT((
                boost::is_same<has_key, boost::mpl::bool_<false> >
            ));
        }
        {
            typedef
                boost::mpl::has_key<assoc_list2, boost::mpl::int_<0> >::type
                has_key;

            BOOST_MPL_ASSERT((
                boost::is_same<has_key, boost::mpl::bool_<true> >
            ));
        }
        {
            typedef
                boost::mpl::has_key<assoc_list2, boost::mpl::int_<2> >::type
                has_key;

            BOOST_MPL_ASSERT((
                boost::is_same<has_key, boost::mpl::bool_<false> >
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(count)
    {
        {
            typedef
                boost::mpl::count<assoc_list0, boost::mpl::int_<0> >::type
                count;

            BOOST_MPL_ASSERT_RELATION(count::value, ==, 0);
        }
        {
            typedef
                boost::mpl::count<assoc_list2, boost::mpl::int_<0> >::type
                count;

            BOOST_MPL_ASSERT_RELATION(count::value, ==, 1);
        }
        {
            typedef
                boost::mpl::count<assoc_list2, boost::mpl::int_<2> >::type
                count;

            BOOST_MPL_ASSERT_RELATION(count::value, ==, 0);
        }
        {
            typedef
                boost::mpl::count<assoc_list3, boost::mpl::int_<0> >::type
                count;

            BOOST_MPL_ASSERT_RELATION(count::value, ==, 2);
        }
    }

    BOOST_AUTO_TEST_CASE(order)
    {
        {
            typedef
                boost::mpl::order<assoc_list0, boost::mpl::int_<0> >::type
                order;

            BOOST_MPL_ASSERT((boost::is_same<order, boost::mpl::void_>));
        }
        {
            typedef
                boost::mpl::order<assoc_list2, boost::mpl::int_<0> >::type
                order;

            BOOST_MPL_ASSERT_NOT((boost::is_same<order, boost::mpl::void_>));
        }
        {
            typedef
                boost::mpl::order<assoc_list2, boost::mpl::int_<2> >::type
                order;

            BOOST_MPL_ASSERT((boost::is_same<order, boost::mpl::void_>));
        }
    }

    BOOST_AUTO_TEST_CASE(at)
    {
        {
            typedef
                boost::mpl::at<assoc_list0, boost::mpl::int_<0> >::type
                value;

            BOOST_MPL_ASSERT((boost::is_same<value, boost::mpl::void_>));
        }
        //{
        //    typedef
        //        boost::mpl::at<
        //            assoc_list0, boost::mpl::int_<0>, boost::mpl::int_<9999>
        //        >::type
        //        value;

        //    BOOST_MPL_ASSERT((
        //        boost::is_same<value, boost::mpl::int_<9999> >
        //    ));
        //}
        {
            typedef
                boost::mpl::at<assoc_list2, boost::mpl::int_<0> >::type
                value;

            BOOST_MPL_ASSERT((
                boost::is_same<value, boost::mpl::int_<2000> >
            ));
        }
        {
            typedef
                boost::mpl::at<assoc_list2, boost::mpl::int_<1> >::type
                value;

            BOOST_MPL_ASSERT((
                boost::is_same<value, boost::mpl::int_<2001> >
            ));
        }
        //{
        //    typedef
        //        boost::mpl::at<
        //            assoc_list2, boost::mpl::int_<0>, boost::mpl::int_<9999>
        //        >::type
        //        value;

        //    BOOST_MPL_ASSERT((
        //        boost::is_same<value, boost::mpl::int_<2000> >
        //    ));
        //}
        {
            typedef
                boost::mpl::at<assoc_list2, boost::mpl::int_<2> >::type
                value;

            BOOST_MPL_ASSERT((boost::is_same<value, boost::mpl::void_>));
        }
        //{
        //    typedef
        //        boost::mpl::at<
        //            assoc_list2, boost::mpl::int_<2>, boost::mpl::int_<9999>
        //        >::type
        //        value;

        //    BOOST_MPL_ASSERT((
        //        boost::is_same<value, boost::mpl::int_<9999> >
        //    ));
        //}
    }

    BOOST_AUTO_TEST_CASE(key_type)
    {
        {
            typedef
                boost::mpl::key_type<
                    assoc_list0,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<1000>
                    >
                >::type
                key_type;

            BOOST_MPL_ASSERT((
                boost::is_same<key_type, boost::mpl::int_<0> >
            ));
        }
        {
            typedef
                boost::mpl::key_type<
                    assoc_list0,
                    boost::mpl::pair<
                        boost::mpl::int_<1>, boost::mpl::int_<1000>
                    >
                >::type
                key_type;

            BOOST_MPL_ASSERT((
                boost::is_same<key_type, boost::mpl::int_<1> >
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(value_type)
    {
        {
            typedef
                boost::mpl::value_type<
                    assoc_list0,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<1000>
                    >
                >::type
                value_type;

            BOOST_MPL_ASSERT((
                boost::is_same<value_type, boost::mpl::int_<1000> >
            ));
        }
        {
            typedef
                boost::mpl::value_type<
                    assoc_list0,
                    boost::mpl::pair<
                        boost::mpl::int_<1>, boost::mpl::int_<1000>
                    >
                >::type
                value_type;

            BOOST_MPL_ASSERT((
                boost::is_same<value_type, boost::mpl::int_<1000> >
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(insert)
    {
        {
            typedef
                boost::mpl::insert<
                    assoc_list0,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<1000>
                    >
                >::type
                inserted;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<inserted>::type::value, ==, 1
            );
            BOOST_MPL_ASSERT((
                boost::mpl::has_key<inserted, boost::mpl::int_<0> >::type
            ));
        }
        {
            typedef
                boost::mpl::insert<
                    assoc_list1,
                    boost::mpl::pair<
                        boost::mpl::int_<1>, boost::mpl::int_<1001>
                    >
                >::type
                inserted;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<inserted>::type::value, ==, 2
            );
            BOOST_MPL_ASSERT((
                boost::mpl::has_key<inserted, boost::mpl::int_<1> >::type
            ));
        }
        {
            typedef
                boost::mpl::insert<
                    assoc_list0,
                    boost::mpl::end<assoc_list0>::type,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<1000>
                    >
                >::type
                inserted;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<inserted>::type::value, ==, 1
            );
            BOOST_MPL_ASSERT((
                boost::mpl::has_key<inserted, boost::mpl::int_<0> >::type
            ));
        }
        {
            typedef
                boost::mpl::insert<
                    assoc_list1,
                    boost::mpl::end<assoc_list1>::type,
                    boost::mpl::pair<
                        boost::mpl::int_<1>, boost::mpl::int_<1001>
                    >
                >::type
                inserted;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<inserted>::type::value, ==, 2
            );
            BOOST_MPL_ASSERT((
                boost::mpl::has_key<inserted, boost::mpl::int_<1> >::type
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(erase_key)
    {
        {
            typedef
                boost::mpl::erase_key<assoc_list0, boost::mpl::int_<0> >::type
                erased;

            BOOST_MPL_ASSERT((boost::mpl::empty<erased>::type));
        }
        {
            typedef
                boost::mpl::erase_key<assoc_list1, boost::mpl::int_<0> >::type
                erased;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<erased>::type::value, ==, 0
            );
            BOOST_MPL_ASSERT_NOT((
                boost::mpl::has_key<erased, boost::mpl::int_<0> >::type
            ));
        }
        {
            typedef
                boost::mpl::erase_key<assoc_list2, boost::mpl::int_<1> >::type
                erased;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<erased>::type::value, ==, 1
            );
            BOOST_MPL_ASSERT_NOT((
                boost::mpl::has_key<erased, boost::mpl::int_<1> >::type
            ));
        }
        {
            typedef
                boost::mpl::erase_key<assoc_list3, boost::mpl::int_<0> >::type
                erased;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<erased>::type::value, ==, 1
            );
            BOOST_MPL_ASSERT_NOT((
                boost::mpl::has_key<erased, boost::mpl::int_<0> >::type
            ));
        }
        {
            typedef
                boost::mpl::erase_key<assoc_list3, boost::mpl::int_<1> >::type
                erased;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<erased>::type::value, ==, 2
            );
            BOOST_MPL_ASSERT_NOT((
                boost::mpl::has_key<erased, boost::mpl::int_<1> >::type
            ));
            BOOST_MPL_ASSERT((
                boost::is_same<
                    erased::element,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<3000>
                    >
                >
            ));
            BOOST_MPL_ASSERT((
                boost::is_same<
                    erased::next::element,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<3100>
                    >
                >
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(erase)
    {
        {
            typedef
                boost::mpl::erase<assoc_list0, assoc_list0>::type
                erased;

            BOOST_MPL_ASSERT((boost::mpl::empty<erased>::type));
        }
        {
            typedef
                boost::mpl::erase<assoc_list1, assoc_list1>::type
                erased;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<erased>::type::value, ==, 0
            );
            BOOST_MPL_ASSERT_NOT((
                boost::mpl::has_key<erased, boost::mpl::int_<0> >::type
            ));
        }
        {
            typedef
                boost::mpl::erase<assoc_list1, assoc_list1::next>::type
                erased;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<erased>::type::value, ==, 1
            );
        }
        {
            typedef
                boost::mpl::erase<assoc_list2, assoc_list2::next>::type
                erased;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<erased>::type::value, ==, 1
            );
            BOOST_MPL_ASSERT_NOT((
                boost::mpl::has_key<erased, boost::mpl::int_<1> >::type
            ));
        }
        {
            typedef
                boost::mpl::erase<assoc_list3, assoc_list3>::type
                erased;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<erased>::type::value, ==, 1
            );
            BOOST_MPL_ASSERT_NOT((
                boost::mpl::has_key<erased, boost::mpl::int_<0> >::type
            ));
        }
        {
            typedef
                boost::mpl::erase<assoc_list3, assoc_list3::next>::type
                erased;

            BOOST_MPL_ASSERT_RELATION(
                boost::mpl::size<erased>::type::value, ==, 2
            );
            BOOST_MPL_ASSERT_NOT((
                boost::mpl::has_key<erased, boost::mpl::int_<1> >::type
            ));
            BOOST_MPL_ASSERT((
                boost::is_same<
                    erased::element,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<3000>
                    >
                >
            ));
            BOOST_MPL_ASSERT((
                boost::is_same<
                    erased::next::element,
                    boost::mpl::pair<
                        boost::mpl::int_<0>, boost::mpl::int_<3100>
                    >
                >
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(clear)
    {
        {
            typedef boost::mpl::clear<assoc_list0>::type cleared;

            BOOST_MPL_ASSERT((boost::mpl::empty<cleared>::type));
        }
        {
            typedef boost::mpl::clear<assoc_list1>::type cleared;

            BOOST_MPL_ASSERT((boost::mpl::empty<cleared>::type));
        }
        {
            typedef boost::mpl::clear<assoc_list2>::type cleared;

            BOOST_MPL_ASSERT((boost::mpl::empty<cleared>::type));
        }
        {
            typedef boost::mpl::clear<assoc_list3>::type cleared;

            BOOST_MPL_ASSERT((boost::mpl::empty<cleared>::type));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
