include testing.mk
test:
	$(MAKE) test_all

clean:
	find tests \( -name "*.actual*" -o -name "tester" -o -name "*.check*" \) -exec rm {} \;
	@echo "Se eliminaron los archivos complementarios de test."