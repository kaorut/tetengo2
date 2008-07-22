/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

//#include <algorithm>
#include <vector>
//std::swap // dummy

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include <concept_tetengo2.String.h>

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

            \param another Another train object.
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
            \brief Swaps the members with another train object.

            \param another Another train object.
        */
        void swap(train& another)
        throw ()
        {
            m_number.swap(another.m_number);
            m_note.swap(another.m_note);
            m_stops.swap(another.m_stops);
        }

        /*!
            \brief Assigns another train object.

            \param another Another train object.

            \return this object.
        */
        train& operator=(const train& another)
        {
            train(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther
                   train object.

            \param another Another train object.

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
            m_stops.insert(position, stop);
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
            m_stops.erase(first, last);
        }


    private:
        // variables

        number_type m_number;

        note_type m_note;

        stops_type m_stops;


    };


}}

namespace std
{
    /*!
        \brief Swaps two train objects.

        \tparam Number A number type. It must conform to
                       concept_tetengo2::String<Number>.
        \tparam Note   A note type. It must conform to
                       concept_tetengo2::String<Note>.
        \tparam Stop   A stop type. It must conform to
                       concept_bobura::model::train_info::Stop<Stop>.

        \param train1 A train object #1.
        \param train2 A train object #2.
    */
    template <typename Number, typename Note, typename Stop>
    void swap(
        bobura::model::train<Number, Note, Stop>& train1,
        bobura::model::train<Number, Note, Stop>& train2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<Number>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<Note>));
        BOOST_CONCEPT_ASSERT((concept_bobura::model::train_info::Stop<Stop>));

        train1.swap(train2);
    }


}

#endif
