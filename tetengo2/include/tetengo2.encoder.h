/*! \file
    \brief The definition of tetengo2::encoder.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODER_H)
#define TETENGO2_ENCODER_H

#include <boost/concept_check.hpp>


namespace tetengo2
{
    /*!
        \brief The concept class template for tetengo2::encoder.
        
        \param Encoder An encoder type.
    */
    template <typename Encoder>
    class EncoderConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints.
        */
        void constraints()
        {
            const_constraints(m_encoder);
        }

        /*!
            \brief Checks the const constraints.
        */
        void const_constraints(const Encoder& encoder)
        {
            encoder.encode<int>(0);
        }


    private:
        // variables

        Encoder m_encoder;


    };

    /*!
        \brief The concept class template for a template parameter Target of
        tetengo2::encoder.

        This is a refinement of boost::DefaultConstructibleConcept and
        boost::CopyConstructibleConcept.
        
        \param Target A target type.
    */
    template <typename Target>
    class EncoderTargetConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints.
        */
        void constraints()
        {
            boost::function_requires<
                boost::DefaultConstructibleConcept<Target>
            >();
            boost::function_requires<
                boost::CopyConstructibleConcept<Target>
            >();

            Target s(m_iterator, m_iterator);
            boost::ignore_unused_variable_warning(s);

            const_constraints(m_target);
        }

        /*!
            \brief Checks the const constraints.
        */
        void const_constraints(const Target& target)
        {}


    private:
        // variables

        Target m_target;

        typename Target::iterator m_iterator;


    };

    /*!
        \brief The concept class template for a template parameter Source of
        tetengo2::encoder.

        \param Source A source type.
    */
    template <typename Source>
    class EncoderSourceConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints.
        */
        void constraints()
        {
            const_constraints(m_source);
        }

        /*!
            \brief Checks the const constraints.
        */
        void const_constraints(const Source& source)
        {
            const bool b = source.empty();
            boost::ignore_unused_variable_warning(b);

            const typename Source::value_type* const p_v = source.c_str();
            boost::ignore_unused_variable_warning(p_v);

            const typename Source::size_type s = source.length();
            boost::ignore_unused_variable_warning(s);
        }


    private:
        // variables

        Source m_source;


    };
}

#endif
