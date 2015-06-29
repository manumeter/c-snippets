helloworld: src/helloworld.c
	gcc src/helloworld.c -o helloworld

pingpong: src/pingpong.c
	gcc -lpthread src/pingpong.c -o pingpong

linkedlist: src/linkedlist.c
	gcc src/linkedlist.c -o linkedlist
