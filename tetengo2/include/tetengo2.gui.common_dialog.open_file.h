/*! \file
    \brief The definition of tetengo2::gui::common_dialog::open_file.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_OPENFILE_H)
#define TETENGO2_GUI_COMMONDIALOG_OPENFILE_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace common_dialog
{
    /*!
        \brief The class template for a open-file dialog box.

        \tparam String              A string type.
        \tparam Path                A path type.
        \tparam CommonDialogDetails A detail implementation type of common
                                    dialog boxes.
    */
    template <typename String, typename Path, typename CommonDialogDetails>
    class open_file : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The path type.
        typedef Path path_type;

        //! The detail implementation type of common dialog boxes.
        typedef CommonDialogDetails common_dialog_details_type;


        // constructors and destructor

        /*!
            \brief Creates a open-file dialog box.
        */
        open_file()
        {}


        // functions



    private:
        // variables



    };


}}}


#endif
