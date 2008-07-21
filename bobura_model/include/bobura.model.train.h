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

#include "concept_bobura.model.train_info.Stop.h"


namespace bobura { namespace model
{
    /*!
        \brief The class for a train.

        \tparam Stop A stop type. It must conform to
                        concept_bobura::model::train_info::Stop<Stop>.
    */
    template <typename Stop>
    class train : private boost::equality_comparable<train<Stop> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_bobura::model::train_info::Stop<Stop>));


    public:
        // types

        //! The stop type.
        typedef Stop stop_type;

        //! The stops type.
        typedef std::vector<stop_type> stops_type;


        // constructors and destructor

        /*!
            \brief Creates a train.
        */
        train()
        :
        m_stops()
        {}

        /*!
            \brief Creates a train.

            \tparam InputIterator An input iterator for stops.

            \param stop_first The first iterator of the stops.
            \param stop_last  The last iterator of the stops.
        */
        template <typename InputIterator>
        train(InputIterator stop_first, InputIterator stop_last)
        :
        m_stops(stop_first, stop_last)
        {}

        /*!
            \brief Copies a train.

            \param another Another train object.
        */
        train(const train& another)
        :
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
            return m_stops == another.m_stops;
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


    private:
        // variables

        stops_type m_stops;


    };


}}

namespace std
{
    /*!
        \brief Swaps two train objects.

        \tparam Stop A stop type. It must conform to
                        concept_bobura::model::train_info::Stop<Stop>.

        \param train1 A train object #1.
        \param train2 A train object #2.
    */
    template <typename Stop>
    void swap(
        bobura::model::train<Stop>& train1,
        bobura::model::train<Stop>& train2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_bobura::model::train_info::Stop<Stop>));

        train1.swap(train2);
    }


}

#endif
