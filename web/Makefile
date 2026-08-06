MANIFEST = ../dsl_module_manifest.txt
SOURCE_CPP = ../Retro\ Push\ Box/Source\ Code.cpp
DSL_STAMP = pushbox_dsl/.stamp
JS_STAMP = src/dsl/.stamp

.PHONY: all clean pipeline lint

all: $(JS_STAMP)

$(DSL_STAMP): $(MANIFEST) $(SOURCE_CPP) scripts/build_pushbox_dsl.py
	python3 scripts/build_pushbox_dsl.py
	touch $(DSL_STAMP)

$(JS_STAMP): $(DSL_STAMP) scripts/transpile_dsl_to_js.py scripts/transpiler_core.py scripts/test_transpiler.py
	python3 scripts/test_transpiler.py
	python3 scripts/transpile_dsl_to_js.py
	npx eslint src/
	touch $(JS_STAMP)

pipeline:
	python3 scripts/test_transpiler.py
	python3 scripts/build_pushbox_dsl.py
	python3 scripts/transpile_dsl_to_js.py
	npx eslint src/
	touch $(DSL_STAMP) $(JS_STAMP)

lint:
	npx eslint src/

clean:
	rm -rf pushbox_dsl src/dsl
