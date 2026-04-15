CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

SRCDIR   := src
BUILDDIR := build

# Use make's built-in wildcard — no shell commands, works on Windows & POSIX
SRCS := $(wildcard $(SRCDIR)/*.cpp)          \
        $(wildcard $(SRCDIR)/http/*.cpp)     \
        $(wildcard $(SRCDIR)/json/*.cpp)

OBJS := $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

# ── Platform detection ────────────────────────────────────────────────────────
ifeq ($(OS), Windows_NT)
    TARGET  := $(BUILDDIR)/cipher_client.exe
    LDFLAGS := -lws2_32
    RMDIR   := rmdir /S /Q
    # mkdir on Windows cmd: suppress "already exists" error with 2>nul
    MKDIR   = if not exist "$(subst /,\,$(@D))" mkdir "$(subst /,\,$(@D))"
else
    TARGET  := $(BUILDDIR)/cipher_client
    LDFLAGS :=
    RMDIR   := rm -rf
    MKDIR   = mkdir -p $(@D)
endif

# ── Default target ────────────────────────────────────────────────────────────
.PHONY: all
all: $(TARGET)

# ── Link ──────────────────────────────────────────────────────────────────────
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# ── Compile each .cpp → matching .o inside build/ ────────────────────────────
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ── Convenience targets ───────────────────────────────────────────────────────
.PHONY: run
run: all
	./$(TARGET)

.PHONY: clean
clean:
	$(RMDIR) $(BUILDDIR)
