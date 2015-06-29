#include <stdio.h>
#include <stdlib.h>

struct node {
	struct node* next;
	void* content;
};

struct node* init(void* content) {
	struct node* list;
	list = (struct node*)malloc(sizeof(list));
	list->content = content;
	list->next = NULL;
	return list;
}

int size(struct node* list) {
	int i = 0;
	if(list) {
		for(i=1; list->next; i++) {
			list = list->next;
		}
	}
	return i;
}

void push(void* content, struct node* list) {
	printf("push: %s (size=%d)\n", content, size(list));
	while(list->next) {
		list = list->next;
	}

	struct node* node;
	node = init(content);
	list->next = node;
}

struct node* pull(struct node** list) {
	struct node* node = *list;
	*list = node->next;
	return node;
}

int main() {
	struct node* list;
	// Strings of push only live in stack - so they get removed if function is 
	//finished, use malloc to crate them on heap, same as the linkedlist.
	printf("init: foo (size=0)\n");
	list = init("foo");
	push("bar", list);
	push("baz", list);
	
	printf("pull: %s (size=%d)\n", pull(&list)->content, size(list));
	
	push("bla", list);
	push("blub", list);
	
	printf("pull: %s (size=%d)\n", pull(&list)->content, size(list));
	printf("pull: %s (size=%d)\n", pull(&list)->content, size(list));
	printf("pull: %s (size=%d)\n", pull(&list)->content, size(list));
	
	push("lorem", list);
	push("ipsum", list);
	push("dolor", list);
	
	printf("pull: %s (size=%d)\n", pull(&list)->content, size(list));

	push("sit", list);
	push("amet", list);

	int i;
	while(i = size(list)) {
		printf("pull: %s (size=%d)\n", pull(&list)->content, i);
	}

	printf("end (size=%d)", size(list));
	return 0;
}

