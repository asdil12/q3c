LIBS  = -lpaho-mqtt3c
CFLAGS = -Wall -O2
LDFLAGS = 

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

SRC := $(wildcard *.c)
OBJECTS := $(patsubst %.c,%.o,$(SRC))


%.o: %.c 
%.o: %.c $(DEPDIR)/%.d Makefile
	$(CC) -o $@ -c $(CFLAGS) $(DEPFLAGS) $<
	mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

read: $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(LIBS) $^ 


clean:
	rm -f *.o
	rm -rf "./$(DEPDIR)"


$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d
.PHONY: clean

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRC)))
