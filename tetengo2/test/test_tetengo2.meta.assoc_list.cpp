/*! \file
    \brief Test of class tetengo2::meta::assoc_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
//#include <boost/mpl/begin.hpp>
//#include <boost/mpl/deref.hpp>
//#include <boost/mpl/end.hpp>
#include <boost/mpl/int.hpp>
//#include <boost/mpl/iterator_tags.hpp>
//#include <boost/mpl/next.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/void.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.meta.assoc_list.h"


namespace
{
    // types

    typedef boost::mpl::void_ assoc_list0;

    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000> >,
        boost::mpl::void_
        >
        assoc_list1;

    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<2000> >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<2001> >,
        boost::mpl::void_
        > >
        assoc_list2;

    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<3000> >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<3001> >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<boost::mpl::int_<2>, boost::mpl::int_<3010> >,
        boost::mpl::void_
        > > >
        assoc_list3;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(meta)
BOOST_AUTO_TEST_SUITE(assoc_list)
    // test cases

    BOOST_AUTO_TEST_CASE(deref)
    {
        {
            typedef boost::mpl::deref<assoc_list0>::type dereferenced;

            BOOST_MPL_ASSERT((
                boost::is_same<dereferenced, boost::mpl::void_>
            ));
        }
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

            BOOST_MPL_ASSERT((boost::is_same<end, boost::mpl::void_>));
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


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
