/*! \file
    \brief The definition of bobura::model::serializer::writer_type_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITERTYPESET_H)
#define BOBURA_MODEL_SERIALIZER_WRITERTYPESET_H

#include <boost/noncopyable.hpp>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer type set.

        \tparam Writer A writer type.
    */
    template <typename Writer>
    class writer_type_set : private boost::noncopyable
    {
    public:
        // types

        //! The writer type.
        typedef Writer writer_type;


    private:
        // forbidden operations

        writer_type_set();


    };


}}}


#endif
