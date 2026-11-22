# ============================================================
#              42 Exam Rank 04 – Makefile 🧪
# ============================================================

# 🧱 Compiler & Flags
CC      := cc
# CFLAGS  := -Wall -Wextra -Werror -g3
CFLAGS  := -g3

# 📁 Project Directories
FT_POPEN_DIR   := level-1/ft_popen
PICOSHELL_DIR  := level-1/picoshell
SANDBOX_DIR    := level-1/sandbox
ARGO_DIR       := level-2/argo
VBC_DIR        := level-2/vbc

# 🎯 Binary Names (per directory)
FT_POPEN_NAME       := ft_popen
FT_POPEN_SHORT_NAME := ft_popen_short
PICOSHELL_NAME      := picoshell
PICOSHELL_SHORT_NAME := picoshell_short
SANDBOX_NAME        := sandbox
ARGO_NAME           := argo
VBC_NAME            := vbc

# 📦 Binaries (full paths)
FT_POPEN_BIN       := $(FT_POPEN_DIR)/$(FT_POPEN_NAME)
FT_POPEN_SHORT_BIN := $(FT_POPEN_DIR)/$(FT_POPEN_SHORT_NAME)
PICOSHELL_BIN      := $(PICOSHELL_DIR)/$(PICOSHELL_NAME)
PICOSHELL_SHORT_BIN := $(PICOSHELL_DIR)/$(PICOSHELL_SHORT_NAME)
SANDBOX_BIN        := $(SANDBOX_DIR)/$(SANDBOX_NAME)
ARGO_BIN           := $(ARGO_DIR)/$(ARGO_NAME)
VBC_BIN            := $(VBC_DIR)/$(VBC_NAME)

# 🧩 Source / Object lists (explicit files)
FT_POPEN_SRCS       := $(FT_POPEN_DIR)/ft_popen.c
FT_POPEN_SHORT_SRCS := $(FT_POPEN_DIR)/ft_popen_short.c
PICOSHELL_SRCS      := $(PICOSHELL_DIR)/picoshell.c
PICOSHELL_SHORT_SRCS := $(PICOSHELL_DIR)/picoshell_short.c
SANDBOX_SRCS    := $(SANDBOX_DIR)/sandbox.c
ARGO_SRCS       :=
VBC_SRCS        := $(VBC_DIR)/vbc.c

FT_POPEN_OBJS       := $(FT_POPEN_SRCS:.c=.o)
FT_POPEN_SHORT_OBJS := $(FT_POPEN_SHORT_SRCS:.c=.o)
PICOSHELL_OBJS      := $(PICOSHELL_SRCS:.c=.o)
PICOSHELL_SHORT_OBJS := $(PICOSHELL_SHORT_SRCS:.c=.o)
SANDBOX_OBJS    := $(SANDBOX_SRCS:.c=.o)
ARGO_OBJS       := $(ARGO_SRCS:.c=.o)
VBC_OBJS        := $(VBC_SRCS:.c=.o)

# 📦 All binaries together
BINS := \
	$(FT_POPEN_BIN) \
	$(FT_POPEN_SHORT_BIN) \
	$(PICOSHELL_BIN) \
	$(PICOSHELL_SHORT_BIN) \
	$(SANDBOX_BIN) \
	$(ARGO_BIN) \
	$(VBC_BIN)

OBJS := \
	$(FT_POPEN_OBJS) \
	$(FT_POPEN_SHORT_OBJS) \
	$(PICOSHELL_OBJS) \
	$(PICOSHELL_SHORT_OBJS) \
	$(SANDBOX_OBJS) \
	$(ARGO_OBJS) \
	$(VBC_OBJS)

# ============================================================
#  Generic Rules
# ============================================================

# Default target
.PHONY: all
all: $(BINS)
	@echo "✅ All exam binaries built."

# Generic rule: compile any .c -> .o (keeps directory structure)
%.o: %.c
	@echo "🔧 Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Link each project

