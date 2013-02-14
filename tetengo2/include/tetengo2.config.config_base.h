/*! \file
    \brief The definition of tetengo2::config::config_base.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_CONFIGBASE_H)
#define TETENGO2_CONFIG_CONFIGBASE_H


namespace tetengo2 { namespace config
{
    /*!
        \brief The class template for a configuration base.

        \tparam String A string type.
    */
    template <typename String>
    class config_base : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        typedef String string_type;


        // constructors and destructor

        /*!
            \brief Creates a configuration base.
        */
        config_base()
        {}

        /*!
            \brief Destroys the configuration base.
        */
        virtual ~config_base()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions
        

    };


}}


#endif
