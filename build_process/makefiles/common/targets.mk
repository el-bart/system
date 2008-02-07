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
		STRIP_BINARY=$(STRIP_BINARY) || \
		{ echo "ERROR: maby component name is incorrect?" >&2 ; false ; }
endef

# inside lib/app we can include any header (not only public ones)
CXXFLAGS+=-I$(CURDIR)
CFLAGS+=-I$(CURDIR)


# this should NEVER happen!
.PHONY: all
all:
	@echo
	@echo 'error - no correct PROFILE has been specified'
	@echo 'choose one of following:'
	@echo -e "\tdebug, release, profile, test"
	@echo
	@exit 1

.PHONY: debug
debug: CXXFLAGS+=-g3 -DDEBUG -pg
debug: CFLAGS+=-g3 -DDEBUG -pg
debug: TARGET=all
debug:
	$(run-in-gen)

.PHONY: release
release: CXXFLAGS+=-O3 -DNDEBUG -Werror
release: CFLAGS+=-O3 -DNDEBUG -Werror
release: TARGET=all
release: STRIP_BINARY=1
release:
	$(run-in-gen)

.PHONY: profile
profile: CXXFLAGS+=-pg -DNDEBUG
profile: CFLAGS+=-pg -DNDEBUG
profile: LDFLAGS+=-pg
profile: TARGET=all
profile:
	$(run-in-gen)

.PHONY: test
test: CXXFLAGS+=-g3 -DDEBUG -pg
test: CFLAGS+=-g3 -DDEBUG -pg
test: TARGET=test
test:
	$(run-in-gen)

.PHONY: mtest
mtest: CXXFLAGS+=-g3 -DDEBUG -pg
mtest: CFLAGS+=-g3 -DDEBUG -pg
mtest: TARGET=mtest
mtest:
	$(run-in-gen)

.PHONY: clean
clean:
	@echo
	@echo "##### clean"
	rm -rvf "$(GENDIR)"

