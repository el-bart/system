# makro for common calls
define run-in-gen
	@echo
	@echo "##### build $(COMPONENT_NAME) in $@"
	# make gen/ dir structure for source files
	GEN_NOW="$(GEN_BASE_DIR)/$@/`basename $(CURDIR)`" && \
		mkdir -p "$$GEN_NOW" && cd "$$GEN_NOW" && \
		mkdir -p $(SOURCE_DIRS)
	# make includes/ dir structure for global includes files
	mkdir -p $(GEN_INCLUDES_DIR)
	cp -p --parent `find . -type f -iname '*.h*' \
		-exec grep -l '^/\* public header \*/$$' {} \; | grep -v '/.svn'` \
		$(GEN_INCLUDES_DIR) \
		2>/dev/null ; true
	mkdir -p "$(GEN_LIBS_DIR)"
	+$(MAKE) $(MFLAGS) -C "$(GEN_BASE_DIR)/$@/`basename $(CURDIR)`" \
		-f "$(CURDIR)/Makefile" TARGET=$@ $(TARGET) \
		STRIP_BINARY=$(STRIP_BINARY) \
		DEP_LIBS_WC="$(DEP_LIBS_WC)"
endef

# inside lib/app we can include any header (not only public ones)
CXXFLAGS+=-I$(CURDIR)
CFLAGS  +=-I$(CURDIR)

# external variables passed by upper make

# this should NEVER happen!
.PHONY: all
all:
	@echo
	@echo 'error - no correct PROFILE has been specified'
	@echo 'choose one of following:'
	@echo -e "\tdebug, release, profile, test"
	@echo
	@exit 1

# compiler flags
PRF_FLAGS:=-pg -DNDEBUG -g3 -O3
DBG_FLAGS:=-g3
OPT_FLAGS:=-O3 -DNDEBUG -Werror

# linker flags
PRF_LDFLAGS:=-pg
DBG_LDFLAGS:=
OPT_LDFLAGS:=


.PHONY: debug
debug: CXXFLAGS+=$(DBG_FLAGS)
debug: CFLAGS  +=$(DBG_FLAGS)
debug: LDFLAGS +=$(DBG_LDFLAGS)
debug: TARGET=all
debug:
	$(run-in-gen)

.PHONY: release
release: CXXFLAGS+=$(OPT_FLAGS)
release: CFLAGS  +=$(OPT_FLAGS)
release: LDFLAGS +=$(OPT_LDFLAGS)
release: TARGET=all
release: STRIP_BINARY=1
release:
	$(run-in-gen)

.PHONY: profile
profile: CXXFLAGS+=$(PRF_FLAGS)
profile: CFLAGS  +=$(PRF_FLAGS)
profile: LDFLAGS +=$(PRF_LDFLAGS)
profile: TARGET=all
profile:
	$(run-in-gen)

.PHONY: test
test: debug
test: CXXFLAGS+=$(DBG_FLAGS)
test: CFLAGS  +=$(DBG_FLAGS)
test: LDFLAGS +=$(DBG_LDFLAGS)
test: TARGET=test
test:
	$(run-in-gen)

.PHONY: mtest
mtest: debug
mtest: CXXFLAGS+=$(DBG_FLAGS)
mtest: CFLAGS  +=$(DBG_FLAGS)
mtest: LDFLAGS +=$(DBG_LDFLAGS)
mtest: TARGET=mtest
mtest:
	$(run-in-gen)

.PHONY: doc
doc: TARGET=doc
doc:
	$(run-in-gen)

.PHONY: clean
clean:
	@echo
	@echo "##### clean"
	rm -rvf "$(GENDIR)"

