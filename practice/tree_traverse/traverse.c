/*
 * traverse algorithms
 */

#include <stdio.h>
#include <stdlib.h>

// "bst.h" already included from stack.h, so don't include again 
// if included, error message : bst.h:6:16: error: redefinition of ‘struct BiTNode’
#include "stack.h"	/* for stack based implementation of BST traverse */
#include "tbt.h"	/* for Threaded Binary Tree */

/* traverse using recursion */
void pre_order(BiTree T)
{
	if (T != NULL) {
		visit_bst(T);
		pre_order(T->lchild);
		pre_order(T->rchild);
	}
}

void in_order(BiTree T)
{
	if (T != NULL) {
		in_order(T->lchild);
		visit_bst(T);
		in_order(T->rchild);
	}
}

void post_order(BiTree T)
{
	if (T != NULL) {
		post_order(T->lchild);
		post_order(T->rchild);
		visit_bst(T);
	}
}

/* traverse using stack structure */
void pre_order_2(BiTree T)
{
	/* can initialize a stack first, then create a pointer to that */
	// a_stack s;
	// init_stack(&s);
	// a_stack *stack = &s;
	/* same as above, initialize, then create pointer */
	// a_stack s = { .top = -1 };
	// a_stack *stack = &s;
	/* Or, use malloc to allocate a memory size of struct 
	 * where malloc's return value is the pointer to stack struct */
	a_stack *stack = malloc(sizeof(a_stack));
	init_stack(stack);
	BiTree p = T;

	while (p || !stack_empty(stack)) {
		if (p) {
			push(stack, p);
			visit_bst(p);
			p = p->lchild;
		}
		else {
			pop(stack, &p);
			p = p->rchild;
		}
	}
}

void in_order_2(BiTree T)
{
	a_stack *stack = malloc(sizeof(a_stack));
	init_stack(stack);
	BiTree p = T;	/* traverse pointer */

	while (p || !stack_empty(stack)) {
		if (p) {
			push(stack, p);
			p = p->lchild;
		}
		else {
			pop(stack, &p);
			visit_bst(p);
			p = p->rchild;
		}
	}
}

void post_order_2(BiTree T)
{
	a_stack *stack = malloc(sizeof(a_stack));
	init_stack(stack);
	BiTree p = T;
	BiTree r = NULL;	/* pointer to check */

	while (p || !stack_empty(stack)) {
		if (p) {
			push(stack, p);
			p = p->lchild;
		}
		else {
			get_top(stack, &p);	/* if rchild hasn't been visited, don't need to pop */
			if (p->rchild && r != p->rchild) 
				p = p->rchild;	/* next loop will push this into stack */
			else {
				pop(stack, &p);
				visit_bst(p);
				r = p;
				p = NULL;	
			}
		}
	}
}

/* can give the right output, but will destroy original tree structure */
void post_order_destory(BiTree T)
{
	a_stack *stack = malloc(sizeof(a_stack));
	init_stack(stack);
	BiTree p = T;

	while (p || !stack_empty(stack)) {
		if (p) {
			push(stack, p);
			p = p->lchild;
		}
		else {
			pop(stack, &p);
			if (p->rchild) {	/* if has right child, push itself and rchild */
				push(stack, p);
				BiTree temp = p->rchild;
				p->rchild = NULL;	/* this destory original tree! */
				p = temp;
			}
			else {
				visit_bst(p);
				p = NULL;	/* set p to NULL */
			}
		}
	}
}

/*
 * Threaded Binary Tree in order traverse
 */
void in_order_thread(ThreadTree T)
{
	ThreadNode *p = malloc(sizeof(ThreadNode));
	for (p = first_node(T); p != NULL; p = next_node(p)) {
		visit_thread(p);
	}
}

int main(int argc, char *argv[])
{
	/* initialize toy trees */

	BiTree root = malloc(sizeof(BiTNode));
	bst_toy(root);

	BiTree root_complete = malloc(sizeof(BiTNode));
	bst_toy_complete(root_complete);

	ThreadTree root_thread = malloc(sizeof(ThreadNode));
	thread_toy(root_thread);

	printf("stack based post order traverse of complete tree\n");
	post_order_2(root_complete);
	printf("\n");
	printf("recursive in order traverse of tree\n");
	in_order(root);
	printf("\n");
	printf("recursive in order traverse of threaded tree\n");
	in_order_thread(root_thread);
	printf("\n");
	// post_order(root);
	// printf("\n");
	// post_order_2(root);
	// printf("\n");

	return 0;
}
