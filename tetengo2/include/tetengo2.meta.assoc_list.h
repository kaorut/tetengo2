/*! \file
    \brief The definition of tetengo2::meta::assoc_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_META_ASSOCLIST_H)
#define TETENGO2_META_ASSOCLIST_H //!< !! Include Guard !!


namespace tetengo2 { namespace meta
{
    /*!
        \brief The metaclass for a node of an associative list.

        \tparam Value A value.
        \tparam Next  A next node.
    */
    template <typename Value, typename Next>
    struct assoc_list
    {
        // types

        //! The value.
        typedef Value value;

        //! The next node.
        typedef Next next;


    };


}}


#endif
