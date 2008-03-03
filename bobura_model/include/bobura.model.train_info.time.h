/*! \file
    \brief The definition of bobura::model::train_info::time.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIME_H)
#define BOBURA_MODEL_TRAININFO_TIME_H

//#include <algorithm>
//std::swap // dummy

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a station location.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
    */
    template <typename Station>
    class time : private boost::equality_comparable<time<Station> >
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
            \brief Creates a time.
        */
        time()
        {}

        /*!
            \brief Creates a time.

            \param another Another time object.
        */
        time(const time& another)
        {}

        /*!
            \brief Destroys the time.
        */
        ~time()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another time object.

            \param another Another time object.
        */
        void swap(time& another)
        throw ()
        {
        }

        /*!
            \brief Assigns another time object.

            \param another Another time object.

            \return this object.
        */
        time& operator=(const time& another)
        {
            time(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther
                   time object.

            \param another Another time object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const time& another)
        const
        {
            return true;
        }


    private:
        // variables


    };


}}}

namespace std
{
    /*!
        \brief Swaps two time objects.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.

        \param time1 A time object #1.
        \param time2 A time object #2.
    */
    template <typename Station>
    void swap(
        bobura::model::train_info::time<Station>& time1,
        bobura::model::train_info::time<Station>& time2
    )
    throw ()
    {
        boost::function_requires<bobura::model::StationConcept<Station> >();

        time1.swap(time2);
    }


}

#endif
