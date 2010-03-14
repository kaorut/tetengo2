/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

#include <iterator>
#include <vector>

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>
//#include <boost/swap.hpp>

#include <concept_tetengo2.String.h>
#include <tetengo2.assignable.h>
#include <tetengo2.swappable.h>

#include "concept_bobura.model.train_info.Stop.h"


namespace bobura { namespace model
{
    /*!
        \brief The class for a train.

        \tparam Number A number type. It must conform to
                       concept_tetengo2::String<Number>.
        \tparam Note   A note type. It must conform to
                       concept_tetengo2::String<Note>.
        \tparam Stop   A stop type. It must conform to
                       concept_bobura::model::train_info::Stop<Stop>.
    */
    template <typename Number, typename Note, typename Stop>
    class train :
        public tetengo2::assignable<train<Number, Note, Stop> >,
        private tetengo2::swappable<train<Number, Note, Stop> >,
        private boost::equality_comparable<train<Number, Note, Stop> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<Number>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<Note>));
        BOOST_CONCEPT_ASSERT((concept_bobura::model::train_info::Stop<Stop>));


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

        /*!
            \brief Copies a train.

            \param another Another train.
        */
        train(const train& another)
        :
        m_number(another.m_number),
        m_note(another.m_note),
        m_stops(another.m_stops)
        {}

        /*!
            \brief Destroys the train.
        */
        ~train()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another train.

            \param another Another train.
        */
        void swap(train& another)
        throw ()
        {
            boost::swap(m_number, another.m_number);
            boost::swap(m_note, another.m_note);
            boost::swap(m_stops, another.m_stops);
        }

        /*!
            \brief Assigns another train.

            \param another Another train.

            \return this object.
        */
        train& operator=(const train& another)
        {
            return assign(another);
        }

        /*!
            \brief Checks whether this is equal to anther
                   train.

            \param another Another train.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const train& another)
        const
        {
            return m_number == another.m_number &&
                m_note == another.m_note &&
                m_stops == another.m_stops;
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
