CC			=	clang++
INCLUDE		=	-Iinclude -Iinclude/**

SDIR 		=	src
ODIR 		=	build
HDIR		=	include
BDIR 		=	bin
OUT			=	c_dev_env_manager_installer

SRCS		=	$(wildcard $(SDIR)/*.cpp)
OBJS		=	$(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SRCS))

$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CC) $(INCLUDE) -c $< -o $@

all : clean $(OUT)

$(OUT) : $(OBJS)
	$(CC) $(OBJS) -o $(BDIR)/$(OUT)

clean :
	rm -f $(OBJS) $(BDIR)/$(OUT)
