all: uber-graph

DISABLE_DEBUG := 1
DISABLE_TRACE := 1

WARNINGS =								\
	-Wall								\
	-Werror								\
	-Wold-style-definition						\
	-Wdeclaration-after-statement					\
	-Wredundant-decls						\
	-Wmissing-noreturn						\
	-Wcast-align							\
	-Wwrite-strings							\
	-Winline							\
	-Wformat-nonliteral						\
	-Wformat-security						\
	-Wswitch-enum							\
	-Wswitch-default						\
	-Winit-self							\
	-Wmissing-include-dirs						\
	-Wundef								\
	-Waggregate-return						\
	-Wmissing-format-attribute					\
	-Wnested-externs

#	-Wshadow

DEBUG_INCLUDES =							\
	-DG_DISABLE_ASSERT						\
	-DG_DISABLE_CHECKS						\
	-DG_DISABLE_CAST_CHECKS						\
	-DDISABLE_DEBUG							\
	$(NULL)

TRACE_INCLUDES =							\
	-DUBER_TRACE							\
	$(NULL)

INCLUDES =								\
	-DHAVE_CONFIG_H=0						\
	$(NULL)

OBJECTS =								\
	uber-buffer.o							\
	uber-graph.o							\
	uber-heat-map.o							\
	uber-label.o							\
	uber-parse.o							\
	g-ring.o							\
	main.o								\
	$(NULL)

ifeq ($(DISABLE_DEBUG),1)
	INCLUDES += $(DEBUG_INCLUDES)
endif

ifeq ($(DISABLE_TRACE),0)
	INCLUDES += $(TRACE_INCLUDES)
endif

main.o: main.c Makefile
	$(CC) -g -c -o $@ $(WARNINGS) $(INCLUDES) main.c $(shell pkg-config --cflags gtk+-2.0 gthread-2.0)

%.o: %.c %.h Makefile
	$(CC) -g -c -o $@ $(WARNINGS) $(INCLUDES) $*.c $(shell pkg-config --cflags gtk+-2.0 gthread-2.0)

uber-graph: $(OBJECTS) Makefile
	$(CC) -g -o $@ $(shell pkg-config --libs gtk+-2.0 gthread-2.0) $(OBJECTS)

clean:
	rm -f uber-graph $(OBJECTS)

run: uber-graph
	./uber-graph
