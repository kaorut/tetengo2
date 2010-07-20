/*! \file
    \brief The definition of bobura::model::station.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATION_H)
#define BOBURA_MODEL_STATION_H

#include <cassert>
#include <cstddef>

#include <boost/operators.hpp>
#include <boost/swap.hpp>

#include <tetengo2.assignable.h>
#include <tetengo2.swappable.h>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a station.

        \tparam Name  A name type.
        \tparam Grade A grade type.
    */
    template <typename Name, typename Grade>
    class station :
        public tetengo2::assignable<station<Name, Grade> >,
        private tetengo2::swappable<station<Name, Grade> >,
        private boost::equality_comparable<station<Name, Grade> >
    {
    public:
        // types

        //! \return The name type.
        typedef Name name_type;

        //! \return The grade type.
        typedef Grade grade_type;


        // constructors and destructor

        /*!
            \brief Creates a station.

            \param name  A name.
            \param grade A grade.
        */
        station(const name_type& name, const grade_type& grade)
        :
        m_name(name),
        m_p_grade(&grade)
        {}

        /*!
            \brief Copies a station.

            \param another Another station.
        */
        station(const station& another)
        :
        m_name(another.m_name),
        m_p_grade(another.m_p_grade)
        {
            assert(another.m_p_grade != NULL);
        }

        /*!
            \brief Destroys the station.
        */
        ~station()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another station.

            \param another Another station.
        */
        void swap(station& another)
        throw ()
        {
            boost::swap(m_name, another.m_name);
            boost::swap(m_p_grade, another.m_p_grade);
        }

        /*!
            \brief Assigns another station.

            \param another Another station.

            \return This object.
        */
        station& operator=(const station& another)
        {
            return assign(another);
        }

        /*!
            \brief Checks whether one station is equal to anther.

            \param one     One station.
            \param another Another station.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const station& one, const station& another)
        {
            return one.m_name == another.m_name &&
                   one.m_p_grade == another.m_p_grade;
        }

        /*!
            \brief Returns the name.

            \return The name.
        */
        const name_type& name()
        const
        {
            return m_name;
        }

        /*!
            \brief Returns the grade.

            \return The grade.
        */
        const grade_type& grade()
        const
        {
            assert(m_p_grade != NULL);
            return *m_p_grade;
        }


    private:
        // variables

        name_type m_name;

        const grade_type* m_p_grade;


    };


}}


#endif
