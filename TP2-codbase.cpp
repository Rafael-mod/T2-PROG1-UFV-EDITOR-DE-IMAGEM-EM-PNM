// INF110 - Trabalho pratico 2
//
// programa para ler, modificar e gravar uma imagem no formato PNM
//
// Autores: Andre Gustavo dos Santos			(criado em 16/06/14)
//          Andre Gustavo dos Santos			(modificado em 22/05/18)
//					Andre Gustavo dos Santos			(modificado em 13/09/21)
//					Andre Gustavo dos Santos			(modificado em 6/05/26)

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "funcoes.h"
#include "funcoescoloridas.h"

const int MAXALTURA  = 500;				//tamanho maximo aceito (pode ser alterado)
const int MAXLARGURA = 500;

using namespace std;

int main() {
	unsigned char imagem[MAXALTURA][MAXLARGURA]; //a imagem  em tons de cinza
	unsigned char imagem_colorida[MAXALTURA][MAXLARGURA][3];	//a imagem colorida
	int largura, altura;						//dimensoes da imagem
	char tipo[4];								//tipo da imagem
	string nome_imagem;							// nome da nova imagem
	ifstream arqentrada;						//arquivo que contem a imagem original
	ofstream arqsaida;							//arquivo que contera a imagem modificada
	char comentario[200], c;				//auxiliares
	int i, j,k, valor, escolha;								//auxiliares

//*** LEITURA DA IMAGEM ***//
//esta parte le a imagem de um arquivo; voce pode deixar para olhar isso depois
//e iniciar a olhar o codigo a partir da linha 75 que de fato le os dados;
//a diferenca e' que le do arquivo (arqentrada) em vez de ler com cin

	//*** Abertura do arquivo ***//
	arqentrada.open("imagem.pnm",ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir arquivo imagem.pnm" << endl;
		return 0;
	}
//***************************//


//*** Leitura do cabecalho ***//
	arqentrada >> tipo;	//Le o tipo de arquivo
	arqentrada.get();		//Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza\n";
	}
	else if (strcmp(tipo,"P3")==0) {
		cout << "Imagem colorida\n";
	}
	else if (strcmp(tipo,"P1")==0) {
		cout << "Imagem preto e branco\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P4")==0 || strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}

	while((c = arqentrada.get()) == '#')	//Enquanto for comentario
		arqentrada.getline(comentario,200);	//Le e descarta a linha "inteira"

	arqentrada.putback(c);	//Devolve o caractere lido para a entrada, pois como
													//nao era comentario, era o primeiro digito da largura

	arqentrada >> largura >> altura;	//Le as dimensoes da imagem, numero de pixels da horizontal e da vertical
	cout << "Tamanho: " << largura << " x " << altura << endl;
	if (largura > MAXLARGURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXLARGURA << " pixels de largura.\n";
		arqentrada.close();
		return 0;
	}
	if (altura > MAXALTURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXALTURA << " pixels de altura.\n";
		arqentrada.close();
		return 0;
	}

	arqentrada >> valor;	//Valor maximo do pixel (temos que ler, mas nao sera usado, assumimos 255)
//****************************//


//*** Leitura dos pixels da imagem ***//

	if (strcmp(tipo,"P2")==0) {
		for(i=0;i<altura;i++)
			for(j=0;j<largura;j++) {
				arqentrada >> valor;
				imagem[i][j] = (unsigned char)valor;	//guarda no formato unsigned char// imagens tons de cinza
			}
	}
	else if (strcmp(tipo,"P3")==0) {
		for(i=0;i<altura;i++)
			for(j=0;j<largura;j++) 
				for(k=0;k<3;k++){
					arqentrada >> valor;
					imagem_colorida[i][j][k] = (unsigned char)valor; //imagens coloridas;
				}
	}
//************************************//

	arqentrada.close();  //Fecha arquivo apos a leitura

//*** FIM DA LEITURA DA IMAGEM ***//


