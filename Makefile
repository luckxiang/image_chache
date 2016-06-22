cc = gcc
SRC = image_chache.c list.c

#CFLAG = -O0
CFLAG = -O0 -pg
#LINK = c_p

image_chache: $(SRC) 
		$(cc) $(CFLAG) $^ -o $@ 
clean:
	@rm -rf *.o
	@rm -f image_chache 
