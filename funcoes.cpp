#include <iostream>
#include <cmath>
#include "funcoes.h"
using namespace std;

void clarear(int altura, int largura, unsigned char imagem[][MAXLARGURA]){
	int fator, valor;
	cout << "Qual o fator de clareamento?(1/100)" << endl;
	cin >> fator;
		
	for(int i=0; i < altura; i++)
		for(int j=0; j<largura; j++){
			valor = (int)imagem[i][j];
			valor += fator;
			if(valor > 255)
				valor = 255;
				
			imagem[i][j] = (unsigned char)valor;
		}
}

void negativo(int altura, int largura, unsigned char imagem[][MAXLARGURA]){
	int valor,negativo; 
	
	for(int i=0; i < altura; i++)
		for(int j=0; j<largura; j++){
			valor = (int)imagem[i][j];
			negativo  = abs(valor - 255);
			imagem[i][j] = (unsigned char)negativo;
		}
	
}

void espelhar(int altura, int largura, unsigned char imagem[][MAXLARGURA]){
	unsigned char aux;
	
	for(int i=0; i < altura; i++)
		for(int j=0, t=largura-1; j<(largura/2); j++, t--){ // trocar coluna   j=0 com a coluna f=largura, dps j=1 com largura-1? 
			aux = imagem[i][j];
			imagem[i][j] = imagem[i][t];
			imagem[i][t] = aux;
		}
}

void filtrosobel(int altura,int largura, unsigned char imagem[][MAXLARGURA], unsigned char imagemCopia[][MAXLARGURA]){
	int aux,somax, somay;
	somax=0, somay=0;
	int Gx[3][3] = {{1,0,-1},{2,0,-2},{1,0,-1}},
		Gy[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
	
	// ***CÓPIA DA MATRIZ IMAGEM ***//
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			imagemCopia[i][j] = imagem[i][j];
			
			
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++){
			
			if(i>0 && j > 0)			 	somax += Gx[0][0]*(int)imagemCopia[i-1][j-1];
			if(i>0)						 	somax += Gx[0][1]*(int)imagemCopia[i-1][j];
			if(i>0 && j<largura-1)			somax += Gx[0][2]*(int)imagemCopia[i-1][j+1];
			if(j>0)						 	somax += Gx[1][0]*(int)imagemCopia[i][j-1];
											somax += Gx[1][1]*(int)imagemCopia[i][j];
			if(j<largura-1)				 	somax += Gx[1][2]*(int)imagemCopia[i][j+1];
			if(i<altura-1 && j>0)		 	somax += Gx[2][0]*(int)imagemCopia[i+1][j-1];
			if(i<altura-1)				 	somax += Gx[2][1]*(int)imagemCopia[i+1][j];
			if(i<altura-1 && j<largura-1)	somax += Gx[2][2]*(int)imagemCopia[i+1][j+1];
			
			if(i>0 && j > 0)				somay += Gy[0][0]*(int)imagemCopia[i-1][j-1]; 
			if(i>0)							somay += Gy[0][1]*(int)imagemCopia[i-1][j]; 
			if(i>0 && j<largura-1)			somay += Gy[0][2]*(int)imagemCopia[i-1][j+1];
			if(j>0)							somay += Gy[1][0]*(int)imagemCopia[i][j-1];
											somay += Gy[1][1]*(int)imagemCopia[i][j];
			if(j<largura-1)					somay += Gy[1][2]*(int)imagemCopia[i][j+1];
			if(i<altura-1 && j>0)			somay += Gy[2][0]*(int)imagemCopia[i+1][j-1];
			if(i<altura-1)					somay += Gy[2][1]*(int)imagemCopia[i+1][j];
			if(i<altura-1 && j<largura-1)	somay += Gy[2][2]*(int)imagemCopia[i+1][j+1];
			
			int Gp = sqrt((somax*somax) + (somay*somay));
			if(Gp > 255)
				Gp = 255;
			else if(Gp < 0)
				Gp = 0;
			
			imagem[i][j] = (unsigned char)Gp;
			somay = 0, somax = 0;
		}		
}

void filtrogaussiano(int altura,int largura, unsigned char imagem[][MAXLARGURA], unsigned char imagemCopia[][MAXLARGURA]){
	int soma = 0;
	int matrizG[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
	
	// ***CÓPIA DA MATRIZ IMAGEM ***//
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			imagemCopia[i][j] = imagem[i][j];
			
			
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++){
			
			if(i>0 && j > 0)			 	soma += matrizG[0][0]*(int)imagemCopia[i-1][j-1];
			if(i>0)						 	soma += matrizG[0][1]*(int)imagemCopia[i-1][j];
			if(i>0 && j<largura-1)			soma += matrizG[0][2]*(int)imagemCopia[i-1][j+1];
			if(j>0)						 	soma += matrizG[1][0]*(int)imagemCopia[i][j-1];
											soma += matrizG[1][1]*(int)imagemCopia[i][j];
			if(j<largura-1)				 	soma += matrizG[1][2]*(int)imagemCopia[i][j+1];
			if(i<altura-1 && j>0)		 	soma += matrizG[2][0]*(int)imagemCopia[i+1][j-1];
			if(i<altura-1)				 	soma += matrizG[2][1]*(int)imagemCopia[i+1][j];
			if(i<altura-1 && j<largura-1)	soma += matrizG[2][2]*(int)imagemCopia[i+1][j+1];
			
			
			int novopixel = soma/16;
			if(novopixel > 255)
				novopixel = 255;
			else if(novopixel < 0)
				novopixel = 0;
			
			imagem[i][j] = (unsigned char)novopixel;
			soma = 0;
		}		
	
	
}

void mascaradenitidez(int altura,int largura, unsigned char imagem[][MAXLARGURA], unsigned char imagemCopia[][MAXLARGURA]){
	float aux,fator;
	cout << "Qual o fator de nitidez?(0.0 - 5.0)\n";
	cin >> fator;
		
	// ***CÓPIA DA MATRIZ IMAGEM ***//
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			imagemCopia[i][j] = imagem[i][j];
			
			
	filtrogaussiano(altura,largura, imagemCopia, imagem);
	
	
	for(int i =0;i< altura;i++)
		for(int j=0;j<largura;j++){
			aux = (float)imagem[i][j] + (((float)imagem[i][j] - (float)imagemCopia[i][j])*fator);
			
			if(aux > 255)
				aux = 255;
			else if(aux < 0)
				aux = 0;
			
			imagem[i][j] = (unsigned char)aux;
		}
}




