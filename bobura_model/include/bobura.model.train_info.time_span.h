/*! \file
    \brief The definition of bobura::model::train_info::time_span.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMESPAN_H)
#define BOBURA_MODEL_TRAININFO_TIMESPAN_H

//#include <algorithm>

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
    class time_span : private boost::equality_comparable<time_span<Station> >
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
            \brief Creates a time_span.
        */
        time_span()
        {}

        /*!
            \brief Creates a time_span.

            \param another Another time_span object.
        */
        time_span(const time_span& another)
        {}

        /*!
            \brief Destroys the time_span.
        */
        ~time_span()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another time_span object.

            \param another Another time_span object.
        */
        void swap(time_span& another)
        throw ()
        {
        }

        /*!
            \brief Assigns another time_span object.

            \param another Another time_span object.

            \return this object.
        */
        time_span& operator=(const time_span& another)
        {
            time_span(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther
                   time_span object.

            \param another Another time_span object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const time_span& another)
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
        \brief Swaps two time_span objects.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.

        \param time_span1 A time_span object #1.
        \param time_span2 A time_span object #2.
    */
    template <typename Station>
    void swap(
        bobura::model::train_info::time_span<Station>& time_span1,
        bobura::model::train_info::time_span<Station>& time_span2
    )
    throw ()
    {
        boost::function_requires<bobura::model::StationConcept<Station> >();

        time_span1.swap(time_span2);
    }


}

#endif
