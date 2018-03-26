/*! \file
    \brief The definition of tetengo2::gui::drawing::transparent_background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_TRANSPARENTBACKGROUND_H)
#define TETENGO2_GUI_DRAWING_TRANSPARENTBACKGROUND_H

#include <cassert>
#include <memory>

#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class template for a transparent background.

        \tparam DrawingDetails A detail implementation type of a drawing.
    */
    template <typename DrawingDetails>
    class transparent_background : public background<DrawingDetails>
    {
    public:
        // types

        //! The base type.
        using base_type = background<DrawingDetails>;


        // constructors and destructor

        /*!
            \brief Creates a transparent background.
        */
        transparent_background()
        : base_type{}, m_p_details{ base_type::drawing_details_type::create_transparent_background() }
        {}

        /*!
            \brief Destroys the background.
        */
        virtual ~transparent_background() = default;


    private:
        // types

        using details_type = typename base_type::details_type;

        using details_ptr_type = typename base_type::details_ptr_type;


        // variables

        const details_ptr_type m_p_details;


        // virtual functions

        virtual std::unique_ptr<base_type> clone_impl() const override
        {
            return stdalt::make_unique<transparent_background>();
        }

        virtual const details_type& details_impl() const override
        {
            assert(m_p_details);
            return *m_p_details;
        }

        virtual details_type& details_impl() override
        {
            assert(m_p_details);
            return *m_p_details;
        }
    };
}


#endif
