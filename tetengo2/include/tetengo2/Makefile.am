# Automake Settings
# Copyright (C) 2007-2019 kaoru
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

pkg_headers_with_stdalt_h = \
    $(pkg_headers) \
    stdalt.h

extra_headers = \
    0namespace.dox \
    concurrent/0namespace.dox \
    config/0namespace.dox \
    iterator/0namespace.dox \
    message/0namespace.dox \
    text/0namespace.dox \
    text/encoding/0namespace.dox \
    text/grammar/0namespace.dox

nobase_pkginclude_HEADERS = $(pkg_headers_with_stdalt_h)
EXTRA_DIST = $(extra_headers)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)
iwyu_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include

lint-iwyu: $(addsuffix .iwyuout, $(pkg_headers))

lint-iwyu-extra: $(addsuffix .iwyuout, $(extra_headers))

%.iwyuout: %
	mkdir -p $(dir $@)
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
	mv $(addsuffix .tmp, $@) $@

format:
	$(top_srcdir)/tools/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(pkg_headers_with_stdalt_h) $(extra_headers)

clean-local:
	-find -name "*.iwyuout.tmp" | xargs rm -f
	-find -name "*.iwyuout" | xargs rm -f
