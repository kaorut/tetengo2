/*! \file
    \brief The definition of bobura::message::diagram_view.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_DIAGRAMVIEW_H)
#define BOBURA_MESSAGE_DIAGRAMVIEW_H

#include <utility>

#include <boost/optional.hpp>

#include <tetengo2.text.h>
#include <tetengo2.utility.h>


namespace bobura { namespace message { namespace diagram_view
{
    /*!
        \brief The class template for a station selection observer of the diagram view.

        \tparam PropertyBar A property bar type.
        \tparam Station     A station type.
    */
    template <typename PropertyBar, typename Station>
    class station_selected
    {
    public:
        // types

        //! The property bar type.
        typedef PropertyBar property_bar_type;

        //! The station type.
        typedef Station station_type;


        // constructors and destructor

        /*!
            brief Creates a station selection observer.

            \param property_bar A property bar.
        */
        explicit station_selected(property_bar_type& property_bar)
        :
        m_property_bar(property_bar)
        {}


        // functions

        /*!
            \brief Called when a station is selected.

            \param station A station.
        */
        void operator()(const station_type& station)
        {
            insert_value(string_type(TETENGO2_TEXT("Name")), station.name());
        }


    private:
        // types

        typedef typename property_bar_type::map_box_type::string_type string_type;

        typedef typename property_bar_type::map_box_type::value_type value_type;


        // variables

        property_bar_type& m_property_bar;


        // functions

        void insert_value(string_type key, string_type mapped)
        {
            m_property_bar.map_box().insert_value(
                m_property_bar.map_box().value_count(), value_type(std::move(key), std::move(mapped))
            );
        }


    };


    /*!
        \brief The class template for a train selection observer of the diagram view.

        \tparam PropertyBar A property bar type.
        \tparam Train       A train type.
    */
    template <typename PropertyBar, typename Train>
    class train_selected
    {
    public:
        // types

        //! The property bar type.
        typedef PropertyBar property_bar_type;

        //! The train type.
        typedef Train train_type;

        //! The stop index type.
        typedef typename train_type::stops_type::size_type stop_index_type;


        // constructors and destructor

        /*!
            brief Creates a train selection observer.

            \param property_bar A property bar.
        */
        explicit train_selected(property_bar_type& property_bar)
        :
        m_property_bar(property_bar)
        {}


        // functions

        /*!
            \brief Called when a train is selected.

            \param train                A train.
            \param departure_stop_index A departure stop index. Or boost::none when a whole train is selected.
        */
        void operator()(const train_type& train, const boost::optional<stop_index_type>& departure_stop_index)
        {
            tetengo2::suppress_unused_variable_warning(departure_stop_index);

            insert_value(string_type(TETENGO2_TEXT("Number")), train.number());
            insert_value(string_type(TETENGO2_TEXT("Name")), train.name());
        }


    private:
        // types

        typedef typename property_bar_type::map_box_type::string_type string_type;

        typedef typename property_bar_type::map_box_type::value_type value_type;


        // variables

        property_bar_type& m_property_bar;


        // functions

        void insert_value(string_type key, string_type mapped)
        {
            m_property_bar.map_box().insert_value(
                m_property_bar.map_box().value_count(), value_type(std::move(key), std::move(mapped))
            );
        }


    };


    /*!
        \brief The class template for an unselection observer of the diagram view.

        \tparam PropertyBar A property bar type.
    */
    template <typename PropertyBar>
    class all_unselected
    {
    public:
        // types

        //! The property bar type.
        typedef PropertyBar property_bar_type;


        // constructors and destructor

        /*!
            brief Creates an unselection observer.

            \param property_bar A property bar.
        */
        explicit all_unselected(property_bar_type& property_bar)
        :
        m_property_bar(property_bar)
        {}


        // functions

        /*!
            \brief Called when all the items are unselected.
        */
        void operator()()
        {
            m_property_bar.map_box().clear();
        }


    private:
        // types

        typedef typename property_bar_type::map_box_type::string_type string_type;

        typedef typename property_bar_type::map_box_type::value_type value_type;


        // variables

        property_bar_type& m_property_bar;


    };


}}}


#endif
