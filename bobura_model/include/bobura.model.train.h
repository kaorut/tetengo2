/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

//#include <algorithm>
//std::swap // dummy

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model
{
    /*!
        \brief The class for a train.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
    */
    template <typename Station>
    class train : private boost::equality_comparable<train<Station> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Station, bobura::model, StationConcept);


    public:
        // types

        //! The station type.
        typedef Station station_type;


        // constructors and destructor

        /*!
            \brief Creates a train.
        */
        train()
        {}

        /*!
            \brief Copies a train.

            \param another Another train object.
        */
        train(const train& another)
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
            return true;
        }


    private:
        // variables


    };


}}

namespace std
{
    /*!
        \brief Swaps two train objects.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.

        \param train1 A train object #1.
        \param train2 A train object #2.
    */
    template <typename Station>
    void swap(
        bobura::model::train<Station>& train1,
        bobura::model::train<Station>& train2
    )
    throw ()
    {
        boost::function_requires<bobura::model::StationConcept<Station> >();

        train1.swap(train2);
    }


}

#endif
