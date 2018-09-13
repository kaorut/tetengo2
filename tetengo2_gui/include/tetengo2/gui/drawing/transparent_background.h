/*! \file
    \brief The definition of tetengo2::gui::drawing::transparent_background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_TRANSPARENTBACKGROUND_H)
#define TETENGO2_GUI_DRAWING_TRANSPARENTBACKGROUND_H

#include <cassert>
#include <memory>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/drawing/background.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a transparent background.
    */
    class transparent_background : public background
    {
    public:
        // types

        //! The base type.
        using base_type = background;

        //! The drawing details type.
        using drawing_details_type = base_type::drawing_details_type;


        // constructors and destructor

        /*!
            \brief Creates a transparent background.

            \param drawing_details A detailm implementation of a drawing.
        */
        explicit transparent_background(const drawing_details_type& drawing_details)
        : base_type{}, m_drawing_details{ drawing_details }, m_p_details{
              m_drawing_details.create_transparent_background()
          }
        {}

        /*!
            \brief Creates a transparent background.

            Creates a background for widgets.
        */
        transparent_background()
        : base_type{}, m_drawing_details{ detail::gui_detail_impl_set().drawing_() }, m_p_details{
              m_drawing_details.create_transparent_background()
          }
        {}

        /*!
            \brief Destroys the background.
        */
        virtual ~transparent_background() = default;


    private:
        // types

        using details_type = typename base_type::details_type;

        using details_ptr_type = drawing_details_type::background_details_ptr_type;


        // variables

        const drawing_details_type& m_drawing_details;

        const details_ptr_type m_p_details;


        // virtual functions

        virtual std::unique_ptr<base_type> clone_impl() const override
        {
            return std::make_unique<transparent_background>(m_drawing_details);
        }

        virtual const drawing_details_type& drawing_details_impl() const override
        {
            return m_drawing_details;
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
