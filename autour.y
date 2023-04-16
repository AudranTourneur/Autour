%{
  #define YYERROR_VERBOSE 1

  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>    
  #include <map>    
  #include <string>    
  #include <stack>    
  #include <vector>
  #include <ostream>
  #include <iostream>
  #include <iomanip>

  #include <iostream>
  #include <chrono>
  #include <thread>

  #include "src/init.hpp"

  using namespace std;

  // éléments qui proviennent de l'analyse lexicale
  extern int yylex ();
  extern char* yytext;
  extern FILE *yyin;
  int yyerror(char *s);

  ProgramState ps;
%}

%code requires 
{
    typedef struct adr {
        int jump;
        int jump_if_false;
    } type_adresse;

    typedef struct type_while_adr {
        int while_start;
        int jump_if_false;
    } type_while_adr;
}

%union 
{
    int ival;
    double dval;
    char sval[256];
    type_adresse address;
    type_while_adr while_adr;
}

%token <dval> INT
%token <dval> FLOAT
%token SIN
%token MAIN
%token <sval> VAR
%token FONCTION
%token KEYWORD_INT
%token KEYWORD_FLOAT
%token KEYWORD_STRING
%token SI
%token SINON
%token SOIT
%token UNE_VAR_DE_TYPE
%token VALANT
%token IMPRIMER
%token <sval> STRING
%token RECUPERER
%token DORMIR
%token <address> IF
%token ELSE
%token ENDIF
%token GOTO
%token THEN
%token EQ
%token LT
%token LTE
%token GT
%token GTE
%token NEQ
%token OR
%token AND
%token NOT
%token <sval> ETIQUETTE
%token SQRT
%token SAISIR_UN_NOMBRE_DANS
%token <ival> TANT_QUE
%token INITIALISER_GRAPHIQUE
%token COLORIER_PIXEL
%token AVEC_COULEUR
%token MISE_A_JOUR_GRAPHIQUE
%token PROCEDURE
%token APPELER
%token MODULO
%token <ival> POUR
%token ALLANT_DE
%token A

%left '+' '-' MODULO
%left '*' '/'
%left EQ LT LTE GT GTE NEQ
%left AND OR

%type <ival> liste

%%
programme :  includes definitions fonctions { printf ("Programme correct!\n"); }
includes :    { }
definitions : INITIALISER_GRAPHIQUE ';' { ps.addInstruction(GRAPHICS_INIT, 0, ""); }
            | { }
fonctions : fonction fonctions { }
            | { }
fonction : PROCEDURE VAR { ps.labels["@@procedure_" + string($2)] = ps.ic; } '{' instructions '}' { ps.addInstruction(RETURN, 0, ""); }
etiquette : ETIQUETTE ':' { printf("got label %s %d\n", $1, ps.ic); ps.labels[$1] = ps.ic; }
            | { }
instructions :  etiquette instruction ';'  instructions {} 
             |  { }
bloc_if: IF '(' expression ')' {$1.jump_if_false = ps.ic;  ps.addInstruction(JUMP_IF_FALSE, 0, "");} 
                '{' instructions '}' {$1.jump = ps.ic; ps.addInstruction(JUMP, 0, ""); ps.allInstructions[$1.jump_if_false]->valueNum = ps.ic;}
                bloc_else { ps.allInstructions[$1.jump]->valueNum = ps.ic; }
bloc_else: ELSE '{' instructions '}' { } 
            | { }
instruction : SOIT VAR VALANT expression {ps.addInstruction(STORE, 0, $2); }
              | bloc_if { }
              | IMPRIMER expression {ps.addInstruction(PRINT, 0, ""); }
              | SAISIR_UN_NOMBRE_DANS VAR {ps.addInstruction(INPUT, 0, $2);}
              | DORMIR FLOAT {ps.addInstruction(SLEEP, $2, "");}
              | GOTO ETIQUETTE {ps.addInstruction(JUMP, 0, $2);}
              | bloc_tant_que { }
              | VAR '[' expression ']' '=' expression { ps.addInstruction(STORE_LIST, 0, $1);  }
              | COLORIER_PIXEL '(' expression ',' expression ')' AVEC_COULEUR '(' expression ',' expression ',' expression ')' { ps.addInstruction(COLOR_PIXEL, 0, ""); }
              | MISE_A_JOUR_GRAPHIQUE { ps.addInstruction(GRAPHICS_UPDATE, 0, ""); }
              | APPELER VAR { ps.addInstruction(CALL, 0, "@@procedure_" + string($2)); }
              | bloc_pour { }
              | { }

