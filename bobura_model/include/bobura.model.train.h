/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

#include <iterator>
#include <utility>
#include <vector>

#include <boost/operators.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a train.

        \tparam String A string type.
        \tparam Stop   A stop type.
    */
    template <typename String, typename Stop>
    class train : private boost::equality_comparable<train<String, Stop>>
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The stop type.
        typedef Stop stop_type;

        //! The stops type.
        typedef std::vector<stop_type> stops_type;


        // constructors and destructor

        /*!
            \brief Creates a train.

            \tparam S1 A string type #1.
            \tparam S2 A string type #2.
            \tparam S3 A string type #3.
            \tparam S4 A string type #4.

            \param number      A number.
            \param name        A name.
            \param name_number A name number.
            \param note        A note.
        */
        template <typename S1, typename S2, typename S3, typename S4>
        train(S1&& number, S2&& name, S3&& name_number, S4&& note)
        :
        m_number(std::forward<S1>(number)),
        m_name(std::forward<S2>(name)),
        m_name_number(std::forward<S3>(name_number)),
        m_note(std::forward<S4>(note)),
        m_stops()
        {}

        /*!
            \brief Creates a train.

            \tparam InputIterator An input iterator for stops.

            \tparam S1 A string type #1.
            \tparam S2 A string type #2.
            \tparam S3 A string type #3.
            \tparam S4 A string type #4.
            \tparam Ss A stops type.

            \param number      A number.
            \param name        A name.
            \param name_number A name number.
            \param note        A note.
            \param stops       Stops.
        */
        template <typename S1, typename S2, typename S3, typename S4, typename Ss>
        train(S1&& number, S2&& name, S3&& name_number, S4&& note, Ss&& stops)
        :
        m_number(std::forward<S1>(number)),
        m_name(std::forward<S2>(name)),
        m_name_number(std::forward<S3>(name_number)),
        m_note(std::forward<S4>(note)),
        m_stops(std::forward<Ss>(stops))
        {}

        /*!
            \brief Creates a train.

            \tparam InputIterator An input iterator for stops.

            \tparam S1            A string type #1.
            \tparam S2            A string type #2.
            \tparam S3            A string type #3.
            \tparam S4            A string type #4.
            \tparam InputIterator An input iterator type.

            \param number      A number.
            \param name        A name.
            \param name_number A name number.
            \param note        A note.
            \param stop_first  The first iterator among stops.
            \param stop_last   The last iterator among stops.
        */
        template <typename S1, typename S2, typename S3, typename S4, typename InputIterator>
        train(
            S1&& number,
            S2&& name,
            S3&& name_number,
            S4&& note,
            const InputIterator stop_first,
            const InputIterator stop_last
        )
        :
        m_number(std::forward<S1>(number)),
        m_name(std::forward<S2>(name)),
        m_name_number(std::forward<S3>(name_number)),
        m_note(std::forward<S4>(note)),
        m_stops(stop_first, stop_last)
        {}


        // functions

        /*!
            \brief Checks whether one train is equal to another.

            \param one     One train.
            \param another Another train.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const train& one, const train& another)
        {
            return
                one.m_number == another.m_number &&
                one.m_name == another.m_name &&
                one.m_name_number == another.m_name_number &&
                one.m_note == another.m_note &&
                one.m_stops == another.m_stops;
        }

        /*!
            \brief Returns the number.

            \return The number.
        */
        const string_type& number()
        const
        {
            return m_number;
        }

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name()
        const
        {
            return m_name;
        }

        /*!
            \brief Returns the name number.

            \return The name number.
        */
        const string_type& name_number()
        const
        {
            return m_name_number;
        }

        /*!
            \brief Returns the note.

            \return The note.
        */
        const string_type& note()
        const
        {
            return m_note;
        }

        /*!
            \brief Returns the stops.

            \return The stops.
        */
        const stops_type& stops()
        const
        {
            return m_stops;
        }

        /*!
            \brief Inserts a stop.

            \tparam S A stop type.

            \param position A position where a stop is inserted.
            \param stop     A stop.
        */
        template <typename S>
        void insert_stop(const typename stops_type::const_iterator position, S&& stop)
        {
            m_stops.insert(to_mutable(position, m_stops), std::forward<S>(stop));
        }

        /*!
            \brief Erases the stops.

            \param first A first iterator among the erased stops.
            \param last  A last iterator among the erased stops.
        */
        void erase_stops(
            const typename stops_type::const_iterator first,
            const typename stops_type::const_iterator last
        )
        {
            m_stops.erase(to_mutable(first, m_stops), to_mutable(last, m_stops));
        }


    private:
        // variables

        string_type m_number;

        string_type m_name;

        string_type m_name_number;

        string_type m_note;

        stops_type m_stops;


        // functions

        template <typename Container>
        typename Container::iterator to_mutable(
            const typename Container::const_iterator const_iter,
            Container&                               container
        )
        {
            typename Container::iterator mutable_iter = container.begin();
            std::advance(
                mutable_iter, std::distance<typename Container::const_iterator>(container.begin(), const_iter)
            );
            return mutable_iter;
        }


    };


}}


#endif
