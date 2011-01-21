/*! \file
    \brief The definition of stub_tetengo2::gui::control.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_CONTROL_H)
#define STUBTETENGO2_GUI_CONTROL_H

#include <boost/optional.hpp>

#include "stub_tetengo2.gui.widget.h"
#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class control : public widget<typename Traits::base_type>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef widget<typename traits_type::base_type> base_type;

        typedef typename traits_type::color_type color_type;


        // constructors and destructor

        virtual ~control()
        TETENGO2_NOEXCEPT
        {}


        // functions

        const boost::optional<color_type>& text_color()
        const
        {
            return m_text_color;
        }

        template <typename C /* = boost::optional<color_type>() */>
        void set_text_color(
            C&& text_color /* = boost::optional<color_type>() */
        )
        {
            m_text_color = text_color;
        }

#if !defined(DOCUMENTATION)
        void set_text_color()
        {
            m_text_color = boost::optional<color_type>();
        }
#endif


    protected:
        // constructors

        control()
        :
        base_type(),
        m_text_color()
        {}


    private:
        // variables

        boost::optional<color_type> m_text_color;


        // virtual functions

        virtual typename control::handle_type handle_impl()
        const
        {
            return 0;
        }


    };


}}

#endif
