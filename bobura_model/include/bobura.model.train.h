/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

#include <algorithm>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2.stdalt.h>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a train.

        \tparam String    A string type.
        \tparam KindIndex A kind index type.
        \tparam Stop      A stop type.
    */
    template <typename String, typename KindIndex, typename Stop>
    class train : private boost::equality_comparable<train<String, KindIndex, Stop>>
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The kind index type.
        typedef KindIndex kind_index_type;

        //! The stop type.
        typedef Stop stop_type;

        //! The stops type.
        typedef std::vector<stop_type> stops_type;

        //! The direction type.
        enum class direction_type
        {
            down, //!< Down.
            up,   //!< Up.
        };


        // constructors and destructor

        /*!
            \brief Creates a train.

            \param direction   A direction.
            \param number      A number.
            \param kind_index  A kind index.
            \param name        A name.
            \param name_number A name number.
            \param note        A note.
        */
        train(
            const direction_type  direction,
            string_type           number,
            const kind_index_type kind_index,
            string_type           name,
            string_type           name_number,
            string_type           note
        )
        :
        m_direction(direction),
        m_number(std::move(number)),
        m_kind_index(kind_index),
        m_name(std::move(name)),
        m_name_number(std::move(name_number)),
        m_note(std::move(note)),
        m_stops()
        {}

        /*!
            \brief Creates a train.

            kind_index must be less than the train kind count in the timetable.

            \param direction   A direction.
            \param number      A number.
            \param kind_index  A kind index.
            \param name        A name.
            \param name_number A name number.
            \param note        A note.
            \param stops       Stops.
        */
        train(
            const direction_type  direction,
            string_type           number,
            const kind_index_type kind_index,
            string_type           name,
            string_type           name_number,
            string_type           note,
            stops_type            stops
        )
        :
        m_direction(direction),
        m_number(std::move(number)),
        m_kind_index(kind_index),
        m_name(std::move(name)),
        m_name_number(std::move(name_number)),
        m_note(std::move(note)),
        m_stops(std::move(stops))
        {}

        /*!
            \brief Creates a train.

            \tparam InputIterator An input iterator type.

            \param direction   A direction.
            \param number      A number.
            \param kind_index  A kind index.
            \param name        A name.
            \param name_number A name number.
            \param note        A note.
            \param stop_first  The first iterator among stops.
            \param stop_last   The last iterator among stops.
        */
        template <typename InputIterator>
        train(
            const direction_type  direction,
            string_type           number,
            const kind_index_type kind_index,
            string_type           name,
            string_type           name_number,
            string_type           note,
            const InputIterator   stop_first,
            const InputIterator   stop_last
        )
        :
        m_direction(direction),
        m_number(std::move(number)),
        m_kind_index(kind_index),
        m_name(std::move(name)),
        m_name_number(std::move(name_number)),
        m_note(std::move(note)),
        m_stops(stop_first, stop_last)
        {}


        // functions

        /*!
            \brief Checks whether one train is equal to another.

            \param one     One train.
            \param another Another train.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const train& one, const train& another)
        {
            return
                one.m_direction == another.m_direction &&
                one.m_number == another.m_number &&
                one.m_kind_index == another.m_kind_index &&
                one.m_name == another.m_name &&
                one.m_name_number == another.m_name_number &&
                one.m_note == another.m_note &&
                one.m_stops == another.m_stops;
        }

        /*!
            \brief Returns the direction.

            \return The direction.
        */
        direction_type direction()
        const
        {
            return m_direction;
        }

        /*!
            \brief Returns the number.

            \return The number.
        */
        const string_type& number()
        const
        {
            return m_number;
        }

        /*!
            \brief Returns the kind index.

            \return The kind index.
        */
        kind_index_type kind_index()
        const
        {
            return m_kind_index;
        }

        /*!
            \brief Sets a kind index.

            \param kind_index A kind index.
        */
        void set_kind_index(const kind_index_type kind_index)
        {
            m_kind_index = kind_index;
        }

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name()
        const
        {
            return m_name;
        }

        /*!
            \brief Returns the name number.

            \return The name number.
        */
        const string_type& name_number()
        const
        {
            return m_name_number;
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
            \brief Returns the stops.

            \return The stops.
        */
        const stops_type& stops()
        const
        {
            return m_stops;
        }

        /*!
            \brief Inserts a stop.

            \param position A position where a stop is inserted.
            \param stop     A stop.
        */
        void insert_stop(const typename stops_type::const_iterator position, stop_type stop)
        {
            m_stops.insert(tetengo2::stdalt::as_insertion_iterator(m_stops, position), std::move(stop));
        }

        /*!
            \brief Erases the stops.

            \param first A first iterator among the erased stops.
            \param last  A last iterator among the erased stops.
        */
        void erase_stops(
            const typename stops_type::const_iterator first,
            const typename stops_type::const_iterator last
        )
        {
            m_stops.erase(
                tetengo2::stdalt::as_insertion_iterator(m_stops, first),
                tetengo2::stdalt::as_insertion_iterator(m_stops, last)
            );
        }

        /*!
            \brief Checks the stop is the origin.

            \param stop A stop.

            \retval true  When the stop is origin.
            \retval false Otherwise.

            \throw std::invalid_argument When the stop does not belong to this train.
        */
        bool is_origin_stop(const stop_type& stop)
        const
        {
            if (
                std::find_if(m_stops.begin(), m_stops.end(), [&stop](const stop_type& s) { return &s == &stop; }) ==
                m_stops.end()
            )
            {
                BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown stop."));
            }

            const auto origin_position = m_direction == direction_type::down ? front_stop() : back_stop();
            if (origin_position == m_stops.end())
                return false;

            return &stop == &*origin_position;
        }

        /*!
            \brief Checks the stop is the destination.

            \param stop A stop.

            \retval true  When the stop is destination.
            \retval false Otherwise.

            \throw std::invalid_argument When the stop does not belong to this train.
        */
        bool is_destination_stop(const stop_type& stop)
        const
        {
            return false;
        }

        /*!
            \brief Returns the stop previous to the specified stop.

            \param stop A stop.

            \return The stop previous to the specified stop.

            \throw std::invalid_argument When the specified stop does not belong to this train.
            \throw std::invalid_argument When the specified stop is the origin.
        */
        const stop_type& previous_stop(const stop_type& stop)
        const
        {
            return m_stops.front();
        }

        /*!
            \brief Returns the stop next to the specified stop.

            \param stop A stop.

            \return The stop next to the specified stop.

            \throw std::invalid_argument When the specified stop does not belong to this train.
            \throw std::invalid_argument When the specified stop is the destination.
        */
        const stop_type& next_stop(const stop_type& stop)
        const
        {
            return m_stops.back();
        }


    private:
        // variables

        direction_type m_direction;

        string_type m_number;

        kind_index_type m_kind_index;

        string_type m_name;

        string_type m_name_number;

        string_type m_note;

        stops_type m_stops;


        // functions

        const typename stops_type::const_iterator front_stop()
        const
        {
            return
                std::find_if(
                    m_stops.begin(),
                    m_stops.end(),
                    [](const stop_type& stop)
                    {
                        return
                            stop.arrival() != time_type::uninitialized() ||
                            stop.departure() != time_type::uninitialized();
                    }
                );
        }

        const typename stops_type::const_iterator back_stop()
        const
        {
            const auto found =
                std::find_if(
                    m_stops.rbegin(),
                    m_stops.rend(),
                    [](const stop_type& stop)
                    {
                        return
                            stop.arrival() != time_type::uninitialized() ||
                            stop.departure() != time_type::uninitialized();
                    }
                );
            return found != m_stops.rend() ? boost::prior(found.base()) : m_stops.end();
        }


    };


}}


#endif
