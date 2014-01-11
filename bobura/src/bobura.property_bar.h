/*! \file
    \brief The definition of bobura::property_bar.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_PROPERTYBAR_H)
#define BOBURA_PROPERTYBAR_H

#include <cassert>
//#include <memory>

#include <boost/mpl/at.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.stdalt.h>
#include <tetengo2.text.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the property bar.

        \tparam SideBar         A side bar type.
        \tparam AbstractWindow  An abstract window type.
        \tparam MapBox          A map box type.
        \tparam Settings        A settings type.
        \tparam MessageCatalog  A message catalog type.
        \tparam MessageTypeList A message type list.
    */
    template <
        typename SideBar,
        typename AbstractWindow,
        typename MapBox,
        typename Settings,
        typename MessageCatalog,
        typename MessageTypeList
    >
    class property_bar : public SideBar
    {
    public:
        // types

        //! The base type.
        typedef SideBar base_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The map box type.
        typedef MapBox map_box_type;

        //! The settings type.
        typedef Settings settings_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The message type list type.
        typedef MessageTypeList message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a property bar.

            \param parent          A parent.
            \param settings        Settings.
            \param message_catalog A message catalog.
        */
        property_bar(
            abstract_window_type&       parent,
            settings_type&              settings,
            const message_catalog_type& message_catalog
        )
        :
        base_type(parent),
        m_settings(settings),
        m_message_catalog(message_catalog),
        m_p_map_box()
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

        /*!
            \brief Returns the map box.

            \return The map box.
        */
        const map_box_type& map_box()
        const
        {
            assert(m_p_map_box);
            return *m_p_map_box;
        }

        /*!
            \brief Returns the map box.

            \return The map box.
        */
        map_box_type& map_box()
        {
            assert(m_p_map_box);
            return *m_p_map_box;
        }

        /*!
            \brief Saves the settings.
        */
        void save_settings()
        {
            m_settings.set_property_bar_width(this->normal_preferred_width());
            m_settings.set_property_bar_minimized(this->minimized());
            m_settings.set_property_bar_splitter_position(m_p_map_box->splitter_position());
        }


    private:
        // types

        typedef typename base_type::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename base_type::dimension_type dimension_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;


        // variables

        settings_type& m_settings;

        const message_catalog_type& m_message_catalog;

        std::unique_ptr<map_box_type> m_p_map_box;


        // functions

        void initialize_property_bar()
        {
            this->set_text(m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Properties")));

            m_p_map_box = tetengo2::stdalt::make_unique<map_box_type>(*this);

            this->size_observer_set().resized().connect(
                typename boost::mpl::at<message_type_list_type, message::property_bar::type::resized>::type(
                    *this, *m_p_map_box
                )
            );

            m_p_map_box->mouse_observer_set().pressed().connect(
                typename boost::mpl::at<message_type_list_type, message::property_bar::type::mouse_pressed>::type(
                    *m_p_map_box
                )
            );

            load_settings();
        }

        void load_settings()
        {
            const auto width = m_settings.property_bar_width();
            if (width)
                this->set_width(*width);
            else
                this->set_width(width_type(32));

            this->size_observer_set().resized()();

            const auto minimized = m_settings.property_bar_minimized();
            if (minimized)
                this->set_minimized(*minimized);
            else
                this->set_minimized(false);

            const auto splitter_position = m_settings.property_bar_splitter_position();
            if (splitter_position)
                m_p_map_box->set_splitter_position(*splitter_position);
            else
                m_p_map_box->set_splitter_position(left_type(16));
        }


    };


}

#endif
