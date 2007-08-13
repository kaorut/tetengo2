/*!
	\file Test of bobura - Initalization

	Copyright (C) 2007 kaoru

	$Id$
*/

#include <boost/test/unit_test.hpp>

boost::unit_test::test_suite* init_unit_test_suite(
	const int    /* argc */,
	char** const /* argv */
)
{
	boost::unit_test::test_suite* const p_test_suite
	  = BOOST_TEST_SUITE("Test of bobura");

	return p_test_suite;
}
