TargetDir=bin
Out=basic.bin
Target=$(TargetDir)/$(Out)
CC=gcc
CFlags=-O0 -fno-stack-protector -nostdinc -m32 -march=i386 -mtune=i386
Objs=bin/main.obj bin/die.obj
Linker=ld -m elf_i386
Include=-I../../libs/
AppMaker=../../tools/appmaker/bin/appmaker
MTA32Obj=../../libs/ilib/bin/mta32.obj

$(Target): bin $(Objs)
	$(Linker) -Tsegs.lds -e mta32main --oformat binary -o $(Target) $(MTA32Obj) $(Objs)	\
-L../../libs/ilib/bin -lilib	\
-L../../libs/imagelib/bin -limagelib	\
-L../../libs/dslib/bin -ldslib	\
-L../../libs/mempoollib/bin -lmempoollib
	$(AppMaker) $(Target)

bin:
	-mkdir bin

bin/main.obj: main.c
	$(CC) $(CFlags) -c main.c -o bin/main.obj $(Include)
	$(CC) $(CFlags) -S main.c -o bin/main.s $(Include)

bin/die.obj: die.c die.h
	$(CC) $(CFlags) -c die.c -o bin/die.obj $(Include)

.PHONY:clean

clean:
	-rm -f $(Objs) $(Target)