//*** TRATAMENTO DA IMAGEM ***//
//inicialmente sera nesta parte do codigo que voce vai trabalhar

	if (strcmp(tipo,"P2")==0){
		cout << "Oque deseja fazer?\n";
		cout << "1 - Escurecer\n";
		cout << "2 - Clarear\n";
		cout << "3 - Negativo\n";
		cout << "4 - Espelhar\n";
		cout << "5 - Filtro de Sobel\n";
		cout << "6 - Desfocagem Gaussiana\n";
		cout << "7 - Mascara de Nitidez\n";
		cin >> escolha;
		
		if(escolha == 1){
			int fator;
			cout << "Qual o fator de escurecimento (1-100)? ";
			cin >> fator;

			//*** Escurece a imagem ***//
			for(i=0;i<altura;i++)
				for(j=0;j<largura;j++) {
					valor = (int)imagem[i][j];			//pega o valor do pixel
					valor -= fator;									//escurece o pixel
					if (valor < 0)									//se der negativo
						valor = 0;										//  deixa preto
					imagem[i][j] = (unsigned char)valor;	//modifica o pixel
				}
		}
		else if(escolha == 2){
			clarear(altura,largura, imagem);
		}
		else if(escolha == 3){
			negativo(altura,largura,imagem);
		}
		else if(escolha == 4){
			espelhar(altura,largura,imagem);
		}
		else if(escolha == 5){
			filtrosobel(altura,largura,imagem);
		}
		else if(escolha == 6){
			filtrogaussiano(altura,largura,imagem);
		}
		else if(escolha == 7){
			mascaradenitidez(altura,largura,imagem);
		}
	}
	else if (strcmp(tipo,"P3")==0){
		cout << "Oque deseja fazer?\n";
		cout << "1 - Escurecer\n";
		cout << "2 - Clarear\n";
		cout << "3 - Negativo\n";
		cout << "4 - Espelhar\n";
		cout << "5 - Filtro de Sobel\n";
		cout << "6 - Desfocagem Gaussiana\n";
		cin >> escolha;
		
		if(escolha == 1){
			escurecer(altura,largura,imagem_colorida);
		}
		else if(escolha == 2){
			clarear(altura,largura,imagem_colorida);
		}
		else if(escolha == 3){
			negativo(altura, largura,imagem_colorida);
		}
	}
    //*************************//
//*** FIM DO TRATAMENTO DA IMAGEM ***//

//*** GRAVACAO DA IMAGEM ***//
//esta parte grava a imagem em um arquivo; voce pode deixar para entender isso depois
//a diferenca e' que escreve no arquivo (arqsaida) em vez de escrever com cout

	//*** Grava a nova imagem ***//
	
	cout << "Escolha o nome da nova imagem:\nobs: Sem espaços\n";
	cin >> nome_imagem;
	arqsaida.open( nome_imagem+ ".pnm",ios::out);	//Abre arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar novaimagem.pnm\n";
		return 0;
	}
	
	if (strcmp(tipo,"P2")==0){
		arqsaida << tipo << endl;							//tipo
		arqsaida << "# TP2-INF110, by AGS\n";	//comentario
		arqsaida << largura << " " << altura;	//dimensoes
		arqsaida << " " << 255 << endl;				//maior valor
		for(i=0;i<altura;i++)
			for(j=0;j<largura;j++)
				arqsaida << (int)imagem[i][j] << endl;	//pixels

		arqsaida.close();		//fecha o arquivo
	}
	else if (strcmp(tipo,"P3")==0){
		arqsaida << tipo << endl;						
		arqsaida << "# TP2-INF110, by AGS\n";	
		arqsaida << largura << " " << altura;	
		arqsaida << " " << 255 << endl;				
		for(i=0;i<altura;i++)
			for(j=0;j<largura;j++)
				for(k=0;k<3;k++)
				arqsaida << (int)imagem_colorida[i][j][k] << endl;

		arqsaida.close();		//fecha o arquivo
	}
	
	//***************************//
	cout << "Imagem gerada!\n" ;
//*** FIM DA GRAVACAO DA IMAGEM ***//

	return 0;
}
