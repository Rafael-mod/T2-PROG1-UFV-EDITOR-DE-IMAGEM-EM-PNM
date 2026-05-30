#include <iostream>
#include <cmath>
#include "funcoescinzas.h"

using namespace std;


// 1. ESCURECER //
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
					valor = 0;   // Trava o valor no menor valor do pixel
				imagem_colorida[i][j][k] = (unsigned char)valor;
			}
}

// 2. NEGATIVO //
void negativo(int altura, int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]){
	int valor,negativo; 
	
	for(int i=0; i < altura; i++)
		for(int j=0; j<largura; j++)
			for(int k=0; k<3;k++) {
				valor = (int)imagem_colorida[i][j][k];
				negativo  = 255 - valor;
				imagem_colorida[i][j][k] = (unsigned char)negativo;
			}
}


// 3. CLAREAR //
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
					valor = 255;  // Trava o valor no máximo de 255(valor máximo do pixel)
					
				imagem_colorida[i][j][k] = (unsigned char)valor;
			}
}

// 4. ESPELHAR //
void espelhar(int altura, int largura,  unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]){
	unsigned char aux;
	
	for(int i=0; i < altura; i++)
		for(int j=0, t=largura-1; j<(largura/2); j++, t--)
			for(int k = 0; k<3;k++)	{ 
				aux = imagem_colorida[i][j][k]; 	//Troca os valores do pixel do primeiro com o ultimo em cada "dimensão" da matriz
				imagem_colorida[i][j][k] = imagem_colorida[i][t][k];
				imagem_colorida[i][t][k] = aux;
		}
}

