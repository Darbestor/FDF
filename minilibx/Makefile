#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c \
mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2
PRINTF=test $(VERBOSE)$(TRAVIS) || printf

all:
	@$(PRINTF) "%-20s\r\033[0;33m$(NOM)\033[0m"
	$(MAKE) -q $(NOM) ; \
	if [ $$? -eq 0 ] ; then $(PRINTF) "\r\x1b[20C\x1b[0K\033[0;31m $(NOM) \
	is already up to date\033[0m\n"; \
	else $(MAKE) $(NOM) && $(PRINTF) "\r\x1b[20C\x1b[0K\033[0;32m✔\033[0m\n"; \
	fi

$(NOM):	$(OBJ)
	@$(PRINTF) "\r\x1b[20C\x1b[0K$@"
	ar -r $(NOM) $(OBJ)
	ranlib $(NOM)

clean:
	rm -f $(NOM) $(OBJ) *~
	rm -f mlx_app

re: clean all

ifndef VERBOSE
 ifndef TRAVIS
.SILENT:
 endif
endif