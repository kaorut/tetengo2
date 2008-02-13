/*! \file
    \brief The definition of bobura::model::station_info::grade.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONINFO_GRADE_H)
#define BOBURA_MODEL_STATIONINFO_GRADE_H

#include <boost/noncopyable.hpp>

#include <tetengo2.StringConcept.h>


namespace bobura { namespace model { namespace station_info
{
    /*!
        \brief The class for a station grade.

        \param String A string type. It must conform to
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

            \param name A name.
        */
        grade()
        {}


    };

    namespace
    {
        template <typename T>
        struct grade_name;

        template <>
        struct grade_name< ::std::string>
        {
            static const ::std::string& local()
            {
                static const ::std::string singleton = "local";
                return singleton;
            }

            static const ::std::string& major()
            {
                static const ::std::string singleton = "major";
                return singleton;
            }

            static const ::std::string& local_terminal()
            {
                static const ::std::string singleton = "local terminal";
                return singleton;
            }

            static const ::std::string& major_terminal()
            {
                static const ::std::string singleton = "major terminal";
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

            static const ::std::wstring& major()
            {
                static const ::std::wstring singleton = L"major";
                return singleton;
            }

            static const ::std::wstring& local_terminal()
            {
                static const ::std::wstring singleton = L"local terminal";
                return singleton;
            }

            static const ::std::wstring& major_terminal()
            {
                static const ::std::wstring singleton = L"major terminal";
                return singleton;
            }


        };


    }

    /*!
        \brief The class for a local station grade.

        \param String A string type. It must conform to
                      tetengo2::StringConcept<String>.
    */
    template <typename String>
    class local : public grade<String>
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the local.
        */
        virtual ~local()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the instance of the local.

            \return The instance of the local.
        */
        static const local& instance()
        {
            static const local singleton;

            return singleton;
        }

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
        \brief The class for a major station grade.
 
        \param String A string type. It must conform to
                      tetengo2::StringConcept<String>.
   */
    template <typename String>
    class major : public grade<String>
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the major.
        */
        virtual ~major()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the instance of the major.

            \return The instance of the major.
        */
        static const major& instance()
        {
            static const major singleton;

            return singleton;
        }

        /*!
            \brief Returns the name.

            \return The name "major".
        */
        virtual const string_type& name()
        const
        {
            return grade_name<string_type>::major();
        }


    private:
        // constructors

        major()
        {}


    };

    /*!
        \brief The class for a local terminal station grade.

        \param String A string type. It must conform to
                      tetengo2::StringConcept<String>.
    */
    template <typename String>
    class local_terminal : public grade<String>
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the local terminal.
        */
        virtual ~local_terminal()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the instance of the local terminal.

            \return The instance of the local terminal.
        */
        static const local_terminal& instance()
        {
            static const local_terminal singleton;

            return singleton;
        }

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
        \brief The class for a major terminal station grade.

        \param String A string type. It must conform to
                      tetengo2::StringConcept<String>.
    */
    template <typename String>
    class major_terminal : public grade<String>
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the major terminal.
        */
        virtual ~major_terminal()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the instance of the major terminal.

            \return The instance of the major terminal.
        */
        static const major_terminal& instance()
        {
            static const major_terminal singleton;

            return singleton;
        }

        /*!
            \brief Returns the name.

            \return The name "major terminal".
        */
        virtual const string_type& name()
        const
        {
            return grade_name<string_type>::major_terminal();
        }


    private:
        // constructors

        major_terminal()
        {}


    };


}}}

#endif
