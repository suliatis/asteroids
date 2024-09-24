default: help

init: build lsp ## Init project

clean: ## Clean build
	rm -rf build
	rm -rf .cache

build: ## Init build
	cmake -B build && cmake --build build

lsp: ## Setup LSP
	cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1

app: ## Build application
	make -C build asteroids

run: app ## Run application
	./build/asteroids

help: ## This help message
	-@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' -e 's/:.*#/: #/' | column -t -s '##'
