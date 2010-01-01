/*! \file
    \brief The definition of concept_tetengo2::gui::Font.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_FONT_H)
#define CONCEPTTETENGO2_GUI_FONT_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a font.

        \tparam Type A type.
    */
    template <typename Type>
    class Font :
        private boost::CopyConstructible<Type>,
        private boost::Assignable<Type>,
        private boost::EqualityComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::string_type string_type;

        typedef typename Type::size_type size_type;

        typedef typename Type::families_type families_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Font)
        {
            const Type& dialog_font = Type::dialog_font();
            boost::ignore_unused_variable_warning(dialog_font);

            const families_type& installed_families =
                Type::installed_families();
            boost::ignore_unused_variable_warning(installed_families);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const string_type& family = object.family();
            boost::ignore_unused_variable_warning(family);

            const size_type size = object.size();
            boost::ignore_unused_variable_warning(size);

            const bool bold = object.bold();
            boost::ignore_unused_variable_warning(bold);

            const bool italic = object.italic();
            boost::ignore_unused_variable_warning(italic);

            const bool underline = object.underline();
            boost::ignore_unused_variable_warning(underline);

            const bool strikeout = object.strikeout();
            boost::ignore_unused_variable_warning(strikeout);
        }


    private:
        // variables

        Type m_object;

        
#endif
    };


}}

#endif
