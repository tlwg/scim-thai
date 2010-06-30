AM_CPPFLAGS = \
	-DSCIM_THAI_LOCALEDIR=\"$(datadir)/locale\" \
	-DSCIM_ICONDIR=\"$(SCIM_ICONDIR)\"

noinst_HEADERS = \
	gettext.h \
	intl.h \
	scim_thai_keymap.h \
	scim_thai_imengine_factory.h \
	scim_thai_imengine.h \
	scim_thai_imengine_config.h

moduledir = $(SCIM_MODULEDIR)/IMEngine
module_LTLIBRARIES = thai.la

thai_la_SOURCES = \
	scim_thai_keymap.cpp \
	scim_thai_imengine_factory.cpp \
	scim_thai_imengine.cpp

thai_la_CFLAGS = $(SCIM_CFLAGS) $(SCIM_DEBUG_FLAGS) $(LIBTHAI_CFLAGS)
thai_la_CXXFLAGS = $(SCIM_CFLAGS) $(SCIM_DEBUG_FLAGS) $(LIBTHAI_CFLAGS)

thai_la_LDFLAGS = \
	-avoid-version \
	-rpath $(moduledir) \
	-module \
	$(LIBTOOL_EXPORT_OPTIONS) \
	$(SCIM_LIBS) \
	$(LIBTHAI_LIBS)

if SCIM_BUILD_SETUP
setupmoduledir = $(SCIM_MODULEDIR)/SetupUI
setupmodule_LTLIBRARIES = thai-imengine-setup.la

thai_imengine_setup_la_SOURCES = scim_thai_imengine_setup.cpp

thai_imengine_setup_la_CFLAGS = \
	$(SCIM_GTKUTILS_CFLAGS) $(SCIM_CFLAGS) $(LIBTHAI_CFLAGS)
thai_imengine_setup_la_CXXFLAGS = \
	$(SCIM_GTKUTILS_CFLAGS) $(SCIM_CFLAGS) $(LIBTHAI_CFLAGS)

thai_imengine_setup_la_LDFLAGS = \
	-avoid-version \
	-rpath $(moduledir) \
	-module \
	$(LIBTOOL_EXPORT_OPTIONS) \
	$(SCIM_GTKUTILS_LIBS) \
	$(SCIM_LIBS)
endif
