/*! \file
    \brief The definition of concept_bobura::model::Train.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MODEL_TRAIN_H)
#define CONCEPTBOBURA_MODEL_TRAIN_H

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.Assignable.h>


namespace concept_bobura { namespace model
{
    /*!
        \brief The concept check class template for a train.

        \tparam Type A type.
    */
    template <typename Type>
    class Train :
        private concept_tetengo2::Assignable<Type>,
        private boost::EqualityComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::number_type number_type;

        typedef typename Type::note_type note_type;

        typedef typename Type::stop_type stop_type;

        typedef typename Type::stops_type stops_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Train)
        {
            m_object.insert_stop(m_stops.begin(), m_stop);

            m_object.erase_stops(m_stops.begin(), m_stops.end());

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const number_type& number = object.number();
            boost::ignore_unused_variable_warning(number);

            const note_type& note = object.note();
            boost::ignore_unused_variable_warning(note);

            const stops_type& stops = object.stops();
            boost::ignore_unused_variable_warning(stops);
        }

        
    private:
        // variables

        Type m_object;

        stop_type m_stop;

        stops_type m_stops;


#endif
    };


}}

#endif
