GCC_OPTIONS=-Wall -pedantic -I ../include
GL_OPTIONS=-framework OpenGL -framework GLUT 
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


.cpp: 
	g++ -ggdb $@.cpp includes/initShader.o kixor/objLoader.o kixor/obj_parser.o kixor/list.o kixor/string_extra.o objects/object.o $(OPTIONS) -o $@  

clean:
	rm main

