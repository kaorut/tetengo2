/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLE_H)
#define BOBURA_MODEL_TIMETABLE_H

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a timetable.

        \tparam String                    A string type.
        \tparam StationLocation           A station location type.
        \tparam StationIntervalCalculator A station interval calculatortype.
        \tparam TrainKindList             A train kind list type.
        \tparam Train                     A train type.
        \tparam ObserverSet               An observer set type.
    */
    template <
        typename String,
        typename StationLocation,
        typename StationIntervalCalculator,
        typename TrainKindList,
        typename Train,
        typename ObserverSet
    >
    class timetable :
        private boost::equality_comparable<
            timetable<String, StationLocation, StationIntervalCalculator, TrainKindList, Train, ObserverSet>
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

        //! The train kind list type.
        typedef TrainKindList train_kind_list_type;

        //! The train kind type.
        typedef typename train_kind_list_type::train_kind_type train_kind_type;

        //! The train kinds type.
        typedef std::vector<std::unique_ptr<train_kind_type>> train_kinds_type;

        //! The train type.
        typedef Train train_type;

        //! The trains type.
        typedef std::vector<train_type> trains_type;

        //! The observer set type.
        typedef ObserverSet observer_set_type;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.
        */
        timetable()
        :
        m_title(),
        m_station_locations(),
        m_train_kinds(build_initial_train_kinds()),
        m_down_trains(),
        m_up_trains(),
        m_observer_set()
        {
            assert(!m_train_kinds.empty());
        }

        /*!
            \brief Creates a timetalble.

            \tparam InputIterator An input iterator for station locations.

            \param station_location_first The first iterator among station locations.
            \param station_location_last  The last iterator among station locations.
        */
        template <typename InputIterator>
        timetable(const InputIterator station_location_first, const InputIterator station_location_last)
        :
        m_title(),
        m_station_locations(station_location_first, station_location_last),
        m_train_kinds(build_initial_train_kinds()),
        m_down_trains(),
        m_up_trains(),
        m_observer_set()
        {
            assert(!m_train_kinds.empty());
        }


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
                one.m_station_locations == another.m_station_locations &&
                one.m_down_trains == another.m_down_trains &&
                one.m_up_trains == another.m_up_trains;
        }

        /*!
            \brief Returns the title.

            \return The title.
        */
        const string_type& title()
        const
        {
            return m_title;
        }

        /*!
            \brief Sets a title.

            \tparam S A string type.

            \param title A title.
        */
        template <typename S>
        void set_title(S&& title)
        {
            m_title = std::forward<S>(title);

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

            \tparam SL A station location type.

            \param position         A position where a station location is inserted.
            \param station_location A station location.

            \throw std::invalid_argument When the station locations are not sequenced in ascending order after the
                                         insertion.
        */
        template <typename SL>
        void insert_station_location(
            const typename station_locations_type::const_iterator position,
            SL&&                                                  station_location
        )
        {
            if (!can_insert_to(position, station_location))
                BOOST_THROW_EXCEPTION(std::invalid_argument("The insertion position is invalid."));

            const difference_type offset =
                std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), position);

            m_station_locations.insert(to_mutable(position, m_station_locations), std::forward<SL>(station_location));

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

            m_station_locations.erase(to_mutable(first, m_station_locations), to_mutable(last, m_station_locations));

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

            \tparam T A train type.

            \param position A position where a down train is inserted.
            \param train    A down train.

            \throw std::invalid_argument When the count of the stops of a train does not coincide with the one of the
                                         station locations.
        */
        template <typename T>
        void insert_down_train(const typename trains_type::const_iterator position, T&& train)
        {
            insert_train_impl(m_down_trains, position, std::forward<T>(train));
        }

        /*!
            \brief Inserts a up train.

            The count of train stops must coincide with the one of the station locations.

            \tparam T A train type.

            \param position A position where a up train is inserted.
            \param train    A up train.

            \throw std::invalid_argument When the count of the stops of a train does not coincide with the one of the
                                         station locations.
        */
        template <typename T>
        void insert_up_train(const typename trains_type::const_iterator position, T&& train)
        {
            insert_train_impl(m_up_trains, position, std::forward<T>(train));
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


        // static functions

        static train_kinds_type build_initial_train_kinds()
        {
            train_kinds_type kinds;

            kinds.push_back(
                tetengo2::make_unique<train_kind_type>(
                    string_type(TETENGO2_TEXT("Local")), string_type(TETENGO2_TEXT("Local"))
                )
            );
            kinds.push_back(
                tetengo2::make_unique<train_kind_type>(
                    string_type(TETENGO2_TEXT("Rapid")), string_type(TETENGO2_TEXT("Rapid"))
                )
            );
            kinds.push_back(
                tetengo2::make_unique<train_kind_type>(
                    string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Express"))
                )
            );
            kinds.push_back(
                tetengo2::make_unique<train_kind_type>(
                    string_type(TETENGO2_TEXT("Limited Express")), string_type(TETENGO2_TEXT("Ltd.Exp."))
                )
            );

            return kinds;
        }

        static void insert_train_stop(train_type& train, const difference_type offset)
        {
            train.insert_stop(
                train.stops().begin() + offset,
                stop_type(
                    train_type::stop_type::time_type::uninitialized(),
                    train_type::stop_type::time_type::uninitialized(),
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

        template <typename Container>
        static typename Container::iterator to_mutable(
            const typename Container::const_iterator const_iter,
            Container&                               container
        )
        {
            typename Container::iterator mutable_iter = container.begin();
            std::advance(
                mutable_iter, std::distance<typename Container::const_iterator>(container.begin(), const_iter)
            );
            return mutable_iter;
        }


        // variables

        string_type m_title;

        station_locations_type m_station_locations;

        train_kinds_type m_train_kinds;

        trains_type m_down_trains;

        trains_type m_up_trains;

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

        template <typename T>
        void insert_train_impl(trains_type& trains, const typename trains_type::const_iterator position, T&& train)
        {
            if (train.stops().size() != m_station_locations.size())
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument(
                        "The count of the train stops does not coincide with the one of the station locations."
                    )
                );
            }

            trains.insert(to_mutable(position, trains), std::forward<T>(train));

            m_observer_set.changed()();
        }

        void erase_trains_impl(
            trains_type&                               trains,
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            trains.erase(to_mutable(first, trains), to_mutable(last, trains));

            m_observer_set.changed()();
        }


    };


}}


#endif
