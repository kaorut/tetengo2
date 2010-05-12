/*! \file
    \brief The definition of concept_tetengo2::Path.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_PATH_H)
#define CONCEPTTETENGO2_PATH_H

#include <boost/concept_check.hpp>
#include <boost/filesystem.hpp>


namespace concept_tetengo2
{
    /*!
        \brief The concept check class template for a path.

        \tparam Type A type.
    */
    template <typename Type>
    class Path
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(Path)
        {
            m_object.error_type_must_be_a_path_type();
        }

       
    private:
        // variables

        Type m_object;


#endif
    };

#if !defined(DOCUMENTATION)
    // A specialized template.
    template <class String, class Traits>
    class Path<boost::filesystem::basic_path<String, Traits> >
    {
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(Path)
        {}


    };
#endif


}

#endif
