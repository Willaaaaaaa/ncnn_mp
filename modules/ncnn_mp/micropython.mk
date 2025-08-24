NCNN_MP_MOD_DIR := $(USERMOD_DIR)
NCNN_DIR := $(NCNN_MP_MOD_DIR)/../../ncnn
NCNN_INSTALL_PREFIX := $(NCNN_DIR)/build/install

SRC_USERMOD_C += $(NCNN_MP_MOD_DIR)/ncnn_mp.c

# Include directories
CFLAGS_USERMOD += -I$(NCNN_INSTALL_PREFIX)/include

# Other compiler flags
CFLAGS_USERMOD += -Wno-unused-function

# Linker flags
LDFLAGS_USERMOD += -L$(NCNN_INSTALL_PREFIX)/lib

ifeq ($(USE_VULKAN), 1)
    LDFLAGS_USERMOD += -lncnn -lglslang
    LDFLAGS_USERMOD += -lncnn
endif

LDFLAGS_USERMOD += -lstdc++