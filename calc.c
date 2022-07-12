#include <stdio.h>
#include <stdlib.h>

enum sym_id{plus = 1000, minus = 1001, mult = 1002, divid = 1003, equal = 1003};

struct num{
	long data;
	int num;
	struct num *next;
};


struct num* add_to_list(int data)
{
	static struct num *tmp, *first, *last = NULL;
	static int id = 1;
	tmp = malloc(sizeof(struct num));
	tmp->data = data;
	tmp->num = id;
	tmp->next = NULL;
	if (last){
		last->next = tmp;
		last = last->next;
	} else {
		first = last = tmp;
	}
	id++;
	return first;
}

void delete_zero_and_def_id(struct num *first)
{
	struct num **pcur;
	pcur = &first;
	while(*pcur) {
		switch((*pcur)->data){
		case 0:
			struct num *tmp = *pcur;
			*pcur = (*pcur)->next;			/* deletes zero's from input */
			free(tmp);				
			break;
		case '=':
			(*pcur)->num = equal;				/* adds 999 to identify char */
			pcur = &(*pcur)->next;
			break;
		case '+':
			(*pcur)->num = plus;
			pcur = &(*pcur)->next;
			break;
		case '-':
			(*pcur)->num = minus;
			pcur = &(*pcur)->next;
			break;
		case '/':
			(*pcur)->num = divid;
			pcur = &(*pcur)->next;
			break;
		case '*':
			(*pcur)->num = mult;
			pcur = &(*pcur)->next;
			break;
		default:
			pcur = &(*pcur)->next;
		}
	}
}

int check_op(int c)
{
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '=')){
		return 1;
	} else {
		return 0;
	}
}


long do_math(long f_op, long s_op, int sym)
{
	long result;
	switch (sym) {
	case plus:
		result = f_op + s_op;
		break;
	case minus:
		result = f_op - s_op;
		break;
	case mult:
		result = f_op * s_op;
		break;
	case divid:
		result = f_op/s_op;
		break;
	}	
	return result;
}

int check_list(struct num *first)
{
	int counter = 0;
	struct num *f;
	f = first;
	while(f){
		counter++;
		f = f->next;
	}
	if ((counter/2) == 0){
		return 1;
	} else 
		return 0;
}

long analyze_list(struct num *first)
{
	int check;
	long first_op;
	long second_op;
	long result = 0;
	check = check_list(first);
	if (check){
		printf("Error! Wrong input.\n");
		exit(1);
	}
	while(first->num != equal) {
		first_op = first->data;  /* first number */
		if (first->next->next == NULL){		
			break;
		}
		second_op = first->next->next->data; /* second number */
		result = do_math(first_op, second_op, first->next->num);
		if (first->next->next->next == NULL){
			first->data = result;
			break;
		} else {
			first = first->next->next;
			first->data = result;
		}
	}
	return first->data;
}


int main()
{
	struct num *first = NULL;
	int c = 0;
	long res = 0;
	long result = 0;
	while ((c = getchar()) != EOF){
		if ((c == '\n') || (check_op(c))){
			if (check_op(c)){
				res = c;		/* in case that c is char, we don't use convertation */
			}
			first = add_to_list(res);
			res = 0;
			c = '\0';
		}
		res = res * 10 + (c - 48); /* convert c in number */
		if (res == -48){
			res = 0;
		}
	}
	delete_zero_and_def_id(first);
	result = analyze_list(first);
	printf("%lu\n", result);
	return 0;
}


