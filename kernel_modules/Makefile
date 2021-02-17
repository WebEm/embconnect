obj-m = simple_char_device_driver.o 
#path to kernel source code folder
KERNEL = $(shell uname -r)

all:
	make -C /lib/modules/$(KERNEL)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KERNEL)/build M=$(PWD) clean
