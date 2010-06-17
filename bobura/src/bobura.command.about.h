/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H

//#include <boost/concept_check.hpp>
#include <boost/swap.hpp>

#include <tetengo2.assignable.h>
#include <tetengo2.swappable.h>

#include "concept_bobura.AboutDialog.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam AboutDialog An about dialog type. It must conform to
                            concept_bobura::AboutDialog<AboutDialog>.
    */
    template <typename AboutDialog>
    class about :
        public tetengo2::assignable<about<AboutDialog> >,
        private tetengo2::swappable<about<AboutDialog> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_bobura::AboutDialog<AboutDialog>));


    public:
        // types

        //! \return The about dialog type.
        typedef AboutDialog about_dialog_type;

        //! \return The abstract window type.
        typedef
            typename about_dialog_type::abstract_window_type
            abstract_window_type;


        // constructors and destructor

        /*!
            \brief Creates an about command.

            \param parent A parent window.
        */
        explicit about(abstract_window_type& parent)
        :
        m_p_parent(&parent)
        {}

        /*!
            \brief Copies an about command.

            \param another Another about command.
        */
        about(const about& another)
        :
        m_p_parent(another.m_p_parent)
        {}

        /*!
            \brief Destroys the about command.
        */
        ~about()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another about command.

            \param another Another about command.
        */
        void swap(about& another)
        throw ()
        {
            boost::swap(m_p_parent, another.m_p_parent);
        }

        /*!
            \brief Assigns another about command.

            \param another Another about command.

            \return This object.
        */
        about& operator=(const about& another)
        {
            return assign(another);
        }

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            about_dialog_type(*m_p_parent).do_modal();
        }


    private:
        // variables

        abstract_window_type* m_p_parent;


    };


}}


#endif
