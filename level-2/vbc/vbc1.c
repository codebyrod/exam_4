typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   t_node;


//Ela analisa se o primeiro caracter é um dígito
//Se não for um dígito ela vai olhar pra ver se é uma abertura de parenteses
//se or abertura de parenteses
//	consome toda a expressão e retorna o ponteiro do fim da expressão
//

//chamar essa função de parser_par
static node *parse_factor(char **s)
{
    if (isdigit((unsigned char)**s))
	{
        node n = { 
			.type = VAL,
			//**s acessa o caracter e converte o caracter em valor;
			.val = **s - '0',
			//Os dois são nulls pq um numero ainda não tem filhos
			.l = NULL, 
			.r = NULL 
		};

		// avançamos um número na memória da string, 
		// vamos para o próximo caracter
        (*s)++;
        return new_node(n);
    }
	//veriica se o caracter é (
	//caso sim, a função accept vai consumir 
	// o caracter e retornar verdadeiro
    if (accept(s, '(')) 
	{
		//aqui começa a recursividade
		//caso seja um parentese, chama a função anterior novamente
        node *e = parse_expr_r(s);

		//verifica se deu certo
		//caso não, retorna null
        if (!e)
            return NULL;

		//verifica o fechamento dos parênteses
		//se não encontrar o parentese de fechamento
		//destroi a árvore

        if (!expect(s, ')'))
		{
            destroy_tree(e);
            return NULL;
        }
        return e;
    }
    unexpected(**s);
    return NULL;
}

t_node parser_parent(char **s)
{
	//verifica se é digito
	if (isdigit((unsigned char)**s))
	{
		t_node n = {
			.type = VAL,
			.val = **s - '0',
			.r = NULL,
			.l = NULL
		};
		(*s)++;
		return (new_node(n));
	}
	//verifica se é parantese
	if (accept(s, '('))
	{
		node e = parse_expr_r(s);
		if (e)
			return NULL;
		if(!expect(s, ')'))
		{
			destroy_tree(e);
			return NULL;
		}
		return e;
	}
	unexpected(**s);
	return NULL;
}

