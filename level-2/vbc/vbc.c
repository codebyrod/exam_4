#include <stdio.h>
#include <stdlib.h>
// MODIFIED: use <stdlib.h> for calloc/free instead of <malloc.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(node n)
{
	// MODIFIED: use sizeof(*ret) instead of sizeof(n)
    node *ret = calloc(1, sizeof(*ret));  
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

// ADDED: declarations of recursive parsing functions
static node *parse_add(char **s);
static node *parse_multi(char **s);
static node *parse_factor (char **s);

// ADDED: parsing of a factor (digit or parenthesis)
static node *parse_factor(char **s)
{
	node *ret;
    if (isdigit((unsigned char)**s))
	{
        ret = new_node((node){
			.type = VAL, 
			.val = **s - '0', 
			.l = NULL, 
			.r = NULL
		});
        (*s)++;
        return ret;
    }
    if (accept(s, '(')) 
	{
        ret = parse_add(s);
        if (!ret)
            return NULL;
		//expect obrigatoriamente precisa ter o caracter
		//se tiver ele consome ele caracter e retorna 1
		//negamos para ele só entrar caso não ache
        if (!expect(s, ')')) 
		{
			//destroi as árvores com o nó
            destroy_tree(ret);
			//retorna null
            return NULL;
        }
		//errei aqui, não fiz esse retorno
        return ret;
    }
    unexpected(**s);
	//errei aqui, coloquei exit(1)
    return NULL;
}

// ADDED: parsing of a term (multiplications)
// This function is a COPY-PASTE of parse_expr_r,
// you just have to REPLACE '+' by '*'
// and REPLACE .type = ADD by .type = MULTI
// and REPLACE parse_term by parse_factor
static node *parse_multi(char **s)
{
	node *left;
	node *right;
	node *tmp;

    left = parse_factor(s);
    if (!left)
        return NULL;
    while (accept(s, '*')) {
        right = parse_factor(s);
        if (!right) 
		{
            destroy_tree(left);
            return NULL;
        }
        tmp = new_node((node){
			.type = MULTI,
			.val = 0,
			.l = left, 
			.r = right });
        left = tmp;
        if (!left)
            return NULL;
    }
    return left;
}

// ADDED: parsing of an expression (additions)
static node *parse_add(char **s)
{
	node *right;
	node *left;
	node *tmp;

	//errei em colocar right
    left = parse_multi(s);
    if (!left)
        return NULL;
    while (accept(s, '+')) 
	{
		//troquei right e left
        right = parse_multi(s);
        if (!right) {
            destroy_tree(left);
            return NULL;
        }
        tmp = new_node((node){
			.type = ADD,
			.val = 0,
			.l = left,
			.r = right 
		});
        left = tmp;
        if (!left)
            return NULL;
    }
    return left;
}

// MODIFIED: parse_expr initializes a local pointer and checks the end of the string
node *parse_expr(char *s)
{
    // char *p = s;
	node *ret;
	char c;
    
	ret = parse_add(&s);
	if (!ret)
		return NULL;
	c = *s;
    // if (*p) {                          
    if (c) {                          
        unexpected(c);
        destroy_tree(ret);
        return (NULL);
    }
    return (ret);
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
    return 0;  //MODIFIED: added return to suppress compiler warning
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    node *tree = parse_expr(argv[1]);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    return 0; // MODIFIED: return 0 on success
}
