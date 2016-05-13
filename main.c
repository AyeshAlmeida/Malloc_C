#include <stdio.h>
#include "malloc_new.h"

int main(){
	
	int *a = (int*)MyMalloc(100);	
	printf("a : %p\n",a);
	int *b = (int*)MyMalloc(100);	
	printf("b : %p\n",b);
	int *c = (int*)MyMalloc(100);
	printf("%p\n",c);
	int *d = (int*)MyMalloc(100);
	printf("%p\n",d);
	int *e = (int*)MyMalloc(100);
	printf("%p\n",e);
	int *f = (int*)MyMalloc(100);
	printf("%p\n",f);
	MyFree(a);
	int *g = (int*)MyMalloc(100);
	printf("%p\n",g);
	MyFree(b);
	int *r = (int*)MyMalloc(200);	
	printf("%p\n",r);
	return 0;
}
