/*! \file
    \brief The definition of bobura::model::serializer::writer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITERSET_H)
#define BOBURA_MODEL_SERIALIZER_WRITERSET_H

#include <boost/noncopyable.hpp>

#include <tetengo2.cpp11.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer set.

        \tparam OutputStream An output stream type.
        \tparam Timetable    A timetable type.
    */
    template <typename OutputStream, typename Timetable>
    class writer_set : private boost::noncopyable
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;


        // constructors and destructor

        /*!
            \brief Creates a writer set.
        */
        writer_set()
        {}

        /*!
            \brief Destroys the writer_set.
        */
        virtual ~writer_set()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions


    protected:
        // constructors


    private:
        // virtual functions

        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        {

        }


    };


}}}


#endif
