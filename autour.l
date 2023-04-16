%{

  #include <stdio.h>
  #include <stdlib.h>
  #include "autour.bison.hpp"
%}

%option yylineno

%%

[0-9]+(\.[0-9]+)?([Ee][+-]?[0-9]+)?   { yylval.dval = atof(yytext); return FLOAT; }
"Soit" {return SOIT; }
"une variable de type" {return UNE_VAR_DE_TYPE; }
"qui prend la valeur" {return VALANT; }
valant {return VALANT; }
main { return MAIN; } 
fonction { return FONCTION;}
entière { return KEYWORD_INT;}
flotante { return KEYWORD_FLOAT;}
"chaîne de caractères" { return KEYWORD_STRING;}
Si {return IF;}
Sinon {return ELSE;}
FinSi {return ENDIF;}
Alors {return THEN;}
Aller {return GOTO;}
Imprimer {return IMPRIMER;}
Récupérer {return RECUPERER;}
"Saisir un nombre dans" {return SAISIR_UN_NOMBRE_DANS;}
Dormir {return DORMIR;}
"est égal à" {return EQ;}
"est supérieur à" {return GT;}
"est supérieur ou égal à" {return GTE;}
"est inférieur à" {return LT;}
"est inférieur ou égal à" {return LTE;}
"est différent de" {return NEQ;}
OU {return OR;}
ET {return AND;}
PAS {return NOT;}
racine {return SQRT;}
"Tant que" {return TANT_QUE;}
"Initialiser l'environnement graphique" {return INITIALISER_GRAPHIQUE;}
"Colorier le pixel" {return COLORIER_PIXEL;}
"avec la couleur" {return AVEC_COULEUR;}
"Mise à jour graphique" {return MISE_A_JOUR_GRAPHIQUE;}
"Procédure" {return PROCEDURE; }
"Appeler" {return APPELER; }
"Pour" {return POUR;}
"allant de" {return ALLANT_DE;}
"à" {return A;}
"{"    {  return '{'; }
"}"    {  return '}'; }
";"    {  return ';'; }
"+"|"plus"    {  return '+';  }
"-"|"moins"    {  return '-'; }
"*"|"fois"    {  return '*'; }
"/"|"divisé par"    {  return '/'; }
"%"|"modulo" {return '%'; }
"="    {  return '='; }
"["   {  return '['; }
"]"   {  return ']'; }
","   {  return ','; }
\(    {  return '('; }
\)    {  return ')'; }
":"    {  return ':'; }
#.* { }

[_a-zA-Z][_a-zA-Z0-9]*  {strcpy(yylval.sval, yytext); return VAR;}

@[_a-z][_a-z0-9]*   {  strcpy( yylval.sval, yytext);
                            return ETIQUETTE; }

\"[^"]*\"  {int len = strlen(yytext); yytext[len-1] = 0; yytext++; strcpy(yylval.sval, yytext); return STRING;}

[ \t]                {   } 
\n|\r  { }
.                    { printf("Lex error %c\n", yytext[0]); return 0;}

%%

int yywrap() {}