/*! \file
    \brief The definition of tetengo2::gui::virtual_key.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <unordered_map>
#include <utility>

#include <boost/predef.h>

#if BOOST_OS_WINDOWS
#include <tetengo2/detail/windows/virtual_key.h>
#elif BOOST_OS_LINUX
#include <tetengo2/detail/stub/virtual_key.h>
#else
#error Unsupported platform.
#endif

#include <tetengo2/gui/virtual_key.h>


namespace tetengo2::gui {
    const virtual_key* virtual_key::find_by_code(const code_type code)
    {
        const auto found = key_map().find(code);
        return found != key_map().end() ? &found->second : nullptr;
    }

    const virtual_key& virtual_key::backspace()
    {
        const auto p_key = find_by_code(details_type::instance().backspace().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::tab()
    {
        const auto p_key = find_by_code(details_type::instance().tab().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::enter()
    {
        const auto p_key = find_by_code(details_type::instance().enter().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::shift()
    {
        const auto p_key = find_by_code(details_type::instance().shift().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::control()
    {
        const auto p_key = find_by_code(details_type::instance().control().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::meta()
    {
        const auto p_key = find_by_code(details_type::instance().meta().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::escape()
    {
        const auto p_key = find_by_code(details_type::instance().escape().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::space()
    {
        const auto p_key = find_by_code(details_type::instance().space().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::page_up()
    {
        const auto p_key = find_by_code(details_type::instance().page_up().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::page_down()
    {
        const auto p_key = find_by_code(details_type::instance().page_down().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::end()
    {
        const auto p_key = find_by_code(details_type::instance().end().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::home()
    {
        const auto p_key = find_by_code(details_type::instance().home().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::left()
    {
        const auto p_key = find_by_code(details_type::instance().left().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::up()
    {
        const auto p_key = find_by_code(details_type::instance().up().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::right()
    {
        const auto p_key = find_by_code(details_type::instance().right().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::down()
    {
        const auto p_key = find_by_code(details_type::instance().down().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::insert()
    {
        const auto p_key = find_by_code(details_type::instance().insert().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::del()
    {
        const auto p_key = find_by_code(details_type::instance().del().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_0()
    {
        const auto p_key = find_by_code(details_type::instance().char_0().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_1()
    {
        const auto p_key = find_by_code(details_type::instance().char_1().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_2()
    {
        const auto p_key = find_by_code(details_type::instance().char_2().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_3()
    {
        const auto p_key = find_by_code(details_type::instance().char_3().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_4()
    {
        const auto p_key = find_by_code(details_type::instance().char_4().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_5()
    {
        const auto p_key = find_by_code(details_type::instance().char_5().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_6()
    {
        const auto p_key = find_by_code(details_type::instance().char_6().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_7()
    {
        const auto p_key = find_by_code(details_type::instance().char_7().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_8()
    {
        const auto p_key = find_by_code(details_type::instance().char_8().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_9()
    {
        const auto p_key = find_by_code(details_type::instance().char_9().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_a()
    {
        const auto p_key = find_by_code(details_type::instance().char_a().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_b()
    {
        const auto p_key = find_by_code(details_type::instance().char_b().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_c()
    {
        const auto p_key = find_by_code(details_type::instance().char_c().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_d()
    {
        const auto p_key = find_by_code(details_type::instance().char_d().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_e()
    {
        const auto p_key = find_by_code(details_type::instance().char_e().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_f()
    {
        const auto p_key = find_by_code(details_type::instance().char_f().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_g()
    {
        const auto p_key = find_by_code(details_type::instance().char_g().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_h()
    {
        const auto p_key = find_by_code(details_type::instance().char_h().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_i()
    {
        const auto p_key = find_by_code(details_type::instance().char_i().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_j()
    {
        const auto p_key = find_by_code(details_type::instance().char_j().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_k()
    {
        const auto p_key = find_by_code(details_type::instance().char_k().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_l()
    {
        const auto p_key = find_by_code(details_type::instance().char_l().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_m()
    {
        const auto p_key = find_by_code(details_type::instance().char_m().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_n()
    {
        const auto p_key = find_by_code(details_type::instance().char_n().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_o()
    {
        const auto p_key = find_by_code(details_type::instance().char_o().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_p()
    {
        const auto p_key = find_by_code(details_type::instance().char_p().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_q()
    {
        const auto p_key = find_by_code(details_type::instance().char_q().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_r()
    {
        const auto p_key = find_by_code(details_type::instance().char_r().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_s()
    {
        const auto p_key = find_by_code(details_type::instance().char_s().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_t()
    {
        const auto p_key = find_by_code(details_type::instance().char_t().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_u()
    {
        const auto p_key = find_by_code(details_type::instance().char_u().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_v()
    {
        const auto p_key = find_by_code(details_type::instance().char_v().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_w()
    {
        const auto p_key = find_by_code(details_type::instance().char_w().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_x()
    {
        const auto p_key = find_by_code(details_type::instance().char_x().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_y()
    {
        const auto p_key = find_by_code(details_type::instance().char_y().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::char_z()
    {
        const auto p_key = find_by_code(details_type::instance().char_z().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f1()
    {
        const auto p_key = find_by_code(details_type::instance().f1().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f2()
    {
        const auto p_key = find_by_code(details_type::instance().f2().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f3()
    {
        const auto p_key = find_by_code(details_type::instance().f3().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f4()
    {
        const auto p_key = find_by_code(details_type::instance().f4().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f5()
    {
        const auto p_key = find_by_code(details_type::instance().f5().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f6()
    {
        const auto p_key = find_by_code(details_type::instance().f6().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f7()
    {
        const auto p_key = find_by_code(details_type::instance().f7().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f8()
    {
        const auto p_key = find_by_code(details_type::instance().f8().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f9()
    {
        const auto p_key = find_by_code(details_type::instance().f9().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f10()
    {
        const auto p_key = find_by_code(details_type::instance().f10().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f11()
    {
        const auto p_key = find_by_code(details_type::instance().f11().first);
        assert(p_key);
        return *p_key;
    }

    const virtual_key& virtual_key::f12()
    {
        const auto p_key = find_by_code(details_type::instance().f12().first);
        assert(p_key);
        return *p_key;
    }

    bool operator==(const virtual_key& one, const virtual_key& another)
    {
        return one.m_code == another.m_code;
    }

    virtual_key::code_type virtual_key::code() const
    {
        return m_code;
    }

    const virtual_key::string_type& virtual_key::to_string() const
    {
        return m_string;
    }

    const virtual_key::key_map_type& virtual_key::key_map()
    {
        static const auto key_map = build_key_map();
        return key_map;
    }

    virtual_key::key_map_type virtual_key::build_key_map()
    {
        key_map_type key_map{};

        insert_key(key_map, details_type::instance().backspace());
        insert_key(key_map, details_type::instance().tab());
        insert_key(key_map, details_type::instance().enter());
        insert_key(key_map, details_type::instance().shift());
        insert_key(key_map, details_type::instance().control());
        insert_key(key_map, details_type::instance().meta());
        insert_key(key_map, details_type::instance().escape());
        insert_key(key_map, details_type::instance().space());
        insert_key(key_map, details_type::instance().page_up());
        insert_key(key_map, details_type::instance().page_down());
        insert_key(key_map, details_type::instance().end());
        insert_key(key_map, details_type::instance().home());
        insert_key(key_map, details_type::instance().left());
        insert_key(key_map, details_type::instance().up());
        insert_key(key_map, details_type::instance().right());
        insert_key(key_map, details_type::instance().down());
        insert_key(key_map, details_type::instance().insert());
        insert_key(key_map, details_type::instance().del());
        insert_key(key_map, details_type::instance().char_0());
        insert_key(key_map, details_type::instance().char_1());
        insert_key(key_map, details_type::instance().char_2());
        insert_key(key_map, details_type::instance().char_3());
        insert_key(key_map, details_type::instance().char_4());
        insert_key(key_map, details_type::instance().char_5());
        insert_key(key_map, details_type::instance().char_6());
        insert_key(key_map, details_type::instance().char_7());
        insert_key(key_map, details_type::instance().char_8());
        insert_key(key_map, details_type::instance().char_9());
        insert_key(key_map, details_type::instance().char_a());
        insert_key(key_map, details_type::instance().char_b());
        insert_key(key_map, details_type::instance().char_c());
        insert_key(key_map, details_type::instance().char_d());
        insert_key(key_map, details_type::instance().char_e());
        insert_key(key_map, details_type::instance().char_f());
        insert_key(key_map, details_type::instance().char_g());
        insert_key(key_map, details_type::instance().char_h());
        insert_key(key_map, details_type::instance().char_i());
        insert_key(key_map, details_type::instance().char_j());
        insert_key(key_map, details_type::instance().char_k());
        insert_key(key_map, details_type::instance().char_l());
        insert_key(key_map, details_type::instance().char_m());
        insert_key(key_map, details_type::instance().char_n());
        insert_key(key_map, details_type::instance().char_o());
        insert_key(key_map, details_type::instance().char_p());
        insert_key(key_map, details_type::instance().char_q());
        insert_key(key_map, details_type::instance().char_r());
        insert_key(key_map, details_type::instance().char_s());
        insert_key(key_map, details_type::instance().char_t());
        insert_key(key_map, details_type::instance().char_u());
        insert_key(key_map, details_type::instance().char_v());
        insert_key(key_map, details_type::instance().char_w());
        insert_key(key_map, details_type::instance().char_x());
        insert_key(key_map, details_type::instance().char_y());
        insert_key(key_map, details_type::instance().char_z());
        insert_key(key_map, details_type::instance().f1());
        insert_key(key_map, details_type::instance().f2());
        insert_key(key_map, details_type::instance().f3());
        insert_key(key_map, details_type::instance().f4());
        insert_key(key_map, details_type::instance().f5());
        insert_key(key_map, details_type::instance().f6());
        insert_key(key_map, details_type::instance().f7());
        insert_key(key_map, details_type::instance().f8());
        insert_key(key_map, details_type::instance().f9());
        insert_key(key_map, details_type::instance().f10());
        insert_key(key_map, details_type::instance().f11());
        insert_key(key_map, details_type::instance().f12());

        return key_map;
    }

    void virtual_key::insert_key(key_map_type& key_map, code_and_string_type code_and_string)
    {
        const auto code = code_and_string.first;
        key_map.insert(std::make_pair(code, virtual_key{ std::move(code_and_string) }));
    }

    virtual_key::virtual_key(code_and_string_type code_and_string)
    : m_code{ code_and_string.first }, m_string{ std::move(code_and_string.second) }
    {}
}