all:
	cd src && $(MAKE)

install:
	cd src && $(MAKE) $@

doc:
	doxygen Doxyfile

clean:
	cd src && $(MAKE) $@
	rm -fr doc

.PHONY: all compile doc clean
