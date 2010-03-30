/*! \file
    \brief The definition of stub_tetengo2::gui::menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENU_H)
#define STUBTETENGO2_GUI_MENU_H

//#include <cassert>
//#include <cstddef>
#include <memory>
#include <stdexcept>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "concept_tetengo2.Encoder.h"
#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuObserver.h"
#include "tetengo2.gui.recursive_menu_iterator.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Id,
        typename Handle,
        typename String,
        typename Encoder,
        typename MenuObserver
    >
    class menu : boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Id>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::Encoder<Encoder>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuObserver<MenuObserver>
        ));


    public:
        // types

        typedef Id id_type;

        typedef Handle handle_type;

        typedef String string_type;

        typedef Encoder encoder_type;

        typedef MenuObserver menu_observer_type;

        typedef typename boost::ptr_vector<menu>::iterator iterator;

        typedef
            typename boost::ptr_vector<menu>::const_iterator const_iterator;

        typedef
            tetengo2::gui::recursive_menu_iterator<menu> recursive_iterator;

        typedef
            tetengo2::gui::recursive_menu_iterator<const menu>
            const_recursive_iterator;


        // constructors and destructor

        virtual ~menu()
        throw ()
        {}


        // functions

        id_type id()
        const
        {
            return 0;
        }

        virtual handle_type handle()
        const
        {
            return NULL;
        }

        const string_type& text()
        const
        {
            return m_text;
        }

        void select()
        {}

        void add_menu_observer(
            std::auto_ptr<menu_observer_type> p_menu_observer
        )
        {}

        virtual const_iterator begin()
        const
        {
            return const_iterator();
        }

        virtual iterator begin()
        {
            return iterator();
        }

        virtual const_iterator end()
        const
        {
            return const_iterator();
        }

        virtual iterator end()
        {
            return iterator();
        }

        virtual const_recursive_iterator recursive_begin()
        const
        {
            return const_recursive_iterator();
        }

        virtual recursive_iterator recursive_begin()
        {
            return recursive_iterator();
        }

        virtual const_recursive_iterator recursive_end()
        const
        {
            return const_recursive_iterator();
        }

        virtual recursive_iterator recursive_end()
        {
            return recursive_iterator();
        }

        virtual void insert(const iterator offset, std::auto_ptr<menu> p_menu)
        {
            assert(false);
            BOOST_THROW_EXCEPTION(
                std::logic_error("Can't insert any menus.")
            );
        }

        virtual void erase(const iterator first, const iterator last)
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Can't erase any menus."));
        }


    protected:
        // constructors

        menu(const string_type& text, const encoder_type& encoder)
        :
        m_text(text),
        m_encoder(encoder)
        {}


        // functions

        const encoder_type& encoder()
        const
        {
            return m_encoder;
        }


    private:
        // variables

        const string_type m_text;

        const encoder_type& m_encoder;


    };


}}

#endif
