#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>


typedef struct {
	int a;
	int b;
} my_struct;


void* mythread(void* arg)
{
	my_struct* l_var = (my_struct*)arg;
	printf("My struct contains: a - %d , b - %d\n", l_var->a, l_var->b);
	
	my_struct* new_str = malloc(sizeof(my_struct));
	new_str->a = l_var->a * 2;
	new_str->b = l_var->b * 2;
	return new_str;
}

int main()
{
	my_struct var = { 20, -1 };
	
	pthread_t p1;
	int rc1 = pthread_create(&p1, NULL, mythread, &var);
	assert(rc1 == 0);
	
	my_struct* str;
	rc1 = pthread_join(p1, &str);
	assert(rc1 == 0);
	
	printf("We get from return: a - %d , b - %d\n", str->a, str->b);
	printf("main end\n");
	free(str);
	return 0;
}	