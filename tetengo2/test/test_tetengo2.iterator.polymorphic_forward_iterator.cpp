/*! \file
    \brief Test of class tetengo2::iterator::observable_forward_iteratorpolymorphic_forward_iterator.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>
#include <boost/test/unit_test.hpp>

#include <tetengo2/iterator/polymorphic_forward_iterator.h>


namespace
{
    // types

    using base_type = tetengo2::iterator::polymorphic_forward_iterator<int>;

    class concrete_iterator : public base_type
    {
    public:
        explicit concrete_iterator(const int first)
        :
        base_type(),
        m_count(first)
        {}

        concrete_iterator(concrete_iterator&& another)
        :
        base_type(std::forward<concrete_iterator>(another)),
        m_count(another.m_count)
        {}

        concrete_iterator(const concrete_iterator& another)
        :
        base_type(another),
        m_count(another.m_count)
        {}


    private:
        int m_count;

        virtual reference dereference()
        override
        {
            return m_count;
        }

        virtual bool equal(const polymorphic_forward_iterator& another)
        const override
        {
            const concrete_iterator* const p_another = dynamic_cast<const concrete_iterator*>(&another);
            if (!p_another)
                return false;

            return m_count == p_another->m_count;
        }

        virtual void increment()
        override
        {
            ++m_count;
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(iterator)
BOOST_AUTO_TEST_SUITE(polymorphic_forward_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_iterator iter{ 42 };
        }
        {
            concrete_iterator iter1{ 42 };
            const concrete_iterator iter2{ std::move(iter1) };

            BOOST_TEST(*iter2 == 42);
        }
        {
            const concrete_iterator iter1{ 42 };
            const concrete_iterator iter2{ iter1 };

            BOOST_TEST(*iter2 == *iter1);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
