/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

#include <iterator>
#include <vector>

#include <boost/operators.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The class for a train.

        \tparam Number A number type.
        \tparam Note   A note type.
        \tparam Stop   A stop type.
    */
    template <typename Number, typename Note, typename Stop>
    class train :
        private boost::equality_comparable<train<Number, Note, Stop>>
    {
    public:
        // types

        //! \return The number type.
        typedef Number number_type;

        //! \return The note type.
        typedef Note note_type;

        //! \return The stop type.
        typedef Stop stop_type;

        //! \return The stops type.
        typedef std::vector<stop_type> stops_type;


        // constructors and destructor

        /*!
            \brief Creates a train.

            \param number A number.
            \param note   A note.
        */
        train(const number_type& number, const note_type& note)
        :
        m_number(number),
        m_note(note),
        m_stops()
        {}

        /*!
            \brief Creates a train.

            \tparam InputIterator An input iterator for stops.

            \param number     A number.
            \param note       A note.
            \param stop_first The first iterator among stops.
            \param stop_last  The last iterator among stops.
        */
        template <typename InputIterator>
        train(
            const number_type& number,
            const note_type&   note,
            InputIterator      stop_first,
            InputIterator      stop_last
        )
        :
        m_number(number),
        m_note(note),
        m_stops(stop_first, stop_last)
        {}


        // functions

        /*!
            \brief Checks whether one train is equal to anther.

            \param one     One train.
            \param another Another train.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const train& one, const train& another)
        {
            return one.m_number == another.m_number &&
                one.m_note == another.m_note &&
                one.m_stops == another.m_stops;
        }

        /*!
            \brief Returns the number.

            \return The number.
        */
        const number_type& number()
        const
        {
            return m_number;
        }

        /*!
            \brief Returns the note.

            \return The note.
        */
        const note_type& note()
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
        void insert_stop(
            const typename stops_type::const_iterator position,
            const stop_type&                          stop
        )
        {
            m_stops.insert(to_mutable(position, m_stops), stop);
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
                to_mutable(first, m_stops), to_mutable(last, m_stops)
            );
        }


    private:
        // variables

        number_type m_number;

        note_type m_note;

        stops_type m_stops;


        // functions

        template <typename Container>
        typename Container::iterator to_mutable(
            const typename Container::const_iterator const_iter,
            Container&                               container
        )
        {
            typename Container::iterator mutable_iter = container.begin();
            std::advance(
                mutable_iter,
                std::distance<typename Container::const_iterator>(
                    container.begin(), const_iter
                )
            );
            return mutable_iter;
        }


    };


}}


#endif
