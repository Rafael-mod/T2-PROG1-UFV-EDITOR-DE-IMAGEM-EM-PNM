#include <iostream>
#include <cmath>
using namespace std;

void escurecer(int altura,int largura, unsigned char imagem_colorida[][500][3]){
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

void negativo(int altura, int largura, unsigned char imagem_colorida[][500][3]){
	int valor,negativo; 
	
	for(int i=0; i < altura; i++)
		for(int j=0; j<largura; j++)
			for(int k=0; k<3;k++) {
				valor = (int)imagem_colorida[i][j][k];
				negativo  = abs(valor - 255);
				imagem_colorida[i][j][k] = (unsigned char)negativo;
			}
}

void clarear(int altura, int largura, unsigned char imagem_colorida[][500][3]){
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
