/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLE_H)
#define BOBURA_MODEL_TIMETABLE_H

#include <algorithm>
#include <memory>
#include <stdexcept>

#include <boost/scoped_ptr.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a timetable.

        \tparam Stations A collection type of stations. It must conform to
                         bobura::model::StationsConcept<Stations>.
    */
    template <
        typename Stations
    >
    class timetable
    {
    private:
        // concept checks


    public:
        // types

        //! The collection type of stations.
        typedef Stations stations_type;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.

            \param p_stations A auto pointer to a collection of stations. It
                              must not be NULL.
        */
        timetable(std::auto_ptr<stations_type> p_stations)
        :
        m_p_stations(p_stations)
        {
            if (m_p_stations.get() == NULL)
                throw std::invalid_argument("p_stations is NULL.");
        }

        /*!
            \brief Copies a timetable.

            \param another Another timetable object.
        */
        timetable(const timetable& another)
        :
        m_p_stations(new stations_type(*another.m_p_stations))
        {}

        /*!
            \brief Destroys the bobura application.
        */
        ~timetable()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another timetable object.

            \param another Another timetable object.
        */
        void swap(timetable& another)
        throw ()
        {
            m_p_stations.swap(another.m_p_stations);
        }

        /*!
            \brief Assigns another timetable object.

            \param another Another timetable object.

            \return this object.
        */
        timetable& operator=(const timetable& another)
        {
            timetable(another).swap(*this);
            return *this;
        }

        /*!
            \brief Returns the pointer to the stations.

            \return The pointer to the stations.
        */
        stations_type* p_stations()
        const
        {
            return m_p_stations.get();
        }


    private:
        // variables

        boost::scoped_ptr<stations_type> m_p_stations;


    };


}}

namespace std
{
    /*!
        \brief Swaps two timetable objects.

        \param timetable1 A timetable object #1.
        \param timetable2 A timetable object #2.
    */
    template <typename Stations>
    void swap(
        bobura::model::timetable<Stations>& timetable1,
        bobura::model::timetable<Stations>& timetable2
    )
    throw ()
    {
        timetable1.swap(timetable2);
    }


}


#endif
