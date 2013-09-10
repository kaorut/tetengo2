/*! \file
    \brief The definition of bobura::message::property_bar.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_PROPERTYBAR_H)
#define BOBURA_MESSAGE_PROPERTYBAR_H


namespace bobura { namespace message { namespace property_bar
{
    /*!
        \brief The class template for a resized observer of the property bar.

        \tparam SideBar A side bar type.
        \tparam MapBox  A map box type.
    */
    template <typename SideBar, typename MapBox>
    class resized
    {
    public:
        // types

        //! The side bar type.
        typedef SideBar side_bar_type;

        //! The map box type.
        typedef MapBox map_box_type;


        // constructors and destructor

        /*!
            \brief Creates a resized observer of the property bar.

            \param property_bar A property_bar.
            \param map_box      A map box.
        */
        resized(const side_bar_type& property_bar, map_box_type& map_box)
        :
        m_property_bar(property_bar),
        m_map_box(map_box)
        {}


        // functions

        /*!
            \brief Called when the main window is resized.
        */
        void operator()()
        const
        {

        }


    private:
        // variables

        const side_bar_type& m_property_bar;

        map_box_type& m_map_box;


    };


}}}


#endif
