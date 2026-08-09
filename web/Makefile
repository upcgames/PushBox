PYTHON ?= $(shell test -x .venv/bin/python && echo .venv/bin/python || echo python3)
MANIFEST = modules_manifest.txt
SOURCE_CPP = ../Retro\ Push\ Box/Source\ Code.cpp
MODULES_STAMP = pushbox_modules/.stamp
JS_STAMP = src/generated/.stamp
ANIM_STAMP = src/generated_anim/.stamp
PUBLIC_MODULES_STAMP = public/pushbox_modules/.stamp

.PHONY: generate test

generate: $(JS_STAMP) $(ANIM_STAMP) $(PUBLIC_MODULES_STAMP)

$(MODULES_STAMP): $(MANIFEST) $(SOURCE_CPP) scripts/build_pushbox_modules.py
	$(PYTHON) scripts/build_pushbox_modules.py
	touch $(MODULES_STAMP)

$(PUBLIC_MODULES_STAMP): $(MODULES_STAMP)
	mkdir -p public/pushbox_modules
	rsync -a --delete pushbox_modules/ public/pushbox_modules/
	touch $(PUBLIC_MODULES_STAMP)

test: scripts/test_transpiler.py scripts/dag.py scripts/ast_transpiler.py
	$(PYTHON) scripts/test_transpiler.py
	npx eslint src/

$(JS_STAMP): $(MODULES_STAMP) scripts/transpile_modules.py scripts/ast_transpiler.py scripts/dag.py scripts/copy_resources.py
	$(PYTHON) scripts/transpile_modules.py
	touch $(JS_STAMP)
	touch $(ANIM_STAMP)


