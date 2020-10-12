NAME = libft.a
OBJ_FILES_REG = ft_atoi.o ft_memset.o ft_bzero.o ft_strlcpy.o ft_strlcat.o \
 ft_memcpy.o ft_memccpy.o ft_memmove.o ft_memchr.o ft_memcmp.o ft_strlen.o \
 ft_strchr.o ft_strrchr.o ft_strncmp.o ft_strnstr.o ft_tolower.o ft_toupper.o \
 ft_isdigit.o ft_isalnum.o ft_isprint.o ft_isascii.o ft_isalpha.o ft_calloc.o \
 ft_strdup.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o \
 ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_strmapi.o ft_itoa.o ft_strcpy.o \
 ft_strdel.o ft_strcmp.o
OBJ_FILES_BONUS = ft_lstiter.o ft_lstlast.o ft_lstadd_back.o ft_lstadd_front.o \
ft_lstclear.o ft_lstdelone.o ft_lstnew.o ft_lstsize.o ft_lstmap.o

ifdef WITH_BONUS
OBJ_FILES = $(OBJ_FILES_REG) $(OBJ_FILES_BONUS)
else
OBJ_FILES = $(OBJ_FILES_REG)
endif

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $(NAME) $^
	ranlib $(NAME)

bonus:
	$(MAKE) WITH_BONUS=1 all

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

so:	bonus
	$(CC) -shared -o libft.so $(OBJ_FILES) $(OBJ_FILES_BONUS)

clean:
	rm -f $(OBJ_FILES) $(OBJ_FILES_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
