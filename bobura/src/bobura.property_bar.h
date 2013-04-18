/*! \file
    \brief The definition of bobura::property_bar.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_PROPERTYBAR_H)
#define BOBURA_PROPERTYBAR_H

#include <boost/mpl/at.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the property bar.

        \tparam SideBar         A side bar type.
        \tparam AbstractWindow  An abstract window type.
        \tparam MessageTypeList A message type list.
    */
    template <typename SideBar, typename AbstractWindow, typename MessageTypeList>
    class property_bar : public SideBar
    {
    public:
        // types

        //! The base type.
        typedef SideBar base_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The message type list type.
        typedef MessageTypeList message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a property bar.

            \param parent A parent.
        */
        explicit property_bar(abstract_window_type& parent)
        :
        base_type(parent)
        {
            set_observers();
        }

        /*!
            \brief Destroys the property bar.
        */
        virtual ~property_bar()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions


    private:
        // functions

        void set_observers()
        {
            //this->keyboard_observer_set().key_down().connect(
            //    typename boost::mpl::at<
            //        message_type_list_type, message::property_bar::type::keyboard_key_down
            //    >::type(*this)
            //);
        }


    };


}

#endif
