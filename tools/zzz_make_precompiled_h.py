#!/usr/bin/python3
# Makes precompiled.h.
# Copyright (C) 2007-2018 kaoru
# $Id$

import re
import sys


def main(args):
    if len(args) < 3:
        sys.stderr.write("Usage: ./zzz_make_precompiled_h.py zzz_include_list.txt precompiled.template.h\n")
        exit(1)

    stdlib_headers, boost_headers = load_include_list(args[1])

    make_precompiled_h(args[2], stdlib_headers, boost_headers)


def load_include_list(path):
    stdlib_headers = []
    boost_headers = []

    stdlib_pattern = re.compile("^#\s*include\s+<(?P<name>[^>\.]+)>")
    boost_pattern = re.compile("^#\s*include\s+<(?P<name>boost/[^>]+)>")

    file = open(path, "r")
    for line in file:
        line = line.strip()

        stdlib_match = stdlib_pattern.match(line)
        if stdlib_match and stdlib_match.group("name"):
            stdlib_headers.append(stdlib_match.group("name"))

        boost_match = boost_pattern.match(line)
        if \
            boost_match and \
            boost_match.group("name") and \
            boost_match.group("name") != "boost/test/unit_test.hpp":
            boost_headers.append(boost_match.group("name"))

    return stdlib_headers, boost_headers


def make_precompiled_h(template_path, stdlib_headers, boost_headers):
    file = open(template_path, "r")
    for line in file:
        line = line.rstrip()

        if line == "////STDLIB_BOOST_INCLUDES////":
            print("// The standard library headers")
            print("")
            for h in stdlib_headers:
                print("#include <{}>".format(h))
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
