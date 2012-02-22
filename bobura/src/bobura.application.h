/*! \file
    \brief The definition of bobura::application.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_APPLICATION_H)
#define BOBURA_APPLICATION_H

#include <memory>

#include <boost/mpl/at.hpp>
#include <boost/noncopyable.hpp>

#include <tetengo2.cpp11.h>

#include "bobura.type_list.h"


namespace bobura
{
   /*!
        \brief The class for a bobura application.
    */
    class application : private boost::noncopyable
    {
    public:
        // types

        typedef
            boost::mpl::at<common_type_list, type::settings>::type
            settings_type;


        // constructors and destructor

        /*!
            \brief Creates a bobura application.

            \param settings Settings of the bobura.
        */
        explicit application(const settings_type& settings);

        /*!
            \brief Destroys the bobura application.
        */
        ~application()
        TETENGO2_CPP11_NOEXCEPT;


        // functions

        /*!
            \brief Runs the main process of the application.

            \return The exit status code.
        */
        int run();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}

#endif
