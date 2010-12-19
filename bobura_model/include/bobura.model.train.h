/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

#include <iterator>
#include <utility>
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

        //! The number type.
        typedef Number number_type;

        //! The note type.
        typedef Note note_type;

        //! The stop type.
        typedef Stop stop_type;

        //! The stops type.
        typedef std::vector<stop_type> stops_type;


        // constructors and destructor

        /*!
            \brief Creates a train.

            \tparam No A number type.
            \tparam Nt A note type.

            \param number A number.
            \param note   A note.
        */
        template <typename No, typename Nt>
        train(No&& number, Nt&& note)
        :
        m_number(std::forward<No>(number)),
        m_note(std::forward<Nt>(note)),
        m_stops()
        {}

        /*!
            \brief Creates a train.

            \tparam InputIterator An input iterator for stops.

            \tparam No A number type.
            \tparam Nt A note type.
            \tparam Ss A stops type.

            \param number     A number.
            \param note       A note.
            \param stops      Stops.
        */
        template <typename No, typename Nt, typename Ss>
        train(No&& number, Nt&& note, Ss&& stops)
        :
        m_number(std::forward<No>(number)),
        m_note(std::forward<Nt>(note)),
        m_stops(std::forward<Ss>(stops))
        {}

        /*!
            \brief Creates a train.

            \tparam InputIterator An input iterator for stops.

            \tparam No            A number type.
            \tparam Nt            A note type.
            \tparam InputIterator An input iterator type.

            \param number     A number.
            \param note       A note.
            \param stop_first The first iterator among stops.
            \param stop_last  The last iterator among stops.
        */
        template <typename No, typename Nt, typename InputIterator>
        train(
            No&&          number,
            Nt&&          note,
            InputIterator stop_first,
            InputIterator stop_last
        )
        :
        m_number(std::forward<No>(number)),
        m_note(std::forward<Nt>(note)),
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

            \tparam S A stop type.

            \param position A position where a stop is inserted.
            \param stop     A stop.
        */
        template <typename S>
        void insert_stop(
            const typename stops_type::const_iterator position,
            S&&                                       stop
        )
        {
            m_stops.insert(
                to_mutable(position, m_stops), std::forward<S>(stop)
            );
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
