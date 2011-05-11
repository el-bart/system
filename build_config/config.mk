#
# project specific configuration file
# to be placed in main project directory
#

# set default mode
export MODE:=default

# set default profile
export PROFILE:=test

# default tool chain
export TC:=gcc

# enable ccache, but not for intel
ifneq ($(TC),intel)
export WITH_CCACHE:=1
endif

ifeq ($(TC),intel)
TMP+=-wd279
TMP+=-wd383
TMP+=-wd444
TMP+=-wd854
TMP+=-wd981
TMP+=-wd1418
TMP+=-wd1572
TMP+=-wd2259
TMP_LD+=-lstdc++
else
TMP+=
TMP_LD+=
endif

# turn compiuler-specific optimizations
ifeq ($(TC),gcc)
TMP_OPT+=-march=native
endif
ifeq ($(TC),intel)
TMP_OPT+=-xhost
endif

export USER_OPT_FLAGS:=$(TMP) $(TMP_OPT)
export USER_DBG_FLAGS:=$(TMP)
export USER_PRF_FLAGS:=$(USER_OPT_FLAGS)
export USER_OPT_LDFLAGS:=$(TMPLD)
export USER_DBG_LDFLAGS:=$(TMPLD)
export USER_PRF_LDFLAGS:=$(TMPLD)

# cleanup TMP
TMP:=
TMP_OPT:=
TMPLD:=
unexport TMP
unexport TMP_OPT
unexport TMPLD
