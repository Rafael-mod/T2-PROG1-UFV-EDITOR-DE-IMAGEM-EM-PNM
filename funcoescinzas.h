
// CONSTANTES //
const int MAXALTURA  = 3000;			
const int MAXLARGURA = 3000;
const int DIMENSAO = 3;

// CHAMADAS 
void clarear(int altura, int largura, unsigned char imagem[][MAXLARGURA]);
void negativo(int altura, int largura, unsigned char imagem[][MAXLARGURA]);
void espelhar(int altura, int largura, unsigned char imagem[][MAXLARGURA]);

void filtrosobel(int altura,int largura, unsigned char imagem[][MAXLARGURA], unsigned char imagemCopia[][MAXLARGURA]);
void filtrogaussiano(int altura,int largura, unsigned char imagem[][MAXLARGURA], unsigned char imagemCopia[][MAXLARGURA]);
void mascaradenitidez(int altura,int largura, unsigned char imagem[][MAXLARGURA], unsigned char imagemCopia[][MAXLARGURA]);

