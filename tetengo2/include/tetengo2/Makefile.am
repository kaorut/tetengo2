# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

pkg_headers = \
    concurrent/channel.h \
    concurrent/consumer.h \
    concurrent/producer.h \
    concurrent/progressive_future.h \
    concurrent/progressive_promise.h \
    config/cached_config.h \
    config/config_base.h \
    config/config_list.h \
    config/persistent_config.h \
    config/temporary_config.h \
    iterator/observable_forward_iterator.h \
    iterator/polymorphic_forward_iterator.h \
    message/messages.h \
    message/message_catalog.h \
    message/message_catalog_parser.h \
    stdalt.h \
    text.h \
    text/character_iterator.h \
    text/encoder.h \
    text/encoding/encoding.h \
    text/encoding/ascii.h \
    text/encoding/cp932.h \
    text/encoding/locale.h \
    text/encoding/polymorphic.h \
    text/encoding/utf8.h \
    text/grammar/grammar.h \
    text/grammar/json.h \
    text/pull_parser.h \
    text/push_parser.h \
    type_list.h

extra_headers = \
    0namespace.dox \
    concurrent/0namespace.dox \
    config/0namespace.dox \
    iterator/0namespace.dox \
    message/0namespace.dox \
    text/0namespace.dox \
    text/encoding/0namespace.dox \
    text/grammar/0namespace.dox

nobase_pkginclude_HEADERS = $(pkg_headers)
EXTRA_DIST = $(extra_headers)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)
iwyu_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include

lint-iwyu:
	for f in $(pkg_headers); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done

lint-iwyu-extra:
	for f in $(extra_headers); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done
