
void escurecer(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]);
void negativo(int altura, int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]);
void clarear(int altura, int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]);
void espelhar(int altura, int largura,  unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO]);
void filtrosobel(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagemCopia[][MAXLARGURA][DIMENSAO]);
void filtrogaussiano(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagemCopia[][MAXLARGURA][DIMENSAO]);
void mascaradenitidez(int altura,int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagemCopia[][MAXLARGURA][DIMENSAO]);
void rgbtocinza(int altura, int largura, unsigned char imagem_colorida[][MAXLARGURA][DIMENSAO], unsigned char imagem[][MAXLARGURA]);
