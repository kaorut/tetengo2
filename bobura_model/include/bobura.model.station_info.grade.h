/*! \file
    \brief The definition of bobura::model::station_info::grade.

    Copyright (C) 2007-2010 kaoru

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

        //! \return The name type.
        typedef GradeName name_type;


        // constructors and destructor

        /*!
            \brief Destroys the grade.
        */
        virtual ~grade()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the name.

            \return The name.
        */
        virtual const name_type& name()
        const = 0;


    protected:
        // constructors

        /*!
            \brief Creates a grade.
        */
        grade()
        {}


    };


    /*!
        \brief The class for a local station grade.

        \tparam GradeName A grade name type. It must conform to
                          concept_tetengo2::String<GradeName>.
    */
    template <typename GradeName>
    class local : public grade<GradeName>
    {
    public:
        // types

        //! \return The base type.
        typedef grade<GradeName> base_type;

        //! \copydoc bobura::model::station_info::grade::name_type
        typedef typename base_type::name_type name_type;


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


        // constructors and destructor

        /*!
            \brief Destroys the local.
        */
        virtual ~local()
        throw ()
        {}


        // functions

        /*!
            \copybrief grade::name

            \return The name "local".
        */
        virtual const name_type& name()
        const
        {
            static const name_type singleton(TETENGO2_TEXT("local"));
            return singleton;
        }


    private:
        // constructors

        local()
        {}


    };

    /*!
        \brief The class for a principal station grade.
 
        \tparam GradeName A grade name type. It must conform to
                          concept_tetengo2::String<GradeName>.
   */
    template <typename GradeName>
    class principal : public grade<GradeName>
    {
    public:
        // types

        //! \return The base type.
        typedef grade<GradeName> base_type;

        //! \copydoc bobura::model::station_info::grade::name_type
        typedef typename base_type::name_type name_type;


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


        // constructors and destructor

        /*!
            \brief Destroys the principal.
        */
        virtual ~principal()
        throw ()
        {}


        // functions

        /*!
            \copybrief grade::name

            \return The name "principal".
        */
        virtual const name_type& name()
        const
        {
            static const name_type singleton(TETENGO2_TEXT("principal"));
            return singleton;
        }


    private:
        // constructors

        principal()
        {}


    };

    /*!
        \brief The class for a local terminal station grade.

        \tparam GradeName A grade name type. It must conform to
                          concept_tetengo2::String<GradeName>.
    */
    template <typename GradeName>
    class local_terminal : public grade<GradeName>
    {
    public:
        // types

        //! \return The base type.
        typedef grade<GradeName> base_type;

        //! \copydoc bobura::model::station_info::grade::name_type
        typedef typename base_type::name_type name_type;


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


        // constructors and destructor

        /*!
            \brief Destroys the local terminal.
        */
        virtual ~local_terminal()
        throw ()
        {}


        // functions

        /*!
            \copybrief grade::name

            \return The name "local terminal".
        */
        virtual const name_type& name()
        const
        {
            static const name_type singleton(TETENGO2_TEXT("local terminal"));
            return singleton;
        }


    private:
        // constructors

        local_terminal()
        {}


    };

    /*!
        \brief The class for a principal terminal station grade.

        \tparam GradeName A grade name type. It must conform to
                          concept_tetengo2::String<GradeName>.
    */
    template <typename GradeName>
    class principal_terminal : public grade<GradeName>
    {
    public:
        // types

        //! \return The base type.
        typedef grade<GradeName> base_type;

        //! \copydoc bobura::model::station_info::grade::name_type
        typedef typename base_type::name_type name_type;


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


        // constructors and destructor

        /*!
            \brief Destroys the principal terminal.
        */
        virtual ~principal_terminal()
        throw ()
        {}


        // functions

        /*!
            \copybrief grade::name

            \return The name "principal terminal".
        */
        virtual const name_type& name()
        const
        {
            static const name_type singleton(
                TETENGO2_TEXT("principal terminal")
            );
            return singleton;
        }


    private:
        // constructors

        principal_terminal()
        {}


    };


}}}

#endif
