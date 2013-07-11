/*! \file
    \brief The definition of bobura::property_bar.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_PROPERTYBAR_H)
#define BOBURA_PROPERTYBAR_H

#include <boost/mpl/at.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.stdalt.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the property bar.

        \tparam SideBar         A side bar type.
        \tparam AbstractWindow  An abstract window type.
        \tparam MessageCatalog  A message catalog type.
        \tparam MessageTypeList A message type list.
    */
    template <typename SideBar, typename AbstractWindow, typename MessageCatalog, typename MessageTypeList>
    class property_bar : public SideBar
    {
    public:
        // types

        //! The base type.
        typedef SideBar base_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The message type list type.
        typedef MessageTypeList message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a property bar.

            \param parent          A parent.
            \param message_catalog A message catalog.
        */
        property_bar(abstract_window_type& parent, const message_catalog_type& message_catalog)
        :
        base_type(parent),
        m_message_catalog(message_catalog)
        {
            initialize_property_bar();
        }

        /*!
            \brief Destroys the property bar.
        */
        virtual ~property_bar()
        TETENGO2_STDALT_NOEXCEPT
        {}


        // functions


    private:
        // variables

        const message_catalog_type& m_message_catalog;


        // functions

        void initialize_property_bar()
        {
            this->set_text(m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Properties")));

            //this->keyboard_observer_set().key_down().connect(
            //    typename boost::mpl::at<
            //        message_type_list_type, message::property_bar::type::keyboard_key_down
            //    >::type(*this)
            //);
        }


    };


}

#endif
