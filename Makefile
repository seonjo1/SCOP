NAME :=	SCOP

all : $(NAME)

$(NAME):
	@cmake -Bbuild . 
	@cmake --build build --config Debug
	@mv ./build/Debug/SCOP.exe ./SCOP.exe
	@echo [SUCCESS] $@ compiled successfully!

clean :
	@rm -rf ./build/
	@echo [CLEAN] Object files have been removed!

fclean : clean
	@rm -rf SCOP.exe
	@echo [FCLEAN] Executable files have been fully removed!

re : fclean all

.PHONY : all clean fclean re