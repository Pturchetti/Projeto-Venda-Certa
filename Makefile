CC = gcc
CFLAGS = -Wall -Wextra -std=c11
MODULOS = cadastro lista_produtos lista_pedidos fila_empacotamento caixas caminhoes geral_menu codigos
CPPFLAGS += $(addprefix -I,$(MODULOS))
FONTES = main.c $(foreach modulo,$(MODULOS),$(modulo)/$(modulo).c)
OBJETOS = $(FONTES:.c=.o)
DEPENDENCIAS = $(OBJETOS:.o=.d)

venda_certa: $(OBJETOS)
	$(CC) $(CFLAGS) -o $@ $(OBJETOS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJETOS) $(DEPENDENCIAS) venda_certa

-include $(DEPENDENCIAS)

.PHONY: clean
