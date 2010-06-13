/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELISTNEW_H)
#define BOBURA_TYPELISTNEW_H

//#include <cstddef>
#include <string>

#include <boost/mpl/pair.hpp>

#include <tetengo2.encoder.h>
#include <tetengo2.messages.h>
#include <tetengo2.message_catalog_parser.h>
#include <tetengo2.encoding.locale.h>
#include <tetengo2.encoding.win32.utf8.h>
#include <tetengo2.meta.assoc_list.h>


namespace bobura
{
    /**** Common ************************************************************/

    namespace type
    {
        struct difference;     //!< The difference type.
        struct size;           //!< The size type.
        struct string;         //!< The string type.
    }

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::size, std::size_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, std::wstring>,
        tetengo2::meta::assoc_list_end
        > > >
        common_type_list;


    /**** Locale ************************************************************/

    namespace type
    {
        struct internal_encoding; //!< The internal encoding type.
        struct ui_encoding;    //!< The encoding type for the user interface.
        struct exception_encoding; //!< The encoding type for exceptions.
        struct message_catalog_encoding; //!< The encoding type for the
                                         //!< message catalog.
        struct locale_name_encoding; //!< The encoder type for locale names.

        struct internal_encoder; //!< The internal encoder type.
        struct ui_encoder;     //!< The encoder type for the user interface.
        struct exception_encoder; //!< The encoder type for exceptions.
        struct message_catalog_encoder; //!< The encoder type for the
                                        //!< message catalog.
        struct locale_name_encoder; //!< The encoder type for locale names.

        struct message_catalog_parser; //!< The message catalog parser type.
        struct messages_facet; //!< The messages facet type.
    }

    //! The type list for the locale.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::internal_encoding,
                tetengo2::encoding::locale<
                    boost::mpl::at<common_type_list, type::string>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui_encoding, int>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::exception_encoding, int>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::message_catalog_encoding, int>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale_name_encoding, int>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::internal_encoder, int>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui_encoder, int>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::exception_encoder, int>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::message_catalog_encoder, int>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale_name_encoder, int>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::messages_facet, int>,
        tetengo2::meta::assoc_list_end
        > > > > > > > > > > >
        locale_type_list;


    /**** All ***************************************************************/

    //! The type list for Bobura.
    typedef
        boost::mpl::insert_range<
            common_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            locale_type_list, tetengo2::meta::assoc_list_end,
        tetengo2::meta::assoc_list_end
        >::type>::type
        bobura_type_list;


}


#endif
