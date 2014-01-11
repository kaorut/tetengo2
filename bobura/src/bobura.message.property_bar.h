/*! \file
    \brief The definition of bobura::message::property_bar.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_PROPERTYBAR_H)
#define BOBURA_MESSAGE_PROPERTYBAR_H

#include <tetengo2.utility.h>


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
            if (m_property_bar.minimized())
            {
                m_map_box.set_visible(false);
            }
            else
            {
                m_map_box.set_position_and_dimension(
                    m_property_bar.child_control_area_position(), m_property_bar.child_control_area_dimension()
                );
                m_map_box.size_observer_set().resized()();
                m_map_box.set_visible(true);
            }
        }


    private:
        // variables

        const side_bar_type& m_property_bar;

        map_box_type& m_map_box;


    };


    /*!
        \brief The class template for a mouse-pressed observer of the map box.

        \tparam MapBox A map box type.
    */
    template <typename MapBox>
    class mouse_pressed
    {
    public:
        // types

        //! The map box type.
        typedef MapBox map_box_type;

        //! The position type.
        typedef typename map_box_type::position_type position_type;

        //! The mouse button type.
        typedef typename map_box_type::mouse_observer_set_type::mouse_button_type mouse_button_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse-pressed observer of the map box.

            \param map_box A map box.
        */
        explicit mouse_pressed(map_box_type& map_box)
        :
        m_map_box(map_box)
        {}


        // functions

        /*!
            \brief Called when the main window is resized.

            \param button   A button kind.
            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        void operator()(
            const mouse_button_type button,
            const position_type&    position,
            const bool              shift,
            const bool              control,
            const bool              meta
        )
        const
        {
            tetengo2::suppress_unused_variable_warning(button, position, shift, control, meta);

            m_map_box.set_focus();
        }


    private:
        // variables

        map_box_type& m_map_box;


    };


}}}


#endif
