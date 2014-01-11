/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

//#include <iterator>
//#include <utility>
#include <vector>

#include <boost/operators.hpp>

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
            \brief Returns the stop previous to the specified stop.

            It returns stops().end() when the specified stop is the origin or earlier.

            \param i_stop An iterator to a stop.

            \return The iterator to the stop previous to the specified stop.
        */
        typename stops_type::const_iterator previous_stop(const typename stops_type::const_iterator i_stop)
        const
        {
            return m_direction == direction_type::down ? rfind_real_stop(i_stop, true) : find_real_stop(i_stop, true);
        }

        /*!
            \brief Returns the stop next to the specified stop.

            It returns stops().end() when the specified stop is the destination or later.

            \param i_stop An iterator to a stop.

            \return The iterator to the stop next to the specified stop.
        */
        typename stops_type::const_iterator next_stop(const typename stops_type::const_iterator i_stop)
        const
        {
            return m_direction == direction_type::down ? find_real_stop(i_stop, true) : rfind_real_stop(i_stop, true);
        }

        /*!
            \brief Returns the origin stop.

            When this train has no stop with arrival or departure, it returns stops().end().

            \return The iterator to the origin stop.
        */
        typename stops_type::const_iterator origin_stop()
        const
        {
            return
                m_direction == direction_type::down ?
                find_real_stop(m_stops.begin(), false) : rfind_real_stop(m_stops.end(), false);
        }

        /*!
            \brief Returns the destination stop.

            When this train has no stop with arrival or departure, it returns stops().end().

            \return The iterator to the destination stop.
        */
        typename stops_type::const_iterator destination_stop()
        const
        {
            return
                m_direction == direction_type::down ?
                rfind_real_stop(m_stops.end(), false) : find_real_stop(m_stops.begin(), false);
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

        typename stops_type::const_iterator find_real_stop(
            typename stops_type::const_iterator i_stop,
            const bool                          skip_start
        )
        const
        {
            if (skip_start && i_stop != m_stops.end())
                std::advance(i_stop, 1);

            for (auto i = i_stop; i != m_stops.end(); ++i)
            {
                if (!i->passing())
                    return i;
            }

            return m_stops.end();
        }

        typename stops_type::const_iterator rfind_real_stop(
            typename stops_type::const_iterator i_stop,
            const bool                          skip_start
        )
        const
        {
            if (skip_start && i_stop != m_stops.begin())
                std::advance(i_stop, -1);

            for (auto i = i_stop; ; --i)
            {
                if (i == m_stops.end())
                {
                    if (i == m_stops.begin())
                        break;
                    else
                        continue;
                }
                if (!i->passing())
                    return i;
                if (i == m_stops.begin())
                    break;
            }

            return m_stops.end();
        }


    };


}}


#endif
