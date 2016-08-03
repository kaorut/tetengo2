/*! \file
    \brief Test of class tetengo2::iterator::observable_forward_iteratorpolymorphic_forward_iterator.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/iterator/polymorphic_forward_iterator.h>


namespace
{
    // types

    class concrete_iterator : public tetengo2::iterator::polymorphic_forward_iterator<int>
    {
    public:
        explicit concrete_iterator(const int first)
        :
        m_count(first)
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
            const concrete_iterator iter1{ 42 };
            const concrete_iterator iter2{ iter1 };

            BOOST_WARN_MESSAGE(false, "Compaire the values of both.");
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
