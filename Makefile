image_chache: list.o image_chache.o 
image_chache.o:image_chache.c list.h
list.o:list.c list.h
clean:
	@rm -rf *.o
	@rm -f image_chache 
