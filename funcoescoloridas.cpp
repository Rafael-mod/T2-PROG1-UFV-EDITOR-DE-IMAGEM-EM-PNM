#include <iostream>
#include <cmath>
#include "funcoes.h"
using namespace std;

void escurecer(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]){
	int fator, valor;
	cout << "Qual o fator de escurecimento(1-100)?\n";
	cin >> fator;
	
	for(int i=0;i<altura;i++)
		for(int j=0;j<largura;j++) 
			for(int k=0;k<3;k++){
				valor = (int)imagem_colorida[i][j][k];
				valor -= fator;
				if (valor < 0)									
					valor = 0;
				imagem_colorida[i][j][k] = (unsigned char)valor; //imagens coloridas;
			}
}

void negativo(int altura, int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]){
	int valor,negativo; 
	
	for(int i=0; i < altura; i++)
		for(int j=0; j<largura; j++)
			for(int k=0; k<3;k++) {
				valor = (int)imagem_colorida[i][j][k];
				negativo  = abs(valor - 255);
				imagem_colorida[i][j][k] = (unsigned char)negativo;
			}
}

void clarear(int altura, int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]){
	int fator, valor;
	cout << "Qual o fator de clareamento?(1/100)" << endl;
	cin >> fator;
		
	for(int i=0; i < altura; i++)
		for(int j=0; j<largura; j++)
			for(int k=0; k<3;k++){
				valor = (int)imagem_colorida[i][j][k];
				valor += fator;
				if(valor > 255)
					valor = 255;
					
				imagem_colorida[i][j][k] = (unsigned char)valor;
			}
}

void espelhar(int altura, int largura,  unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]){
	
	unsigned char aux;
	
	for(int i=0; i < altura; i++)
		for(int j=0, t=largura-1; j<(largura/2); j++, t--)
			for(int k = 0; k<3;k++)	{ 
				aux = imagem_colorida[i][j][k];
				imagem_colorida[i][j][k] = imagem_colorida[i][t][k];
				imagem_colorida[i][t][k] = aux;
		}
}

