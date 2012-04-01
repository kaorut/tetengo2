/*! \file
    \brief The definition of bobura::model::serializer::writer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITERSET_H)
#define BOBURA_MODEL_SERIALIZER_WRITERSET_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <tetengo2.cpp11.h>

#include "bobura.model.serializer.writer.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer set.

        \tparam OutputStream An output stream type.
        \tparam Timetable    A timetable type.
        \tparam PathString   A path string type.
    */
    template <typename OutputStream, typename Timetable, typename PathString>
    class writer_set : public writer<OutputStream, Timetable, PathString>
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path string type.
        typedef PathString path_string_type;

        //! The base type.
        typedef
            writer<output_stream_type, timetable_type, path_string_type>
            base_type;


        // constructors and destructor

        /*!
            \brief Creates a writer set.

            The extention must not include the first dot;
            not ".txt" but "txt".

            \tparam PS A path string type.

            \param p_writers Unique pointers to writers.
            \param extention An extention.
        */
        template <typename PS>
        writer_set(
            std::vector<std::unique_ptr<base_type>>&& p_writers,
            PS&&                                      extention
        )
        :
        m_p_writers(std::move(p_writers)),
        m_extention(std::forward<PS>(extention))
        {}

        /*!
            \brief Destroys the writer_set.
        */
        virtual ~writer_set()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // variables

        const std::vector<std::unique_ptr<base_type>> m_p_writers;

        const path_string_type m_extention;


        // virtual functions

        virtual path_string_type extention_impl()
        const
        {
            throw std::logic_error("No extention.");
        }

        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        {

        }


    };


}}}


#endif
