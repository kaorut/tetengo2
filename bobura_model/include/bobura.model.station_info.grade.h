/*! \file
    \brief The definition of bobura::model::station_info::grade.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONINFO_GRADE_H)
#define BOBURA_MODEL_STATIONINFO_GRADE_H

//#include <string>

#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include <tetengo2.StringConcept.h>


namespace bobura { namespace model { namespace station_info
{
    /*!
        \brief The class for a station grade.

        \tparam String A string type. It must conform to
                       tetengo2::StringConcept<String>.
    */
    template <typename String>
    class grade : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(String, tetengo2, StringConcept);


    public:
        // types

        //! The string type.
        typedef String string_type;


        // static functions

        /*!
            \brief Returns the instance of the grade.

            \return The instance of the local.
        */
        static const grade& instance()
        {
            return local<string_type>::instance();
        }


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
        virtual const string_type& name()
        const = 0;


    protected:
        // constructors

        /*!
            \brief Creates a grade.
        */
        grade()
        {}


    };

    namespace
    {
        template <typename String>
        struct grade_name;

        template <>
        struct grade_name< ::std::string>
        {
            static const ::std::string& local()
            {
                static const ::std::string singleton = "local";
                return singleton;
            }

            static const ::std::string& principal()
            {
                static const ::std::string singleton = "principal";
                return singleton;
            }

            static const ::std::string& local_terminal()
            {
                static const ::std::string singleton = "local terminal";
                return singleton;
            }

            static const ::std::string& principal_terminal()
            {
                static const ::std::string singleton = "principal terminal";
                return singleton;
            }


        };

        template <>
        struct grade_name< ::std::wstring>
        {
            static const ::std::wstring& local()
            {
                static const ::std::wstring singleton = L"local";
                return singleton;
            }

            static const ::std::wstring& principal()
            {
                static const ::std::wstring singleton = L"principal";
                return singleton;
            }

            static const ::std::wstring& local_terminal()
            {
                static const ::std::wstring singleton = L"local terminal";
                return singleton;
            }

            static const ::std::wstring& principal_terminal()
            {
                static const ::std::wstring singleton = L"principal terminal";
                return singleton;
            }


        };


    }

    /*!
        \brief The class for a local station grade.

        \tparam String A string type. It must conform to
                       tetengo2::StringConcept<String>.
    */
    template <typename String>
    class local : public grade<String>
    {
    public:
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
            \brief Returns the name.

            \return The name "local".
        */
        virtual const string_type& name()
        const
        {
            return grade_name<string_type>::local();
        }


    private:
        // constructors

        local()
        {}


    };

    /*!
        \brief The class for a principal station grade.
 
        \tparam String A string type. It must conform to
                       tetengo2::StringConcept<String>.
   */
    template <typename String>
    class principal : public grade<String>
    {
    public:
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
            \brief Returns the name.

            \return The name "principal".
        */
        virtual const string_type& name()
        const
        {
            return grade_name<string_type>::principal();
        }


    private:
        // constructors

        principal()
        {}


    };

    /*!
        \brief The class for a local terminal station grade.

        \tparam String A string type. It must conform to
                       tetengo2::StringConcept<String>.
    */
    template <typename String>
    class local_terminal : public grade<String>
    {
    public:
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
            \brief Returns the name.

            \return The name "local terminal".
        */
        virtual const string_type& name()
        const
        {
            return grade_name<string_type>::local_terminal();
        }


    private:
        // constructors

        local_terminal()
        {}


    };

    /*!
        \brief The class for a principal terminal station grade.

        \tparam String A string type. It must conform to
                       tetengo2::StringConcept<String>.
    */
    template <typename String>
    class principal_terminal : public grade<String>
    {
    public:
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
            \brief Returns the name.

            \return The name "principal terminal".
        */
        virtual const string_type& name()
        const
        {
            return grade_name<string_type>::principal_terminal();
        }


    private:
        // constructors

        principal_terminal()
        {}


    };


}}}

#endif