bloc_tant_que : TANT_QUE {
    $1 = ps.getUniqueInternalId(); 
    ps.labels["@@while_start_" + to_string($1)] = ps.ic;
} '(' expression ')' {
    ps.addInstruction(JUMP_IF_FALSE, 0, "@@while_end_" + to_string($1));
    } '{' instructions '}' {
        ps.addInstruction(JUMP, 0, "@@while_start_" + to_string($1));
        ps.addInstruction(JUMP, 0, "@@while_end_" + to_string($1)); 
        ps.labels["@@while_end_" + to_string($1)] = ps.ic;
    }

bloc_pour : POUR VAR ALLANT_DE expression {ps.addInstruction(STORE, 0, $2); } A {
     $1 = ps.getUniqueInternalId();
    ps.labels["@@for_start_" + to_string($1)] = ps.ic; 
} expression { 
    ps.addInstruction(LOAD_VARIABLE, 0, $2); 
    ps.addInstruction(CMP_GT, 0, "");
    ps.addInstruction(JUMP_IF_FALSE, 0, "@@for_end_" + to_string($1));
} 
'{' instructions '}' { 
    ps.addInstruction(LOAD_LITERAL, 1, "");
    ps.addInstruction(LOAD_VARIABLE, 0, $2); 
    ps.addInstruction(ADD, 0, "");
    ps.addInstruction(STORE, 0, $2);
    ps.addInstruction(JUMP, 0, "@@for_start_" + to_string($1)); 
    ps.labels["@@for_end_" + to_string($1)] = ps.ic;
}

expression : INT   {ps.addInstruction(LOAD_LITERAL, $1, "");} 
              | FLOAT {ps.addInstruction(LOAD_LITERAL, $1, "");}
              | VAR {ps.addInstruction(LOAD_VARIABLE, 0, $1);}
              | STRING {ps.addInstruction(LOAD_LITERAL, 0, $1);}
              | expression '+' expression {ps.addInstruction(ADD, 0, ""); }
              | expression '-' expression {ps.addInstruction(SUB, 0, ""); }
              | expression '*' expression {ps.addInstruction(MUL, 0, ""); }
              | expression '/' expression {ps.addInstruction(DIV, 0, ""); }
              | expression '%' expression {ps.addInstruction(MOD, 0, ""); }
              | expression EQ expression {ps.addInstruction(CMP_EQ, 0, ""); }
              | expression GT expression {ps.addInstruction(CMP_GT, 0, ""); }
              | expression GTE expression {ps.addInstruction(CMP_GTE, 0, ""); }
              | expression LT expression {ps.addInstruction(CMP_LT, 0, ""); }
              | expression LTE expression {ps.addInstruction(CMP_LTE, 0, ""); }
              | expression NEQ expression {ps.addInstruction(CMP_NEQ, 0, ""); }
              | NOT expression {ps.addInstruction(LOGIC_NOT, 0, ""); }
              | expression AND expression {ps.addInstruction(LOGIC_AND, 0, ""); }
              | expression OR expression {ps.addInstruction(LOGIC_OR, 0, ""); }
              | '-' expression {ps.addInstruction(NEG, 0, ""); }
              | SQRT '(' expression ')' {ps.addInstruction(MATH_SQRT, 0, ""); }
              | '(' expression ')' { }
              | liste { }
              | expression '[' expression ']' {ps.addInstruction(LOAD_LIST_ITEM, 0, ""); printf("LOAD_LIST_ITEM\n");}
liste_expression : expression { ps.encouteredLists.top()++; } 
                  | liste_expression ',' expression { ps.encouteredLists.top()++; } 
                  | { }
liste : '[' { ps.encouteredLists.push(0); } liste_expression ']' { int listSize = ps.encouteredLists.top(); ps.addInstruction(LOAD_LIST, listSize, ""); ps.encouteredLists.pop(); printf("LOAD_LIST %d\n", listSize);  } 
%%

int yyerror(char *s) {					
    printf("%s : %s\n", s, yytext);
}

void printProgram() {
    cout << "Printing program" << endl;
    for (int i = 0; i < ps.allInstructions.size(); i++) {

        // Trouve la lebel qui correspond a l'instruction
        string label = "";
        for (auto it = ps.labels.begin(); it != ps.labels.end(); it++) {
            if (it->second == i) {
                label = it->first;
                break;
            }
        }

        if (label != "") {
            cout << label << ":" << endl;
        }

        // Affichage de l'instruction
        Instruction* instruction = ps.allInstructions[i];
        cout << "    " << i << " " << setw(20) << left << opcodeToString(instruction->type) << "\t\t" << instruction->valueNum << "\t" << instruction->valueStr << endl;
    }
}

int main(int argc, char** argv) {
    printf("AUTOUR ! V0.0\n<================>\n");
    
    if ( argc > 1 )
        yyin = fopen( argv[1], "r" );
    else
        yyin = stdin;

    yyparse();						

    printProgram();
    executeProgram(ps);
    return 0;
}