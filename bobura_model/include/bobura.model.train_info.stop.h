/*! \file
    \brief The definition of bobura::model::train_info::stop.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_STOP_H)
#define BOBURA_MODEL_TRAININFO_STOP_H

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include "bobura.model.train_info.PlatformConcept.h"
#include "bobura.model.train_info.TimeConcept.h"


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a train stop.

        \tparam Time     A time type. It must conform to
                         bobura::model::train_info::TimeConcept<Time>.
        \tparam Platform A string type. It must conform to
                         bobura::model::train_info::PlatformConcept<Platform>.
    */
    template <typename Time, typename Platform>
    class stop : private boost::equality_comparable<stop<Time, Platform> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Time, bobura::model::train_info, TimeConcept);
        BOOST_CLASS_REQUIRE(
            Platform, bobura::model::train_info, PlatformConcept
        );


    public:
        // types

        //! The time type.
        typedef Time time_type;

        //! The platform type.
        typedef Platform platform_type;


        // constructors and destructor

        /*!
            \brief Creates a stop.
        */
        stop()
        {}

        /*!
            \brief Copies a stop.

            \param another Another stop object.
        */
        stop(const stop& another)
        {}

        /*!
            \brief Destroys the stop.
        */
        ~stop()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another stop object.

            \param another Another stop object.
        */
        void swap(stop& another)
        throw ()
        {
        }

        /*!
            \brief Assigns another stop object.

            \param another Another stop object.

            \return this object.
        */
        stop& operator=(const stop& another)
        {
            stop(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther stop object.

            \param another Another stop object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const stop& another)
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
        \brief Swaps two stop objects.

        \tparam Time     A time type. It must conform to
                         bobura::model::train_info::TimeConcept<Time>.
        \tparam Platform A platform type. It must conform to
                         bobura::model::train_info::PlatformConcept<Platform>.

        \param stop1 A stop object #1.
        \param stop2 A stop object #2.
    */
    template <typename Time, typename Platform>
    void swap(
        bobura::model::train_info::stop<Time, Platform>& stop1,
        bobura::model::train_info::stop<Time, Platform>& stop2
    )
    throw ()
    {
        boost::function_requires<
            bobura::model::train_info::TimeConcept<Time>
        >();
        boost::function_requires<
            bobura::model::train_info::PlatformConcept<Platform>
        >();

        stop1.swap(stop2);
    }


}

#endif
