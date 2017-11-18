CXX = g++
CXXFLAGS = -std=c++11 -Wall -W -pedantic

DEPDIR := .obj
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

OBJDIR := .obj

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

COMPILE = $(CXX) $(DEPFLAGS) $(CXXFLAGS) -c
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

.PHONY: release debug clean

release : CXXFLAGS += -O2
release : game

debug : CXXFLAGS += -g
debug : game

game : $(OBJS)
	g++ -o game $(OBJS)

$(OBJDIR)/%.o : %.cpp
$(OBJDIR)/%.o : %.cpp $(DEPDIR)/%.d
	$(COMPILE) -o $@ $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))

clean:
	rm -rf $(OBJDIR)
	rm -rf $(DEPDIR)
	rm game
 
