/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H

#include <algorithm>
//#include <utility>

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.gui.Dialog.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam Dialog A dialog type. It must conform to
                       concept_tetengo2::gui::Dialog<Dialog>.
    */
    template <typename Dialog>
    class about
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Dialog<Dialog>));


    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;

        //! The window type.
        typedef typename dialog_type::window_type window_type;


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
            dialog_type dialog(*m_p_window);

            const typename window_type::position_type& window_position =
                m_p_window->position();
            dialog.set_dimension(std::make_pair(384, 256));
            dialog.set_position(
                std::make_pair(
                    window_position.first + 64, window_position.second + 64
                )
            );

            dialog.do_modal();
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

        \tparam Dialog A dialog type. It must conform to
                       concept_tetengo2::gui::Dialog<Dialog>.

        \param about1 An about object #1.
        \param about2 An about object #2.
    */
    template <typename Dialog>
    void swap(
        bobura::command::about<Dialog>& about1,
        bobura::command::about<Dialog>& about2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Dialog<Dialog>));

        about1.swap(about2);
    }


}

#endif
