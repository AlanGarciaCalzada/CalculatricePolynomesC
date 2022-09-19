#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

// Cr‚ation de la struture "rationnel"
struct rationnel{
  int num; // num‚rateur
  int den; // d‚nominateur
};
typedef struct rationnel Rationnel;

// fonction permettant de calculer le PGCD entre deux rationnels
int PGCD(int n, int m){
    if (n==0) {
        return m;
    }
    else if(m==0){
        return n;
    }
    else{
        return PGCD(m, n%m);
    }
}

// fonction permettant de simplifier un rationnel
Rationnel Simplification(Rationnel r){
  int simplification = PGCD(r.num, r.den);

  r.num = r.num/simplification;
  r.den = r.den/simplification;

  return r;
}

// fonction permettant de cr‚er un rationnel
Rationnel CreateRationnel(int num, int den){
  Rationnel result;
  result.num = num;
  if (den == 0) {
    printf("Division par 0."); // stop le programme si il y a une division par 0
    exit(EXIT_FAILURE);
  }
  result.den = den;

  return Simplification(result);
}

// fonction permettant de lire un rationnel depuis la console
Rationnel LireRationnel(){
  Rationnel result;

  printf("         ³ Num‚rateur = ");
  if (scanf(" %d", &result.num) != 1) {
    printf("Mauvaise entr‚e.\n"); // stop le programme si une entr‚e est erron‚e
    exit(EXIT_FAILURE);
  }

  printf("         ³ D‚nominateur = ");
  if (scanf(" %d", &result.den) != 1) {
    printf("Mauvaise entr‚e.\n"); // stop le programme si une entr‚e est erron‚e
    exit(EXIT_FAILURE);
  }

  int simplification = PGCD(result.num, result.den);

  result.num = result.num/simplification;
  result.den = result.den/simplification;

  if (result.num < 0 && result.den < 0) {
    result.num *= -1;
    result.den *= -1;
  }

  return result;
}

// fonction permettant d'afficher un rationnel dans la console
void EcritureRationnel(Rationnel r){
  if (r.den == 1) {
    printf("%d", r.num);
  }
  else{
    printf("(%d/%d)", r.num, r.den);
  }
}

// fonction permettant de renvoyer la somme de deux rationnel
Rationnel SommeRationnel(Rationnel a, Rationnel b){
  Rationnel result;

  result.num = a.num * b.den + a.den * b.num;
  result.den = a.den * b.den;

  return Simplification(result);
}

// fonction permettant de renvoyer le produit de deux rationnel
Rationnel ProduitRationnel(Rationnel a, Rationnel b){
  Rationnel result;
  result.num = a.num * b.num;
  result.den = a.den * b.den;

  return Simplification(result);
}

// fonction permettant de renvoyer le rationnel ‚lev‚ … une certain exposant
Rationnel PuissanceRationnel(Rationnel r, int p){
  Rationnel result = CreateRationnel(1,1);

  for (int i = 0; i < p; i++) {
    result = ProduitRationnel(result,r);
  }

  return result;
}

// fonction permettant de renvoyer le produit d'un rationnel et d'un entier
Rationnel ProduitRationnelInt(Rationnel r, int n){
  return CreateRationnel(r.num * n, r.den);
}

// Cr‚ation de la structure polynome
struct polynome{
int degre; // degr‚ du polynome
Rationnel* poly; // les coefficients du polynome
};
typedef struct polynome Polynome;

// fonction permettant de cr‚er un polynome
Polynome CreatePoly(int degre){
  Polynome result;
  result.poly = malloc((degre + 1) * sizeof(Rationnel));
  result.degre = degre;

  for (int i = 0; i < degre + 1; i++) {
    result.poly[i] = CreateRationnel(0,1);
  }

  return result;
}

