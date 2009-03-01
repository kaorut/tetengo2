/*! \file
    \brief The definition of concept_bobura::Settings.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_SETTINGS_H)
#define CONCEPTBOBURA_SETTINGS_H

#include <boost/concept_check.hpp>


namespace concept_bobura
{
    /*!
        \brief The concept check class template for settings.

        \tparam Type A type.
    */
    template <typename Type>
    class Settings
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::string_type string_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Settings)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            //const name_type name = object.name();
            //boost::ignore_unused_variable_warning(name);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}

#endif
