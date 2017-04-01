/*! \file
    \brief Test of class tetengo2::iterator::observable_forward_iteratorpolymorphic_forward_iterator.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>
#include <string>

#include <boost/test/unit_test.hpp>

#include <tetengo2/iterator/polymorphic_forward_iterator.h>


namespace
{
    // types

    using base_type = tetengo2::iterator::polymorphic_forward_iterator<std::string>;

    class concrete_iterator : public base_type
    {
    public:
        explicit concrete_iterator(const int first)
        :
        m_value(first, 'a')
        {}


    private:
        std::string m_value;

        virtual reference dereference()
        override
        {
            return m_value;
        }

        virtual bool equal(const polymorphic_forward_iterator& another)
        const override
        {
            const concrete_iterator* const p_another = dynamic_cast<const concrete_iterator*>(&another);
            if (!p_another)
                return false;

            return m_value == p_another->m_value;
        }

        virtual void increment()
        override
        {
            m_value += "a";
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

        const concrete_iterator iter{ 42 };
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
