/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007 kaoru

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

        \param Stations A collection of stations. It must conform to
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

        void swap(timetable& another)
        throw ()
        {
            m_p_stations.swap(another.m_p_stations);
        }

        timetable& operator=(const timetable& another)
        {
            timetable(another).swap(*this);
            return *this;
        }


    private:
        // variables

        boost::scoped_ptr<stations_type> m_p_stations;


    };


}}

namespace std
{
    template <typename Stations>
    void swap(
        bobura::model::timetable<Stations>& left,
        bobura::model::timetable<Stations>& right
    )
    throw ()
    {
        left.swap(right);
    }


}


#endif
