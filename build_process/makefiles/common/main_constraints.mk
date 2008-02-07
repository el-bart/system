# is any profile set?
ifneq ($(PROFILE),test)
ifneq ($(PROFILE),mtest)
ifneq ($(PROFILE),debug)
ifneq ($(PROFILE),release)
ifneq ($(PROFILE),profile)
$(error PROFILE not set (aviable are: debug, release, test, mtest, profile))
endif # PROFILE=profile
endif # PROFILE=release
endif # PROFILE=debug
endif # PROFILE=mtest
endif # PROFILE=test

# PROFILE=*test given correctly?
ifeq ($(PROFILE),test)
ifeq ($(TEST_COMPONENT),)
$(error TEST_COMPONENT must be set for PROFILE=test)
endif
endif
ifeq ($(PROFILE),mtest)
ifeq ($(TEST_COMPONENT),)
$(error TEST_COMPONENT must be set for PROFILE=mtest)
endif
endif

