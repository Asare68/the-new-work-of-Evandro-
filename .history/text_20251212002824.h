#ifndef texto_h
#define texto_h

typedef void* Texto;
typedef void* Estilo;

/*
    Arquivo .h relacionado a forma de um texto, com funcoes de get, set e calculo de area
*/

// FUNCOES DE ESTILO //

/// @brief Cria e retorna o estilo que sera inserido em um texto
/// @param family Familia da fonte
/// @param weight Weight da fonte
/// @param size Tamanho da fonte
/// @return Retorna um ponteiro para o estilo
Estilo criar_estilo(char *family, char *weight, char *size);

/// @brief Pega a familia da fonte do texto
/// @param ts O estilo
/// @return Retorna a familia da fonte
char* getFAMILY(Estilo ts);

/// @brief Pega o weight da fonte do texto
/// @param ts O estilo
/// @return Retorna o weight da fonte
char* getWEIGHT(Estilo ts);

/// @brief Pega o tamanho da fonte do texto
/// @param ts O estilo
/// @return Retorna o tamanho da fonte
char* getSIZE(Estilo ts);

/// @brief Define a familia da fonte do texto
/// @param ts O estilo
/// @param family A familia da fonte
void setFAMILY(Estilo ts, char*family);

/// @brief Define o weight da fonte do texto
/// @param ts O estilo
/// @param weight O weight da fonte
void setWEIGHT(Estilo ts, char* weight);

/// @brief Define o tamanho da fonte do texto
/// @param ts O estilo
/// @param size O tamanho da fonte
void setSIZE(Estilo ts, char* size);

/// @brief Libera a memoria do estilo
/// @param ts O estilo
void freeEstilo(Estilo ts);

// FUNCOES DE TEXTO //

/// @brief Cria um texto com os valores dos parametros especificados
/// @param i Valor do identificador do texto
/// @param x Valor da coordenada x da ancora do texto 
/// @param y Valor da coordenada y da ancora do texto
/// @param corb Valor hexadecimal da cor da borda do texto
/// @param corp Valor hexaddecimal da cor do preenchimento de texto
/// @param a Valor que indica a posicao da ancora do texto, sendo i = inicio, m= meio e f = fim
/// @param txto Array de caracteres que compoe o texto
/// @return Retorna
Texto criar_texto(int i, double x, double y, char* corb,char* corp, char a, char* txto);

/// @brief Pega o valor do identificador do texto t
/// @param t O texto que tera o identificadro lido
/// @return Retorna o valor do identificador do texto
int getItexto(Texto t);

/// @brief Pega o valor da coordenada x da ancora do texto t
/// @param t O texto no qual tera a coordenada x da ancora lida
/// @return Retorna o valor da coordenada x da ancora do texto
double getXtexto(Texto t);

/// @brief Pega o valor da coordenada y da ancora do texto t
/// @param t O texto que tera a coordenada y da ancora lida
/// @return Retorna o valor da coordenada y da ancora do texto
double getYtexto(Texto t);

/// @brief Pega o valor hexadecimal da cor do texto t
/// @param t O texto que tera a cor lida
/// @return Retorna um array de caracteres com o valor hexadecimal da cor de borda do texto
char* getCORBtexto(Texto t);

/// @brief Pega o valor hexadecimal da cor complementar do texto t
/// @param t O texto que tera a cor complementar lida
/// @return Retorna um array de caracteres com o valor hexadecimal da cor complementar do texto
char* getCORPtexto(Texto t);

/// @brief Pega o valor que indica a posicao da ancora do texto
/// @param t O texto no qual tera a posicao da ancora lida
/// @return Retorna o valor que indica a posicao da ancora do texto
char getAtexto(Texto t);

/// @brief Pega o array de caracteres que compoe o texto
/// @param t O texto no qual o array de caracteres sera lido
/// @return Retorna o array de caracteres que compoe o texto
char* getTXTOtexto(Texto t);

/// @brief Pega a quantidade de caracteres contida no texto t
/// @param t O texto que tera seu tamanho lido
/// @return Retorna a quantidade de caracteres do texto
int getTAMANHOtexto(Texto t);

/// @brief Define o valor do identificador do texto t
/// @param t O texto que tera seu identificador definido
/// @param i O valor do identificadro do texto
void setItexto(Texto t, int i);

/// @brief Define o valor da coordenada x da ancora do texto t
/// @param t O texto que tera sua coordeada x definida
/// @param x O valor da coordenada x da ancora do texto
void setXtexto(Texto t, double x);

/// @brief Define o valor da coordenada y da ancora do texto t
/// @param t O texto que tera sua coordenada y da ancora lida
/// @param y O valor da coordenada y da ancora do texto
void setYtexto(Texto t, double y);

/// @brief Define o valor hexadecimal da cor do texto t
/// @param t O texto no qual tera sua cor definida
/// @param cor O valor hexadecimal da cor de borda do texto
void setCORBtexto(Texto t, char* corb);

/// @brief Define o valor hexadecimal da cor complementar do texto t
/// @param t O texto no qual tera sua cor complementar lida
/// @param corcompl O valor da cor complementar do texto
void setCORPtexto(Texto t, char* corp);

/// @brief Define a posicao da ancora do texto t
/// @param t O texto no qual tera a posicao de sua ancora definida
/// @param a O caracter que informa a posicao da ancora do texto
void setAtexto(Texto t, char a);

/// @brief Define a mensagem contida no texto t
/// @param t O texto que tera sua mensagem definida
/// @param txto O array de caracteres que compoe a mensagem
void setTXTOtexto(Texto t, char* txto);

/// @brief Calcula e retorna a area do texto t
/// @param t O texto que tera sua area calculada
/// @param tamanho A quantia de caracteres presentes no texto t
/// @return Retorna a area do texto t
double calcula_area_texto(Texto t);

/// @brief Libera a memoria da cor de borda do texto
/// @param t O texto
void freeCorbTexto(Texto t);

/// @brief Libera a memoria da cor de preenchimento do texto
/// @param t O texto
void freeCorpTexto(Texto t);

/// @brief Libera a memoria do texto da forma texto
/// @param t A forma texto
void freeTXTOtexto(Texto t);

#endif