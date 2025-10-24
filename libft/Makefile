# ————————————————————————————————————————————————————————————————————————————— #
#                                   SETTINGS                                      #
# ————————————————————————————————————————————————————————————————————————————— #

NAME      := libft.a
CC        := gcc
CFLAGS    := -Wall -Wextra -Werror

SRCDIR    := src
OBJDIR    := obj

# ————————————————————————————————————————————————————————————————————————————— #
#                                 SOURCE FILES                                    #
# ————————————————————————————————————————————————————————————————————————————— #

SRCS := \
	ft_isalpha.c    ft_isdigit.c    ft_isalnum.c     \
	ft_isprint.c    ft_atoi.c       ft_bzero.c       \
	ft_memset.c     ft_memcpy.c     ft_memmove.c     \
	ft_memchr.c     ft_memcmp.c     ft_strdup.c      \
	ft_strlcat.c    ft_strchr.c     ft_strrchr.c     \
	ft_strnstr.c    ft_strncmp.c    ft_isascii.c     \
	ft_striteri.c   ft_strjoin.c    ft_strlen.c      \
	ft_strtrim.c    ft_itoa.c       ft_putchar_fd.c  \
	ft_putstr_fd.c  ft_putendl_fd.c ft_putnbr_fd.c   \
	ft_isspace.c    ft_tolower.c    ft_toupper.c     \
	ft_calloc.c		ft_strlcpy.c	ft_substr.c 	 \
	ft_split.c		ft_strmapi.c	

BONUS_SRCS := \
	ft_lstnew.c     	ft_lstdelone.c  ft_lstadd_front.c  \
	ft_lstadd_back.c 	ft_lstiter.c    ft_lstmap.c		   \
	ft_lstclear.c		ft_lstlast.c	ft_lstsize.c

OBJS      := $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
BONUS_OBJS:= $(addprefix $(OBJDIR)/, $(BONUS_SRCS:.c=.o))

# ————————————————————————————————————————————————————————————————————————————— #
#                                   RULES                                          #
# ————————————————————————————————————————————————————————————————————————————— #

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

bonus: $(OBJDIR) $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re