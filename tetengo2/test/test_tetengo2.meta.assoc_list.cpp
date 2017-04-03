/*! \file
    \brief Test of class tetengo2::meta::assoc_list.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <type_traits>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/key_type.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/value_type.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/void.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/meta/assoc_list.h>


namespace
{
    // types

    using assoc_list0 = tetengo2::meta::assoc_list_end;

    using assoc_list1 =
        tetengo2::meta::assoc_list<boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000>>,
        tetengo2::meta::assoc_list_end
        >;

    using assoc_list2 =
        tetengo2::meta::assoc_list<boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<2000>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<2001>>,
        tetengo2::meta::assoc_list_end
        >>;

    using assoc_list3 =
        tetengo2::meta::assoc_list<boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<3000>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<3001>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<3100>>,
        tetengo2::meta::assoc_list_end
        >>>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(meta)
BOOST_AUTO_TEST_SUITE(assoc_list)
    // test cases

    BOOST_AUTO_TEST_CASE(type)
    {
        {
            using this_type = assoc_list0::type;

            BOOST_MPL_ASSERT((std::is_same<this_type, assoc_list0>));
        }
        {
            using this_type = assoc_list1::type;

            BOOST_MPL_ASSERT((std::is_same<this_type, assoc_list1>));
        }
        {
            using this_type = assoc_list2::type;

            BOOST_MPL_ASSERT((std::is_same<this_type, assoc_list2>));
        }
    }

    BOOST_AUTO_TEST_CASE(is_sequence)
    {
        {
            using is_sequence = boost::mpl::is_sequence<assoc_list0>::type;

            BOOST_MPL_ASSERT((is_sequence));
        }
        {
            using is_sequence = boost::mpl::is_sequence<assoc_list1>::type;

            BOOST_MPL_ASSERT((is_sequence));
        }
        {
            using is_sequence = boost::mpl::is_sequence<assoc_list2>::type;

            BOOST_MPL_ASSERT((is_sequence));
        }
    }

    BOOST_AUTO_TEST_CASE(sequence_tag)
    {
        {
            using sequence_tag = boost::mpl::sequence_tag<assoc_list0>::type;

            BOOST_MPL_ASSERT((std::is_same<sequence_tag, tetengo2::meta::assoc_list_tag>));
        }
        {
            using sequence_tag = boost::mpl::sequence_tag<assoc_list1>::type;

            BOOST_MPL_ASSERT((std::is_same<sequence_tag, tetengo2::meta::assoc_list_tag>));
        }
        {
            using sequence_tag = boost::mpl::sequence_tag<assoc_list2>::type;

            BOOST_MPL_ASSERT((std::is_same<sequence_tag, tetengo2::meta::assoc_list_tag>));
        }
    }

    BOOST_AUTO_TEST_CASE(deref)
    {
        {
            using dereferenced = boost::mpl::deref<assoc_list1>::type;

            BOOST_MPL_ASSERT((
                std::is_same<dereferenced, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000>>>
            ));
        }
        {
            using dereferenced = boost::mpl::deref<assoc_list2>::type;

            BOOST_MPL_ASSERT((
                std::is_same<dereferenced, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<2000>>>
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        {
            using next = boost::mpl::next<assoc_list1>::type;

            BOOST_MPL_ASSERT((std::is_same<next, assoc_list1::next>));
        }
        {
            using next = boost::mpl::next<assoc_list2>::type;

            BOOST_MPL_ASSERT((std::is_same<next, assoc_list2::next>));

            using next2 = boost::mpl::next<next>::type;

            BOOST_MPL_ASSERT((std::is_same<next2, assoc_list2::next::next>));
        }
    }

    BOOST_AUTO_TEST_CASE(category)
    {
        {
            using category = assoc_list0::category;

            BOOST_MPL_ASSERT((std::is_convertible<category, boost::mpl::forward_iterator_tag>));
        }
        {
            using category = assoc_list1::category;

            BOOST_MPL_ASSERT((std::is_convertible<category, boost::mpl::forward_iterator_tag>));
        }
        {
            using category = assoc_list2::category;

            BOOST_MPL_ASSERT((std::is_convertible<category, boost::mpl::forward_iterator_tag>));
        }
    }

    BOOST_AUTO_TEST_CASE(begin)
    {
        {
            using begin = boost::mpl::begin<assoc_list0>::type;

            BOOST_MPL_ASSERT((std::is_same<begin, assoc_list0>));
        }
        {
            using begin = boost::mpl::begin<assoc_list1>::type;

            BOOST_MPL_ASSERT((std::is_same<begin, assoc_list1>));
            BOOST_MPL_ASSERT((
                std::is_same<
                    boost::mpl::deref<begin>::type, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000>>
                >
            ));
        }
        {
            using begin = boost::mpl::begin<assoc_list2>::type;

            BOOST_MPL_ASSERT((std::is_same<begin, assoc_list2>));
            BOOST_MPL_ASSERT((
                std::is_same<
                    boost::mpl::deref<begin>::type, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<2000>>
                >
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(end)
    {
        {
            using end = boost::mpl::end<assoc_list0>::type;

            BOOST_MPL_ASSERT((std::is_same<end, tetengo2::meta::assoc_list_end>));
        }
        {
            using end = boost::mpl::end<assoc_list1>::type;

            BOOST_MPL_ASSERT((std::is_same<end, assoc_list1::next>));
        }
        {
            using end = boost::mpl::end<assoc_list2>::type;

            BOOST_MPL_ASSERT((std::is_same<end, assoc_list2::next::next>));
        }
    }

    BOOST_AUTO_TEST_CASE(size)
    {
        {
            using size = boost::mpl::size<assoc_list0>::type;

            BOOST_MPL_ASSERT_RELATION(size::value, ==, 0);
        }
        {
            using size = boost::mpl::size<assoc_list1>::type;

            BOOST_MPL_ASSERT_RELATION(size::value, ==, 1);
        }
        {
            using size = boost::mpl::size<assoc_list2>::type;

            BOOST_MPL_ASSERT_RELATION(size::value, ==, 2);
        }
    }

    BOOST_AUTO_TEST_CASE(empty)
    {
        {
            using empty = boost::mpl::empty<assoc_list0>::type;

            BOOST_MPL_ASSERT((empty));
        }
        {
            using empty = boost::mpl::empty<assoc_list1>::type;

            BOOST_MPL_ASSERT_NOT((empty));
        }
        {
            using empty = boost::mpl::empty<assoc_list2>::type;

            BOOST_MPL_ASSERT_NOT((empty));
        }
    }

    BOOST_AUTO_TEST_CASE(front)
    {
        {
            using front = boost::mpl::front<assoc_list1>::type;

            BOOST_MPL_ASSERT((std::is_same<front, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000>>>));
        }
        {
            using front = boost::mpl::front<assoc_list2>::type;

            BOOST_MPL_ASSERT((std::is_same<front, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<2000>>>));
        }
    }

    BOOST_AUTO_TEST_CASE(has_key)
    {
        {
            using has_key = boost::mpl::has_key<assoc_list0, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT_NOT((has_key));
        }
        {
            using has_key = boost::mpl::has_key<assoc_list2, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT((has_key));
        }
        {
            using has_key = boost::mpl::has_key<assoc_list2, boost::mpl::int_<2>>::type;

            BOOST_MPL_ASSERT_NOT((has_key));
        }
    }

    BOOST_AUTO_TEST_CASE(count)
    {
        {
            using count = boost::mpl::count<assoc_list0, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT_RELATION(count::value, ==, 0);
        }
        {
            using count = boost::mpl::count<assoc_list2, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT_RELATION(count::value, ==, 1);
        }
        {
            using count = boost::mpl::count<assoc_list2, boost::mpl::int_<2>>::type;

            BOOST_MPL_ASSERT_RELATION(count::value, ==, 0);
        }
        {
            using count = boost::mpl::count<assoc_list3, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT_RELATION(count::value, ==, 2);
        }
    }

    BOOST_AUTO_TEST_CASE(order)
    {
        {
            using order = boost::mpl::order<assoc_list0, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT((std::is_same<order, boost::mpl::void_>));
        }
        {
            using order = boost::mpl::order<assoc_list2, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT_NOT((std::is_same<order, boost::mpl::void_>));
        }
        {
            using order = boost::mpl::order<assoc_list2, boost::mpl::int_<2>>::type;

            BOOST_MPL_ASSERT((std::is_same<order, boost::mpl::void_>));
        }
    }

    BOOST_AUTO_TEST_CASE(at)
    {
        {
            using value = boost::mpl::at<assoc_list0, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT((std::is_same<value, boost::mpl::void_>));
        }
        //{
        //    using value = boost::mpl::at<assoc_list0, boost::mpl::int_<0>, boost::mpl::int_<9999>>::type;

        //    BOOST_MPL_ASSERT((std::is_same<value, boost::mpl::int_<9999>>));
        //}
        {
            using value = boost::mpl::at<assoc_list2, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT((std::is_same<value, boost::mpl::int_<2000>>));
        }
        {
            using value = boost::mpl::at<assoc_list2, boost::mpl::int_<1>>::type;

            BOOST_MPL_ASSERT((std::is_same<value, boost::mpl::int_<2001>>));
        }
        //{
        //    using value = boost::mpl::at<assoc_list2, boost::mpl::int_<0>, boost::mpl::int_<9999>>::type;

        //    BOOST_MPL_ASSERT((std::is_same<value, boost::mpl::int_<2000>>));
        //}
        {
            using value = boost::mpl::at<assoc_list2, boost::mpl::int_<2>>::type;

            BOOST_MPL_ASSERT((std::is_same<value, boost::mpl::void_>));
        }
        //{
        //    using value = boost::mpl::at<assoc_list2, boost::mpl::int_<2>, boost::mpl::int_<9999>>::type;

        //    BOOST_MPL_ASSERT((std::is_same<value, boost::mpl::int_<9999>>));
        //}
    }

    BOOST_AUTO_TEST_CASE(key_type)
    {
        {
            using key_type =
                boost::mpl::key_type<assoc_list0, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000>>>::type;

            BOOST_MPL_ASSERT((std::is_same<key_type, boost::mpl::int_<0>>));
        }
        {
            using key_type =
                boost::mpl::key_type<assoc_list0, boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<1000>>>::type;

            BOOST_MPL_ASSERT((std::is_same<key_type, boost::mpl::int_<1>>));
        }
    }

    BOOST_AUTO_TEST_CASE(value_type)
    {
        {
            using value_type =
                boost::mpl::value_type<
                    assoc_list0, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000>>
                >::type;

            BOOST_MPL_ASSERT((std::is_same<value_type, boost::mpl::int_<1000>>));
        }
        {
            using value_type =
                boost::mpl::value_type<
                    assoc_list0, boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<1000>>
                >::type;

            BOOST_MPL_ASSERT((std::is_same<value_type, boost::mpl::int_<1000>>));
        }
    }

    BOOST_AUTO_TEST_CASE(insert)
    {
        {
            using inserted =
                boost::mpl::insert<assoc_list0, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000>>>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<inserted>::type::value, ==, 1);
            BOOST_MPL_ASSERT((boost::mpl::has_key<inserted, boost::mpl::int_<0>>));
        }
        {
            using inserted =
                boost::mpl::insert<assoc_list1, boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<1001>>>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<inserted>::type::value, ==, 2);
            BOOST_MPL_ASSERT((boost::mpl::has_key<inserted, boost::mpl::int_<1>>));
        }
        {
            using inserted =
                boost::mpl::insert<
                    assoc_list0,
                    boost::mpl::end<assoc_list0>::type,
                    boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000>>
                >::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<inserted>::type::value, ==, 1);
            BOOST_MPL_ASSERT((boost::mpl::has_key<inserted, boost::mpl::int_<0>>));
        }
        {
            using inserted =
                boost::mpl::insert<
                    assoc_list1,
                    boost::mpl::end<assoc_list1>::type,
                    boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<1001>>
                >::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<inserted>::type::value, ==, 2);
            BOOST_MPL_ASSERT((boost::mpl::has_key<inserted, boost::mpl::int_<1>>));
        }
    }

    BOOST_AUTO_TEST_CASE(insert_range)
    {
        {
            using inserted = boost::mpl::insert_range<assoc_list0, boost::mpl::na, assoc_list0>::type;

            BOOST_MPL_ASSERT((boost::mpl::empty<inserted>));
        }
        {
            using inserted = boost::mpl::insert_range<assoc_list0, boost::mpl::na, assoc_list1>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<inserted>::type::value, ==, 1);
            BOOST_MPL_ASSERT((boost::mpl::has_key<inserted, boost::mpl::int_<0>>));
        }
        {
            using inserted = boost::mpl::insert_range<assoc_list1, boost::mpl::na, assoc_list2>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<inserted>::type::value, ==, 3);
            BOOST_MPL_ASSERT((boost::mpl::has_key<inserted, boost::mpl::int_<1>>));
        }
        {
            using inserted = boost::mpl::insert_range<assoc_list0, boost::mpl::na, boost::mpl::vector<>>::type;

            BOOST_MPL_ASSERT((boost::mpl::empty<inserted>));
        }
        {
            using inserted =
                boost::mpl::insert_range<
                    assoc_list1,
                    boost::mpl::na,
                    boost::mpl::vector<
                        boost::mpl::pair<boost::mpl::int_<11>, boost::mpl::int_<9001>>,
                        boost::mpl::pair<boost::mpl::int_<12>, boost::mpl::int_<9002>>
                    >
                >::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<inserted>::type::value, ==, 3);
            BOOST_MPL_ASSERT((boost::mpl::has_key<inserted, boost::mpl::int_<11>>));
            BOOST_MPL_ASSERT((boost::mpl::has_key<inserted, boost::mpl::int_<12>>));
        }
    }

    BOOST_AUTO_TEST_CASE(erase_key)
    {
        {
            using erased = boost::mpl::erase_key<assoc_list0, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT((boost::mpl::empty<erased>));
        }
        {
            using erased = boost::mpl::erase_key<assoc_list1, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<erased>::type::value, ==, 0);
            BOOST_MPL_ASSERT_NOT((boost::mpl::has_key<erased, boost::mpl::int_<0>>));
        }
        {
            using erased = boost::mpl::erase_key<assoc_list2, boost::mpl::int_<1>>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<erased>::type::value, ==, 1);
            BOOST_MPL_ASSERT_NOT((boost::mpl::has_key<erased, boost::mpl::int_<1>>));
        }
        {
            using erased = boost::mpl::erase_key<assoc_list3, boost::mpl::int_<0>>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<erased>::type::value, ==, 1);
            BOOST_MPL_ASSERT_NOT((boost::mpl::has_key<erased, boost::mpl::int_<0>>));
        }
        {
            using erased = boost::mpl::erase_key<assoc_list3, boost::mpl::int_<1>>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<erased>::type::value, ==, 2);
            BOOST_MPL_ASSERT_NOT((boost::mpl::has_key<erased, boost::mpl::int_<1>>));
            BOOST_MPL_ASSERT((
                std::is_same<erased::element, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<3000>>>
            ));
            BOOST_MPL_ASSERT((
                std::is_same<erased::next::element, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<3100>>>
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(erase)
    {
        {
            using erased = boost::mpl::erase<assoc_list0, assoc_list0>::type;

            BOOST_MPL_ASSERT((boost::mpl::empty<erased>));
        }
        {
            using erased = boost::mpl::erase<assoc_list1, assoc_list1>::type;
            
            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<erased>::type::value, ==, 0);
            BOOST_MPL_ASSERT_NOT((boost::mpl::has_key<erased, boost::mpl::int_<0>>));
        }
        {
            using erased = boost::mpl::erase<assoc_list1, assoc_list1::next>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<erased>::type::value, ==, 1);
        }
        {
            using erased = boost::mpl::erase<assoc_list2, assoc_list2::next>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<erased>::type::value, ==, 1);
            BOOST_MPL_ASSERT_NOT((boost::mpl::has_key<erased, boost::mpl::int_<1>>));
        }
        {
            using erased = boost::mpl::erase<assoc_list3, assoc_list3>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<erased>::type::value, ==, 1);
            BOOST_MPL_ASSERT_NOT((boost::mpl::has_key<erased, boost::mpl::int_<0>>));
        }
        {
            using erased = boost::mpl::erase<assoc_list3, assoc_list3::next>::type;
            
            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<erased>::type::value, ==, 2);
            BOOST_MPL_ASSERT_NOT((boost::mpl::has_key<erased, boost::mpl::int_<1>>));
            BOOST_MPL_ASSERT((
                std::is_same<erased::element, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<3000>>>
            ));
            BOOST_MPL_ASSERT((
                std::is_same<erased::next::element, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<3100>>>
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(clear)
    {
        {
            using cleared = boost::mpl::clear<assoc_list0>::type;

            BOOST_MPL_ASSERT((boost::mpl::empty<cleared>));
        }
        {
            using cleared = boost::mpl::clear<assoc_list1>::type;

            BOOST_MPL_ASSERT((boost::mpl::empty<cleared>));
        }
        {
            using cleared = boost::mpl::clear<assoc_list2>::type;

            BOOST_MPL_ASSERT((boost::mpl::empty<cleared>));
        }
        {
            using cleared = boost::mpl::clear<assoc_list3>::type;

            BOOST_MPL_ASSERT((boost::mpl::empty<cleared>));
        }
    }

    BOOST_AUTO_TEST_CASE(push_front)
    {
        {
            using pushed =
                boost::mpl::push_front<
                    assoc_list0, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000>>
                >::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<pushed>::type::value, ==, 1);
            BOOST_MPL_ASSERT((
                std::is_same<pushed::element, boost::mpl::pair<boost::mpl::int_<0>, boost::mpl::int_<1000>>>
            ));
        }
        {
            using pushed =
                boost::mpl::push_front<
                    assoc_list1, boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<1001>>
                >::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<pushed>::type::value, ==, 2);
            BOOST_MPL_ASSERT((
                std::is_same<pushed::element, boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<1001>>>
            ));
        }
    }

    BOOST_AUTO_TEST_CASE(pop_front)
    {
        {
            using popped = boost::mpl::pop_front<assoc_list1>::type;

            BOOST_MPL_ASSERT((boost::mpl::empty<popped>));
        }
        {
            using popped = boost::mpl::pop_front<assoc_list2>::type;

            BOOST_MPL_ASSERT_RELATION(boost::mpl::size<popped>::type::value, ==, 1);
            BOOST_MPL_ASSERT((
                std::is_same<popped::element, boost::mpl::pair<boost::mpl::int_<1>, boost::mpl::int_<2001>>>
            ));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
