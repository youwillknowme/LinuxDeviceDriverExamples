obj-m:=hello1.o

docompile:
	@make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	rm *.o *.ko *.mod.c *.mod Mod* mod*