// fonction permettant de lire un polynome dans le console
Polynome LirePolynome(){
  int degre;
  printf("      º Degr‚ du polynome : ");
  if (scanf(" %d", &degre) != 1) { // demande le d‚gr‚ du polynome
    printf("Mauvaise entr‚e."); // stop le progreamme si on entre une information erron‚e
    exit(EXIT_FAILURE);
  }

  Polynome result = CreatePoly(degre);

  printf("      ÈÍÍ»\n");
  for (int i = 0; i < degre + 1; i++) {
    printf("         ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    printf("         ³ Degr‚ : %d\n", i);
    printf("         ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
    result.poly[i] = LireRationnel(); // demande un rationnel pour le coefficient d'indice i
  }
  printf("      ÉÍÍ¼\n");

  return result;
}

// fonction permettant d'afficher un polynome dans la console et d'une belle maniŠre
void EcriturePolynome(Polynome p){
  bool began = false;
  printf("   º R‚sultat : ");
  if (0 < p.degre + 1 && p.poly[0].num != 0) {
    began = true;

    if ((p.poly[0].num > 0 && p.poly[0].den > 0) || (p.poly[0].num < 0 && p.poly[0].den < 0)) {
      EcritureRationnel(p.poly[0]);
    }
    else{
      EcritureRationnel(p.poly[0]);
    }
  }

  if (1 < p.degre + 1 && p.poly[1].num != 0) {
    if (!began || !((p.poly[1].num > 0 && p.poly[1].den > 0) || (p.poly[1].num < 0 && p.poly[1].den < 0))) {
      EcritureRationnel(p.poly[1]);
      began = true;
    }
    else if (began) {
      printf("+");
      EcritureRationnel(p.poly[1]);
    }
    else{
      EcritureRationnel(p.poly[1]);
      began = true;
    }

    printf("x");
  }

  for (int i = 2; i < p.degre + 1; i++) {

    if (p.poly[i].num != 0) {

      if (!began || !((p.poly[i].num > 0 && p.poly[i].den > 0) || (p.poly[i].num < 0 && p.poly[i].den < 0))) {
        EcritureRationnel(p.poly[i]);
        began = true;
      }
      else if (began) {
        printf("+");
        EcritureRationnel(p.poly[i]);
      }
      else{
        EcritureRationnel(p.poly[i]);
        began = true;
      }

      printf("x^%d", i);

    }

  }

  if (p.degre == 0 && p.poly[0].num == 0) {
    EcritureRationnel(p.poly[0]);
  }

}

// fonction renvoyant une copie d'un polynome pris en paramŠtre
Polynome CopyPolynome(Polynome p){
  Polynome result = CreatePoly(p.degre);

  for (int i = 0; i < p.degre + 1; i++) {
    result.poly[i] = p.poly[i];
  }

  return result;
}

// fonction renvoyant la somme de deux polynomes
Polynome SommePolynome(Polynome p1, Polynome p2){
  int size;
  Polynome result;

  if (p1.degre > p2.degre) {
    size = p2.degre + 1;
    result = CopyPolynome(p1);
    for (int i = 0; i < size; i++) {
      result.poly[i] = SommeRationnel(p1.poly[i], p2.poly[i]);
    }
  }
  else{
    size = p1.degre + 1;
    result = CopyPolynome(p2);
    for (int i = 0; i < size; i++) {
      result.poly[i] = SommeRationnel(p1.poly[i], p2.poly[i]);
    }
  }

  return result;
}

Polynome ProduitPolynome(Polynome p1, Polynome p2){
  Polynome result = CreatePoly(p1.degre + p2.degre);

  for (int i = 0; i < p1.degre + 1; i++) {
    for (int j = 0; j < p2.degre + 1; j++) {
      result.poly[i+j] = SommeRationnel(result.poly[i+j], ProduitRationnel(p1.poly[i], p2.poly[j]));
    }
  }

  return result;
}

// fonction renvoyant l'‚valuation d'un polynome en un point donn‚
Rationnel PolynomeEnX(Polynome p, Rationnel x){
  Rationnel result = CreateRationnel(0,1);

  for (int i = 0; i < p.degre + 1; i++) {
    result = SommeRationnel(result, ProduitRationnel(p.poly[i], PuissanceRationnel(x,i)));
  }

  return result;
}

// fonction renvoyant la d‚riv‚ d'un polynome
Polynome DerivePolynome(Polynome p){
  if (p.degre == 0) {
      Polynome resultZero = CreatePoly(0);
      resultZero.poly[0] = CreateRationnel(0,1);
      return resultZero;
  }

  Polynome result = CreatePoly(p.degre-1);

  for (int i = 0; i < result.degre + 1; i++) {
    result.poly[i] = ProduitRationnelInt(p.poly[i+1], i+1);
  }

  return result;
}

// fonction permettant d'‚x‚cuter le free() sur le tableau des coefficients d'un polynome
void freePoly(Polynome p){
  free(p.poly);
}

// ... bah c'est le main quoi :)
void main(){
    char wannaContinue = 'y';

    printf("ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
    printf("ºÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»º\n");
    printf("ºº  ÛÛÛÛÛÛ» ÛÛ»ÛÛÛÛÛÛÛ»ÛÛÛ»   ÛÛ»ÛÛ»   ÛÛ»ÛÛÛÛÛÛÛ»ÛÛÛ»   ÛÛ»ÛÛ»   ÛÛ»ÛÛÛÛÛÛÛ»ÛÛ»  ºº\n");
    printf("ºº  ÛÛÉÍÍÛÛ»ÛÛºÛÛÉÍÍÍÍ¼ÛÛÛÛ»  ÛÛºÛÛº   ÛÛºÛÛÉÍÍÍÍ¼ÛÛÛÛ»  ÛÛºÛÛº   ÛÛºÛÛÉÍÍÍÍ¼ÛÛº  ºº\n");
    printf("ºº  ÛÛÛÛÛÛÉ¼ÛÛºÛÛÛÛÛ»  ÛÛÉÛÛ» ÛÛºÛÛº   ÛÛºÛÛÛÛÛ»  ÛÛÉÛÛ» ÛÛºÛÛº   ÛÛºÛÛÛÛÛ»  ÛÛº  ºº\n");
    printf("ºº  ÛÛÉÍÍÛÛ»ÛÛºÛÛÉÍÍ¼  ÛÛºÈÛÛ»ÛÛºÈÛÛ» ÛÛÉ¼ÛÛÉÍÍ¼  ÛÛºÈÛÛ»ÛÛºÛÛº   ÛÛºÛÛÉÍÍ¼  ÈÍ¼  ºº\n");
    printf("ºº  ÛÛÛÛÛÛÉ¼ÛÛºÛÛÛÛÛÛÛ»ÛÛº ÈÛÛÛÛº ÈÛÛÛÛÉ¼ ÛÛÛÛÛÛÛ»ÛÛº ÈÛÛÛÛºÈÛÛÛÛÛÛÉ¼ÛÛÛÛÛÛÛ»ÛÛ»  ºº\n");
    printf("ºº  ÈÍÍÍÍÍ¼ ÈÍ¼ÈÍÍÍÍÍÍ¼ÈÍ¼  ÈÍÍÍ¼  ÈÍÍÍ¼  ÈÍÍÍÍÍÍ¼ÈÍ¼  ÈÍÍÍ¼ ÈÍÍÍÍÍ¼ ÈÍÍÍÍÍÍ¼ÈÍ¼  ºº\n");
    printf("ºÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼º\n");
    printf("ÈÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");

    while (wannaContinue == 'y'){
      char choix;
      Polynome ope1, ope2, result;
      Rationnel ope3, resultRationnel;


      printf("ÉÍÍÊÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
      printf("º + : Somme de polynomes                     º\n");
      printf("º * : Produit de polynomes                   º\n");
      printf("º x : Evaluation de polynome en un point     º\n");
      printf("º D : D‚riv‚ d'un polynome                   º\n");
      printf("ÈÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");

      /*
      printf("--------------------------------------------\n");
      printf("| + : Somme de polynomes                   |\n");
      printf("| * : Produit de polynomes                 |\n");
      printf("| x : Evaluation de polynome en un point   |\n");
      printf("| D : DÃ©rivÃ© d'un polynome                 |\n");
      printf("--------------------------------------------\n");*/
      printf("   º\n");
      printf("   º Choisissez une op‚ration : ");
      scanf(" %c", &choix);
      printf("   º\n");

      while (!(choix == '+' || choix == '*' || choix == 'x' || choix == 'D')) {
        printf("   ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("   º       Erreur : Mauvais choix       º\n");
        printf("   ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        printf("   º\n");
        printf("   º Choisissez une op‚ration : ");
        scanf(" %c", &choix);
        printf("   º\n");
      }

      switch (choix) {
        case '+':
          printf("   ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
          printf("   º    Entrez la premiŠre op‚rande     º\n");
          printf("   ÈÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
          ope1 = LirePolynome();
          printf("   ÉÍÍÊÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
          printf("   º    Entrez la deuxiŠme op‚rande     º\n");
          printf("   ÈÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
          ope2 = LirePolynome();
          printf("      º\n");
          printf("   ÉÍÍ¼\n");
          result = SommePolynome(ope1,ope2);
          EcriturePolynome(result);
          freePoly(result);
          freePoly(ope1);
          freePoly(ope2);
          printf("\n");
          break;

        case '*':
          printf("   ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
          printf("   º    Entrez la premiŠre op‚rande     º\n");
          printf("   ÈÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
          ope1 = LirePolynome();
          printf("   ÉÍÍÊÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
          printf("   º    Entrez la deuxiŠme op‚rande     º\n");
          printf("   ÈÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
          ope2 = LirePolynome();
          printf("   ÉÍÍ¼\n");
          result = ProduitPolynome(ope1,ope2);
          EcriturePolynome(result);
          freePoly(result);
          freePoly(ope1);
          freePoly(ope2);
          printf("\n");
          break;

        case 'x':
          printf("   ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
          printf("   º       Entrez le polynome f(x)      º\n");
          printf("   ÈÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
          ope1 = LirePolynome();
          printf("   ÉÍÍÊÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
          printf("   º        Entrez le rationnel x       º\n");
          printf("   ÈÍÍÍÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
          ope3 = LireRationnel();
          printf("   ÉÍÍÍÍÍ¼\n");
          printf("   º R‚sultat : ");
          resultRationnel = PolynomeEnX(ope1,ope3);
          EcritureRationnel(resultRationnel);
          freePoly(ope1);
          printf("\n");
          break;

        case 'D':
          printf("   ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
          printf("   º         Entrez le polynome         º\n");
          printf("   ÈÍÍËÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
          ope1 = LirePolynome();
          printf("   ÉÍÍ¼\n");
          result = DerivePolynome(ope1);
          EcriturePolynome(result);
          freePoly(result);
          freePoly(ope1);
          printf("\n");
          break;
      }

      printf("   ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\n");
      printf("   º Souhaitez-vous continuer ? (y = Oui) : ");
      scanf(" %c", &wannaContinue);
      if (&wannaContinue == "y") {
        printf("   ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\n");
      }
      printf("   º\n");
    }

    printf("   º\n");
    printf("ÉÍÍÊÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
    printf("º  Fin du programme, merci de l'avoir utilis‚!  º\n");
    printf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
}

// commentaire secret : nous esp‚rons que vous aimez le style du programme !
