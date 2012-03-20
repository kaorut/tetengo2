/*! \file
    \brief The definition of test_bobura::model::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TYPELIST_H)
#define TESTBOBURA_MODEL_TYPELIST_H

//#include <boost/mpl/at.hpp>
//#include <boost/mpl/pair.hpp>


namespace test_bobura { namespace model
{
    namespace type
    {
        //struct difference;     //!< The difference type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        //typedef std::size_t size_type;
    }
#endif

    //! The type list.
    //typedef
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<type::difference, std::ptrdiff_t>,
    //    tetengo2::meta::assoc_list_end
    //    >
    //    type_list;


}}


#endif
