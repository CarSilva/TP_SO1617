programs:
	cc const.c -o const
	cc filter.c -o filter
	cc window.c -o window
	cc spawn.c -o spawn

controlador:
	cc controlador -o controlador.c

clean:
	rm filter const window spawn