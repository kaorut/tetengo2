/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

#include <utility>
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


        // constructors and destructor

        /*!
            \brief Creates a train.

            \param number      A number.
            \param kind_index  A kind index.
            \param name        A name.
            \param name_number A name number.
            \param note        A note.
        */
        train(
            string_type           number,
            const kind_index_type kind_index,
            string_type           name,
            string_type           name_number,
            string_type           note
        )
        :
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

            \param number      A number.
            \param kind_index  A kind index.
            \param name        A name.
            \param name_number A name number.
            \param note        A note.
            \param stops       Stops.
        */
        train(
            string_type           number,
            const kind_index_type kind_index,
            string_type           name,
            string_type           name_number,
            string_type           note,
            stops_type            stops
        )
        :
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
            string_type           number,
            const kind_index_type kind_index,
            string_type           name,
            string_type           name_number,
            string_type           note,
            const InputIterator   stop_first,
            const InputIterator   stop_last
        )
        :
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
                one.m_number == another.m_number &&
                one.m_kind_index == another.m_kind_index &&
                one.m_name == another.m_name &&
                one.m_name_number == another.m_name_number &&
                one.m_note == another.m_note &&
                one.m_stops == another.m_stops;
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


    private:
        // variables

        string_type m_number;

        kind_index_type m_kind_index;

        string_type m_name;

        string_type m_name_number;

        string_type m_note;

        stops_type m_stops;


    };


}}


#endif
