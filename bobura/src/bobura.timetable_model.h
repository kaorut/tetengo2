/*! \file
    \brief The definition of bobura::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_TIMETABLEMODEL_H)
#define BOBURA_TIMETABLEMODEL_H

#include <cassert>
#include <cstddef>
//#include <memory>
#include <stdexcept>
//#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.unique.h>


namespace bobura
{
   /*!
        \brief The class template for a model.

        \tparam Timetable       A timetable type.
        \tparam Path            A path type.
        \tparam ObserverSet     A observer set type.
    */
    template <typename Timetable, typename Path, typename ObserverSet>
    class timetable_model : private boost::noncopyable
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path type.
        typedef Path path_type;

        //! The observer set type.
        typedef ObserverSet observer_set_type;


        // constructors and destructor

        /*!
            \brief Creates a model.
        */
        timetable_model()
        :
        m_p_timetable(tetengo2::make_unique<timetable_type>()),
        m_path(),
        m_changed(false),
        m_observer_set()
        {
            set_timetable_observer_set();
        }


        // functions

        /*!
            \brief Returns the timetable.

            \return The timetable.
        */
        const timetable_type& timetable()
        const
        {
            assert(m_p_timetable);
            return *m_p_timetable;
        }

        /*!
            \brief Returns the timetable.

            \return The timetable.
        */
        timetable_type& timetable()
        {
            assert(m_p_timetable);
            return *m_p_timetable;
        }

        /*!
            \brief Resets an empty timetable.
        */
        void reset_timetable()
        {
            reset_timetable_impl(tetengo2::make_unique<timetable_type>(), boost::optional<path_type>());
        }

        /*!
            \brief Resets a timetable.

            \param p_timetable A unique pointer to a timetable.

            \throw std::invalid_argument When p_timetable is NULL.
        */
        void reset_timetable(std::unique_ptr<timetable_type> p_timetable)
        {
            reset_timetable_impl(std::move(p_timetable), boost::optional<path_type>());
        }

        /*!
            \brief Resets a timetable.

            \tparam P A path type.

            \param p_timetable A unique pointer to a timetable.
            \param path        A path.

            \throw std::invalid_argument When p_timetable is NULL.
        */
        template <typename P>
        void reset_timetable(std::unique_ptr<timetable_type> p_timetable, P&& path)
        {
            reset_timetable_impl(std::move(p_timetable), boost::make_optional<path_type>(std::forward<P>(path)));
        }

        /*!
            \brief Checks whether the model has a path.

            \retval true  When the model has a path.
            \retval false Otherwise.
        */
        bool has_path()
        const
        {
            return static_cast<bool>(m_path);
        }

        /*!
            \brief Returns the path.

            \return The path.

            \throw std::logic_error When the model does not have a path.
        */
        const path_type& path()
        const
        {
            if (!has_path())
                BOOST_THROW_EXCEPTION(std::logic_error("This model does not have a path."));

            return *m_path;
        }

        /*!
            \brief Sets a path.

            \tparam P A path type.

            \param path A path.
        */
        template <typename P>
        void set_path(P&& path)
        {
            m_path = boost::make_optional(std::forward<path_type>(path));
            m_changed = false;

            m_observer_set.reset()();
        }

        /*!
            \brief Checks whether the model is changed.

            \retval true  When the model is changed.
            \retval false Otherwise.
        */
        bool changed()
        const
        {
            return m_changed;
        }

        /*!
            \brief Sets a changed status.

            \param changed A changed status.
        */
        void set_changed(const bool changed)
        {
            m_changed = changed;

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        const observer_set_type& observer_set()
        const
        {
            return m_observer_set;
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        observer_set_type& observer_set()
        {
            return m_observer_set;
        }


    private:
        // types

        typedef typename timetable_type::string_type string_type;

        class timetable_changed
        {
        public:
            timetable_changed(timetable_model& self)
            :
            m_self(self)
            {}

            void operator()()
            {
                m_self.set_changed(true);
            }

        private:
            timetable_model& m_self;

        };


        // variables

        std::unique_ptr<timetable_type> m_p_timetable;

        boost::optional<path_type> m_path;

        bool m_changed;

        observer_set_type m_observer_set;


        // functions

        void reset_timetable_impl(std::unique_ptr<timetable_type> p_timetable, boost::optional<path_type>&& path)
        {
            if (!p_timetable)
                BOOST_THROW_EXCEPTION(std::invalid_argument("Timetable is NULL."));

            m_p_timetable = std::move(p_timetable);
            m_path = std::forward<boost::optional<path_type>>(path);
            m_changed = false;

            set_timetable_observer_set();

            m_observer_set.reset()();
        }

        void set_timetable_observer_set()
        {
            m_p_timetable->observer_set().changed().connect(timetable_changed(*this));
        }


    };


}

#endif
