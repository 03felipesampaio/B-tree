all:
	@gcc *.c *.h -Wall -o exercicio3.bin
run:
	@./exercicio3.bin
zip:
	@zip exercicio3 *.c *.h Makefile binFiles