$(FT_POPEN_BIN): $(FT_POPEN_OBJS)
	@echo "🔗 Linking $@"
	@$(CC) $(CFLAGS) $^ -o $@

$(FT_POPEN_SHORT_BIN): $(FT_POPEN_SHORT_OBJS)
	@echo "🔗 Linking $@"
	@$(CC) $(CFLAGS) $^ -o $@

$(PICOSHELL_BIN): $(PICOSHELL_OBJS)
	@echo "🔗 Linking $@"
	@$(CC) $(CFLAGS) $^ -o $@

$(PICOSHELL_SHORT_BIN): $(PICOSHELL_SHORT_OBJS)
	@echo "🔗 Linking $@"
	@$(CC) $(CFLAGS) $^ -o $@

$(SANDBOX_BIN): $(SANDBOX_OBJS)
	@echo "🔗 Linking $@"
	@$(CC) $(CFLAGS) $^ -o $@

$(ARGO_BIN): $(ARGO_OBJS)
	@echo "🔗 Linking $@"
	@$(CC) $(CFLAGS) $^ -o $@

$(VBC_BIN): $(VBC_OBJS)
	@echo "🔗 Linking $@"
	@$(CC) $(CFLAGS) $^ -o $@

# ============================================================
#  Per-project build targets
# ============================================================

.PHONY: ft_popen ft_popen_short picoshell picoshell_short sandbox argo vbc

ft_popen: $(FT_POPEN_BIN)
	@echo "✅ Built $(FT_POPEN_BIN)"

ft_popen_short: $(FT_POPEN_SHORT_BIN)
	@echo "✅ Built $(FT_POPEN_SHORT_BIN)"

picoshell: $(PICOSHELL_BIN)
	@echo "✅ Built $(PICOSHELL_BIN)"

picoshell_short: $(PICOSHELL_SHORT_BIN)
	@echo "✅ Built $(PICOSHELL_SHORT_BIN)"

sandbox: $(SANDBOX_BIN)
	@echo "✅ Built $(SANDBOX_BIN)"

argo: $(ARGO_BIN)
	@echo "✅ Built $(ARGO_BIN)"

vbc: $(VBC_BIN)
	@echo "✅ Built $(VBC_BIN)"

# ============================================================
#  Run helpers (build + run)
# ============================================================

.PHONY: run_ft_popen run_ft_popen_short run_picoshell run_picoshell_short run_sandbox run_argo run_vbc run_all

run_ft_popen: ft_popen
	@echo "🚀 Running ft_popen\n"
	@$(FT_POPEN_BIN)

run_ft_popen_short: ft_popen_short
	@echo "🚀 Running ft_popen_short\n"
	@$(FT_POPEN_SHORT_BIN)

run_picoshell: picoshell
	@echo "🚀 Running picoshell\n"
	@$(PICOSHELL_BIN)

run_picoshell_short: picoshell_short
	@echo "🚀 Running picoshell_short\n"
	@$(PICOSHELL_SHORT_BIN)

run_sandbox: sandbox
	@echo "🚀 Running sandbox\n"
	@$(SANDBOX_BIN)

run_argo: argo
	@echo "🚀 Running argo\n"
	@$(ARGO_BIN)

run_vbc: vbc
	@echo "🚀 Running vbc '2+3' | cat -e\n"
	@$(VBC_BIN) '2+3' | cat -e

run_all: all
	@echo "🚀 Running all binaries (in order)"
	@$(FT_POPEN_BIN)   || true
	@$(PICOSHELL_BIN)  || true
	@$(SANDBOX_BIN)    || true
	@$(ARGO_BIN)       || true
	@$(VBC_BIN)        || true

# ============================================================
#  Cleanup
# ============================================================

.PHONY: clean fclean re

clean:
	@echo "🧹 Cleaning object files"
	@rm -f $(OBJS)

fclean: clean
	@echo "🗑  Removing binaries"
	@rm -f $(BINS)

re: fclean all
	@echo "🔁 Rebuilt everything from scratch."
