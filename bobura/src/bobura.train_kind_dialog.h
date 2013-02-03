/*! \file
    \brief The definition of bobura::train_kind_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_TRAINKINDDIALOG_H)
#define BOBURA_TRAINKINDDIALOG_H

#include <memory>
#include <utility>
#include <vector>

#include <boost/optional.hpp>

#include <tetengo2.cpp11.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the train kind dialog.

        \tparam Dialog         A dialog type.
        \tparam MessageCatalog A message catalog type.
        \tparam IntSize        An integer size type.
        \tparam TrainKind      A train kind type.
    */
    template <typename Dialog, typename MessageCatalog, typename IntSize, typename TrainKind>
    class train_kind_dialog : public Dialog
    {
    public:
        // types

        //! The base type.
        typedef Dialog base_type;

        //! The abstract window type.
        typedef typename base_type::base_type abstract_window_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The integer size type.
        typedef IntSize int_size_type;

        //! The train kind type.
        typedef TrainKind train_kind_type;

        //! The information set type.
        class info_set_type
        {
        public:

            /*!
                \brief Creates an information set.

                \param original_index An original index.
                \param referred       A referred status.
                \param train_kind     A train kind.
            */
            info_set_type(
                boost::optional<int_size_type> original_index,
                const bool                     referred,
                train_kind_type                train_kind
            )
            :
            m_original_index(std::move(original_index)),
            m_referred(referred),
            m_train_kind(std::move(train_kind))
            {}


            /*!
                \brief Returns the original index.

                \return The original index.
            */
            const boost::optional<int_size_type>& original_index()
            const
            {
                return m_original_index;
            }

            /*!
                \brief Returns the referred status.

                \return The referred status.
            */
            bool referred()
            const
            {
                return m_referred;
            }

            /*!
                \brief Returns the train kind.

                \return The train kind.
            */
            const train_kind_type& train_kind()
            const
            {
                return m_train_kind;
            }

            /*!
                \brief Returns the train kind.

                \return The train kind.
            */
            train_kind_type& train_kind()
            {
                return m_train_kind;
            }

        private:
            boost::optional<int_size_type> m_original_index;

            bool m_referred;

            train_kind_type m_train_kind;

        };


        // constructors and destructor

        /*!
            \brief Creates a train kind dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        train_kind_dialog(abstract_window_type& parent, const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the train kind dialog.
        */
        virtual ~train_kind_dialog()
        TETENGO2_CPP11_NOEXCEPT;


        // functions

        /*!
            \brief Returns the information sets.

            \return The information sets.
        */
        const std::vector<info_set_type> info_sets()
        const;

        /*!
            \brief Sets information sets.

            \param info_sets Information sets.
        */
        void set_info_sets(std::vector<info_set_type> info_sets);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void do_modal_impl();


    };


}

#endif
