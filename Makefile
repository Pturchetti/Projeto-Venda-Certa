CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJETOS = main.o cadastro.o lista_produtos.o lista_pedidos.o json_produtos.o

venda_certa: $(OBJETOS)
	$(CC) $(CFLAGS) -o venda_certa $(OBJETOS)

main.o: main.c cadastro.h lista_produtos.h lista_pedidos.h
	$(CC) $(CFLAGS) -c main.c

cadastro.o: cadastro.c cadastro.h json_produtos.h
	$(CC) $(CFLAGS) -c cadastro.c

lista_produtos.o: lista_produtos.c lista_produtos.h cadastro.h
	$(CC) $(CFLAGS) -c lista_produtos.c

lista_pedidos.o: lista_pedidos.c lista_pedidos.h lista_produtos.h
	$(CC) $(CFLAGS) -c lista_pedidos.c

json_produtos.o: json_produtos.c json_produtos.h cadastro.h
	$(CC) $(CFLAGS) -c json_produtos.c

clean:
	rm -f $(OBJETOS) venda_certa