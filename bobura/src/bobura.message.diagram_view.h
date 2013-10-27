/*! \file
    \brief The definition of bobura::message::diagram_view.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_DIAGRAMVIEW_H)
#define BOBURA_MESSAGE_DIAGRAMVIEW_H


namespace bobura { namespace message { namespace diagram_view
{
     /*!
        \brief The class for a unselection observer of the diagram view.
    */
    class unselected_all
    {
    public:
        // functions

        /*!
            \brief Called when a station is selected.

            \param station
        */
        void operator()()
        const
        {

        }


    };


}}}


#endif
