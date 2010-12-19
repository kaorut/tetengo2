/*! \file
    \brief The definition of bobura::model::station.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATION_H)
#define BOBURA_MODEL_STATION_H

#include <cassert>
#include <cstddef>
#include <utility>

#include <boost/operators.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a station.

        \tparam Name  A name type.
        \tparam Grade A grade type.
    */
    template <typename Name, typename Grade>
    class station : private boost::equality_comparable<station<Name, Grade>>
    {
    public:
        // types

        //! The name type.
        typedef Name name_type;

        //! The grade type.
        typedef Grade grade_type;


        // constructors and destructor

        /*!
            \brief Creates a station.

            \tparam N A name type.

            \param name  A name.
            \param grade A grade.
        */
        template <typename N>
        station(N&& name, const grade_type& grade)
        :
        m_name(std::forward<N>(name)),
        m_p_grade(&grade)
        {}


        // functions

        /*!
            \brief Checks whether one station is equal to another.

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
