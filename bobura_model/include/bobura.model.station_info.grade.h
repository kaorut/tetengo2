/*! \file
    \brief The definition of bobura::model::station_info::grade.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONINFO_GRADE_H)
#define BOBURA_MODEL_STATIONINFO_GRADE_H

#include <boost/noncopyable.hpp>

#include <tetengo2.text.h>


namespace bobura { namespace model { namespace station_info
{
    /*!
        \brief The class for a station grade.

        \tparam GradeName A grade name type.
    */
    template <typename GradeName>
    class grade : private boost::noncopyable
    {
    public:
        // types

        //! The name type.
        typedef GradeName name_type;


        // functions

        /*!
            \brief Returns the name.

            \return The name.
        */
        const name_type& name()
        const
        {
            return name_impl();
        }


    protected:
        // constructors and destructor

        /*!
            \brief Creates a grade.
        */
        grade()
        {}

        /*!
            \brief Destroys the grade.
        */
        virtual ~grade()
        {}


    private:
        // virtual functions

        virtual const name_type& name_impl()
        const = 0;


    };


    /*!
        \brief The class for a local station grade.

        \tparam GradeName A grade name type.
    */
    template <typename GradeName>
    class local : public grade<GradeName>
    {
    public:
        // types

        //! The base type.
        typedef grade<GradeName> base_type;


        // static functions

        /*!
            \brief Returns the instance of the local.

            \return The instance of the local.
        */
        static const local& instance()
        {
            static const local singleton;

            return singleton;
        }


    private:
        // constructors and destructor

        local()
        {}

        virtual ~local()
        {}


        // virtual functions

        virtual const typename local::name_type& name_impl()
        const
        {
            static const typename local::name_type singleton(TETENGO2_TEXT("local"));
            return singleton;
        }


    };

    /*!
        \brief The class for a principal station grade.

        \tparam GradeName A grade name type.
   */
    template <typename GradeName>
    class principal : public grade<GradeName>
    {
    public:
        // types

        //! The base type.
        typedef grade<GradeName> base_type;


        // static functions

        /*!
            \brief Returns the instance of the principal.

            \return The instance of the principal.
        */
        static const principal& instance()
        {
            static const principal singleton;

            return singleton;
        }


    private:
        // constructors and destructor

        principal()
        {}

        virtual ~principal()
        {}


        // virtual functions

        virtual const typename principal::name_type& name_impl()
        const
        {
            static const typename principal::name_type singleton(TETENGO2_TEXT("principal"));
            return singleton;
        }


    };

    /*!
        \brief The class for a local terminal station grade.

        \tparam GradeName A grade name type.
    */
    template <typename GradeName>
    class local_terminal : public grade<GradeName>
    {
    public:
        // types

        //! The base type.
        typedef grade<GradeName> base_type;


        // static functions

        /*!
            \brief Returns the instance of the local terminal.

            \return The instance of the local terminal.
        */
        static const local_terminal& instance()
        {
            static const local_terminal singleton;

            return singleton;
        }


    private:
        // constructors and destructor

        local_terminal()
        {}

        virtual ~local_terminal()
        {}


        // virtual functions

        virtual const typename local_terminal::name_type& name_impl()
        const
        {
            static const typename local_terminal::name_type singleton(TETENGO2_TEXT("local terminal"));
            return singleton;
        }


   };

    /*!
        \brief The class for a principal terminal station grade.

        \tparam GradeName A grade name type.
    */
    template <typename GradeName>
    class principal_terminal : public grade<GradeName>
    {
    public:
        // types

        //! The base type.
        typedef grade<GradeName> base_type;


        // static functions

        /*!
            \brief Returns the instance of the principal terminal.

            \return The instance of the principal terminal.
        */
        static const principal_terminal& instance()
        {
            static const principal_terminal singleton;

            return singleton;
        }


    private:
        // constructors and destructor

        principal_terminal()
        {}

        virtual ~principal_terminal()
        {}


        // virtual functions

        virtual const typename principal_terminal::name_type& name_impl()
        const
        {
            static const typename principal_terminal::name_type singleton(TETENGO2_TEXT("principal terminal"));
            return singleton;
        }


    };


    /*!
        \brief The class template for a grade type set.

        \tparam String A string type.
    */
    template <typename String>
    class grade_type_set : boost::noncopyable
    {
    public:
        // types

        //! The grade type.
        typedef grade<String> grade_type;

        //! The local type.
        typedef local<String> local_type;

        //! The principal type.
        typedef principal<String> principal_type;

        //! The local terminal type.
        typedef local_terminal<String> local_terminal_type;

        //! The principal terminal type.
        typedef principal_terminal<String> principal_terminal_type;


    private:
        // forbidden operations

        grade_type_set();


    };


}}}

#endif
