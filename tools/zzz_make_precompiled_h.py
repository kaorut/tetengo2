#!/usr/bin/python3
# Makes precompiled.h.
# Copyright (C) 2007-2019 kaoru
# $Id$

import re
import sys


def main(args):
    if len(args) < 3:
        sys.stderr.write("Usage: ./zzz_make_precompiled_h.py zzz_include_list.txt precompiled.template.h\n")
        exit(1)

    stdlib_headers, special_stdlib_headers, boost_headers = load_include_list(args[1])

    make_precompiled_h(args[2], stdlib_headers, special_stdlib_headers, boost_headers)


def load_include_list(path):
    stdlib_headers = []
    special_stdlib_headers = []
    boost_headers = []

    stdlib_pattern = re.compile("^#\s*include\s+<(?P<name>[^>\.]+)>")
    boost_pattern = re.compile("^#\s*include\s+<(?P<name>boost/[^>]+)>")

    file = open(path, "r")
    for line in file:
        line = line.strip()

        stdlib_match = stdlib_pattern.match(line)
        if stdlib_match and stdlib_match.group("name"):
            if \
                stdlib_match.group('name') != "filesystem" and \
                stdlib_match.group('name') != "experimental/filesystem" and \
                stdlib_match.group('name') != "optional" and \
                stdlib_match.group('name') != "experimental/optional" and \
                stdlib_match.group('name') != "string_view" and \
                stdlib_match.group('name') != "variant":
                stdlib_headers.append(stdlib_match.group("name"))

        boost_match = boost_pattern.match(line)
        if \
            boost_match and \
            boost_match.group("name") and \
            boost_match.group("name") != "boost/test/unit_test.hpp":
            boost_match.group('name') != "boost/utility/string_view.hpp" and \
            boost_match.group('name') != "boost/variant.hpp" and \
            boost_headers.append(boost_match.group("name"))

    special_stdlib_headers.append("filesystem,experimental/filesystem")
    special_stdlib_headers.append("optional,experimental/optional")
    special_stdlib_headers.append("string_view,boost/utility/string_view.hpp")
    special_stdlib_headers.append("variant,boost/variant.hpp")

    return stdlib_headers, special_stdlib_headers, boost_headers


def make_precompiled_h(template_path, stdlib_headers, special_stdlib_headers, boost_headers):
    file = open(template_path, "r")
    for line in file:
        line = line.rstrip()

        if line == "////STDLIB_BOOST_INCLUDES////":
            print("// The standard library headers")
            print("")
            for h in stdlib_headers:
                print("#include <{}>".format(h))
            for h in special_stdlib_headers:
                std_alt = h.split(",")
                print("#if __has_include(<{}>)".format(std_alt[0]))
                print("#   include <{}>".format(std_alt[0]))
                print("#elif __has_include(<{}>)".format(std_alt[1]))
                print("#   include <{}>".format(std_alt[1]))
                print("#endif")
            print("")
            print("")
            print("// The Boost library headers")
            print("")
            for h in boost_headers:
                print("#include <{}>".format(h))
            print("")
        else:
            print(line)


main(sys.argv)
