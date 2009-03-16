/*! \file
    \brief The definition of stub_tetengo2::gui::font.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_FONT_H)
#define STUBTETENGO2_GUI_FONT_H

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include "concept_tetengo2.String.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename String, typename Size>
    class font : public boost::equality_comparable<font<String, Size> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));


    public:
        // types

        typedef String string_type;

        typedef Size size_type;


        // constructors and destructor

        font(const string_type& family, const size_type size)
        {}

        font(const font& another)
        {}

        virtual ~font()
        throw ()
        {}


        // functions

        void swap(font& another)
        {}

        font& operator=(const font& another)
        {
            font(another).swap(*this);
            return *this;
        }

        bool operator==(const font& another)
        const
        {
            return true;
        }


    };


}}


namespace std
{
    template <typename String, typename Size>
    void swap(
        stub_tetengo2::gui::font<String, Size>& font1,
        stub_tetengo2::gui::font<String, Size>& font2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));

        font1.swap(font2);
    }

    
}


#endif
