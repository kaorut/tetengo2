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

#include <boost/throw_exception.hpp>

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

            When no writer adopts the extention, the first writer of p_writers
            is used.

            \tparam PS A path string type.

            \param p_writers Unique pointers to writers.
            \param extention An extention.

            \throw std::invalid_argument When the count of the writers is
                                         empty.
        */
        template <typename PS>
        writer_set(
            std::vector<std::unique_ptr<base_type>>&& p_writers,
            PS&&                                      extention
        )
        :
        m_p_writers(std::move(p_writers)),
        m_extention(std::forward<PS>(extention))
        {
            if (m_p_writers.empty())
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("No writer is specified.")
                );
            }
        }

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
            BOOST_THROW_EXCEPTION(std::logic_error("No extention."));
        }

        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        {
            typedef
                typename std::vector<
                    std::unique_ptr<base_type>
                >::const_iterator
                iterator_type;

            const iterator_type found =
                std::find_if(
                    m_p_writers.begin(),
                    m_p_writers.end(),
                    TETENGO2_CPP11_BIND(
                        &writer_set::call_adopts,
                        this,
                        tetengo2::cpp11::placeholders_1()
                    )
                );
            if (found == m_p_writers.end())
            {
                assert(!m_p_writers.empty());
                m_p_writers.front()->write(timetable, output_stream);
                return;
            }

            (*found)->write(timetable, output_stream);
        }

        bool call_adopts(const std::unique_ptr<base_type>& p_writer)
        const
        {
            return p_writer->adopts(m_extention);
        }


    };


}}}


#endif
