include $(MAKEFILES_BASE_DIR)/common/dirs_features.mk

.PHONY: all
all:: mk_gen_link
all:: $(LIBRARY_NAME)

.PHONY: test
test:: mk_gen_link
test:: copy_testdata
test:: $(TEST_PROGRAM_NAME)

.PHONY: mtest
mtest:: mk_gen_link
mtest:: copy_testdata
mtest:: $(CXXBIN_MTEST) $(CBIN_MTEST)


$(TEST_PROGRAM_NAME):: $(CXXOBJS_TEST) $(COBJS_TEST) \
					  $(CXXOBJS_NOMAIN) $(COBJS_NOMAIN)
	@echo "LD    $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LINK_LIBS) $(LINK_LIBS)

$(LIBRARY_NAME):: $(CXXOBJS) $(COBJS)
	@echo "AR    $@"
	$(AR) -r $@ $^


%.mt: %.mt.o $(CXXOBJS_NOMAIN) $(COBJS_NOMAIN)
	@echo "LD    $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LINK_LIBS) $(LINK_LIBS)

$(CBIN_MTEST)::
	@echo "mtest taget is not implemented for C sources"
	@false

.PHONY: mk_gen_link
mk_gen_link:
	ln -fs "$(CURDIR)/$(LIBRARY_NAME)" "$(GEN_LIBS_DIR)"

.PHONY: copy_testdata
copy_testdata:
	#@echo "copying test data"
	cp -pur "$(THIS_SRC_BASE_DIR)/features/testdata" .

