SUBDIRS = src data po

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST =	\
	config.rpath			\
	build-aux/git-version-gen	\
	$(NULL)

dist-hook:
	echo $(VERSION) > $(distdir)/VERSION
