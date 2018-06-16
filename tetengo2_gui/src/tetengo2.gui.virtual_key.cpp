/*! \file
    \brief The definition of tetengo2::gui::virtual_key.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/virtual_key.h>
#include <tetengo2/gui/virtual_key.h>


namespace tetengo2::gui {
    class virtual_key::impl
    {
    public:
        // types

        using code_type = virtual_key::code_type;

        using string_type = virtual_key::string_type;

        using code_and_string_type = virtual_key::code_and_string_type;


        // constructors and destructor

        explicit impl(code_and_string_type code_and_string)
        : m_code{ code_and_string.first }, m_string{ std::move(code_and_string.second) }
        {}

        impl(const impl& another) : m_code{ another.m_code }, m_string{ another.m_string } {}

        impl(impl&& another) : m_code{ another.m_code }, m_string{ std::move(another.m_string) } {}


        // static functions

        static const virtual_key* find_by_code(const code_type code)
        {
            const auto found = key_map().find(code);
            return found != key_map().end() ? &found->second : nullptr;
        }

        static const virtual_key& backspace()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().backspace().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& tab()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().tab().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& enter()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().enter().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& shift()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().shift().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& control()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().control().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& meta()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().meta().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& escape()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().escape().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& space()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().space().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& page_up()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().page_up().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& page_down()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().page_down().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& end()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().end().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& home()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().home().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& left()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().left().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& up()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().up().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& right()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().right().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& down()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().down().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& insert()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().insert().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& del()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().del().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_0()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_0().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_1()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_1().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_2()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_2().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_3()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_3().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_4()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_4().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_5()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_5().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_6()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_6().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_7()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_7().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_8()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_8().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_9()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_9().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_a()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_a().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_b()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_b().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_c()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_c().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_d()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_d().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_e()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_e().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_f()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_f().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_g()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_g().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_h()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_h().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_i()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_i().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_j()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_j().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_k()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_k().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_l()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_l().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_m()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_m().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_n()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_n().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_o()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_o().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_p()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_p().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_q()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_q().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_r()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_r().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_s()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_s().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_t()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_t().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_u()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_u().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_v()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_v().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_w()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_w().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_x()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_x().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_y()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_y().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& char_z()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().char_z().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f1()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f1().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f2()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f2().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f3()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f3().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f4()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f4().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f5()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f5().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f6()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f6().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f7()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f7().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f8()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f8().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f9()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f9().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f10()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f10().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f11()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f11().first);
            assert(p_key);
            return *p_key;
        }

        static const virtual_key& f12()
        {
            const auto p_key = find_by_code(detail::gui_detail_impl_set().virtual_key_().f12().first);
            assert(p_key);
            return *p_key;
        }

        /*!
            \brief Returns the string representation of the combined keys.

            \param keys The bombined keys.

            \return The whole string representation of the combined keys.
        */
        static string_type to_combined_string(const std::vector<virtual_key>& keys)
        {
            std::vector<string_type> key_strings{};
            key_strings.reserve(keys.size());
            std::transform(keys.begin(), keys.end(), std::back_inserter(key_strings), [](const virtual_key& key) {
                return key.to_string();
            });
            return detail::gui_detail_impl_set().virtual_key_().to_combined_string(key_strings);
        }


        // functions

        bool equal_to(const impl& another) const
        {
            return m_code == another.m_code;
        }

        code_type code() const
        {
            return m_code;
        }

        const string_type& to_string() const
        {
            return m_string;
        }


    private:
        // types

        using key_map_type = std::unordered_map<code_type, virtual_key>;


        // static functions


        static const key_map_type& key_map()
        {
            static const auto key_map = build_key_map();
            return key_map;
        }

        static key_map_type build_key_map()
        {
            const auto& details = detail::gui_detail_impl_set().virtual_key_();

            key_map_type key_map{};

            insert_key(key_map, details.backspace());
            insert_key(key_map, details.tab());
            insert_key(key_map, details.enter());
            insert_key(key_map, details.shift());
            insert_key(key_map, details.control());
            insert_key(key_map, details.meta());
            insert_key(key_map, details.escape());
            insert_key(key_map, details.space());
            insert_key(key_map, details.page_up());
            insert_key(key_map, details.page_down());
            insert_key(key_map, details.end());
            insert_key(key_map, details.home());
            insert_key(key_map, details.left());
            insert_key(key_map, details.up());
            insert_key(key_map, details.right());
            insert_key(key_map, details.down());
            insert_key(key_map, details.insert());
            insert_key(key_map, details.del());
            insert_key(key_map, details.char_0());
            insert_key(key_map, details.char_1());
            insert_key(key_map, details.char_2());
            insert_key(key_map, details.char_3());
            insert_key(key_map, details.char_4());
            insert_key(key_map, details.char_5());
            insert_key(key_map, details.char_6());
            insert_key(key_map, details.char_7());
            insert_key(key_map, details.char_8());
            insert_key(key_map, details.char_9());
            insert_key(key_map, details.char_a());
            insert_key(key_map, details.char_b());
            insert_key(key_map, details.char_c());
            insert_key(key_map, details.char_d());
            insert_key(key_map, details.char_e());
            insert_key(key_map, details.char_f());
            insert_key(key_map, details.char_g());
            insert_key(key_map, details.char_h());
            insert_key(key_map, details.char_i());
            insert_key(key_map, details.char_j());
            insert_key(key_map, details.char_k());
            insert_key(key_map, details.char_l());
            insert_key(key_map, details.char_m());
            insert_key(key_map, details.char_n());
            insert_key(key_map, details.char_o());
            insert_key(key_map, details.char_p());
            insert_key(key_map, details.char_q());
            insert_key(key_map, details.char_r());
            insert_key(key_map, details.char_s());
            insert_key(key_map, details.char_t());
            insert_key(key_map, details.char_u());
            insert_key(key_map, details.char_v());
            insert_key(key_map, details.char_w());
            insert_key(key_map, details.char_x());
            insert_key(key_map, details.char_y());
            insert_key(key_map, details.char_z());
            insert_key(key_map, details.f1());
            insert_key(key_map, details.f2());
            insert_key(key_map, details.f3());
            insert_key(key_map, details.f4());
            insert_key(key_map, details.f5());
            insert_key(key_map, details.f6());
            insert_key(key_map, details.f7());
            insert_key(key_map, details.f8());
            insert_key(key_map, details.f9());
            insert_key(key_map, details.f10());
            insert_key(key_map, details.f11());
            insert_key(key_map, details.f12());

            return key_map;
        }

        static void insert_key(key_map_type& key_map, code_and_string_type code_and_string)
        {
            const auto code = code_and_string.first;
            key_map.insert(std::make_pair(code, virtual_key{ std::move(code_and_string) }));
        }


        // variables

        code_type m_code;

        string_type m_string;
    };


    virtual_key::virtual_key(const virtual_key& another) : m_p_impl{ std::make_unique<impl>(*another.m_p_impl) } {}

    virtual_key::virtual_key(virtual_key&& another) : m_p_impl{ std::move(another.m_p_impl) } {}

    virtual_key::~virtual_key() = default;

    const virtual_key* virtual_key::find_by_code(const code_type code)
    {
        return impl::find_by_code(code);
    }

    const virtual_key& virtual_key::backspace()
    {
        return impl::backspace();
    }

    const virtual_key& virtual_key::tab()
    {
        return impl::tab();
    }

    const virtual_key& virtual_key::enter()
    {
        return impl::enter();
    }

    const virtual_key& virtual_key::shift()
    {
        return impl::shift();
    }

    const virtual_key& virtual_key::control()
    {
        return impl::control();
    }

    const virtual_key& virtual_key::meta()
    {
        return impl::meta();
    }

    const virtual_key& virtual_key::escape()
    {
        return impl::escape();
    }

    const virtual_key& virtual_key::space()
    {
        return impl::space();
    }

    const virtual_key& virtual_key::page_up()
    {
        return impl::page_up();
    }

    const virtual_key& virtual_key::page_down()
    {
        return impl::page_down();
    }

    const virtual_key& virtual_key::end()
    {
        return impl::end();
    }

    const virtual_key& virtual_key::home()
    {
        return impl::home();
    }

    const virtual_key& virtual_key::left()
    {
        return impl::left();
    }

    const virtual_key& virtual_key::up()
    {
        return impl::up();
    }

    const virtual_key& virtual_key::right()
    {
        return impl::right();
    }

    const virtual_key& virtual_key::down()
    {
        return impl::down();
    }

    const virtual_key& virtual_key::insert()
    {
        return impl::insert();
    }

    const virtual_key& virtual_key::del()
    {
        return impl::del();
    }

    const virtual_key& virtual_key::char_0()
    {
        return impl::char_0();
    }

    const virtual_key& virtual_key::char_1()
    {
        return impl::char_1();
    }

    const virtual_key& virtual_key::char_2()
    {
        return impl::char_2();
    }

    const virtual_key& virtual_key::char_3()
    {
        return impl::char_3();
    }

    const virtual_key& virtual_key::char_4()
    {
        return impl::char_4();
    }

    const virtual_key& virtual_key::char_5()
    {
        return impl::char_5();
    }

    const virtual_key& virtual_key::char_6()
    {
        return impl::char_6();
    }

    const virtual_key& virtual_key::char_7()
    {
        return impl::char_7();
    }

    const virtual_key& virtual_key::char_8()
    {
        return impl::char_8();
    }

    const virtual_key& virtual_key::char_9()
    {
        return impl::char_9();
    }

    const virtual_key& virtual_key::char_a()
    {
        return impl::char_a();
    }

    const virtual_key& virtual_key::char_b()
    {
        return impl::char_b();
    }

    const virtual_key& virtual_key::char_c()
    {
        return impl::char_c();
    }

    const virtual_key& virtual_key::char_d()
    {
        return impl::char_d();
    }

    const virtual_key& virtual_key::char_e()
    {
        return impl::char_e();
    }

    const virtual_key& virtual_key::char_f()
    {
        return impl::char_f();
    }

    const virtual_key& virtual_key::char_g()
    {
        return impl::char_g();
    }

    const virtual_key& virtual_key::char_h()
    {
        return impl::char_h();
    }

    const virtual_key& virtual_key::char_i()
    {
        return impl::char_i();
    }

    const virtual_key& virtual_key::char_j()
    {
        return impl::char_j();
    }

    const virtual_key& virtual_key::char_k()
    {
        return impl::char_k();
    }

    const virtual_key& virtual_key::char_l()
    {
        return impl::char_l();
    }

    const virtual_key& virtual_key::char_m()
    {
        return impl::char_m();
    }

    const virtual_key& virtual_key::char_n()
    {
        return impl::char_n();
    }

    const virtual_key& virtual_key::char_o()
    {
        return impl::char_o();
    }

    const virtual_key& virtual_key::char_p()
    {
        return impl::char_p();
    }

    const virtual_key& virtual_key::char_q()
    {
        return impl::char_q();
    }

    const virtual_key& virtual_key::char_r()
    {
        return impl::char_r();
    }

    const virtual_key& virtual_key::char_s()
    {
        return impl::char_s();
    }

    const virtual_key& virtual_key::char_t()
    {
        return impl::char_t();
    }

    const virtual_key& virtual_key::char_u()
    {
        return impl::char_u();
    }

    const virtual_key& virtual_key::char_v()
    {
        return impl::char_v();
    }

    const virtual_key& virtual_key::char_w()
    {
        return impl::char_w();
    }

    const virtual_key& virtual_key::char_x()
    {
        return impl::char_x();
    }

    const virtual_key& virtual_key::char_y()
    {
        return impl::char_y();
    }

    const virtual_key& virtual_key::char_z()
    {
        return impl::char_z();
    }

    const virtual_key& virtual_key::f1()
    {
        return impl::f1();
    }

    const virtual_key& virtual_key::f2()
    {
        return impl::f2();
    }

    const virtual_key& virtual_key::f3()
    {
        return impl::f3();
    }

    const virtual_key& virtual_key::f4()
    {
        return impl::f4();
    }

    const virtual_key& virtual_key::f5()
    {
        return impl::f5();
    }

    const virtual_key& virtual_key::f6()
    {
        return impl::f6();
    }

    const virtual_key& virtual_key::f7()
    {
        return impl::f7();
    }

    const virtual_key& virtual_key::f8()
    {
        return impl::f8();
    }

    const virtual_key& virtual_key::f9()
    {
        return impl::f9();
    }

    const virtual_key& virtual_key::f10()
    {
        return impl::f10();
    }

    const virtual_key& virtual_key::f11()
    {
        return impl::f11();
    }

    const virtual_key& virtual_key::f12()
    {
        return impl::f12();
    }

    virtual_key::string_type virtual_key::to_combined_string(const std::vector<virtual_key>& keys)
    {
        return impl::to_combined_string(keys);
    }

    bool operator==(const virtual_key& one, const virtual_key& another)
    {
        return one.m_p_impl->equal_to(*another.m_p_impl);
    }

    virtual_key::code_type virtual_key::code() const
    {
        return m_p_impl->code();
    }

    const virtual_key::string_type& virtual_key::to_string() const
    {
        return m_p_impl->to_string();
    }

    virtual_key::virtual_key(code_and_string_type code_and_string)
    : m_p_impl{ std::make_unique<impl>(std::move(code_and_string)) }
    {}
}