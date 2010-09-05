/*! \file
    \brief The definition of bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H

#include <boost/operators.hpp>
#include <boost/swap.hpp>

#include <tetengo2.assignable.h>
#include <tetengo2.swappable.h>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class for a station location.

        \tparam Station  A station type.
        \tparam Meterage A meterage type.
    */
    template <typename Station, typename Meterage>
    class station_location :
        public tetengo2::assignable<station_location<Station, Meterage>>,
        private tetengo2::swappable<station_location<Station, Meterage>>,
        private boost::equality_comparable<
            station_location<Station, Meterage>
        >
    {
    public:
        // types

        //! \return The station type.
        typedef Station station_type;

        //! \return The meterage type.
        typedef Meterage meterage_type;


        // constructors and destructor

        /*!
            \brief Creates a station location.

            \param station  A station.
            \param meterage A meterage.
        */
        station_location(
            const station_type& station,
            const meterage_type meterage
        )
        :
        m_station(station),
        m_meterage(meterage)
        {}

        /*!
            \brief Copies a station location.

            \param another Another station location.
        */
        station_location(const station_location& another)
        :
        m_station(another.m_station),
        m_meterage(another.m_meterage)
        {}

        /*!
            \brief Destroys the station location.
        */
        ~station_location()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another station location.

            \param another Another station location.
        */
        void swap(station_location& another)
        throw ()
        {
            boost::swap(m_station, another.m_station);
            boost::swap(m_meterage, another.m_meterage);
        }

        /*!
            \brief Assigns another station location.

            \param another Another station location.

            \return This object.
        */
        station_location& operator=(const station_location& another)
        {
            return assign(another);
        }

        /*!
            \brief Checks whether one station location is equal to anther.

            \param one     One station location.
            \param another Another station location.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(
            const station_location& one,
            const station_location& another
        )
        {
            return one.m_station == another.m_station &&
                   one.m_meterage == another.m_meterage;
        }

        /*!
            \brief Returns the station.

            \return The station.
        */
        const station_type& station()
        const
        {
            return m_station;
        }

        /*!
            \brief Returns the meterage.

            \return The meterage.
        */
        meterage_type meterage()
        const
        {
            return m_meterage;
        }

        /*!
            \brief Checks this station is located before another.

            \param another Another sation_location.

            \retval true  When meterage() <= another.meterage().
            \retval false Otherwise.
        */
        bool before(const station_location& another)
        const
        {
            return m_meterage <= another.m_meterage;
        }


    private:
        // variables

        station_type m_station;

        meterage_type m_meterage;


    };


}}}


#endif
