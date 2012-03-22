/*! \file
    \brief The definition of test_tetengo2::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_TYPELIST_H)
#define TESTTETENGO2_TYPELIST_H

//#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>


namespace test_tetengo2
{
    /**** Common ************************************************************/

    namespace type
    {
        //struct size;           //!< The size type.
        //struct difference;     //!< The difference type.
        //struct string;         //!< The string type.
        //struct output_stream;  //!< The output stream type.
    }

    //! The common type list.
    //typedef
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<type::size, std::size_t>,
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<type::difference, std::ptrdiff_t>,
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<type::string, std::string>,
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<type::output_stream, std::ostream>,
    //    tetengo2::meta::assoc_list_end
    //    >>>>
    //    type_list;


    /**** Tetengo2 **********************************************************/

    namespace type { namespace tetengo2
    {
        struct grade_type_set; //!< The station grade type set type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace tetengo2
    {

    }}
#endif

    //! The tetengo2 type list.
    //typedef
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<
    //            type::model::grade_type_set, detail::grade_type_set_type
    //        >,
    //    tetengo2::meta::assoc_list_end
    //    >
    //    tetengo2_type_list;


}


#endif