// 5. FILTRO DE SOBEL //
void filtrosobel(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagemCopia[][MAXLARGURA][DIMENSAO]){
	int aux,somax, somay;
	somax=0, somay=0;
	
	//MATRIZES DO OPERADOR DE SOBEL
	int Gx[3][3] = {{1,0,-1},{2,0,-2},{1,0,-1}},
		Gy[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
	
	//COPIA A MATRIZ ORIGINAL PARA NÃO ALTERAR OS PIXELS NO CÁLCULO
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			for(int k=0; k <3; k++)
				imagemCopia[i][j][k] = imagem_colorida[i][j][k];
			
			
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			for(int k=0; k<3;k++){
				
				//EIXO X
				if(i>0 && j > 0)			 	somax += Gx[0][0]*(int)imagemCopia[i-1][j-1][k];
				if(i>0)						 	somax += Gx[0][1]*(int)imagemCopia[i-1][j][k];
				if(i>0 && j<largura-1)			somax += Gx[0][2]*(int)imagemCopia[i-1][j+1][k];
				if(j>0)						 	somax += Gx[1][0]*(int)imagemCopia[i][j-1][k];
												somax += Gx[1][1]*(int)imagemCopia[i][j][k];
				if(j<largura-1)				 	somax += Gx[1][2]*(int)imagemCopia[i][j+1][k];
				if(i<altura-1 && j>0)		 	somax += Gx[2][0]*(int)imagemCopia[i+1][j-1][k];
				if(i<altura-1)				 	somax += Gx[2][1]*(int)imagemCopia[i+1][j][k];
				if(i<altura-1 && j<largura-1)	somax += Gx[2][2]*(int)imagemCopia[i+1][j+1][k];
				
				//EIXO Y
				if(i>0 && j > 0)				somay += Gy[0][0]*(int)imagemCopia[i-1][j-1][k]; 
				if(i>0)							somay += Gy[0][1]*(int)imagemCopia[i-1][j][k]; 
				if(i>0 && j<largura-1)			somay += Gy[0][2]*(int)imagemCopia[i-1][j+1][k];
				if(j>0)							somay += Gy[1][0]*(int)imagemCopia[i][j-1][k];
												somay += Gy[1][1]*(int)imagemCopia[i][j][k];
				if(j<largura-1)					somay += Gy[1][2]*(int)imagemCopia[i][j+1][k];
				if(i<altura-1 && j>0)			somay += Gy[2][0]*(int)imagemCopia[i+1][j-1][k];
				if(i<altura-1)					somay += Gy[2][1]*(int)imagemCopia[i+1][j][k];
				if(i<altura-1 && j<largura-1)	somay += Gy[2][2]*(int)imagemCopia[i+1][j+1][k];
				
				//CALCULA A FORMULA DO FILTRO
				int Gp = sqrt((somax*somax) + (somay*somay));
				
				// TRAVA OS VALORES PARA O MENOR E MAIOR VALOR DO PIXEL
				if(Gp > 255)
					Gp = 255;
				else if(Gp < 0)
					Gp = 0;
				
				imagem_colorida[i][j][k] = (unsigned char)Gp;
				somay = 0, somax = 0; //Zera para o próximo pixel
			}		
}

// 6. FILTRO GAUSSIANO(DESFOQUE) //
void filtrogaussiano(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagemCopia[][MAXLARGURA][DIMENSAO]){
	int soma = 0;
	
	//MATRIZ DO OPERADOR GAUSSIANO
	int matrizG[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
	
	//COPIA A MATRIZ IMAGEM PARA NÃO ALTERAR O VALOR DOS PIXEIS ORIGINAIS
	for(int i=0; i < altura;i++)
		for(int j=0; j < largura;j++)
			for(int k=0; k<3;k++)
				imagemCopia[i][j][k] = imagem_colorida[i][j][k];
			
	//APLICAÇÃO DO FILTRO
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			for(int k=0;k<3;k++){
				
				if(i>0 && j > 0)			 	soma += matrizG[0][0]*(int)imagemCopia[i-1][j-1][k];
				if(i>0)						 	soma += matrizG[0][1]*(int)imagemCopia[i-1][j][k];
				if(i>0 && j<largura-1)			soma += matrizG[0][2]*(int)imagemCopia[i-1][j+1][k];
				if(j>0)						 	soma += matrizG[1][0]*(int)imagemCopia[i][j-1][k];
												soma += matrizG[1][1]*(int)imagemCopia[i][j][k]; // Valor central
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

// 7. MASCARA DE NITIDEZ //
void mascaradenitidez(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagemCopia[][MAXLARGURA][DIMENSAO]){
	float aux,fator;
	
	cout << "Qual o fator de nitidez?(0.0 - 5.0)\n";
	cin >> fator;
		
	//CRIA UMA CÓPIA DA MATRIZ IMAGEM
	for(int i=0; i < altura; i++)
		for(int j=0; j < largura; j++)
			for(int k=0;k<3; k++)
				imagemCopia[i][j][k] = imagem_colorida[i][j][k];
				
	//APLICA O FILTRO DE DESFOQUE NA IMAGEM COPIADA
	filtrogaussiano(altura,largura, imagemCopia, imagem_colorida);
	
	//APLICA O FILTRO 
	//Calculo da nitidez: Original + (Original - Borrada) * fator
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

// 8. COLORIDA PARA TONS DE CINZA //
void rgbtocinza(int altura, int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagem[][MAXLARGURA]){
	// Estou utilizando a equação para monitores modernos que calcula a intensidade da luminosidade
	// Y = 0.2126*Red + 0.7152*Green + 0.0722*Blue
	float somaY=0;
	
	for(int i=0; i<altura; i++)
		for(int j=0;j<largura;j++){
			// Aqui não é necessário o for para K, posso acessar os canais RGB diretamente;
			somaY += (float)imagem_colorida[i][j][0] * 0.2126;
			somaY += (float)imagem_colorida[i][j][1] * 0.7152;
			somaY += (float)imagem_colorida[i][j][2] * 0.0722;
			
			if(somaY > 255)
				somaY = 255;
			else if(somaY < 0)
				somaY = 0;
					
			imagem[i][j] = (unsigned char)somaY;
			somaY=0; 	
		}
}

// 9. PSEUDO-COR PARA RAIO-X/RESSONANCIA MAGNETICA (MAPA DE CALOR)//
void pseudocor_raiox(int altura, int largura, unsigned char imagem[][MAXLARGURA], unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]){
	int aux;
	
	// Transformo a imagem em P2, para extrair a luminosidade dos pixeis em tons de cinza
	rgbtocinza(altura,largura, imagem_colorida, imagem);
	
	// RE-TRANSFORMO A IMAGEM P2 EM P3, definindo um mapa de cores(THERMAL) para cada valor de tom de cinza
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

// 10. PSEUDOCOR PARA TOPOGRAFIA //
void pseudocor_topografia(int altura, int largura, unsigned char imagem[][MAXLARGURA], unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]){
	int aux;
	
	// Trago a imagem P3, para P2, extraindo  o mapa de elevação, em tons de cinza.
	rgbtocinza(altura,largura, imagem_colorida, imagem);
	
	// RE-TRANSFORMO A IMAGEM P2 EM P3, definindo um mapa de cores(escolhido por mim) para cada valor de tom de cinza
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

