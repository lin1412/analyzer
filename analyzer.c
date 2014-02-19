#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lex(void);
void left();
void right();
void foundToken();
void foundInt();

int S();
int SS();
int A();
int AA();
int B();
int BB(); 
int D();
int DD();
int E();
int F();

char *token = "";
int integer = 0;

int main(){
	
	int c;
	while( (c = getchar()) != EOF ){
		ungetc(c, stdin);

		lex();
		int i = S();

		if(i >= 1){
			printf(" --> %d (TRUE)\n", i);
		}
		else{
			printf(" --> %d (FALSE)\n", i);
		}
	}

	return 0;
}


void lex(void){
	int c = getchar();

	if ( c >= 48 && c <= 57 ){
		token = "Int";
		integer = c - 48;
	}

	else if(c == '|'){
		token = "||";
		getchar();
	}
	else if(c == '&'){
		token = "&&";
		getchar();
	}
	else if(c == '='){
		token = "==";
		getchar();
	}
	else if(c == '!'){
		if( getchar() == '='){
			token = "!=";
		}
		else{
			token = "!";
			fseek(stdin, ftell(stdin)-1, SEEK_SET);
		}
	}
	else if(c == '>'){
		if( getchar() == '='){
			token = ">=";
		}
		else{
			token = ">";
			fseek(stdin, ftell(stdin)-1, SEEK_SET);
		}
	}
	else if(c == '<'){
		if( getchar() == '='){
			token = "<=";
		}
		else{
			token = "<";
			fseek(stdin, ftell(stdin)-1, SEEK_SET);
		}

	}
	else if(c == '('){
		token = "(";
	}
	else if(c == ')'){
		token = ")";
	}

	else if(c == '\n'){
		token = "\n";
	}
	
}

//helpers for print
void left(){
	printf("(");
}

void right(){
	printf(")");
}

void foundToken(){
	printf("%s", token);
}

void foundInt(){
	printf("%d", integer);
}


//grammer
int S(){
	return SS(A());
}
int SS(int v){
	int st = v;
	int val = 0;

	if(strcmp(token,"||") == 0){
		foundToken();
		lex();
		int temp = A();
		val = SS((st|| temp));
	}
	else{
		val = st;
	}
	return val;
}
int A(){
	return AA(B());
}
int AA(int v){
	int st = v;
	int val = 0;
	if(strcmp(token,"&&") == 0){
		foundToken();
		lex();
		int temp = B();
		val = AA(st && temp);
	}
	else{
		val = st;
	}
	return val;
}
int B(){
	return BB(D());
}
int BB(int v){
	int st = v;
	int val = 0;
	if(strcmp(token,"==") == 0){
		foundToken();
		lex();
		val = BB(st == D());
	}
	else if(strcmp(token,"!=") == 0){
		foundToken();
		lex();
		val = BB(st != D());
	}
	else{
		val = st;
	}
	return val;
	
}
int D(){
	return DD(E());
}
int DD(int v){
	int st = v;
	int val = 0;
	if(strcmp(token,">") == 0){
		foundToken();
		lex();
		val = DD(st > E());
	}
	else if(strcmp(token,"<") == 0){
		foundToken();
		lex();
		val = DD(st < E());
	}
	else if(strcmp(token,">=") == 0){
		foundToken();
		lex();
		val = DD(st >= E());
	}
	else if(strcmp(token,"<=") == 0){
		foundToken();
		lex();
		val = DD(st <= E());
	}
	else{
		val = st;
	}
	return val;
	
}
int E(){
	int val = 0;
	if(strcmp(token,"!") == 0){
		foundToken();
		lex();
		val = !E();
	}
	else{
		val = F();
	}
	return val;
}
int F(){
	int val = 0;
	if(strcmp(token,"(") == 0){
		left();
		lex();
		val = S();
		right();
		lex();
	}
	else if (strcmp(token,"Int") == 0){
		foundInt();
		lex();
		val = integer;
	}
	return val;
}