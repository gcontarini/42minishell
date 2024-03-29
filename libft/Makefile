############## CORE FILES ##############
CORE 	=	ft_atoi.c			\
			ft_bzero.c			\
			ft_calloc.c			\
			ft_intlen.c			\
			ft_isalnum.c		\
			ft_isalpha.c		\
			ft_isascii.c		\
			ft_isdigit.c		\
			ft_isprint.c		\
			ft_itoa.c			\
			ft_itoa_mem.c		\
			ft_longlen_base.c	\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_memcpy.c			\
			ft_memmove.c		\
			ft_memset.c			\
			ft_putchar_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c		\
			ft_putstr_fd.c		\
			ft_split.c			\
			ft_strchr.c			\
			ft_strdup.c			\
			ft_striteri.c		\
			ft_strjoin.c		\
			ft_strlcat.c		\
			ft_strlcpy.c		\
			ft_strlen.c			\
			ft_strmapi.c		\
			ft_strncmp.c		\
			ft_strndup.c 		\
			ft_strnstr.c		\
			ft_strrchr.c		\
			ft_strtrim.c		\
			ft_substr.c			\
			ft_tolower.c		\
			ft_toupper.c		\
			ft_uintlen.c		\
			ft_uintlen_base.c	\
			ft_ulonglen_base.c	\
			ft_ultoa_membase.c	\
			ft_utoa_mem.c		\
			ft_utoa_membase.c

########### LINKED LIST FILES ###########
LLST	=	ft_lstadd_back.c	\
			ft_lstadd_front.c	\
			ft_lstclear.c		\
			ft_lstdelone.c		\
			ft_lstiter.c		\
			ft_lstlast.c		\
			ft_lstmap.c			\
			ft_lstnew.c			\
			ft_lstsize.c		\
			ft_lst_remove.c


########### DOUBLE LIST FILES ###########
DLST	=	ft_dlstadd_back.c	\
			ft_dlstadd_front.c	\
			ft_dlstclear.c		\
			ft_dlstdelone.c		\
			ft_dlstiter.c		\
			ft_dlstlast.c		\
			ft_dlstmap.c		\
			ft_dlstnew.c		\
			ft_dlstsize.c

############### GNL FILES ###############
GNL		=	get_next_line.c

############## PRINTF FILES #############
PTF		=	ft_printf.c			\
			ftptf_args.c		\
			ftptf_char.c		\
			ftptf_flush.c		\
			ftptf_int.c			\
			ftptf_jptab.c		\
			ftptf_lowhex.c		\
			ftptf_memerror.c	\
			ftptf_perc.c		\
			ftptf_ptr.c			\
			ftptf_queue.c		\
			ftptf_str.c			\
			ftptf_uint.c		\
			ftptf_uphex.c		\

############## STACK FILES #############
STK		=	ft_istkclean.c	\
			ft_istkpeek.c	\
			ft_istkprint.c	\
			ft_istksort.c	\
			ft_stkclean.c	\
			ft_stkcpy.c		\
			ft_stkcpyn.c	\
			ft_stkget.c		\
			ft_stklen.c		\
			ft_stkpop.c		\
			ft_stkposh.c	\
			ft_stkpush.c	\
			ft_stkrot.c		\
			ft_stkrpush.c	\
			ft_stkrrot.c	\
			ft_stkstart.c	\
			ft_stkswap.c	\
			ft_stkswapn.c

############## QUEUE FILES #############
QUE		=	ft_deque.c		\
			ft_enque.c		\
			ft_iqueclean.c	\
			ft_iqueprint.c	\
			ft_queclean.c	\
			ft_quecpy.c		\
			ft_quecpyn.c	\
			ft_queget.c		\
			ft_quelen.c		\
			ft_questart.c

################ PATHS #################
INC		= -I includes/
POBJS	= obj
PCORE 	= $(addprefix $(POBJS)/, $(CORE:.c=.o))
PLST 	= $(addprefix $(POBJS)/, $(LLST:.c=.o))
PDLST	= $(addprefix $(POBJS)/, $(DLST:.c=.o))
PPTF	= $(addprefix $(POBJS)/, $(PTF:.c=.o))
PGNL	= $(addprefix $(POBJS)/, $(GNL:.c=.o))
PSTK	= $(addprefix $(POBJS)/, $(STK:.c=.o))
PQUE	= $(addprefix $(POBJS)/, $(QUE:.c=.o))

############### ALL OBJS ###############
OBJS 	= 	$(PCORE) $(PLST) $(PDLST)	\
			$(PPTF) $(PGNL) $(PSTK)		\
			$(PQUE)

############### TARGET #################
NAME 	= 	libft.a

############# COMPILER OPTS ############
CC		= 	gcc 
CFLAGS	= 	-Wall -Werror -Wextra
RM		= 	rm -f
AR		=	ar rcs

################ RULES #################
$(POBJS)/%.o : */%.c
	@mkdir -p $(POBJS)/
	$(CC) $(CFLAGS) -c $(INC) $< -o $@

$(NAME)	: $(OBJS)
	$(AR) $@ $^

all		: $(NAME)

core	: $(PCORE) 
	$(AR) $(NAME) $^

lst		: core $(PLST)
	$(AR) $(NAME) $(PLST)

dlst	: core $(PDLST)
	$(AR) $(NAME) $(PDLST)

gnl		: core $(PGNL)
	$(AR) $(NAME) $(PGNL)

printf	: core $(PPTF)
	$(AR) $(NAME) $(PPTF)

stk		: core lst printf $(PSTK)
	$(AR) $(NAME) $(PSTK)

que		: core dlst printf $(PQUE)
	$(AR) $(NAME) $(PQUE)

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re core lst dlst gnl printf stk que
