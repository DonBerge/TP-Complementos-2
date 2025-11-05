# Este makefile de test esta fuertemente inspirado en el usado en la materia "Compiladores"

TESTDIRS += tests/ropeEnteros
TESTDIRS += tests/ropeEnterosLazy
TESTDIRS += tests/ropeGenericoSuma
TESTDIRS += tests/ropeGenericoMinimo
TESTDIRS += tests/ropeGenericoPrefijos
TESTDIRS += tests/ropeGenericoSets
TESTDIRS += tests/ropeGenericoLazySuma

TESTS	:= $(shell find $(TESTDIRS) -name '*.in' -type f | sort)

CC  := g++
CFLAGS := -lgc -std=c++20 -g

EXTRAFLAGS	:=

OUTS := $(patsubst %.in,%.actual_out,$(TESTS))
CHECK := $(patsubst %.in,%.check,$(TESTS))

TESTERS := $(addsuffix /tester,$(TESTDIRS))

$(TESTERS): %/tester: %/tester.cpp
	$(Q)$(CC) $(CFLAGS) $(EXTRAFLAGS) -o $@ $<

# Esta regla corre todos los tests (por sus dependencias) y luego
# imprime un mensaje.
test_all: $(TESTERS) $(CHECK)
	@echo "---------------------------------"
	@echo "             Todo OK             "
	@echo "---------------------------------"

Q=@
ifneq ($(V),)
	Q=
endif

%.actual_out: %.in
	$(Q)"$(dir $<)tester" < $< > $@

# Comparar salidas
%.check: %.out %.actual_out
	$(Q)if diff -u -q $^; then \
		echo "OK	$(patsubst %.out,%,$<)"; \
		touch $@; \
	else \
		echo "FAILED	$(patsubst %.out,%,$<)"; \
		false; \
	fi

# Descomentar para no borrar los archivos *.actual_out
# .SECONDARY: $(OUTS)