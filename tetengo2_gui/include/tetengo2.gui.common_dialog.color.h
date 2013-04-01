/*! \file
    \brief The definition of tetengo2::gui::common_dialog::color.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_COLOR_H)
#define TETENGO2_GUI_COMMONDIALOG_COLOR_H

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>


namespace tetengo2 { namespace gui { namespace common_dialog
{
    /*!
        \brief The class template for a color dialog.

        \tparam AbstractWindow      An abstract window type.
        \tparam Color               A color type.
        \tparam CommonDialogDetails A detail implementation type of common dialogs.
    */
    template <typename AbstractWindow, typename Color, typename CommonDialogDetails>
    class color : private boost::noncopyable
    {
    public:
        // types

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The color type.
        typedef Color color_type;

        //! The detail implementation type of common dialogs.
        typedef CommonDialogDetails common_dialog_details_type;

        //! The detail implementation type.
        typedef typename common_dialog_details_type::color_dialog_details_type details_type;

        //! The detail implementaiton pointer type;
        typedef typename common_dialog_details_type::color_dialog_details_ptr_type details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a color dialog.

            \param color  A color.
            \param parent A parent widget.
        */
        color(const boost::optional<color_type>& color, abstract_window_type& parent)
        :
        m_p_details(common_dialog_details_type::create_color_dialog(parent, color)),
        m_result(color ? *color : color_type(0, 0, 0))
        {}


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        const color_type& result()
        const
        {
            return m_result;
        }

        /*!
            \brief Shows the dialog as model.

            \retval true  When the OK button is pressed.
            \retval false Otherwise.
        */
        bool do_modal()
        {
            const auto result = common_dialog_details_type::template show_color_dialog<color_type>(*m_p_details);
            if (!result)
                return false;

            m_result = *result;
            return true;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details()
        const
        {
            return *m_p_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            return *m_p_details;
        }


    private:
        // variables

        details_ptr_type m_p_details;

        color_type m_result;


    };


}}}


#endif
