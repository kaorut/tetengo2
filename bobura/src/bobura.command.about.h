/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H

#include <algorithm>

//#include <boost/concept_check.hpp>

#include "concept_bobura.AboutDialog.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam AboutDialog An about dialog type. It must conform to
                            concept_bobura::AboutDialog<AboutDialog>.
    */
    template <typename AboutDialog>
    class about
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_bobura::AboutDialog<AboutDialog>));


    public:
        // types

        //! The about dialog type.
        typedef AboutDialog about_dialog_type;

        //! The window type.
        typedef typename about_dialog_type::window_type window_type;


        // constructors and destructor

        /*!
            \brief Creates an about command.

            \param window A window.
        */
        explicit about(window_type& window)
        :
        m_p_window(&window)
        {}

        /*!
            \brief Copies an about command.

            \param another Another about command object.
        */
        about(const about& another)
        :
        m_p_window(another.m_p_window)
        {}

        /*!
            \brief Destroys the about command.
        */
        ~about()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another about command object.

            \param another Another about command object.
        */
        void swap(about& another)
        throw ()
        {
            std::swap(m_p_window, another.m_p_window);
        }

        /*!
            \brief Assigns another about command object.

            \param another Another about command object.

            \return this object.
        */
        about& operator=(const about& another)
        {
            about(another).swap(*this);
            return *this;
        }

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            about_dialog_type(*m_p_window).do_modal();
        }


    private:
        // variables

        window_type* m_p_window;


    };


}}

namespace std
{
    /*!
        \brief Swaps two about objects.

        \tparam AboutDialog An about dialog type. It must conform to
                            concept_bobura::AboutDialog<AboutDialog>.

        \param about1 An about object #1.
        \param about2 An about object #2.
    */
    template <typename AboutDialog>
    void swap(
        bobura::command::about<AboutDialog>& about1,
        bobura::command::about<AboutDialog>& about2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_bobura::AboutDialog<AboutDialog>));

        about1.swap(about2);
    }


}

#endif
