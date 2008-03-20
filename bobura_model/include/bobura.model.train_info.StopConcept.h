/*! \file
    \brief The definition of bobura::model::stoptable_info::StopConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_STOPCONCEPT_H)
#define BOBURA_MODEL_TRAININFO_STOPCONCEPT_H

#include <algorithm>

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a stop.

        \tparam Stop A stop type.
    */
    template <typename Stop>
    class StopConcept
    {
    public:
        // constructors and destructor

        StopConcept();


        // functions

        /*!
            \brief Checks the constraints on a stop.
        */
        void constraints()
        {
            typedef typename Stop::time_type time_type;
            typedef typename Stop::platform_type platform_type;

            m_stop.swap(m_stop);
            std::swap(m_stop, m_stop);

            Stop& assigned = m_stop = m_stop;
            boost::ignore_unused_variable_warning(assigned);

            const_constraints(m_stop);
        }

        /*!
            \brief Checks the const constraints on a stop.

            \param stop A constant object.
        */
        void const_constraints(const Stop& stop)
        {
            const bool equality = stop == stop;
            boost::ignore_unused_variable_warning(equality);
        }


    private:
        // variables

        Stop m_stop;


    };


}}}

#endif
