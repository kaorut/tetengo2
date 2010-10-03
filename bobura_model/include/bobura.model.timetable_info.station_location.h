/*! \file
    \brief The definition of bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H

#include <boost/operators.hpp>
#include <boost/swap.hpp>

#include <tetengo2.cpp0x_keyword.h>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class for a station location.

        \tparam Station  A station type.
        \tparam Meterage A meterage type.
    */
    template <typename Station, typename Meterage>
    class station_location :
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


        // functions

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
