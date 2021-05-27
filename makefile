brainf : BrainFuckCompiler.c
	gcc BrainFuckCompiler.c -o brainf

install : 
	cp brainf /usr/bin/
