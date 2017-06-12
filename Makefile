programs:
	$(CC) const.c -o const
	$(CC) filter.c -o filter
	$(CC) window.c -o window
	$(CC) spawn.c -o spawn

controlador: 
	$(CC) controlador.c -o controlador
clean:
	rm filter const window spawn controlador