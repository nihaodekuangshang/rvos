# Run usertests or usershell
TEST ?=

build:
	@ cd ./os && make build TEST=$(TEST)

run:
	@ cd ./os && make run TEST=$(TEST)

debug:
	@ cd ./os && make debug TEST=$(TEST)


clean:
	@ cd ./os && make clean TEST=$(TEST)
disasm:
	@ cd ./os && make disasm TEST=$(TEST)
disasm-vim:
	@ cd ./os && make disasm-vim TEST=$(TEST)
.PHONY: build  clean  run  disasm disasm-vim