void filtrosobel(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagemCopia[][MAXLARGURA][DIMENSAO]){
	int aux,somax, somay;
	somax=0, somay=0;
	int Gx[3][3] = {{1,0,-1},{2,0,-2},{1,0,-1}},
		Gy[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
	
	// ***CÓPIA DA MATRIZ IMAGEM ***//
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			for(int k=0; k <3; k++)
				imagemCopia[i][j][k] = imagem_colorida[i][j][k];
			
			
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			for(int k=0; k<3;k++){
			
				if(i>0 && j > 0)			 	somax += Gx[0][0]*(int)imagemCopia[i-1][j-1][k];
				if(i>0)						 	somax += Gx[0][1]*(int)imagemCopia[i-1][j][k];
				if(i>0 && j<largura-1)			somax += Gx[0][2]*(int)imagemCopia[i-1][j+1][k];
				if(j>0)						 	somax += Gx[1][0]*(int)imagemCopia[i][j-1][k];
												somax += Gx[1][1]*(int)imagemCopia[i][j][k];
				if(j<largura-1)				 	somax += Gx[1][2]*(int)imagemCopia[i][j+1][k];
				if(i<altura-1 && j>0)		 	somax += Gx[2][0]*(int)imagemCopia[i+1][j-1][k];
				if(i<altura-1)				 	somax += Gx[2][1]*(int)imagemCopia[i+1][j][k];
				if(i<altura-1 && j<largura-1)	somax += Gx[2][2]*(int)imagemCopia[i+1][j+1][k];
				
				if(i>0 && j > 0)				somay += Gy[0][0]*(int)imagemCopia[i-1][j-1][k]; 
				if(i>0)							somay += Gy[0][1]*(int)imagemCopia[i-1][j][k]; 
				if(i>0 && j<largura-1)			somay += Gy[0][2]*(int)imagemCopia[i-1][j+1][k];
				if(j>0)							somay += Gy[1][0]*(int)imagemCopia[i][j-1][k];
												somay += Gy[1][1]*(int)imagemCopia[i][j][k];
				if(j<largura-1)					somay += Gy[1][2]*(int)imagemCopia[i][j+1][k];
				if(i<altura-1 && j>0)			somay += Gy[2][0]*(int)imagemCopia[i+1][j-1][k];
				if(i<altura-1)					somay += Gy[2][1]*(int)imagemCopia[i+1][j][k];
				if(i<altura-1 && j<largura-1)	somay += Gy[2][2]*(int)imagemCopia[i+1][j+1][k];
				
				int Gp = sqrt((somax*somax) + (somay*somay));
				if(Gp > 255)
					Gp = 255;
				else if(Gp < 0)
					Gp = 0;
				
				imagem_colorida[i][j][k] = (unsigned char)Gp;
				somay = 0, somax = 0;
			}		
}

void filtrogaussiano(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagemCopia[][MAXLARGURA][DIMENSAO]){
	int soma = 0;
	int matrizG[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
	
	// ***CÓPIA DA MATRIZ IMAGEM ***//
	for(int i=0; i < altura;i++)
		for(int j=0; j < largura;j++)
			for(int k=0; k<3;k++)
				imagemCopia[i][j][k] = imagem_colorida[i][j][k];
			
			
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			for(int k=0;k<3;k++){
				
				if(i>0 && j > 0)			 	soma += matrizG[0][0]*(int)imagemCopia[i-1][j-1][k];
				if(i>0)						 	soma += matrizG[0][1]*(int)imagemCopia[i-1][j][k];
				if(i>0 && j<largura-1)			soma += matrizG[0][2]*(int)imagemCopia[i-1][j+1][k];
				if(j>0)						 	soma += matrizG[1][0]*(int)imagemCopia[i][j-1][k];
												soma += matrizG[1][1]*(int)imagemCopia[i][j][k];
				if(j<largura-1)				 	soma += matrizG[1][2]*(int)imagemCopia[i][j+1][k];
				if(i<altura-1 && j>0)		 	soma += matrizG[2][0]*(int)imagemCopia[i+1][j-1][k];
				if(i<altura-1)				 	soma += matrizG[2][1]*(int)imagemCopia[i+1][j][k];
				if(i<altura-1 && j<largura-1)	soma += matrizG[2][2]*(int)imagemCopia[i+1][j+1][k];
				
				
				int novopixel = soma/16;
				if(novopixel > 255)
					novopixel = 255;
				else if(novopixel < 0)
					novopixel = 0;
				
				imagem_colorida[i][j][k] = (unsigned char)novopixel;
				soma = 0;
			}		
}


void mascaradenitidez(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagemCopia[][MAXLARGURA][DIMENSAO]){
	float aux,fator;
	cout << "Qual o fator de nitidez?(0.0 - 5.0)\n";
	cin >> fator;
		
	// ***CÓPIA DA MATRIZ IMAGEM ***//
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			for(int k=0;k<3; k++)
				imagemCopia[i][j][k] = imagem_colorida[i][j][k];
			
	filtrogaussiano(altura,largura, imagemCopia, imagem_colorida);
		
	for(int i =0;i< altura;i++)
		for(int j=0;j<largura;j++)
			for(int k=0;k<3;k++){
				aux = (float)imagem_colorida[i][j][k] + (((float)imagem_colorida[i][j][k] - (float)imagemCopia[i][j][k])*fator);
				
				if(aux > 255)
					aux = 255;
				else if(aux < 0)
					aux = 0;
				
				imagem_colorida[i][j][k] = (unsigned char)aux;
			}

}

void rgbtocinza(int altura, int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagem[][MAXLARGURA]){
	// vou utilizar a equação para monitores modernos que calcula a intensidade da luminosidade(para transformar o rgb em um pixel preto e cinza);
	// Y = 0.2126*Red + 0.7152*Green + 0.0722*Blue
	float somaY=0;
	for(int i=0; i<altura; i++)
		for(int j=0;j<largura;j++){
			for(int k=0; k<3;k++){
				if(k==0)
					somaY += (float)imagem_colorida[i][j][k] * 0.2126;
				else if(k==1)
					somaY += (float)imagem_colorida[i][j][k] * 0.7152;
				else
					somaY += (float)imagem_colorida[i][j][k] * 0.0722;
			}
			
			if(somaY > 255)
				somaY = 255;
			else if(somaY < 0)
				somaY = 0;
				
			imagem[i][j] = (unsigned char)somaY;
			somaY=0;	
		}
	
	
	
}

void pseudocor_raiox(int altura, int largura, unsigned char imagem[][MAXLARGURA], unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]){
	int aux;
	
	rgbtocinza(altura,largura, imagem_colorida, imagem);
	
	for(int i =0;i< altura;i++)
		for(int j=0;j<largura;j++){
				aux = (int) imagem[i][j];
				
				if(aux < 15){
					imagem_colorida[i][j][0] =  aux;
					imagem_colorida[i][j][1] = aux;
					imagem_colorida[i][j][2] = aux;
				}
				else if(aux <=85){
					imagem_colorida[i][j][0] = aux*3;
					imagem_colorida[i][j][1] = 0;
					imagem_colorida[i][j][2] = 0;
				}
				else if(aux <= 170){
					imagem_colorida[i][j][0] = 255;
					imagem_colorida[i][j][1] = (aux-85)*3;
					imagem_colorida[i][j][2] = 0;
				}
				else if(aux <= 255){
					imagem_colorida[i][j][0] =  255;
					imagem_colorida[i][j][1] = 255;
					imagem_colorida[i][j][2] = (aux-170)*3;
				}

		}
	
}

void pseudocor_topografia(int altura, int largura, unsigned char imagem[][MAXLARGURA], unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]){
	int aux;
	
	rgbtocinza(altura,largura, imagem_colorida, imagem);
	
	for(int i =0;i< altura;i++)
		for(int j=0;j<largura;j++){
				aux = (int) imagem[i][j];
				
				if(aux <= 30){
					imagem_colorida[i][j][0] =  20 + aux;
					imagem_colorida[i][j][1] = 70 + (aux * 2.0);
					imagem_colorida[i][j][2] = 140 + (aux * 2.0);
				}
				else if(aux <= 70){
					imagem_colorida[i][j][0] = 50 + ((aux - 30) * 1.5);
					imagem_colorida[i][j][1] =140 + ((aux - 30) * 1.0);
					imagem_colorida[i][j][2] = 60;
				}
				else if(aux <= 140){
					imagem_colorida[i][j][0] =110 + ((aux - 70) * 1.3);
					imagem_colorida[i][j][1] = 180 + ((aux - 70) * 0.1);
					imagem_colorida[i][j][2] = 60 + ((aux - 70) * 0.4);
				}
				else if(aux <= 210){
					imagem_colorida[i][j][0] =  201 - ((aux - 140) * 0.7);
					imagem_colorida[i][j][1] = 187 - ((aux - 140) * 1.2);
					imagem_colorida[i][j][2] = 88 - ((aux - 140) * 0.6);
				}
				else if(aux <= 255){
					imagem_colorida[i][j][0] = 152 - ((aux - 210) * 1.2);
					imagem_colorida[i][j][1] = 103 - ((aux - 210) * 1.1);
					imagem_colorida[i][j][2] = 46 - ((aux - 210) * 0.5);
						
				}

		}
	
}

