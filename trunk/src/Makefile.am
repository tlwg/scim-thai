AM_CPPFLAGS = \
	-DSCIM_THAI_LOCALEDIR=\"$(datadir)/locale\" \
	-DSCIM_ICONDIR=\"@SCIM_ICONDIR@\"

noinst_HEADERS = \
	gettext.h \
	intl.h \
	scim_thai_keymap.h \
	scim_thai_imengine_factory.h \
	scim_thai_imengine.h

moduledir = @SCIM_MODULEDIR@/IMEngine
module_LTLIBRARIES = thai.la

thai_la_SOURCES = \
	scim_thai_keymap.cpp \
	scim_thai_imengine_factory.cpp \
	scim_thai_imengine.cpp

thai_la_CFLAGS = @SCIM_CFLAGS@ @SCIM_DEBUG_FLAGS@
thai_la_CXXFLAGS = @SCIM_CFLAGS@ @SCIM_DEBUG_FLAGS@

thai_la_LDFLAGS = \
	-avoid-version \
	-rpath $(moduledir) \
	-module \
	@LIBTOOL_EXPORT_OPTIONS@ \
	@SCIM_LIBS@
