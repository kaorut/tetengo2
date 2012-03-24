/*! \file
    \brief The definition of test_tetengo2::gui::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_TYPELIST_H)
#define TESTTETENGO2_GUI_TYPELIST_H

namespace test_tetengo2
{
    /**** Common ************************************************************/

    namespace type
    {
        struct size;           //!< The size type.
        //struct string;         //!< The string type.
        //struct io_string;      //!< The I/O string type.
    }

    //! The common type list.
    //typedef
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<type::size, std::size_t>,
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<type::string, std::string>,
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<type::io_string, std::string>,
    //    tetengo2::meta::assoc_list_end
    //    >>>
    //    type_list;


    /**** Text **************************************************************/

    namespace type { namespace text
    {
        //struct grammar;        //!< The grammar type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace text
    {

    }}
#endif

    //! The text type list.
    //typedef
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<
    //            type::text::grammar, detail::text::grammar_type
    //        >,
    //    tetengo2::meta::assoc_list_end
    //    >
    //    text_type_list;


}


#endif
