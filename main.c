#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

// Cr�ation de la struture "rationnel"
struct rationnel{
  int num; // num�rateur
  int den; // d�nominateur
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

// fonction permettant de cr�er un rationnel
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

  printf("         � Num�rateur = ");
  if (scanf(" %d", &result.num) != 1) {
    printf("Mauvaise entr�e.\n"); // stop le programme si une entr�e est erron�e
    exit(EXIT_FAILURE);
  }

  printf("         � D�nominateur = ");
  if (scanf(" %d", &result.den) != 1) {
    printf("Mauvaise entr�e.\n"); // stop le programme si une entr�e est erron�e
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

// fonction permettant de renvoyer le rationnel �lev� � une certain exposant
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

// Cr�ation de la structure polynome
struct polynome{
int degre; // degr� du polynome
Rationnel* poly; // les coefficients du polynome
};
typedef struct polynome Polynome;

// fonction permettant de cr�er un polynome
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
  printf("      � Degr� du polynome : ");
  if (scanf(" %d", &degre) != 1) { // demande le d�gr� du polynome
    printf("Mauvaise entr�e."); // stop le progreamme si on entre une information erron�e
    exit(EXIT_FAILURE);
  }

  Polynome result = CreatePoly(degre);

  printf("      ��ͻ\n");
  for (int i = 0; i < degre + 1; i++) {
    printf("         �����������������\n");
    printf("         � Degr� : %d\n", i);
    printf("         �����������������\n");
    result.poly[i] = LireRationnel(); // demande un rationnel pour le coefficient d'indice i
  }
  printf("      ��ͼ\n");

  return result;
}

// fonction permettant d'afficher un polynome dans la console et d'une belle mani�re
void EcriturePolynome(Polynome p){
  bool began = false;
  printf("   � R�sultat : ");
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

// fonction renvoyant une copie d'un polynome pris en param�tre
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

// fonction renvoyant l'�valuation d'un polynome en un point donn�
Rationnel PolynomeEnX(Polynome p, Rationnel x){
  Rationnel result = CreateRationnel(0,1);

  for (int i = 0; i < p.degre + 1; i++) {
    result = SommeRationnel(result, ProduitRationnel(p.poly[i], PuissanceRationnel(x,i)));
  }

  return result;
}

// fonction renvoyant la d�riv� d'un polynome
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

// fonction permettant d'�x�cuter le free() sur le tableau des coefficients d'un polynome
void freePoly(Polynome p){
  free(p.poly);
}

// ... bah c'est le main quoi :)
void main(){
    char wannaContinue = 'y';

    printf("����������������������������������������������������������������������������������ͻ\n");
    printf("���������������������������������������������������������������������������������ͻ�\n");
    printf("��  �����ۻ �ۻ������ۻ��ۻ   �ۻ�ۻ   �ۻ������ۻ��ۻ   �ۻ�ۻ   �ۻ������ۻ�ۻ  ��\n");
    printf("��  ������ۻ�ۺ������ͼ���ۻ  �ۺ�ۺ   �ۺ������ͼ���ۻ  �ۺ�ۺ   �ۺ������ͼ�ۺ  ��\n");
    printf("��  ������ɼ�ۺ����ۻ  ����ۻ �ۺ�ۺ   �ۺ����ۻ  ����ۻ �ۺ�ۺ   �ۺ����ۻ  �ۺ  ��\n");
    printf("��  ������ۻ�ۺ����ͼ  �ۺ��ۻ�ۺ��ۻ ��ɼ����ͼ  �ۺ��ۻ�ۺ�ۺ   �ۺ����ͼ  �ͼ  ��\n");
    printf("��  ������ɼ�ۺ������ۻ�ۺ ����ۺ �����ɼ ������ۻ�ۺ ����ۺ�������ɼ������ۻ�ۻ  ��\n");
    printf("��  �����ͼ �ͼ������ͼ�ͼ  ���ͼ  ���ͼ  ������ͼ�ͼ  ���ͼ �����ͼ ������ͼ�ͼ  ��\n");
    printf("���������������������������������������������������������������������������������ͼ�\n");
    printf("����������������������������������������������������������������������������������ͼ\n");

    while (wannaContinue == 'y'){
      char choix;
      Polynome ope1, ope2, result;
      Rationnel ope3, resultRationnel;


      printf("��������������������������������������������ͻ\n");
      printf("� + : Somme de polynomes                     �\n");
      printf("� * : Produit de polynomes                   �\n");
      printf("� x : Evaluation de polynome en un point     �\n");
      printf("� D : D�riv� d'un polynome                   �\n");
      printf("��������������������������������������������ͼ\n");

      /*
      printf("--------------------------------------------\n");
      printf("| + : Somme de polynomes                   |\n");
      printf("| * : Produit de polynomes                 |\n");
      printf("| x : Evaluation de polynome en un point   |\n");
      printf("| D : Dérivé d'un polynome                 |\n");
      printf("--------------------------------------------\n");*/
      printf("   �\n");
      printf("   � Choisissez une op�ration : ");
      scanf(" %c", &choix);
      printf("   �\n");

      while (!(choix == '+' || choix == '*' || choix == 'x' || choix == 'D')) {
        printf("   ������������������������������������ͻ\n");
        printf("   �       Erreur : Mauvais choix       �\n");
        printf("   ������������������������������������ͼ\n");
        printf("   �\n");
        printf("   � Choisissez une op�ration : ");
        scanf(" %c", &choix);
        printf("   �\n");
      }

      switch (choix) {
        case '+':
          printf("   ������������������������������������ͻ\n");
          printf("   �    Entrez la premi�re op�rande     �\n");
          printf("   ������������������������������������ͼ\n");
          ope1 = LirePolynome();
          printf("   ������������������������������������ͻ\n");
          printf("   �    Entrez la deuxi�me op�rande     �\n");
          printf("   ������������������������������������ͼ\n");
          ope2 = LirePolynome();
          printf("      �\n");
          printf("   ��ͼ\n");
          result = SommePolynome(ope1,ope2);
          EcriturePolynome(result);
          freePoly(result);
          freePoly(ope1);
          freePoly(ope2);
          printf("\n");
          break;

        case '*':
          printf("   ������������������������������������ͻ\n");
          printf("   �    Entrez la premi�re op�rande     �\n");
          printf("   ������������������������������������ͼ\n");
          ope1 = LirePolynome();
          printf("   ������������������������������������ͻ\n");
          printf("   �    Entrez la deuxi�me op�rande     �\n");
          printf("   ������������������������������������ͼ\n");
          ope2 = LirePolynome();
          printf("   ��ͼ\n");
          result = ProduitPolynome(ope1,ope2);
          EcriturePolynome(result);
          freePoly(result);
          freePoly(ope1);
          freePoly(ope2);
          printf("\n");
          break;

        case 'x':
          printf("   ������������������������������������ͻ\n");
          printf("   �       Entrez le polynome f(x)      �\n");
          printf("   ������������������������������������ͼ\n");
          ope1 = LirePolynome();
          printf("   ������������������������������������ͻ\n");
          printf("   �        Entrez le rationnel x       �\n");
          printf("   ������������������������������������ͼ\n");
          ope3 = LireRationnel();
          printf("   �����ͼ\n");
          printf("   � R�sultat : ");
          resultRationnel = PolynomeEnX(ope1,ope3);
          EcritureRationnel(resultRationnel);
          freePoly(ope1);
          printf("\n");
          break;

        case 'D':
          printf("   ������������������������������������ͻ\n");
          printf("   �         Entrez le polynome         �\n");
          printf("   ������������������������������������ͼ\n");
          ope1 = LirePolynome();
          printf("   ��ͼ\n");
          result = DerivePolynome(ope1);
          EcriturePolynome(result);
          freePoly(result);
          freePoly(ope1);
          printf("\n");
          break;
      }

      printf("   �������������������������������������������\n");
      printf("   � Souhaitez-vous continuer ? (y = Oui) : ");
      scanf(" %c", &wannaContinue);
      if (&wannaContinue == "y") {
        printf("   �������������������������������������������\n");
      }
      printf("   �\n");
    }

    printf("   �\n");
    printf("�����������������������������������������������ͻ\n");
    printf("�  Fin du programme, merci de l'avoir utilis�!  �\n");
    printf("�����������������������������������������������ͼ\n");
}

// commentaire secret : nous esp�rons que vous aimez le style du programme !
