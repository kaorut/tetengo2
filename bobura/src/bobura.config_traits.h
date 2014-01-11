/*! \file
    \brief The definition of bobura::config_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_CONFIGTRAITS_H)
#define BOBURA_CONFIGTRAITS_H

#include <tetengo2.config.cached_config.h>
#include <tetengo2.config.config_base.h>
#include <tetengo2.config.config_list.h>
#include <tetengo2.config.persistent_config.h>
#include <tetengo2.config.temporary_config.h>


namespace bobura
{
   /*!
        \brief The class template for a configuration traits.

        \tparam String        A string type.
        \tparam UInt          An unsigned integer type.
        \tparam Encoder       An encoder type.
        \tparam ConfigDetails A detail implementation type of a configuration.
    */
    template <typename String, typename UInt, typename Encoder, typename ConfigDetails>
    class config_traits
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The unsigned integer type.
        typedef UInt uint_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The detail implementation type of the configuration.
        typedef ConfigDetails config_details_type;

        //! The configuration base type.
        typedef tetengo2::config::config_base<string_type, uint_type> config_base_type;

        //! The configuration list type.
        typedef tetengo2::config::config_list<string_type, uint_type> config_list_type;

        //! The cached configuration type.
        typedef tetengo2::config::cached_config<string_type, uint_type> cached_config_type;

        //! The temporary configuration type.
        typedef tetengo2::config::temporary_config<string_type, uint_type> temporary_config_type;

        //! The persistent configuration type.
        typedef
            tetengo2::config::persistent_config<string_type, uint_type, encoder_type, config_details_type>
            persistent_config_type;


    };


}


#endif
