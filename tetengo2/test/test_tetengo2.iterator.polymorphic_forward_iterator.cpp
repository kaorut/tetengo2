/*! \file
    \brief Test of class tetengo2::iterator::observable_forward_iteratorpolymorphic_forward_iterator.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>
#include <string>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/iterator/polymorphic_forward_iterator.h>


namespace {
    // types

    using base_type = tetengo2::iterator::polymorphic_forward_iterator<std::string>;

    class concrete_iterator : public base_type
    {
    public:
        explicit concrete_iterator(const int first) : m_value(first, 'a') {}


    private:
        std::string m_value;

        virtual reference dereference() override
        {
            return m_value;
        }

        virtual bool equal(const base_type& another) const override
        {
            const concrete_iterator* const p_another = dynamic_cast<const concrete_iterator*>(&another);
            if (!p_another)
                return false;

            return m_value == p_another->m_value;
        }

        virtual void increment() override
        {
            m_value += "a";
        }
    };

    class other_concrete_iterator : public base_type
    {
    public:
        explicit other_concrete_iterator(const int first) : m_value(first, 'a') {}


    private:
        std::string m_value;

        virtual reference dereference() override
        {
            return m_value;
        }

        virtual bool equal(const base_type& another) const override
        {
            const other_concrete_iterator* const p_another = dynamic_cast<const other_concrete_iterator*>(&another);
            if (!p_another)
                return false;

            return m_value == p_another->m_value;
        }

        virtual void increment() override
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

            BOOST_AUTO_TEST_CASE(operator_dereference)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const concrete_iterator iter{ 42 };

                    BOOST_CHECK(*iter == std::string(42, 'a'));
                }
                {
                    concrete_iterator iter{ 42 };

                    *iter = std::string(24, 'a');

                    BOOST_CHECK(*iter == std::string(24, 'a'));
                }
            }

            BOOST_AUTO_TEST_CASE(operator_arrow)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const concrete_iterator iter{ 42 };

                    BOOST_TEST(iter->length() == 42U);
                }
                {
                    const concrete_iterator iter{ 42 };

                    iter->append("a");

                    BOOST_TEST(iter->length() == 43U);
                }
            }

            BOOST_AUTO_TEST_CASE(operator_increment)
            {
                BOOST_TEST_PASSPOINT();

                concrete_iterator iter{ 42 };

                const base_type& incremented = ++iter;

                BOOST_CHECK(*iter == std::string(43, 'a'));
                BOOST_CHECK(*incremented == std::string(43, 'a'));
            }

            BOOST_AUTO_TEST_CASE(operator_postincrement)
            {
                BOOST_TEST_PASSPOINT();

                concrete_iterator iter{ 42 };

                iter++;

                BOOST_CHECK(*iter == std::string(43, 'a'));
            }

            BOOST_AUTO_TEST_CASE(operator_equal)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const concrete_iterator iter1{ 42 };
                    const concrete_iterator iter2{ 42 };

                    BOOST_CHECK(iter1 == iter2);
                }
                {
                    const concrete_iterator iter1{ 42 };
                    const concrete_iterator iter2{ 24 };

                    BOOST_CHECK(!(iter1 == iter2));
                }
                {
                    const concrete_iterator       iter1{ 42 };
                    const other_concrete_iterator iter2{ 42 };

                    BOOST_CHECK(!(iter1 == iter2));
                }
            }

            BOOST_AUTO_TEST_CASE(operator_not_equal)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const concrete_iterator iter1{ 42 };
                    const concrete_iterator iter2{ 42 };

                    BOOST_CHECK(!(iter1 != iter2));
                }
                {
                    const concrete_iterator iter1{ 42 };
                    const concrete_iterator iter2{ 24 };

                    BOOST_CHECK(iter1 != iter2);
                }
                {
                    const concrete_iterator       iter1{ 42 };
                    const other_concrete_iterator iter2{ 42 };

                    BOOST_CHECK(iter1 != iter2);
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
