/*! \file
    \brief The definition of bobura::message::diagram_view.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_DIAGRAMVIEW_H)
#define BOBURA_MESSAGE_DIAGRAMVIEW_H

#include <cassert>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <boost/format.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.text.h>


namespace bobura { namespace message { namespace diagram_view
{
    /*!
        \brief The class template for a station selection observer of the diagram view.

        \tparam PropertyBar         A property bar type.
        \tparam Model               A model type.
        \tparam StationGradeTypeSet A station grade type set type.
        \tparam MessageCatalog      A message catalog type.
    */
    template <typename PropertyBar, typename Model, typename StationGradeTypeSet, typename MessageCatalog>
    class station_selected
    {
    public:
        // types

        //! The property bar type.
        typedef PropertyBar property_bar_type;

        //! The model type.
        typedef Model model_type;

        //! The timetable type.
        typedef typename model_type::timetable_type timetable_type;

        //! The station location type.
        typedef typename timetable_type::station_location_type station_location_type;

        //! The station type.
        typedef typename station_location_type::station_type station_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            brief Creates a station selection observer.

            \param property_bar    A property bar.
            \param model           A model.
            \param message_catalog A message catalog.
        */
        station_selected(
            property_bar_type&          property_bar,
            const model_type&           model,
            const message_catalog_type& message_catalog
        )
        :
        m_property_bar(property_bar),
        m_model(model),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Called when a station is selected.

            \param station A station.
        */
        void operator()(const station_type& station)
        {
            insert_value(m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Name")), station.name());
            insert_value(m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Grade")), grade_string(station.grade()));
        }


    private:
        // types

        typedef typename property_bar_type::map_box_type::string_type string_type;

        typedef typename property_bar_type::map_box_type::value_type value_type;

        typedef typename station_type::grade_type grade_type;


        // variables

        property_bar_type& m_property_bar;

        const model_type& m_model;

        const message_catalog_type& m_message_catalog;


        // functions

        void insert_value(string_type key, string_type mapped)
        {
            m_property_bar.map_box().insert_value(
                m_property_bar.map_box().value_count(), value_type(std::move(key), std::move(mapped))
            );
        }

        string_type grade_string(const grade_type& grade)
        const
        {
            if      (&grade == &station_grade_type_set_type::local_type::instance())
                return m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Local Station"));
            else if (&grade == &station_grade_type_set_type::principal_type::instance())
                return m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Principal Station"));
            else if (&grade == &station_grade_type_set_type::local_terminal_type::instance())
                return m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Local Terminal Station"));
            else if (&grade == &station_grade_type_set_type::principal_terminal_type::instance())
                return m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Principal Terminal Station"));

            assert(false);
            BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown station grade."));
        }


    };


    /*!
        \brief The class template for a train selection observer of the diagram view.

        \tparam PropertyBar         A property bar type.
        \tparam Model               A model type.
        \tparam StationGradeTypeSet A station grade type set type.
        \tparam MessageCatalog      A message catalog type.
    */
    template <typename PropertyBar, typename Model, typename StationGradeTypeSet, typename MessageCatalog>
    class train_selected
    {
    public:
        // types

        //! The property bar type.
        typedef PropertyBar property_bar_type;

        //! The model type.
        typedef Model model_type;

        //! The timetable type.
        typedef typename model_type::timetable_type timetable_type;

        //! The train type.
        typedef typename timetable_type::train_type train_type;

        //! The stop index type.
        typedef typename train_type::stops_type::size_type stop_index_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            brief Creates a train selection observer.

            \param property_bar    A property bar.
            \param model           A model.
            \param message_catalog A message catalog.
        */
        train_selected(
            property_bar_type&          property_bar,
            const model_type&           model,
            const message_catalog_type& message_catalog
        )
        :
        m_property_bar(property_bar),
        m_model(model),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Called when a train is selected.

            \param train                A train.
            \param down                 Set true when the train is downward. Otherwise the train is upward.
            \param departure_stop_index A departure stop index. Or boost::none when a whole train is selected.
        */
        void operator()(
            const train_type&                       train,
            const bool                              down,
            const boost::optional<stop_index_type>& departure_stop_index
        )
        {
            insert_value(m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Train Number")), train.number());
            insert_value(m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Kind")), build_kind_name(train));
            insert_value(m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Name")), build_name(train));
            insert_value(m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Note")), train.note());
            if (departure_stop_index)
            {
                insert_value(
                    m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Departure and Arrival")),
                    build_departure_and_arrival(train, *departure_stop_index, down)
                );
            }
            else
            {
                insert_value(
                    m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Principal Arrivals and Departures")),
                    build_departures_and_arrivals(train, down)
                );
            }
       }


    private:
        // types

        typedef typename property_bar_type::map_box_type::string_type string_type;

        typedef typename property_bar_type::map_box_type::value_type value_type;

        typedef typename train_type::kind_index_type kind_index_type;

        typedef typename train_type::stop_type stop_type;

        typedef typename stop_type::time_type time_type;


        // variables

        property_bar_type& m_property_bar;

        const model_type& m_model;

        const message_catalog_type& m_message_catalog;


        // functions

        void insert_value(string_type key, string_type mapped)
        {
            m_property_bar.map_box().insert_value(
                m_property_bar.map_box().value_count(), value_type(std::move(key), std::move(mapped))
            );
        }

        string_type build_kind_name(const train_type& train)
        const
        {
            const kind_index_type kind_index = train.kind_index();
            if (kind_index >= m_model.timetable().train_kinds().size())
                BOOST_THROW_EXCEPTION(std::out_of_range("Too large train kind index."));

            return m_model.timetable().train_kinds()[kind_index].name();
        }

        string_type build_name(const train_type& train)
        const
        {
            if (train.name_number().empty())
            {
                return train.name();
            }
            else
            {
                return
                    (
                        boost::basic_format<typename string_type::value_type>(
                            m_message_catalog.get(TETENGO2_TEXT("Diagram:%1% No. %2%"))
                        ) % train.name() % train.name_number()
                    ).str();
            }
        }

        string_type build_departure_and_arrival(
            const train_type&     train,
            const stop_index_type stop_index,
            const bool            down
        )
        const
        {
            if (stop_index >= train.stops().size() || stop_index >= m_model.timetable().station_locations().size())
                BOOST_THROW_EXCEPTION(std::out_of_range("Too large train stop index."));

            string_type text;

            {
                const stop_type& departure = train.stops()[stop_index];
                string_type stop_text = build_stop_text(departure, stop_index, false, true);
                if (stop_text.empty())
                    text += m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Pass"));
                else
                    text += std::move(stop_text);
            }
            text += string_type(TETENGO2_TEXT("\n"));
            {
                const stop_index_type arrival_stop_index = next_stop(train, stop_index, down);
                const stop_type& arrival = train.stops()[arrival_stop_index];
                string_type stop_text = build_stop_text(arrival, arrival_stop_index, true, false);
                if (stop_text.empty())
                    text += m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Pass"));
                else
                    text += std::move(stop_text);
            }

            return text;
        }

        string_type build_departures_and_arrivals(const train_type& train, const bool down)
        const
        {
            string_type text;

            const std::ptrdiff_t first = down ? 0 : train.stops().size() - 1;
            const std::ptrdiff_t last = down ? train.stops().size(): -1;
            const std::ptrdiff_t step = down ? 1 : -1;
            for (std::ptrdiff_t i = first; i != last; i += step)
            {
                if (i != first && i + step != last && !is_principal_station(i))
                    continue;

                const stop_type& stop = train.stops()[i];
                string_type stop_text = build_stop_text(stop, i, true, true);
                if (!stop_text.empty())
                {
                    if (!text.empty())
                        text += string_type(TETENGO2_TEXT("\n"));
                    text += std::move(stop_text);
                }
            }

            return text;
        }

        bool is_principal_station(const stop_index_type stop_index)
        const
        {
            return
                &m_model.timetable().station_locations()[stop_index].station().grade() !=
                &station_grade_type_set_type::local_type::instance();
        }

        string_type build_stop_text(
            const stop_type&      stop,
            const stop_index_type stop_index,
            const bool            arrival,
            const bool            departure
        )
        const
        {
            if (stop.arrival() == time_type::uninitialized() && stop.departure() == time_type::uninitialized())
                return string_type();

            assert(stop_index < m_model.timetable().station_locations().size());

            string_type arrival_time;
            if (
                stop.arrival() != time_type::uninitialized() &&
                (arrival || (departure && stop.departure() == time_type::uninitialized()))
            )
            {
                arrival_time = time_text(stop.arrival(), false);
            }

            string_type departure_time;
            if (
                stop.departure() != time_type::uninitialized() &&
                (departure || (arrival && stop.arrival() == time_type::uninitialized()))
            )
            {
                departure_time = time_text(stop.departure(), true);
            }

            std::basic_ostringstream<typename string_type::value_type> stream;

            stream <<
                m_model.timetable().station_locations()[stop_index].station().name() <<
                string_type(TETENGO2_TEXT(" "));

            if (!arrival_time.empty() && !departure_time.empty())
            {
                stream << std::move(arrival_time) << string_type(TETENGO2_TEXT("/")) << std::move(departure_time);
            }
            else if (!arrival_time.empty())
            {
                stream << std::move(arrival_time);
            }
            else if (!departure_time.empty())
            {
                stream << std::move(departure_time);
            }
            else
            {
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("We must not come here."));
            }

            if (stop.operational())
            {
                stream <<
                    string_type(TETENGO2_TEXT(" (")) <<
                    m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Operational")) <<
                    string_type(TETENGO2_TEXT(")"));
            }

            if (!stop.platform().empty())
                stream << string_type(TETENGO2_TEXT(" [")) << stop.platform() << string_type(TETENGO2_TEXT("]"));

            return stream.str();
        }

        string_type time_text(const time_type& time, const bool departure)
        const
        {
            assert(time != time_type::uninitialized());

            const typename time_type::hours_minutes_seconds_type hms = time.hours_minutes_seconds();
            std::basic_ostringstream<typename string_type::value_type> stream;
            if (departure)
            {
                stream <<
                    boost::basic_format<typename string_type::value_type>(
                        m_message_catalog.get(TETENGO2_TEXT("PropertyBar:%1$2d %2$02dd"))
                    ) % hms.hours() % hms.minutes();
            }
            else
            {
                stream <<
                    boost::basic_format<typename string_type::value_type>(
                        m_message_catalog.get(TETENGO2_TEXT("PropertyBar:%1$2d %2$02da"))
                    ) % hms.hours() % hms.minutes();
            }

            return stream.str();
        }

        stop_index_type next_stop(const train_type& train, const stop_index_type stop_index, const bool down)
        const
        {
            const std::ptrdiff_t step = down ? 1 : -1;
            for (stop_index_type i = stop_index; ; i += step)
            {
                if (down && stop_index == train.stops().size() - 1)
                    return i;
                if (!down && stop_index == 0)
                    return i;

                if (i == stop_index)
                    continue;

                const stop_type& stop = train.stops()[i];
                if (stop.departure() != time_type::uninitialized() || stop.arrival() != time_type::uninitialized())
                    return i;
            }
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
