/*! \file
    \brief The definition of bobura::model::station.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATION_H)
#define BOBURA_MODEL_STATION_H

#include <algorithm>
#include <cassert>
#include <cstddef>
//#include <string>

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include <tetengo2.StringConcept.h>

#include "bobura.model.station_info.GradeConcept.h"


namespace bobura { namespace model
{
    /*!
        \brief The class template for a station.

        \tparam String A string type. It must conform to
                       tetengo2::StringConcept<String>.
        \tparam Grade  A grade type. It must conform to
                       bobura::model::station_info::GradeConcept<Grade>.
    */
    template <typename String, typename Grade>
    class station :
        private boost::equality_comparable<station<String, Grade> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(String, tetengo2, StringConcept);
        BOOST_CLASS_REQUIRE(Grade, bobura::model::station_info, GradeConcept);


    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The grade type.
        typedef Grade grade_type;


        // constructors and destructor

        /*!
            \brief Creates a station.

            \param name  A name.
            \param grade A grade.
        */
        station(const string_type& name, const grade_type& grade)
        :
        m_name(name),
        m_p_grade(&grade)
        {}

        /*!
            \brief Copies a station.

            \param another Another station object.
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
            \brief Swaps the members with another station object.

            \param another Another station object.
        */
        void swap(station& another)
        throw ()
        {
            m_name.swap(another.m_name);
            std::swap(m_p_grade, another.m_p_grade);
        }

        /*!
            \brief Assigns another station object.

            \param another Another station object.

            \return this object.
        */
        station& operator=(const station& another)
        {
            station(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther station object.

            \param another Another station object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const station& another)
        const
        {
            return m_name == another.m_name &&
                   m_p_grade == another.m_p_grade;
        }

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type name()
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

        string_type m_name;

        const grade_type* m_p_grade;


    };


}}

namespace std
{
    /*!
        \brief Swaps two station objects.

        \tparam String A string type. It must conform to
                       tetengo2::StringConcept<String>.
        \tparam Grade  A grade type. It must conform to
                       bobura::model::station_info::GradeConcept<Grade>.

        \param station1 A station object #1.
        \param station2 A station object #2.
    */
    template <typename String, typename Grade>
    void swap(
        bobura::model::station<String, Grade>& station1,
        bobura::model::station<String, Grade>& station2
    )
    throw ()
    {
        boost::function_requires<tetengo2::StringConcept<String> >();
        boost::function_requires<
            bobura::model::station_info::GradeConcept<Grade>
        >();

        station1.swap(station2);
    }


}

#endif
