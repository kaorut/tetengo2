/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLE_H)
#define BOBURA_MODEL_TIMETABLE_H

#include <algorithm>
#include <cstddef>
//#include <functional>
//#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2.cpp11.h>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a timetable.

        \tparam String                    A string type.
        \tparam StationLocation           A station location type.
        \tparam StationIntervalCalculator A station interval calculatortype.
        \tparam TrainKind                 A train kind type.
        \tparam Train                     A train type.
        \tparam FontColorSet              A font and color set type.
        \tparam ObserverSet               An observer set type.
    */
    template <
        typename String,
        typename StationLocation,
        typename StationIntervalCalculator,
        typename TrainKind,
        typename Train,
        typename FontColorSet, 
        typename ObserverSet
    >
    class timetable :
        private boost::equality_comparable<
            timetable<String, StationLocation, StationIntervalCalculator, TrainKind, Train, FontColorSet, ObserverSet>
        >
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The station location type.
        typedef StationLocation station_location_type;

        //! The station locations type.
        typedef std::vector<station_location_type> station_locations_type;

        //! The station interval calculator type.
        typedef StationIntervalCalculator station_interval_calculator_type;

        //! The station intervals type.
        typedef typename station_interval_calculator_type::station_intervals_type station_intervals_type;

        //! The train kind type.
        typedef TrainKind train_kind_type;

        //! The train kinds type.
        typedef std::vector<train_kind_type> train_kinds_type;

        //! The train kind index type.
        typedef typename train_kinds_type::size_type train_kind_index_type;

        //! The train type.
        typedef Train train_type;

        //! The trains type.
        typedef std::vector<train_type> trains_type;

        //! The font color set type.
        typedef FontColorSet font_color_set_type;

        //! The observer set type.
        typedef ObserverSet observer_set_type;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.
        */
        timetable()
        :
        m_company_name(),
        m_line_name(),
        m_note(),
        m_station_locations(),
        m_train_kinds(),
        m_down_trains(),
        m_up_trains(),
        m_font_color_set(font_color_set_type::default_()),
        m_observer_set()
        {}


        // functions

        /*!
            \brief Checks whether this is equal to another timetable.

            \param one     One timetable.
            \param another Another timetable.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const timetable& one, const timetable& another)
        {
            return
                one.m_company_name == another.m_company_name &&
                one.m_line_name == another.m_line_name &&
                one.m_note == another.m_note &&
                one.m_station_locations == another.m_station_locations &&
                one.m_train_kinds == another.m_train_kinds &&
                one.m_down_trains == another.m_down_trains &&
                one.m_up_trains == another.m_up_trains;
        }

        /*!
            \brief Returns the company name.

            \return The company name.
        */
        const string_type& company_name()
        const
        {
            return m_company_name;
        }

        /*!
            \brief Sets a company name.

            \param company_name A company name.
        */
        void set_company_name(string_type company_name)
        {
            m_company_name = std::move(company_name);

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the line name.

            \return The line name.
        */
        const string_type& line_name()
        const
        {
            return m_line_name;
        }

        /*!
            \brief Sets a line name.

            \param line_name A line name.
        */
        void set_line_name(string_type line_name)
        {
            m_line_name = std::move(line_name);

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the note.

            \return The note.
        */
        const string_type& note()
        const
        {
            return m_note;
        }

        /*!
            \brief Sets a note.

            \param note A note.
        */
        void set_note(string_type note)
        {
            m_note = std::move(note);

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the station locations.

            \return The station locations.
        */
        const station_locations_type& station_locations()
        const
        {
            return m_station_locations;
        }

        /*!
            \brief Inserts a station location.

            After the insertion, the station locations must be sequenced in ascending order.

            It also inserts a stop to the every train with uninitialized arrival and departure time and an empty
            platform, so that the count of the station locations coincides with the one of the every train stop.

            \param position         A position where a station location is inserted.
            \param station_location A station location.

            \throw std::invalid_argument When the station locations are not sequenced in ascending order after the
                                         insertion.
        */
        void insert_station_location(
            const typename station_locations_type::const_iterator position,
            station_location_type                                 station_location
        )
        {
            if (!can_insert_to(position, station_location))
                BOOST_THROW_EXCEPTION(std::invalid_argument("The insertion position is invalid."));

            const difference_type offset =
                std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), position);

            m_station_locations.insert(
                tetengo2::cpp11::as_insertion_iterator(m_station_locations, position), std::move(station_location)
            );

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                TETENGO2_CPP11_BIND(insert_train_stop, tetengo2::cpp11::placeholders_1(), offset)
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                TETENGO2_CPP11_BIND(insert_train_stop, tetengo2::cpp11::placeholders_1(), offset)
            );

            m_observer_set.changed()();
        }

        /*!
            \brief Erases the station locations.

            It also erases stops from the every train, so that the count of the station locations coincides with the
            one of the every train stop.

            \param first A first iterator among the erased station locations.
            \param last  A last iterator among the erased station locations.
        */
        void erase_station_locations(
            const typename station_locations_type::const_iterator first,
            const typename station_locations_type::const_iterator last
        )
        {
            const difference_type first_offset =
                std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), first);
            const difference_type last_offset =
                std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), last);

            m_station_locations.erase(
                tetengo2::cpp11::as_insertion_iterator(m_station_locations, first),
                tetengo2::cpp11::as_insertion_iterator(m_station_locations, last)
            );

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                TETENGO2_CPP11_BIND(erase_train_stops, tetengo2::cpp11::placeholders_1(), first_offset, last_offset)
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                TETENGO2_CPP11_BIND(erase_train_stops, tetengo2::cpp11::placeholders_1(), first_offset, last_offset)
            );

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the station intervals.

            \return The station intervals.
        */
        station_intervals_type station_intervals()
        const
        {
            const station_interval_calculator_type calculator(m_station_locations, m_down_trains, m_up_trains);
            return calculator.calculate();
        }

        /*!
            \brief Returns the train kinds.

            \return The train kinds.
        */
        const train_kinds_type& train_kinds()
        const
        {
            return m_train_kinds;
        }

        /*!
            \brief Checks whether the train kind is referred by trains.

            \param position A train kind position.

            \retval true  The train kind is referred.
            \retval false Otherwise.
        */
        bool train_kind_referred(const typename train_kinds_type::const_iterator position)
        const
        {
            return train_kind_referred(std::distance(m_train_kinds.begin(), position));
        }

        /*!
            \brief Checks whether the train kind is referred by trains.

            \param train_kind_index A train kind index.

            \retval true  The train kind is referred.
            \retval false Otherwise.
        */
        bool train_kind_referred(const train_kind_index_type& train_kind_index)
        const
        {
            const bool referred_by_down_trains =
                std::find_if(
                    m_down_trains.begin(),
                    m_down_trains.end(),
                    TETENGO2_CPP11_BIND(
                        std::equal_to<train_kind_index_type>(),
                        TETENGO2_CPP11_BIND(&train_type::kind_index, tetengo2::cpp11::placeholders_1()),
                        train_kind_index
                    )
                ) != m_down_trains.end();
            const bool referred_by_up_trains =
                std::find_if(
                    m_up_trains.begin(),
                    m_up_trains.end(),
                    TETENGO2_CPP11_BIND(
                        std::equal_to<train_kind_index_type>(),
                        TETENGO2_CPP11_BIND(&train_type::kind_index, tetengo2::cpp11::placeholders_1()),
                        train_kind_index
                    )
                ) != m_up_trains.end();

            return referred_by_down_trains || referred_by_up_trains;
        }

        /*!
            \brief Inserts a train kind.

            \param position   A position where a train kind is inserted.
            \param train_kind A train kind.
        */
        void insert_train_kind(
            const typename train_kinds_type::const_iterator position,
            train_kind_type                                 train_kind
        )
        {
            const train_kind_index_type inserted_index =
                std::distance<typename train_kinds_type::const_iterator>(m_train_kinds.begin(), position);

            m_train_kinds.insert(
                tetengo2::cpp11::as_insertion_iterator(m_train_kinds, position), std::move(train_kind)
            );

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                TETENGO2_CPP11_BIND(update_train_kind_index, tetengo2::cpp11::placeholders_1(), inserted_index, 1)
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                TETENGO2_CPP11_BIND(update_train_kind_index, tetengo2::cpp11::placeholders_1(), inserted_index, 1)
            );

            m_observer_set.changed();
        }

        /*!
            \brief Sets a train kind.

            \param position   A position where a train kind is inserted.
            \param train_kind A train kind.
        */
        void set_train_kind(
            const typename train_kinds_type::const_iterator position,
            train_kind_type                                 train_kind
        )
        {
            typename train_kinds_type::iterator mutable_position = m_train_kinds.begin();
            std::advance(
                mutable_position,
                std::distance(static_cast<typename train_kinds_type::const_iterator>(m_train_kinds.begin()), position)
            );

            *mutable_position = std::move(train_kind);

            m_observer_set.changed();
        }

        /*!
            \brief Erases a train kind.

            train_kind to erase must not be referred by any trains.

            \param position The position of a train kind to erase.

            \throw std::invalid_argument When train_kind is referred by trains.
        */
        void erase_train_kind(const typename train_kinds_type::const_iterator position)
        {
            if (train_kind_referred(position))
                BOOST_THROW_EXCEPTION(std::invalid_argument("The train kind is still referred."));

            const train_kind_index_type erased_index =
                std::distance<typename train_kinds_type::const_iterator>(m_train_kinds.begin(), position);

            m_train_kinds.erase(tetengo2::cpp11::as_insertion_iterator(m_train_kinds, position));

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                TETENGO2_CPP11_BIND(update_train_kind_index, tetengo2::cpp11::placeholders_1(), erased_index, -1)
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                TETENGO2_CPP11_BIND(update_train_kind_index, tetengo2::cpp11::placeholders_1(), erased_index, -1)
            );

            m_observer_set.changed();
        }

        /*!
            \brief Assign train kinds.

            train_kind_index_map is a vector such that train_kind_index_map[old_index] returns the new index.
            The train kind index stored in the trains are updated.

            \param train_kinds          Train kinds.
            \param train_kind_index_map A train kind index map.

            \throw std::out_of_range When the size and/or the elements of train_kind_index_map is out of range.
        */
        void assign_train_kinds(
            train_kinds_type                          train_kinds,
            const std::vector<train_kind_index_type>& train_kind_index_map
        )
        {
            m_train_kinds = std::move(train_kinds);

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                replace_train_kind_index(m_train_kinds, train_kind_index_map)
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                replace_train_kind_index(m_train_kinds, train_kind_index_map)
            );
        }

        /*!
            \brief Returns the down trains.

            \return The down trains
        */
        const trains_type& down_trains()
        const
        {
            return m_down_trains;
        }

        /*!
            \brief Returns the up trains.

            \return The up trains
        */
        const trains_type& up_trains()
        const
        {
            return m_up_trains;
        }

        /*!
            \brief Inserts a down train.

            The count of train stops must coincide with the one of the station locations.

            \param position A position where a down train is inserted.
            \param train    A down train.

            \throw std::invalid_argument When the kind index of a train is greater than the train kind count.
            \throw std::invalid_argument When the count of the stops of a train does not coincide with the one of the
                                         station locations.
        */
        void insert_down_train(const typename trains_type::const_iterator position, train_type train)
        {
            insert_train_impl(m_down_trains, position, std::move(train));
        }

        /*!
            \brief Inserts a up train.

            The count of train stops must coincide with the one of the station locations.

            \param position A position where a up train is inserted.
            \param train    A up train.

            \throw std::invalid_argument When the kind index of a train is greater than the train kind count.
            \throw std::invalid_argument When the count of the stops of a train does not coincide with the one of the
                                         station locations.
        */
        void insert_up_train(const typename trains_type::const_iterator position, train_type train)
        {
            insert_train_impl(m_up_trains, position, std::move(train));
        }

        /*!
            \brief Erases the down trains.

            \param first A first iterator among the erased trains.
            \param last  A last iterator among the erased trains.
        */
        void erase_down_trains(
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            erase_trains_impl(m_down_trains, first, last);
        }

        /*!
            \brief Erases the up trains.

            \param first A first iterator among the erased trains.
            \param last  A last iterator among the erased trains.
        */
        void erase_up_trains(
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            erase_trains_impl(m_up_trains, first, last);
        }

        /*!
            \brief Returns the font and color set.

            \return The font and color set.
        */
        const font_color_set_type& font_color_set()
        const
        {
            return m_font_color_set;
        }

        /*!
            \brief Sets a font and color set.

            \param font_color_set A font color set.
        */
        void set_font_color_set(font_color_set_type font_color_set)
        {
            m_font_color_set = std::move(font_color_set);

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        const observer_set_type& observer_set()
        const
        {
            return m_observer_set;
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        observer_set_type& observer_set()
        {
            return m_observer_set;
        }


    private:
        // types

        typedef typename train_type::stops_type::difference_type difference_type;

        typedef typename train_type::stop_type stop_type;

        struct replace_train_kind_index
        {
            const train_kinds_type& m_train_kinds;

            const std::vector<train_kind_index_type>& m_train_kind_index_map;

            replace_train_kind_index(
                const train_kinds_type&                   train_kinds,
                const std::vector<train_kind_index_type>& train_kind_index_map
            )
            :
            m_train_kinds(train_kinds),
            m_train_kind_index_map(train_kind_index_map)
            {}

            void operator()(train_type& train)
            const
            {
                if (train.kind_index() >= m_train_kind_index_map.size())
                    BOOST_THROW_EXCEPTION(std::out_of_range("Invalid old index in the train kind index map."));
                const train_kind_index_type new_index = m_train_kind_index_map[train.kind_index()];
                if (new_index >= m_train_kinds.size())
                    BOOST_THROW_EXCEPTION(std::out_of_range("Invalid new index in the train_kind index map."));

                train.set_kind_index(new_index);
            }

        };


        // static functions

        static void insert_train_stop(train_type& train, const difference_type offset)
        {
            train.insert_stop(
                train.stops().begin() + offset,
                stop_type(
                    train_type::stop_type::time_type::uninitialized(),
                    train_type::stop_type::time_type::uninitialized(),
                    false,
                    string_type()
                )
            );
        }

        static void erase_train_stops(
            train_type&           train,
            const difference_type first_offset,
            const difference_type last_offset
        )
        {
            train.erase_stops(train.stops().begin() + first_offset, train.stops().begin() + last_offset);
        }

        static void update_train_kind_index(
            train_type&                 train,
            const train_kind_index_type index,
            const std::ptrdiff_t        index_delta
        )
        {
            if (train.kind_index() < index)
                return;

            train_type new_train(
                train.number(), train.kind_index() + index_delta, train.name(), train.name_number(), train.note()
            );
            BOOST_FOREACH (const stop_type& stop, train.stops())
            {
                new_train.insert_stop(new_train.stops().end(), stop);
            }

            train = new_train;
        }


        // variables

        string_type m_company_name;

        string_type m_line_name;

        string_type m_note;

        station_locations_type m_station_locations;

        train_kinds_type m_train_kinds;

        trains_type m_down_trains;

        trains_type m_up_trains;

        font_color_set_type m_font_color_set;

        observer_set_type m_observer_set;


        // functions

        bool can_insert_to(
            const typename station_locations_type::const_iterator position,
            const station_location_type&                          station_location
        )
        const
        {
            if (position != m_station_locations.begin() && !boost::prior(position)->before(station_location))
                return false;

            if (position != m_station_locations.end() && !station_location.before(*position))
                return false;

            return true;
        }

        void insert_train_impl(
            trains_type&                               trains,
            const typename trains_type::const_iterator position,
            train_type                                 train
        )
        {
            if (train.kind_index() >= m_train_kinds.size())
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("The kind index of the train is greater than the train kind count.")
                );
            }
            if (train.stops().size() != m_station_locations.size())
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument(
                        "The count of the train stops does not coincide with the one of the station locations."
                    )
                );
            }

            trains.insert(tetengo2::cpp11::as_insertion_iterator(trains, position), std::move(train));

            m_observer_set.changed()();
        }

        void erase_trains_impl(
            trains_type&                               trains,
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            trains.erase(
                tetengo2::cpp11::as_insertion_iterator(trains, first),
                tetengo2::cpp11::as_insertion_iterator(trains, last)
            );

            m_observer_set.changed()();
        }


    };


}}


#endif
