FLAGS = -ggdb3 -std=c++17 -O0 \
	-Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat \
	-Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
	-Wconditionally-supported -Wconversion -Wctor-dtor-privacy \
	-Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security \
	-Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
	-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked \
	-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow \
	-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
	-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types \
	-Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef \
	-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
	-Wno-literal-suffix -Wno-missing-field-initializers \
	-Wno-narrowing -Wno-old-style-cast -Wno-varargs \
    -fcheck-new -fsized-deallocation -fstack-protector \
	-fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer \
	-Wlarger-than=32768 -Wstack-usage=8192 -pie -fPIE -Werror=vla \
	-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
SRCDIR = src

OBJDIR_AKINATOR = $(OBJDIR)/akinator
OBJDIR_STACK = $(OBJDIR)/stack
OBJDIR_DEBUG = $(OBJDIR)/debug

SRCDIR_AKINATOR = $(SRCDIR)/akinator
SRCDIR_STACK = $(SRCDIR)/stack
SRCDIR_DEBUG = $(SRCDIR)/debug

OUTPUTDIR = build

$(OBJDIR_AKINATOR):
	@mkdir -p $(OBJDIR_AKINATOR)

$(OBJDIR_STACK):
	@mkdir -p $(OBJDIR_STACK)

$(OBJDIR_DEBUG):
	@mkdir -p $(OBJDIR_DEBUG)

FILES = $(OBJDIR_AKINATOR)/main.o $(OBJDIR_AKINATOR)/tree.o $(OBJDIR_AKINATOR)/io.o \
    $(OBJDIR_AKINATOR)/comparison.o $(OBJDIR_AKINATOR)/menu.o \
    $(OBJDIR_STACK)/stack.o $(OBJDIR_STACK)/error.o
DEBUG_FILES = $(OBJDIR_DEBUG)/graph_generator.o $(OBJDIR_DEBUG)/html_builder.o
FLAGS += -Iinclude

OUTPUT_NAME = akinator


clean: 
	@echo "cleaning up object files..."
	@rm -rf $(OBJDIR)


run:
	@cd $(BUILDDIR) && ./$(OUTPUT_NAME)


debug: FLAGS += -DDEBUG


debug: $(FILES) $(DEBUG_FILES)
	@g++ $(FILES) $(DEBUG_FILES) $(FLAGS) -o $(OUTPUTDIR)/$(OUTPUT_NAME)


release: $(FILES)
	@g++ $(FILES) $(FLAGS) -o $(OUTPUT_NAME)


$(OBJDIR_AKINATOR)/main.o: $(SRCDIR_AKINATOR)/main.cpp | $(OBJDIR_AKINATOR)
	@g++ -c $(SRCDIR_AKINATOR)/main.cpp $(FLAGS) -o $(OBJDIR_AKINATOR)/main.o


$(OBJDIR_AKINATOR)/tree.o: $(SRCDIR_AKINATOR)/tree.cpp | $(OBJDIR_AKINATOR)
	@g++ -c $(SRCDIR_AKINATOR)/tree.cpp $(FLAGS) -o $(OBJDIR_AKINATOR)/tree.o


$(OBJDIR_AKINATOR)/io.o: $(SRCDIR_AKINATOR)/io.cpp | $(OBJDIR_AKINATOR)
	@g++ -c $(SRCDIR_AKINATOR)/io.cpp $(FLAGS) -o $(OBJDIR_AKINATOR)/io.o


$(OBJDIR_AKINATOR)/comparison.o: $(SRCDIR_AKINATOR)/comparison.cpp | $(OBJDIR_AKINATOR)
	@g++ -c $(SRCDIR_AKINATOR)/comparison.cpp $(FLAGS) -o $(OBJDIR_AKINATOR)/comparison.o


$(OBJDIR_AKINATOR)/menu.o: $(SRCDIR_AKINATOR)/menu.cpp | $(OBJDIR_AKINATOR)
	@g++ -c $(SRCDIR_AKINATOR)/menu.cpp $(FLAGS) -o $(OBJDIR_AKINATOR)/menu.o


$(OBJDIR_STACK)/stack.o: $(SRCDIR_STACK)/stack.cpp | $(OBJDIR_STACK)
	@g++ -c $(SRCDIR_STACK)/stack.cpp $(FLAGS) -o $(OBJDIR_STACK)/stack.o


$(OBJDIR_STACK)/error.o: $(SRCDIR_STACK)/error.cpp | $(OBJDIR_STACK)
	@g++ -c $(SRCDIR_STACK)/error.cpp $(FLAGS) -o $(OBJDIR_STACK)/error.o


$(OBJDIR_DEBUG)/graph_generator.o: $(SRCDIR_DEBUG)/graph_generator.cpp | $(OBJDIR_DEBUG)
	@g++ -c $(SRCDIR_DEBUG)/graph_generator.cpp $(FLAGS) -o $(OBJDIR_DEBUG)/graph_generator.o


$(OBJDIR_DEBUG)/html_builder.o: $(SRCDIR_DEBUG)/html_builder.cpp | $(OBJDIR_DEBUG)
	@g++ -c $(SRCDIR_DEBUG)/html_builder.cpp $(FLAGS) -o $(OBJDIR_DEBUG)/html_builder.o
