# Right half wired in reverse on one of the two boards; see config.h.
ifeq ($(strip $(MIRRORED_RIGHT)), yes)
    OPT_DEFS += -DMIRRORED_RIGHT
endif
