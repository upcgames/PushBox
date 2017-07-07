#include<iostream>
#include<conio.h>
#include<Windows.h>
#include <MMSystem.h>

using namespace std;
using namespace System;

int nrandom(int minimo, int maximo){
	Random r;
	return r.Next(minimo, maximo + 1);
}
//--------------------------------------SONIDOS------------------------------

void RisaDuckHunt(int n){
	if (n == 1)PlaySound(TEXT("DuckHunt1.wav"), NULL, SND_ASYNC);
	if (n == 2)PlaySound(TEXT("DuckHunt2.wav"), NULL, SND_ASYNC);
}
void RisaJocker()
{
	int n = nrandom(1, 200);
	if (n<100)PlaySound(TEXT("Guason01.wav"), NULL, SND_ASYNC);
	if (n >= 100)PlaySound(TEXT("Guason02.wav"), NULL, SND_ASYNC);
}
void SonidoGameCoin(){
	int n = nrandom(1, 200);
	if (n<100)PlaySound(TEXT("Gameboy.wav"), NULL, SND_ASYNC);
	if (n >= 100)PlaySound(TEXT("MarioCoin.wav"), NULL, SND_ASYNC);
}
void SonidoPixelmen()
{
	PlaySound(TEXT("Pixelmen.wav"), NULL, SND_ASYNC);
}
void SonidoPacman()
{
	PlaySound(TEXT("WakaWaka.wav"), NULL, SND_ASYNC | SND_LOOP);
}
void SonidoTroll(int modo)
{
	if (modo == 1)PlaySound(TEXT("Sabe.wav"), NULL, SND_ASYNC);
	if (modo == 2)PlaySound(TEXT("Terroristas.wav"), NULL, SND_ASYNC);
	if (modo == 3)PlaySound(TEXT("Despierta.wav"), NULL, SND_ASYNC);
	if (modo == 4)PlaySound(TEXT("Rbr.wav"), NULL, SND_ASYNC);
}
void SonidoMovilSeMueve(int caso = 1)
{
	if (caso == 1)PlaySound(TEXT("movf.wav"), NULL, SND_ASYNC);
	if (caso == 2)PlaySound(TEXT("mov3.wav"), NULL, SND_ASYNC);
}
void SonidoMovilNoSeMueve()
{
	PlaySound(TEXT("mov2.wav"), NULL, SND_ASYNC);
}
void SonidoMaquinaEscribir(int tipo)
{
	if (tipo == 1){ PlaySound(TEXT("TypeWriter1.wav"), NULL, SND_LOOP | SND_ASYNC); }
	if (tipo == 2){ PlaySound(TEXT("TypeWriter2.wav"), NULL, SND_SYNC); }
}
void SonidoCajaHueco()
{
	PlaySound(TEXT("Coin02.wav"), NULL, SND_ASYNC);
}
void SonidoCajaVacio(){
	PlaySound(TEXT("CajayVacio.wav"), NULL, SND_ASYNC);
}
void SonidoEndurecimiento(){
	PlaySound(TEXT("Endurecimiento.wav"), NULL, SND_ASYNC);
}
void SonidoTeletransporte(){
	PlaySound(TEXT("Teletransporte.wav"), NULL, SND_ASYNC);
}
void Musicatiempo(int tipo){
	if (tipo == 1)PlaySound(TEXT("PuedeRe.wav"), NULL, SND_ASYNC);
	if (tipo == 2)PlaySound(TEXT("NoPuedeRe.wav"), NULL, SND_ASYNC);
}
void SonidoAlarma()
{
	PlaySound(TEXT("alert.wav"), NULL, SND_ASYNC | SND_LOOP);
}
void SonidoHurryUp()
{
	PlaySound(TEXT("HurryUp.wav"), NULL, SND_ASYNC);
}
void SonidoSpiderman()
{
	PlaySound(TEXT("Thwip.wav"), NULL, SND_ASYNC);
};
void MusicaMenu(){
	PlaySound(TEXT("Intro.wav"), NULL, SND_LOOP | SND_ASYNC);
}
void MusicaCreditos(){
	PlaySound(TEXT("outro.wav"), NULL, SND_LOOP | SND_ASYNC);
}
void MusicaAparecePortal()
{
	PlaySound(TEXT("DigDugCoin.wav"), NULL, SND_ASYNC);
}
void MusicaDesaparecePortal(){
	PlaySound(TEXT("DesaparecePortal.wav"), NULL, SND_ASYNC);
}
void MusicaMuerte(int opcion = 1)
{
	if (opcion == 1)PlaySound(TEXT("muerte.wav"), NULL, SND_ASYNC);
	if (opcion == 2){
		int n = nrandom(1, 200);
		if (n<100)PlaySound(TEXT("DigDugmuerte.wav"), NULL, SND_ASYNC);
		if (n >= 100)PlaySound(TEXT("MarioDead.wav"), NULL, SND_ASYNC);
	}
}
void MusicaLore(){
	PlaySound(TEXT("LoreMusic.wav"), NULL, SND_ASYNC);
}
void MusicaYouWin(){
	PlaySound(TEXT("MarioWin.wav"), NULL, SND_ASYNC);
}
void MusicaCongratulations(){
	PlaySound(TEXT("YouWinMetal.wav"), NULL, SND_ASYNC);
}
void MusicaGameOver()
{
	PlaySound(TEXT("GameOver.wav"), NULL, SND_ASYNC);
}
void MusicaPausa(){
	PlaySound(TEXT("PausaSound.wav"), NULL, SND_ASYNC);
}
void MusicaDeOutro()
{
	PlaySound(TEXT("Outro.wav"), NULL, SND_ASYNC);
}
void SonidoStop(){
	PlaySound(NULL, NULL, 0);
}

//----------------------------------------------------------------------------------------------------------------

/*-----------------------FUNCIONES CON NOMBRE PROPIO-----------------------------*/
void ir(int x, int y)//lleva el cursor a un punto de la consola.
{
	Console::SetCursorPosition(x, y);
}
void colorfondo(int color)//Pinta el background del caracter donde se encuentra el cursor
{
	switch (color){
	case 1: Console::BackgroundColor = ConsoleColor::White; break;      //1 = Color BLANCO
	case 2: Console::BackgroundColor = ConsoleColor::Red; break;        //2 = Color Rojo
	case 3: Console::BackgroundColor = ConsoleColor::Green; break;      //3 = Color Verde
	case 4: Console::BackgroundColor = ConsoleColor::Blue; break;       //4 = Color Azul
	case 5: Console::BackgroundColor = ConsoleColor::Cyan; break;       //5 = Color Celeste
	case 6: Console::BackgroundColor = ConsoleColor::Magenta; break;    //6 = Color Fuxia
	case 7: Console::BackgroundColor = ConsoleColor::Yellow; break;     //7 = Color Amarillo
	case 8: Console::BackgroundColor = ConsoleColor::Gray; break;       //8 = Color Plomo
	case 9: Console::BackgroundColor = ConsoleColor::Black; break;      //9 = Color NEGRO
	case 10: Console::BackgroundColor = ConsoleColor::DarkRed; break;    //10 = Color Rojo Oscuro
	case 11: Console::BackgroundColor = ConsoleColor::DarkGreen; break;  //11 = Color Verde Oscuro
	case 12: Console::BackgroundColor = ConsoleColor::DarkBlue; break;   //12 = Color Azul Oscuro
	case 13: Console::BackgroundColor = ConsoleColor::DarkCyan; break;   //13 = Color Celeste Oscuro
	case 14: Console::BackgroundColor = ConsoleColor::DarkMagenta; break;//14 = Color Fuxia Oscuro
	case 15: Console::BackgroundColor = ConsoleColor::DarkYellow; break; //15 = Color Amarillo Oscuro
	case 16: Console::BackgroundColor = ConsoleColor::DarkGray; break;   //16 = Color Plomo Oscuro
	}
}
void colorletra(int color)//Pinta el foreground del caracter donde se encuentra el cursor
{
	switch (color){
	case 1: Console::ForegroundColor = ConsoleColor::White; break;      //1 = Color BLANCO
	case 2: Console::ForegroundColor = ConsoleColor::Red; break;        //2 = Color Rojo
	case 3: Console::ForegroundColor = ConsoleColor::Green; break;      //3 = Color Verde
	case 4: Console::ForegroundColor = ConsoleColor::Blue; break;       //4 = Color Azul
	case 5: Console::ForegroundColor = ConsoleColor::Cyan; break;       //5 = Color Celeste
	case 6: Console::ForegroundColor = ConsoleColor::Magenta; break;    //6 = Color Fuxia
	case 7: Console::ForegroundColor = ConsoleColor::Yellow; break;     //7 = Color Amarillo
	case 8: Console::ForegroundColor = ConsoleColor::Gray; break;       //8 = Color Plomo
	case 9: Console::ForegroundColor = ConsoleColor::Black; break;      //9 = Color NEGRO
	case 10: Console::ForegroundColor = ConsoleColor::DarkRed; break;    //10 = Color Rojo Oscuro
	case 11: Console::ForegroundColor = ConsoleColor::DarkGreen; break;  //11 = Color Verde Oscuro
	case 12: Console::ForegroundColor = ConsoleColor::DarkBlue; break;   //12 = Color Azul Oscuro
	case 13: Console::ForegroundColor = ConsoleColor::DarkCyan; break;   //13 = Color Celeste Oscuro
	case 14: Console::ForegroundColor = ConsoleColor::DarkMagenta; break;//14 = Color Fuxia Oscuro
	case 15: Console::ForegroundColor = ConsoleColor::DarkYellow; break; //15 = Color Amarillo Oscuro
	case 16: Console::ForegroundColor = ConsoleColor::DarkGray; break;   //16 = Color Plomo Oscuro
	}
}
void guardarpos(int &x, int &y)//Guarda las coordenadas donde se encuentra el cursor
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	x = csbi.dwCursorPosition.X;
	y = csbi.dwCursorPosition.Y;
}
void SetColor(int ForgC)//Es utilizada unicamente por las funciones fondo**, sirve para asingar color a los strings de dichas funciones. 
{
	WORD wColor = ForgC;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	return;
}
void limpiartecla(int modo)
{
	if (modo == 1 || modo == 3)fflush(stdin);
	if (modo == 2 || modo == 3); FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}
void esperartecla(char teclapasa = 'E')
{
	limpiartecla(3);
	while (1){
		char tecla = _getch();
		tecla = toupper(tecla);
		if (tecla == teclapasa)break;
	}

}
void Escribir(const char*Cadena, int retraso = 0, int sonido = 0){
	int t = strlen(Cadena);
	if (sonido == 1 || sonido == 2 || sonido == 4)SonidoMaquinaEscribir(1);
	for (int i = 0; i <= t - 1; i++){ cout << Cadena[i]; Sleep(retraso); }
	if (sonido == 2 || sonido == 3)SonidoMaquinaEscribir(2);
	if (sonido == 4)SonidoStop();
}
/*---------------------------------------------------------------------------------------------------*/

//---------------------------------------MANEJO DE GRAFICOS Y TEXTO ----------------------------------------------------------------------
void GIF(int **matriz, int filainicio = 0, int filafinal = 34, int columnainicio = 0, int columnafinal = 29, int x = 0, int y = 0, int pintarcero = 1, int colorcero = 16, int retraso = 0, int modo = 78)
{
	int f, c; int cf2, cl2, cc2;

	if (pintarcero == 2){ cf2 = colorcero / 100000; cl2 = (colorcero % 100000) / 1000; cc2 = (colorcero % 1000); }

	if (modo == 78){
		for (f = filainicio; f <= filafinal; f++){
			for (c = columnainicio; c <= columnafinal; c++){
				ir(c + x - columnainicio, f + y - filainicio); if (matriz[f][c]>0){ colorletra(matriz[f][c]); cout << char(219); Sleep(retraso); }
				if (pintarcero == 1 && matriz[f][c] == 0){ colorfondo(colorcero); cout << " "; Sleep(retraso); }
				if (pintarcero == 2 && matriz[f][c] == 0){ colorfondo(cf2); colorletra(cl2); cout << char(cc2); Sleep(retraso); }
			}
		}
	}
	if (modo == 98){
		for (f = filainicio; f <= filafinal; f++){
			for (c = columnafinal; c >= columnainicio; c--){
				ir(c + x, f + y); if (matriz[f][c]>0){ colorletra(matriz[f][c]); cout << char(219); Sleep(retraso); }
				if (pintarcero == 1 && matriz[f][c] == 0){ colorfondo(colorcero); cout << " "; Sleep(retraso); }
				if (pintarcero == 2 && matriz[f][c] == 0){ colorfondo(cf2); colorletra(cl2); cout << char(cc2); Sleep(retraso); }
			}
		}
	}
	if (modo == 12){
		for (f = filafinal; f >= filainicio; f--){
			for (c = columnainicio; c <= columnafinal; c++){
				ir(c + x - columnainicio, f + y - filainicio); if (matriz[f][c]>0){ colorletra(matriz[f][c]); cout << char(219); Sleep(retraso); }
				if (pintarcero == 1 && matriz[f][c] == 0){ colorfondo(colorcero); cout << " "; Sleep(retraso); }
				if (pintarcero == 2 && matriz[f][c] == 0){ colorfondo(cf2); colorletra(cl2); cout << char(cc2); Sleep(retraso); }
			}
		}
	}
	if (modo == 32){
		for (f = filafinal; f >= filainicio; f--){
			for (c = columnafinal; c >= columnainicio; c--){
				ir(c + x - columnainicio, f + y - filainicio); if (matriz[f][c]>0){ colorletra(matriz[f][c]); cout << char(219); Sleep(retraso); }
				if (pintarcero == 1 && matriz[f][c] == 0){ colorfondo(colorcero); cout << " "; Sleep(retraso); }
				if (pintarcero == 2 && matriz[f][c] == 0){ colorfondo(cf2); colorletra(cl2); cout << char(cc2); Sleep(retraso); }
			}
		}
	}
	if (modo == 36){
		for (c = columnafinal; c >= columnainicio; c--){
			for (f = filafinal; f >= filainicio; f--){
				ir(c + x - columnainicio, f + y - filainicio); if (matriz[f][c]>0){ colorletra(matriz[f][c]); cout << char(219); Sleep(retraso); }
				if (pintarcero == 1 && matriz[f][c] == 0){ colorfondo(colorcero); cout << " "; Sleep(retraso); }
				if (pintarcero == 2 && matriz[f][c] == 0){ colorfondo(cf2); colorletra(cl2); cout << char(cc2); Sleep(retraso); }
			}
		}
	}
	if (modo == 96){
		for (c = columnafinal; c >= columnainicio; c--){
			for (f = filainicio; f <= filafinal; f++){
				ir(c + x - columnainicio, f + y - filainicio); if (matriz[f][c]>0){ colorletra(matriz[f][c]); cout << char(219); Sleep(retraso); }
				if (pintarcero == 1 && matriz[f][c] == 0){ colorfondo(colorcero); cout << " "; Sleep(retraso); }
				if (pintarcero == 2 && matriz[f][c] == 0){ colorfondo(cf2); colorletra(cl2); cout << char(cc2); Sleep(retraso); }
			}
		}
	}
	if (modo == 74){
		for (c = columnainicio; c <= columnafinal; c++){
			for (f = filainicio; f <= filafinal; f++){
				ir(c + x - columnainicio, f + y - filainicio); if (matriz[f][c]>0){ colorletra(matriz[f][c]); cout << char(219); Sleep(retraso); }
				if (pintarcero == 1 && matriz[f][c] == 0){ colorfondo(colorcero); cout << " "; Sleep(retraso); }
				if (pintarcero == 2 && matriz[f][c] == 0){ colorfondo(cf2); colorletra(cl2); cout << char(cc2); Sleep(retraso); }
			}
		}
	}
	if (modo == 14){
		for (c = columnainicio; c <= columnafinal; c++){
			for (f = filafinal; f >= filainicio; f--){
				ir(c + x - columnainicio, f + y - filainicio); if (matriz[f][c]>0){ colorletra(matriz[f][c]); cout << char(219); Sleep(retraso); }
				if (pintarcero == 1 && matriz[f][c] == 0){ colorfondo(colorcero); cout << " "; Sleep(retraso); }
				if (pintarcero == 2 && matriz[f][c] == 0){ colorfondo(cf2); colorletra(cl2); cout << char(cc2); Sleep(retraso); }
			}
		}
	}

}
void GIFL(int **matriz, int filainicio, int filafinal, int columnainicio, int columnafinal, int x, int y, int color0, int color1, int color2, int retraso = 0, int modo = 78)
{
	int f, c;

	if (modo == 78){
		for (f = filainicio; f <= filafinal; f++){
			for (c = columnainicio; c <= columnafinal; c++){
				ir(c + x - columnainicio, f + y - filainicio);
				if (color0 != 0 && matriz[f][c] == 0){ colorfondo(color0); cout << " "; Sleep(retraso); }
				if (color1 != 0 && matriz[f][c] == 9){ colorletra(color1); cout << char(219); Sleep(retraso); }
				if (color2 != 0 && matriz[f][c] == 7){ colorletra(color2); cout << char(219); Sleep(retraso); }
			}
		}
	}
	if (modo == 98){
		for (f = filainicio; f <= filafinal; f++){
			for (c = columnafinal; c >= columnainicio; c--){
				ir(c + x - columnainicio, f + y - filainicio);
				if (color0 != 0 && matriz[f][c] == 0){ colorfondo(color0); cout << " "; Sleep(retraso); }
				if (color1 != 0 && matriz[f][c] == 9){ colorletra(color1); cout << char(219); Sleep(retraso); }
				if (color2 != 0 && matriz[f][c] == 7){ colorletra(color2); cout << char(219); Sleep(retraso); }
			}
		}
	}
	if (modo == 12){
		for (f = filafinal; f >= filainicio; f--){
			for (c = columnainicio; c <= columnafinal; c++){
				ir(c + x - columnainicio, f + y - filainicio);
				if (color0 != 0 && matriz[f][c] == 0){ colorfondo(color0); cout << " "; Sleep(retraso); }
				if (color1 != 0 && matriz[f][c] == 9){ colorletra(color1); cout << char(219); Sleep(retraso); }
				if (color2 != 0 && matriz[f][c] == 7){ colorletra(color2); cout << char(219); Sleep(retraso); }
			}
		}
	}
	if (modo == 32){
		for (f = filafinal; f >= filainicio; f--){
			for (c = columnafinal; c >= columnainicio; c--){
				ir(c + x - columnainicio, f + y - filainicio);
				if (color0 != 0 && matriz[f][c] == 0){ colorfondo(color0); cout << " "; Sleep(retraso); }
				if (color1 != 0 && matriz[f][c] == 9){ colorletra(color1); cout << char(219); Sleep(retraso); }
				if (color2 != 0 && matriz[f][c] == 7){ colorletra(color2); cout << char(219); Sleep(retraso); }
			}
		}
	}
	if (modo == 36){
		for (c = columnafinal; c >= columnainicio; c--){
			for (f = filafinal; f >= filainicio; f--){
				ir(c + x - columnainicio, f + y - filainicio);
				if (color0 != 0 && matriz[f][c] == 0){ colorfondo(color0); cout << " "; Sleep(retraso); }
				if (color1 != 0 && matriz[f][c] == 9){ colorletra(color1); cout << char(219); Sleep(retraso); }
				if (color2 != 0 && matriz[f][c] == 7){ colorletra(color2); cout << char(219); Sleep(retraso); }
			}
		}
	}
	if (modo == 96){
		for (c = columnafinal; c >= columnainicio; c--){
			for (f = filainicio; f <= filafinal; f++){
				ir(c + x - columnainicio, f + y - filainicio);
				if (color0 != 0 && matriz[f][c] == 0){ colorfondo(color0); cout << " "; Sleep(retraso); }
				if (color1 != 0 && matriz[f][c] == 9){ colorletra(color1); cout << char(219); Sleep(retraso); }
				if (color2 != 0 && matriz[f][c] == 7){ colorletra(color2); cout << char(219); Sleep(retraso); }
			}
		}
	}
	if (modo == 74){
		for (c = columnainicio; c <= columnafinal; c++){
			for (f = filainicio; f <= filafinal; f++){
				ir(c + x - columnainicio, f + y - filainicio);
				if (color0 != 0 && matriz[f][c] == 0){ colorfondo(color0); cout << " "; Sleep(retraso); }
				if (color1 != 0 && matriz[f][c] == 9){ colorletra(color1); cout << char(219); Sleep(retraso); }
				if (color2 != 0 && matriz[f][c] == 7){ colorletra(color2); cout << char(219); Sleep(retraso); }
			}
		}
	}
	if (modo == 14){
		for (c = columnainicio; c <= columnafinal; c++){
			for (f = filafinal; f >= filainicio; f--){
				ir(c + x - columnainicio, f + y - filainicio);
				if (color0 != 0 && matriz[f][c] == 0){ colorfondo(color0); cout << " "; Sleep(retraso); }
				if (color1 != 0 && matriz[f][c] == 9){ colorletra(color1); cout << char(219); Sleep(retraso); }
				if (color2 != 0 && matriz[f][c] == 7){ colorletra(color2); cout << char(219); Sleep(retraso); }
			}
		}
	}
}

void CuadroDeTexto(int x, int y, int a, int b, int cfondo = 9, int marco = 1, int colormarco = 16)
{
	int c, f;
	if (marco == 1){
		colorfondo(cfondo); colorletra(colormarco);
		for (c = x, f = y - 1; c <= a; c++){ ir(c, f); cout << char(205); }
		ir(a + 1, y - 1); cout << char(187);
		for (c = a + 1, f = y; f <= b; f++){ ir(c, f); cout << char(186); }
		ir(a + 1, b + 1); cout << char(188);
		for (c = a, f = b + 1; c >= x; c--){ ir(c, f); cout << char(205); }
		ir(x - 1, b + 1); cout << char(200); Sleep(10);
		for (c = x - 1, f = b; f >= y; f--){ ir(c, f); cout << char(186); }
		ir(x - 1, y - 1); cout << char(201);
		for (f = y; f <= b; f++){ for (c = x; c <= a; c++){ ir(c, f); colorfondo(cfondo); cout << " "; } }
	}//end modo 1

	if (marco == 0){

		for (f = y; f <= b; f++){ for (c = x; c <= a; c++){ ir(c, f); colorfondo(cfondo); cout << " "; } }
	}//end modo 0

}
//---------------------------------------------------------------------------------------------------------------------------------------

/*-----------------------MODIFICACION DE COORDENADAS-----------------------------*/
void movi(int &x, int&y, int mov)//modifica las coordenadas(binarias) dependiendo del movimiento
{
	if (mov == 1)y -= 2;
	if (mov == 2)y += 2;
	if (mov == 3)x += 2;
	if (mov == 4)x -= 2;
}
void mod(int *caja, int mov)//modifica las coordenadas(de matriz) dependiendo del movimiento
{
	if (mov == 1){ caja[1] = caja[1] - 2; }
	if (mov == 2){ caja[1] = caja[1] + 2; }
	if (mov == 3){ caja[0] = caja[0] + 2; }
	if (mov == 4){ caja[0] = caja[0] - 2; }
}
void movinv(int &mov)
{
	if (mov == 1)mov = 2;
	else if (mov == 2)mov = 1;
	if (mov == 3)mov = 4;
	else if (mov == 4)mov = 3;

}
/*-------------------------------------------------------------------------------*/

// --------------------------------------FRAPES DE GIFS E IMAGENES EN SOLITARIO-------------------
void Pixelmen(int **matriz){
	int matrizint[60][42] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2 },
	{ 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
	{ 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2 },
	{ 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 0, 9, 0, 9, 9, 0, 9, 9, 0, 9, 9, 9, 9, 9, 0, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9 },
	{ 9, 0, 0, 0, 9, 0, 9, 0, 0, 9, 0, 9, 0, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9 },
	{ 9, 9, 9, 9, 9, 0, 9, 0, 0, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 0, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 9, 9, 9, 9, 0, 9, 0, 0, 0, 9 },
	{ 9, 0, 0, 0, 0, 0, 9, 0, 0, 9, 0, 9, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 9 },
	{ 9, 0, 0, 0, 0, 0, 9, 0, 9, 9, 0, 9, 9, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 9, 0, 9, 0, 9, 0, 9, 9, 9, 9, 9, 0, 9, 0, 0, 0, 9 }
	};
	int f, c; for (f = 0; f <60; f++)for (c = 0; c <42; c++)matriz[f][c] = matrizint[f][c];
}
void UPC(int **matriz){
	int matrizint[76][59] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 9, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0 },
	{ 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0 },
	{ 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0 },
	{ 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 0, 9, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 9, 9, 0, 9, 9, 0, 9, 9, 0, 9, 9, 0, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0 },
	{ 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 0, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0 },
	{ 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 9, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 9, 0 }
	};
	int f, c; for (f = 0; f <76; f++)for (c = 0; c <59; c++)matriz[f][c] = matrizint[f][c];
}
void Cartelpausa(int **matriz){
	int matrizint[35][61] =
	{ { 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 0, 5, 5, 5, 0, 0, 5, 0, 0, 0, 5, 0, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 0, 0, 0, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 0, 0, 5, 0, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 5, 0, 0, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 5, 5, 0, 5, 5, 0, 5, 5, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 5, 5, 0, 0, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 0, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 5, 5, 5, 0, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 5, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 0, 0, 0, 5, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 0, 5, 5, 5, 0, 0, 5, 5, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 0, 0, 5, 0, 0, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 0, 0, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 5, 5, 0, 5, 5, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 0, 5, 0, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 5, 5, 0, 5, 5, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 5, 0, 5, 5, 5, 5, 5, 0, 0, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 5, 5, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 5, 5, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3 }
	};
	int f, c; for (f = 0; f < 35; f++)for (c = 0; c < 61; c++)matriz[f][c] = matrizint[f][c];
}
void YouWinYouLose(int **matriz){
	int matrizint[63][57] =
	{ { 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 0, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 0, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 0, 9, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 0, 9, 0, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 0, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 0 },
	{ 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 9, 0, 9, 0, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 9, 9, 0, 9, 0, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 9, 0, 9, 0, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 0 },
	{ 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 9, 9, 0, 9, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 9, 9, 0, 9, 0, 9, 0, 9, 0, 9, 9, 9, 0, 9, 0, 9, 0, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 9, 0, 0, 9, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 9, 2, 1, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 1, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 1, 2, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 2, 2, 1, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 1, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 1, 2, 2, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 9, 2, 2, 2, 1, 2, 2, 2, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 2, 2, 2, 1, 2, 2, 2, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 2, 2, 2, 1, 2, 2, 2, 9, 9, 9, 0, 0, 0 },
	{ 0, 9, 9, 4, 4, 4, 4, 2, 2, 1, 2, 2, 4, 4, 4, 4, 9, 9, 0, 0, 9, 9, 4, 4, 4, 4, 2, 2, 1, 2, 2, 4, 4, 4, 4, 9, 9, 0, 0, 9, 9, 4, 4, 4, 4, 2, 2, 1, 2, 2, 4, 4, 4, 4, 9, 9, 0 },
	{ 9, 4, 4, 4, 4, 4, 4, 9, 9, 1, 9, 9, 4, 4, 4, 4, 4, 4, 9, 9, 4, 4, 4, 4, 4, 4, 9, 9, 1, 9, 9, 4, 4, 4, 4, 4, 4, 9, 9, 4, 4, 4, 4, 4, 4, 9, 9, 1, 9, 9, 4, 4, 4, 4, 4, 4, 9 },
	{ 9, 4, 4, 4, 4, 4, 9, 1, 1, 1, 1, 1, 9, 4, 4, 4, 4, 4, 9, 9, 4, 4, 4, 4, 4, 9, 1, 1, 1, 1, 1, 9, 4, 4, 4, 4, 4, 9, 9, 4, 4, 4, 4, 4, 9, 1, 1, 1, 1, 1, 9, 4, 4, 4, 4, 4, 9 },
	{ 0, 9, 4, 4, 4, 4, 4, 9, 9, 1, 9, 9, 4, 4, 4, 4, 4, 9, 0, 0, 9, 4, 4, 4, 4, 4, 9, 9, 1, 9, 9, 4, 4, 4, 4, 4, 9, 0, 0, 9, 4, 4, 4, 4, 4, 9, 9, 1, 9, 9, 4, 4, 4, 4, 4, 9, 0 },
	{ 0, 0, 9, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 9, 0, 0, 0, 0, 9, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 9, 0, 0, 0, 0, 9, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 9, 0, 0 },
	{ 0, 0, 0, 9, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 9, 0, 0, 0, 0, 0, 0, 9, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 9, 0, 0, 0, 0, 0, 0, 9, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 9, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 2, 2, 2, 9, 1, 9, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 9, 1, 9, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 9, 1, 9, 2, 2, 2, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 2, 2, 2, 2, 9, 2, 9, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 9, 2, 9, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 9, 2, 9, 2, 2, 2, 2, 9, 0, 0, 0 },
	{ 0, 0, 9, 2, 2, 2, 2, 2, 9, 2, 9, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 9, 2, 9, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 9, 2, 9, 2, 2, 2, 2, 2, 9, 0, 0 },
	{ 0, 0, 9, 2, 2, 2, 9, 9, 2, 2, 2, 9, 9, 2, 2, 2, 9, 0, 0, 0, 0, 9, 2, 2, 2, 9, 9, 2, 2, 2, 9, 9, 2, 2, 2, 9, 0, 0, 0, 0, 9, 2, 2, 2, 9, 9, 2, 2, 2, 9, 9, 2, 2, 2, 9, 0, 0 },
	{ 0, 9, 2, 2, 4, 9, 4, 2, 2, 2, 2, 2, 4, 9, 4, 2, 2, 9, 0, 0, 9, 2, 2, 4, 9, 4, 2, 2, 2, 2, 2, 4, 9, 4, 2, 2, 9, 0, 0, 9, 2, 2, 4, 9, 4, 2, 2, 2, 2, 2, 4, 9, 4, 2, 2, 9, 0 },
	{ 9, 2, 2, 4, 9, 4, 2, 9, 9, 9, 9, 9, 2, 4, 9, 4, 2, 2, 9, 9, 2, 2, 4, 9, 4, 2, 9, 9, 9, 9, 9, 2, 4, 9, 4, 2, 2, 9, 9, 2, 2, 4, 9, 4, 2, 9, 9, 9, 9, 9, 2, 4, 9, 4, 2, 2, 9 },
	{ 9, 2, 4, 9, 4, 2, 9, 2, 2, 2, 2, 2, 9, 2, 4, 9, 4, 2, 9, 9, 2, 4, 9, 4, 2, 9, 2, 2, 2, 2, 2, 9, 2, 4, 9, 4, 2, 9, 9, 2, 4, 9, 4, 2, 9, 2, 2, 2, 2, 2, 9, 2, 4, 9, 4, 2, 9 },
	{ 9, 2, 9, 2, 2, 9, 2, 2, 2, 2, 2, 2, 2, 9, 2, 2, 9, 2, 9, 9, 2, 9, 2, 2, 9, 2, 2, 2, 2, 2, 2, 2, 9, 2, 2, 9, 2, 9, 9, 2, 9, 2, 2, 9, 2, 2, 2, 2, 2, 2, 2, 9, 2, 2, 9, 2, 9 },
	{ 9, 2, 9, 2, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 2, 9, 2, 9, 9, 2, 9, 2, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 2, 9, 2, 9, 9, 2, 9, 2, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 2, 9, 2, 9 },
	{ 0, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 0 },
	{ 0, 0, 0, 0, 9, 2, 2, 9, 9, 2, 9, 9, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 2, 9, 1, 9, 2, 9, 1, 9, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 9, 9, 2, 9, 9, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 2, 9, 1, 9, 2, 9, 1, 9, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 9, 1, 9, 2, 9, 1, 9, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 9, 9, 9, 2, 9, 9, 9, 2, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 2, 9, 9, 9, 2, 9, 9, 9, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 9, 9, 9, 2, 9, 9, 9, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 9, 9, 9, 2, 9, 9, 9, 2, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 2, 9, 2, 2, 2, 2, 2, 9, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 9, 2, 2, 2, 2, 2, 9, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 9, 2, 2, 2, 2, 2, 9, 2, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f <63; f++)for (c = 0; c <57; c++)matriz[f][c] = matrizint[f][c];

}
void Abecedario(int **matriz)
{
	int matrizint[136][80] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9 },
	{ 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 1, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9 },
	{ 0, 9, 1, 1, 1, 9, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9 },
	{ 0, 0, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 9, 1, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9 },
	{ 0, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9 },
	{ 9, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 9, 0, 9, 9, 1, 1, 1, 9, 9, 0, 9, 9, 1, 1, 1, 1, 9, 9, 0, 9, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 0, 0, 9, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 9, 9, 9, 0, 0, 9, 1, 9, 9 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 1, 1, 1, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 9 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 0, 9, 9, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 1, 9, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 1, 1, 9, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0 },
	{ 9, 1, 1, 1, 9, 9, 9, 0, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 9, 9, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 9, 1, 1, 1, 1, 9, 9, 9, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 9, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 1, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 1, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 1, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 0, 9, 9, 1, 9, 1, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 0, 0, 9, 9, 1, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 9, 1, 9, 1, 9, 9, 9, 0, 9, 1, 9, 1, 9, 1, 9, 1, 9, 9, 0, 0, 9, 1, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 1, 9, 9, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 0, 9, 9, 1, 9, 9, 9, 0, 0, 9, 9, 1, 9, 9, 9, 1, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 9, 1, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 0, 0 },
	{ 9, 1, 1, 9, 9, 0, 9, 9, 9, 9, 9, 1, 9, 9, 0, 9, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0 },
	{ 9, 9, 1, 9, 9, 0, 0, 0, 9, 9, 9, 1, 9, 9, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0 },
	{ 0, 9, 1, 9, 9, 0, 0, 0, 9, 9, 1, 9, 9, 0, 0, 0, 0, 9, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 9, 9, 1, 1, 1, 9, 9, 0, 0, 9, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0 },
	{ 0, 9, 1, 9, 9, 0, 0, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 1, 9, 9, 0, 9, 9, 9, 9, 9, 1, 9, 9, 0, 9, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 0, 0 },
	{ 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 9, 9, 9, 1, 9, 9, 0, 0, 0 },
	{ 0, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 9, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 0, 9, 1, 1, 1, 9, 9, 9, 0, 0, 0 },
	{ 0, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 9, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 9, 0, 9, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 0, 9, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 1, 1, 9, 9, 9, 1, 1, 9, 9, 0, 9, 1, 1, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 1, 9, 1, 9, 1, 9, 1, 9, 9, 0, 9, 1, 9, 1, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 1, 9, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 1, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 1, 1, 1, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 1, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 0, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 9, 0, 0, 9, 9, 9, 0, 9, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 0, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 1, 9, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 9, 9, 9, 9, 9, 1, 9, 9, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 9, 9, 1, 9, 9, 1, 9, 9, 9, 0, 9, 9, 1, 9, 9, 9, 1, 9, 9, 9, 0, 0, 0, 9, 9, 1, 9, 9, 9, 0, 0, 0 },
	{ 9, 9, 1, 1, 1, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 9, 9, 1, 9, 9, 0, 0, 9, 9, 1, 1, 9, 9, 9, 0, 0, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0 },
	{ 0, 9, 9, 9, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 1, 9, 9, 0, 0, 0, 0, 9, 9, 1, 9, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 9, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 1, 9, 9, 0, 0, 9, 1, 9, 1, 9, 1, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 9, 1, 1, 1, 1, 9, 9, 9, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 0, 9, 9, 1, 1, 9, 9, 9, 0, 0, 9, 9, 1, 9, 9, 9, 1, 9, 9, 9, 0, 9, 1, 9, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 1, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 9, 1, 9, 1, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 1, 9, 1, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 9, 1, 9, 1, 9, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0 },
	{ 9, 1, 1, 9, 9, 1, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 1, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 9, 1, 1, 1, 9, 9, 9, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 9, 9, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 1, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 1, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 9, 9, 0, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 9, 1, 1, 1, 1, 9, 9, 0, 9, 9, 1, 1, 1, 1, 9, 9, 0, 9, 1, 9, 9, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 9, 0, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 1, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 9, 1, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 0, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 9, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 0, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 9, 1, 9, 9, 9, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 0, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 9, 9, 1, 1, 1, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f <136; f++)for (c = 0; c <80; c++)matriz[f][c] = matrizint[f][c];

}
void BuscarLetra(char k, int &ci, int &fi, int &cf, int &ff)
{
	if (k == 'a'){ ci = 0; fi = 0; cf = 7; ff = 12; }if (k == 'A'){ ci = 0; fi = 65; cf = 7; ff = 77; }if (k == '0'){ ci = 63; fi = 34; cf = 70; ff = 46; }
	if (k == 'b'){ ci = 9; fi = 0; cf = 16; ff = 12; }if (k == 'B'){ ci = 9; fi = 65; cf = 16; ff = 77; }if (k == '1'){ ci = 0; fi = 51; cf = 4; ff = 63; }
	if (k == 'c'){ ci = 18; fi = 0; cf = 24; ff = 12; }if (k == 'C'){ ci = 18; fi = 65; cf = 25; ff = 77; }if (k == '2'){ ci = 6; fi = 51; cf = 13; ff = 63; }
	if (k == 'd'){ ci = 26; fi = 0; cf = 33; ff = 12; }if (k == 'D'){ ci = 27; fi = 65; cf = 34; ff = 77; }if (k == '3'){ ci = 15; fi = 51; cf = 22; ff = 63; }
	if (k == 'e'){ ci = 35; fi = 0; cf = 42; ff = 12; }if (k == 'E'){ ci = 36; fi = 65; cf = 42; ff = 77; }if (k == '4'){ ci = 24; fi = 51; cf = 31; ff = 63; }
	if (k == 'f'){ ci = 44; fi = 0; cf = 50; ff = 12; }if (k == 'F'){ ci = 44; fi = 65; cf = 50; ff = 77; }if (k == '5'){ ci = 33; fi = 51; cf = 40; ff = 63; }
	if (k == 'g'){ ci = 52; fi = 0; cf = 59; ff = 15; }if (k == 'G'){ ci = 52; fi = 65; cf = 59; ff = 77; }if (k == '6'){ ci = 42; fi = 51; cf = 49; ff = 63; }
	if (k == 'h'){ ci = 61; fi = 0; cf = 68; ff = 12; }if (k == 'H'){ ci = 61; fi = 65; cf = 68; ff = 77; }if (k == '7'){ ci = 51; fi = 51; cf = 58; ff = 63; }
	if (k == 'i'){ ci = 70; fi = 0; cf = 73; ff = 12; }if (k == 'I'){ ci = 70; fi = 65; cf = 73; ff = 77; }if (k == '8'){ ci = 60; fi = 51; cf = 67; ff = 63; }
	if (k == 'j'){ ci = 75; fi = 0; cf = 79; ff = 15; }if (k == 'J'){ ci = 0; fi = 79; cf = 7; ff = 91; }if (k == '9'){ ci = 69; fi = 51; cf = 76; ff = 63; }
	if (k == 'k'){ ci = 0; fi = 17; cf = 7; ff = 29; }if (k == 'K'){ ci = 9; fi = 79; cf = 16; ff = 91; }if (k == -96){ ci = 18; fi = 109; cf = 25; ff = 121; }//a
	if (k == 'l'){ ci = 9; fi = 17; cf = 12; ff = 29; }if (k == 'L'){ ci = 18; fi = 79; cf = 25; ff = 91; }if (k == -126){ ci = 27; fi = 109; cf = 34; ff = 121; }//e
	if (k == 'm'){ ci = 14; fi = 17; cf = 23; ff = 29; }if (k == 'M'){ ci = 27; fi = 79; cf = 36; ff = 91; }if (k == -95){ ci = 36; fi = 109; cf = 39; ff = 121; }//i
	if (k == 'n'){ ci = 25; fi = 17; cf = 32; ff = 29; }if (k == 'N'){ ci = 38; fi = 79; cf = 45; ff = 91; }if (k == -94){ ci = 41; fi = 109; cf = 48; ff = 121; }//o
	if (k == -92){ ci = 9; fi = 109; cf = 17; ff = 121; }if (k == -91){ ci = 0; fi = 109; cf = 7; ff = 121; }if (k == -93){ ci = 50; fi = 109; cf = 57; ff = 121; }//u
	if (k == 'o'){ ci = 34; fi = 17; cf = 41; ff = 29; }if (k == 'O'){ ci = 24; fi = 123; cf = 31; ff = 135; }if (k == -75){ ci = 59; fi = 109; cf = 66; ff = 121; }//A
	if (k == 'p'){ ci = 43; fi = 17; cf = 50; ff = 32; }if (k == 'P'){ ci = 47; fi = 79; cf = 54; ff = 91; }if (k == -112){ ci = 68; fi = 109; cf = 74; ff = 121; }//E
	if (k == 'q'){ ci = 52; fi = 17; cf = 59; ff = 32; }if (k == 'Q'){ ci = 56; fi = 79; cf = 63; ff = 93; }if (k == -42){ ci = 0; fi = 123; cf = 4; ff = 135; }//I
	if (k == 'r'){ ci = 61; fi = 17; cf = 66; ff = 29; }if (k == 'R'){ ci = 65; fi = 79; cf = 72; ff = 91; }if (k == -32){ ci = 6; fi = 123; cf = 13; ff = 135; }//O
	if (k == 's'){ ci = 68; fi = 17; cf = 75; ff = 29; }if (k == 'S'){ ci = 0; fi = 95; cf = 7; ff = 107; }if (k == -23){ ci = 15; fi = 123; cf = 22; ff = 135; }//U
	if (k == 't'){ ci = 0; fi = 34; cf = 5; ff = 46; }if (k == 'T'){ ci = 9; fi = 95; cf = 16; ff = 107; }
	if (k == 'u'){ ci = 7; fi = 34; cf = 14; ff = 46; }if (k == 'U'){ ci = 18; fi = 95; cf = 25; ff = 107; }
	if (k == 'v'){ ci = 16; fi = 34; cf = 23; ff = 46; }if (k == 'V'){ ci = 27; fi = 95; cf = 35; ff = 107; }
	if (k == 'w'){ ci = 25; fi = 34; cf = 34; ff = 46; }if (k == 'W'){ ci = 37; fi = 95; cf = 46; ff = 107; }
	if (k == 'x'){ ci = 36; fi = 34; cf = 43; ff = 46; }if (k == 'X'){ ci = 48; fi = 95; cf = 56; ff = 107; }
	if (k == 'y'){ ci = 45; fi = 34; cf = 52; ff = 49; }if (k == 'Y'){ ci = 58; fi = 95; cf = 67; ff = 107; }
	if (k == 'z'){ ci = 54; fi = 34; cf = 61; ff = 46; }if (k == 'Z'){ ci = 69; fi = 95; cf = 76; ff = 107; }
}
void ni1(int **matriz){
	int matrizint[17][78] =
	{
		{ 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c;

	for (f = 0; f < 17; f++)
		for (c = 0; c < 78; c++)
			matriz[f][c] = matrizint[f][c];
}
void ni2(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni3(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni4(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni5(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni6(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni7(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni8(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni9(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni10(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni11(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni12(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void ni13(int **matriz){
	int matrizint[17][78] =
	{ { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0 },
	{ 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0 },
	{ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f < 17; f++)for (c = 0; c < 78; c++)matriz[f][c] = matrizint[f][c];
}
void dh1(int **matriz){
	int matrizint[35][29] =
	{ { 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 10, 9, 9, 10, 10, 9, 9, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 0, 9, 9, 9, 9, 9, 0, 0, 9, 10, 9, 1, 1, 10, 10, 1, 1, 9, 10, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9 },
	{ 0, 9, 9, 9, 9, 9, 0, 0, 10, 9, 1, 1, 1, 10, 10, 1, 1, 1, 9, 10, 0, 0, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 10, 9, 1, 9, 1, 10, 10, 1, 9, 1, 9, 10, 0, 0, 0, 9, 9, 9, 9, 9, 0 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 10, 9, 1, 1, 9, 10, 10, 9, 1, 1, 9, 10, 0, 0, 0, 0, 0, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 10, 9, 1, 1, 1, 10, 10, 1, 1, 1, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 8, 10, 10, 9, 1, 9, 9, 9, 9, 1, 9, 10, 10, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 9, 0, 0, 8, 1, 1, 1, 10, 9, 9, 9, 9, 9, 9, 10, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 9, 0, 8, 1, 1, 1, 1, 1, 1, 9, 1, 1, 9, 1, 1, 1, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 0, 8, 1, 9, 1, 1, 9, 1, 1, 9, 9, 1, 1, 9, 1, 1, 9, 1, 8, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 8, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 10, 10, 9, 1, 1, 9, 1, 1, 1, 9, 9, 1, 1, 1, 9, 1, 1, 9, 10, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 10, 10, 10, 1, 9, 1, 1, 1, 1, 9, 1, 1, 9, 1, 1, 1, 1, 9, 1, 10, 10, 0, 0, 0, 0, 0 },
	{ 0, 0, 10, 10, 10, 10, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 10, 10, 10, 0, 0, 0, 0 },
	{ 0, 0, 10, 10, 10, 10, 1, 9, 1, 1, 1, 9, 1, 1, 1, 1, 9, 1, 1, 1, 9, 1, 10, 10, 10, 10, 0, 0, 0 },
	{ 0, 10, 10, 10, 10, 9, 10, 9, 9, 1, 9, 9, 9, 1, 1, 9, 9, 9, 10, 10, 9, 9, 9, 10, 10, 10, 10, 0, 0 },
	{ 0, 10, 10, 10, 10, 9, 10, 10, 1, 1, 1, 9, 1, 1, 1, 1, 10, 10, 9, 10, 10, 9, 9, 10, 10, 10, 10, 0, 0 },
	{ 0, 10, 10, 10, 10, 9, 9, 10, 10, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 0, 0 },
	{ 0, 9, 10, 10, 10, 10, 9, 9, 10, 10, 10, 1, 1, 1, 1, 10, 9, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 10, 0 },
	{ 0, 9, 10, 10, 10, 10, 10, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 9, 9, 10, 10, 10, 10, 0 },
	{ 0, 9, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 0 },
	{ 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 10, 10, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0 },
	{ 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0 },
	{ 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 10, 9, 9, 0 },
	{ 0, 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 9, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 9, 9, 9, 10, 10, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 10, 9, 10, 10, 10, 9, 10, 10, 10, 10, 10, 10, 9, 0, 9, 9, 9, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 10, 9, 9, 10, 9, 10, 9, 10, 10, 10, 10, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 10, 10, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0, 0 }
	};

	int f, c; for (f = 0; f < 35; f++)for (c = 0; c < 29; c++)matriz[f][c] = matrizint[f][c];
}
void dh2(int **matriz){
	int matrizint[35][29] =
	{ { 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 9, 9 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 10, 9, 9, 10, 10, 9, 9, 10, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 9, 10, 9, 1, 1, 10, 10, 1, 1, 9, 10, 9, 0, 0, 0, 9, 9, 9, 9, 9, 0 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 10, 9, 1, 1, 1, 10, 10, 1, 1, 1, 9, 10, 0, 0, 0, 0, 0, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 10, 9, 1, 1, 1, 10, 10, 1, 1, 1, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 10, 9, 1, 9, 9, 10, 10, 9, 9, 1, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 9, 0, 0, 0, 0, 10, 9, 1, 1, 1, 10, 10, 1, 1, 1, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 9, 0, 0, 0, 8, 10, 10, 9, 1, 9, 9, 9, 9, 1, 9, 10, 10, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 0, 0, 8, 1, 1, 1, 10, 9, 9, 9, 9, 9, 9, 10, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 8, 1, 1, 1, 1, 1, 1, 9, 1, 1, 9, 1, 1, 1, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 8, 1, 9, 1, 1, 9, 1, 1, 9, 9, 1, 1, 9, 1, 1, 9, 1, 8, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 10, 10, 10, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 10, 10, 0, 0, 0, 0, 0 },
	{ 0, 0, 10, 10, 10, 10, 9, 1, 1, 9, 1, 1, 1, 9, 9, 1, 1, 1, 9, 1, 1, 9, 10, 10, 10, 0, 0, 0, 0 },
	{ 0, 0, 10, 10, 10, 10, 1, 9, 1, 1, 1, 1, 9, 1, 1, 9, 1, 1, 1, 1, 9, 1, 10, 10, 10, 10, 0, 0, 0 },
	{ 0, 10, 10, 10, 10, 9, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 1, 1, 9, 1, 9, 10, 10, 10, 10, 0, 0 },
	{ 0, 10, 10, 10, 10, 9, 10, 9, 1, 1, 1, 9, 1, 1, 1, 9, 10, 10, 9, 10, 10, 9, 9, 10, 10, 10, 10, 0, 0 },
	{ 0, 10, 10, 10, 10, 9, 10, 10, 1, 1, 1, 9, 1, 1, 1, 9, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 0, 0 },
	{ 0, 9, 10, 10, 10, 10, 9, 10, 10, 10, 1, 1, 1, 1, 1, 10, 9, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 10, 0 },
	{ 0, 9, 10, 10, 10, 10, 10, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 9, 9, 10, 10, 10, 10, 0 },
	{ 0, 9, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 0 },
	{ 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 10, 10, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0 },
	{ 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0 },
	{ 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 10, 9, 9, 0 },
	{ 0, 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 9, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 9, 9, 9, 10, 10, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 10, 9, 10, 10, 10, 9, 10, 10, 10, 10, 10, 10, 9, 0, 9, 9, 9, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 10, 9, 9, 10, 9, 10, 9, 10, 10, 10, 10, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 10, 10, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0, 0 }
	};

	int f, c; for (f = 0; f < 35; f++)for (c = 0; c < 29; c++)matriz[f][c] = matrizint[f][c];
}
void joker01(int **matriz){
	int matrizint[55][42] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 11, 11, 11, 11, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 11, 11, 11, 11, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 1, 1, 11, 11, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 1, 1, 11, 11, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 1, 1, 9, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 1, 1, 9, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 9, 9, 3, 3, 3, 3, 14, 14, 1, 1, 14, 14, 3, 3, 3, 3, 9, 9, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 9, 9, 3, 3, 3, 3, 14, 14, 1, 1, 14, 14, 3, 3, 3, 3, 9, 9, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 12, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 12, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 3, 3, 12, 12, 3, 3, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 3, 3, 12, 12, 3, 3, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }
	};
	int f, c; for (f = 0; f <55; f++)for (c = 0; c <42; c++)matriz[f][c] = matrizint[f][c];
}
void joker02(int **matriz){
	int matrizint[55][42] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 11, 11, 11, 11, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 11, 11, 11, 11, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 1, 1, 11, 11, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 1, 1, 11, 11, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 1, 1, 9, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 1, 1, 9, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 1, 1, 10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 9, 9, 3, 3, 3, 3, 14, 14, 1, 1, 14, 14, 3, 3, 3, 3, 9, 9, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 9, 9, 3, 3, 3, 3, 14, 14, 1, 1, 14, 14, 3, 3, 3, 3, 9, 9, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 12, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 12, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 3, 3, 12, 12, 3, 3, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 3, 3, 12, 12, 3, 3, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }
	};
	int f, c; for (f = 0; f <55; f++)for (c = 0; c <42; c++)matriz[f][c] = matrizint[f][c];
}
void joker03(int **matriz){
	int matrizint[55][42] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 11, 11, 11, 11, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 11, 11, 11, 11, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 1, 1, 11, 11, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 1, 1, 11, 11, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 1, 1, 9, 9, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 1, 1, 9, 9, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 1, 1, 10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 9, 9, 3, 3, 3, 3, 14, 14, 1, 1, 14, 14, 3, 3, 3, 3, 9, 9, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 9, 9, 3, 3, 3, 3, 14, 14, 1, 1, 14, 14, 3, 3, 3, 3, 9, 9, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 12, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 12, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 3, 3, 12, 12, 3, 3, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 3, 3, 12, 12, 3, 3, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }
	};
	int f, c; for (f = 0; f <55; f++)for (c = 0; c <42; c++)matriz[f][c] = matrizint[f][c];
}
void joker04(int **matriz){
	int matrizint[55][42] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 11, 11, 11, 11, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 11, 11, 11, 11, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 11, 11, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 11, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 1, 1, 11, 11, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 1, 1, 11, 11, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 9, 9, 10, 10, 10, 10, 9, 9, 1, 1, 9, 9, 10, 10, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 9, 9, 9, 9, 10, 10, 10, 10, 9, 9, 1, 1, 9, 9, 10, 10, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 11, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 11, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 1, 1, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 9, 9, 1, 1, 10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 10, 1, 1, 1, 1, 1, 1, 1, 1, 10, 9, 9, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 9, 9, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 3, 3, 3, 3, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 14, 14, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 14, 14, 1, 1, 14, 14, 3, 3, 3, 3, 9, 9, 9, 9, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 12, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 12, 12, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 3, 3, 12, 12, 3, 3, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 3, 3, 12, 12, 3, 3, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }
	};
	int f, c; for (f = 0; f <55; f++)for (c = 0; c <42; c++)matriz[f][c] = matrizint[f][c];
}
//--------------------------------------------------------------------------------------------------------------

/*-----------------------IMPRESION DE OBJETOS-----------------------------*/
void PintarCaja(int nivel, int x, int y, int c = 0, int adf = 0, int adl = 0, char adc = '.')//Pinta la caja dependiendo del nivel en la que se encuentre, notese que los modelos pueden cambiar con el nivel
{
	if (nivel == 1){
		ir(x, y); colorfondo(14); cout << " ";
		ir(x + 1, y); colorfondo(14); cout << " ";
		ir(x, y + 1); colorfondo(14); cout << " ";
		ir(x + 1, y + 1); colorfondo(14); cout << " ";
	}
	if (nivel == 2){
		ir(x, y); colorfondo(2); cout << " ";
		ir(x + 1, y); colorfondo(2); cout << " ";
		ir(x, y + 1); colorfondo(2); cout << " ";
		ir(x + 1, y + 1); colorfondo(2); cout << " ";
	}
	if (nivel == 3){
		ir(x, y); colorfondo(16); cout << " ";
		ir(x + 1, y); colorfondo(16); cout << " ";
		ir(x, y + 1); colorfondo(16); cout << " ";
		ir(x + 1, y + 1); colorfondo(16); cout << " ";
	}
	if (nivel == 4){
		ir(x, y); colorfondo(4); cout << " ";
		ir(x + 1, y); colorfondo(4); cout << " ";
		ir(x, y + 1); colorfondo(4); cout << " ";
		ir(x + 1, y + 1); colorfondo(4); cout << " ";
	}
	if (nivel == 5){
		if (c == 0){
			ir(x, y); colorfondo(5); cout << " ";
			ir(x + 1, y); colorfondo(5); cout << " ";
			ir(x, y + 1); colorfondo(5); cout << " ";
			ir(x + 1, y + 1); colorfondo(5); cout << " ";
		}
		if (c == 1){
			ir(x, y); colorfondo(9); cout << " ";
			ir(x + 1, y); colorfondo(9); cout << " ";
			ir(x, y + 1); colorfondo(9); cout << " ";
			ir(x + 1, y + 1); colorfondo(9); cout << " ";
		}
	}
	if (adf != 0 && adl != 0 && adc != '.'){
		colorfondo(adf); colorletra(adl);
		ir(x, y); cout << adc;
		ir(x + 1, y); cout << adc;
		ir(x, y + 1); cout << adc;
		ir(x + 1, y + 1); cout << adc;

	}
}
void PonerCaja(int nivel, int c, int ***Cajas){
	int x; int y;
	x = Cajas[nivel][c][0];
	y = Cajas[nivel][c][1];
	PintarCaja(nivel, x, y);
}
void PintarHueco(int nivel, int x, int y)//Pinta un hueco dependiendo del nivel en la que se encuentre, notese que los modelos pueden cambiar con el nivel
{
	if (nivel == 2){
		colorletra(2);
		ir(x, y); colorfondo(7); colorletra(2); cout << char(218);
		ir(x + 1, y); colorfondo(7); colorletra(2); cout << char(191);
		ir(x, y + 1); colorfondo(7); colorletra(2); cout << char(192);
		ir(x + 1, y + 1); colorfondo(7); colorletra(2); cout << char(217);
	}
	if (nivel == 1){
		colorletra(14);
		ir(x, y); colorfondo(6); colorletra(14); cout << char(218);
		ir(x + 1, y); colorfondo(6); colorletra(14); cout << char(191);
		ir(x, y + 1); colorfondo(6); colorletra(14); cout << char(192);
		ir(x + 1, y + 1); colorfondo(6); colorletra(14); cout << char(217);
	}
	if (nivel == 3){
		colorletra(14);
		ir(x, y); colorfondo(5); colorletra(16); cout << char(218);
		ir(x + 1, y); colorfondo(5); colorletra(16); cout << char(191);
		ir(x, y + 1); colorfondo(5); colorletra(16); cout << char(192);
		ir(x + 1, y + 1); colorfondo(5); colorletra(16); cout << char(217);
	}
	if (nivel == 4){
		colorletra(14);
		ir(x, y); colorfondo(1); colorletra(9); cout << char(218);
		ir(x + 1, y); colorfondo(1); colorletra(9); cout << char(191);
		ir(x, y + 1); colorfondo(1); colorletra(9); cout << char(192);
		ir(x + 1, y + 1); colorfondo(1); colorletra(9); cout << char(217);
	}
	if (nivel == 5){
		if (y == 14){
			ir(x, y); colorfondo(7); colorletra(9); cout << char(218);
			ir(x + 1, y); colorfondo(7); colorletra(9); cout << char(191);
			ir(x, y + 1); colorfondo(7); colorletra(9); cout << char(192);
			ir(x + 1, y + 1); colorfondo(7); colorletra(9); cout << char(217);
		}
		else
		{
			ir(x, y); colorfondo(2); colorletra(9); cout << char(218);
			ir(x + 1, y); colorfondo(2); colorletra(9); cout << char(191);
			ir(x, y + 1); colorfondo(2); colorletra(9); cout << char(192);
			ir(x + 1, y + 1); colorfondo(2); colorletra(9); cout << char(217);
		}
	}

}
void PintarMovil(int nivel, int x, int y, int cf = 9, int cl = 1)//Pinta el movil dependiendo del nivel en la que se encuentre, notese que los modelos pueden cambiar con el nivel
{
	ir(x, y); colorfondo(cf); colorletra(cl); cout << char(201);
	ir(x + 1, y); colorfondo(cf); colorletra(cl); cout << char(187);
	ir(x, y + 1); colorfondo(cf); colorletra(cl); cout << char(200);
	ir(x + 1, y + 1); colorfondo(cf); colorletra(cl); cout << char(188);

}
void PintarMuerte(int x, int y)
{
	colorfondo(1); colorletra(2);
	MusicaMuerte();
	ir(x, y); cout << char(254);
	ir(x + 1, y); cout << char(254);
	ir(x, y + 1); cout << char(254);
	ir(x + 1, y + 1); cout << char(254);
	Sleep(200);
	colorletra(2);
	ir(x, y); cout << "\\";
	ir(x + 1, y); cout << "/";
	ir(x, y + 1); cout << "/";
	ir(x + 1, y + 1); cout << "\\";
	Sleep(200);
	colorletra(10);
	ir(x, y); cout << "\\";
	ir(x + 1, y); cout << "/";
	ir(x, y + 1); cout << "/";
	ir(x + 1, y + 1); cout << "\\";
	Sleep(200);
	colorletra(1);
	ir(x, y); cout << "\\";
	ir(x + 1, y); cout << "/";
	ir(x, y + 1); cout << "/";
	ir(x + 1, y + 1); cout << "\\";
	Sleep(200);
	colorletra(8);
	ir(x, y); cout << "\\";
	ir(x + 1, y); cout << "/";
	ir(x, y + 1); cout << "/";
	ir(x + 1, y + 1); cout << "\\";
	Sleep(200);
	colorletra(16);
	ir(x, y); cout << "\\";
	ir(x + 1, y); cout << "/";
	ir(x, y + 1); cout << "/";
	ir(x + 1, y + 1); cout << "\\";
	Sleep(200);
	colorletra(9);
	ir(x, y); cout << "\\";
	ir(x + 1, y); cout << "/";
	ir(x, y + 1); cout << "/";
	ir(x + 1, y + 1); cout << "\\";
}
void PintarPortal(int nivel, int x = -1, int y = -1)//Pinta el movil dependiendo del nivel en la que se encuentre, notese que los modelos pueden cambiar con el nivel
{
	int xportal; int yportal;//coordenadas del portal
	if (nivel == 1){ xportal = 36; yportal = 34; }
	if (nivel == 2){ xportal = 42; yportal = 18; }
	if (nivel == 3){ xportal = 36; yportal = 28; }
	if (nivel == 4){ xportal = 38; yportal = 12; }
	if (nivel == 5) { xportal = 40; yportal = 6; }

	if (nivel == 1)colorfondo(6);
	if (nivel == 2)colorfondo(7);
	if (nivel == 3)colorfondo(5);
	if (nivel == 4)colorfondo(8);
	if (nivel == 5)colorfondo(2);
	if (x == -1 || y == -1){ x = xportal; y = yportal; }
	ir(x, y); colorletra(4); cout << char(178);
	ir(x + 1, y); colorletra(4); cout << char(178);
	ir(x, y + 1); colorletra(4); cout << char(178);
	ir(x + 1, y + 1); colorletra(4); cout << char(178);
}
void PintarPuente(int nivel, int x, int y)
{
	if (nivel == 2){
		ir(x, y); colorfondo(7); colorletra(6); cout << " ";
		ir(x + 1, y); colorfondo(7); colorletra(6); cout << " ";
		ir(x, y + 1); colorfondo(7); colorletra(6); cout << " ";
		ir(x + 1, y + 1); colorfondo(7); colorletra(6); cout << " ";
	}
	if (nivel == 1){
		ir(x, y); colorfondo(6); colorletra(6); cout << " ";
		ir(x + 1, y); colorfondo(6); colorletra(6); cout << " ";
		ir(x, y + 1); colorfondo(6); colorletra(6); cout << " ";
		ir(x + 1, y + 1); colorfondo(6); colorletra(6); cout << " ";
	}
	if (nivel == 3){
		ir(x, y); colorfondo(5); colorletra(6); cout << " ";
		ir(x + 1, y); colorfondo(5); colorletra(6); cout << " ";
		ir(x, y + 1); colorfondo(5); colorletra(6); cout << " ";
		ir(x + 1, y + 1); colorfondo(5); colorletra(6); cout << " ";
	}
	if (nivel == 4){
		ir(x, y); colorfondo(1); colorletra(1); cout << " ";
		ir(x + 1, y); colorfondo(1); colorletra(1); cout << " ";
		ir(x, y + 1); colorfondo(1); colorletra(1); cout << " ";
		ir(x + 1, y + 1); colorfondo(1); colorletra(1); cout << " ";
	}
}
void PBorrar(int nivel, int x, int y, int ad = 0)//Se utiliza para borrar al movil antes de que se mueva. No hay una fucion de este tipo para las cajas, porque el movil ya lo hace
{//el ultimo argumento es utilizado para borrar al portal

	if (ad == 0){
		if (nivel == 1){
			ir(x, y); colorfondo(6); cout << " ";
			ir(x + 1, y); colorfondo(6); cout << " ";
			ir(x, y + 1); colorfondo(6); cout << " ";
			ir(x + 1, y + 1); colorfondo(6); cout << " ";
		}
		if (nivel == 2){
			ir(x, y); colorfondo(7); cout << " ";
			ir(x + 1, y); colorfondo(7); cout << " ";
			ir(x, y + 1); colorfondo(7); cout << " ";
			ir(x + 1, y + 1); colorfondo(7); cout << " ";
		}
		if (nivel == 3){
			ir(x, y); colorfondo(5); cout << " ";
			ir(x + 1, y); colorfondo(5); cout << " ";
			ir(x, y + 1); colorfondo(5); cout << " ";
			ir(x + 1, y + 1); colorfondo(5); cout << " ";
		}
		if (nivel == 4){
			if ((x == 36 && y == 30) || (x == 38 && y == 30) || (x == 40 && y == 30) || (x == 42 && y == 30) || (x == 32 && y == 32) || (x == 34 && y == 32) || (x == 36 && y == 32) || (x == 38 && y == 32) || (x == 40 && y == 32) || (x == 42 && y == 32) || (x == 44 && y == 32) || (x == 30 && y == 34) || (x == 32 && y == 34) || (x == 34 && y == 34) || (x == 36 && y == 34) || (x == 38 && y == 34) || (x == 40 && y == 34) || (x == 42 && y == 34) || (x == 44 && y == 34) || (x == 46 && y == 34) || (x == 30 && y == 38) || (x == 32 && y == 38) || (x == 34 && y == 38) || (x == 36 && y == 38) || (x == 38 && y == 38) || (x == 40 && y == 38) || (x == 42 && y == 38) || (x == 44 && y == 38) || (x == 46 && y == 38) || (x == 30 && y == 40) || (x == 32 && y == 40) || (x == 34 && y == 40) || (x == 36 && y == 40) || (x == 38 && y == 40) || (x == 40 && y == 40) || (x == 42 && y == 40) || (x == 44 && y == 40) || (x == 46 && y == 40) || (x == 30 && y == 42) || (x == 32 && y == 42) || (x == 34 && y == 42) || (x == 42 && y == 42) || (x == 44 && y == 42) || (x == 46 && y == 42))
				colorfondo(5);
			else if ((x == 32 && y == 18) || (x == 34 && y == 18) || (x == 36 && y == 18) || (x == 38 && y == 18) || (x == 40 && y == 18) || (x == 42 && y == 18) || (x == 44 && y == 18) || (x == 30 && y == 20) || (x == 46 && y == 20) || (x == 30 && y == 22) || (x == 46 && y == 22) || (x == 30 && y == 24) || (x == 46 && y == 24) || (x == 32 && y == 26) || (x == 34 && y == 26) || (x == 36 && y == 26) || (x == 38 && y == 26) || (x == 40 && y == 26) || (x == 42 && y == 26) || (x == 44 && y == 26) || (x == 36 && y == 36) || (x == 38 && y == 36) || (x == 40 && y == 36))
				colorfondo(15);
			else
				colorfondo(1);
			ir(x, y); colorletra(2); cout << " ";
			ir(x + 1, y); colorletra(2); cout << " ";
			ir(x, y + 1); colorletra(3); cout << " ";
			ir(x + 1, y + 1); cout << " ";
		}
		if (nivel == 5){
			if ((x == 34 && y == 6) || (x == 36 && y == 6) || (x == 44 && y == 6) || (x == 46 && y == 6) || (x == 32 && y == 8) || (x == 34 && y == 8) || (x == 36 && y == 8) || (x == 38 && y == 8) || (x == 42 && y == 8) || (x == 44 && y == 8) || (x == 46 && y == 8) || (x == 48 && y == 8) || (x == 34 && y == 10) || (x == 36 && y == 10) || (x == 38 && y == 10) || (x == 40 && y == 10) || (x == 42 && y == 10) || (x == 44 && y == 10) || (x == 46 && y == 10) || (x == 38 && y == 12) || (x == 40 && y == 12) || (x == 42 && y == 12) || (x == 32 && y == 14) || (x == 48 && y == 14) || (x == 32 && y == 16) || (x == 34 && y == 16) || (x == 36 && y == 16) || (x == 38 && y == 16) || (x == 40 && y == 16) || (x == 42 && y == 16) || (x == 44 && y == 16) || (x == 46 && y == 16) || (x == 48 && y == 16) || (x == 34 && y == 18) || (x == 36 && y == 18) || (x == 38 && y == 18) || (x == 40 && y == 18) || (x == 42 && y == 18) || (x == 44 && y == 18) || (x == 46 && y == 18) || (x == 36 && y == 20) || (x == 38 && y == 20) || (x == 40 && y == 20) || (x == 42 && y == 20) || (x == 44 && y == 20) || (x == 36 && y == 22) || (x == 44 && y == 22) || (x == 18 && y == 24) || (x == 20 && y == 24) || (x == 26 && y == 24) || (x == 28 && y == 24) || (x == 38 && y == 24) || (x == 40 && y == 24) || (x == 42 && y == 24) || (x == 52 && y == 24) || (x == 54 && y == 24) || (x == 60 && y == 24) || (x == 62 && y == 24) || (x == 20 && y == 26) || (x == 22 && y == 26) || (x == 26 && y == 26) || (x == 54 && y == 26) || (x == 58 && y == 26) || (x == 60 && y == 26) || (x == 34 && y == 40) || (x == 46 && y == 40) || (x == 32 && y == 42) || (x == 34 && y == 42) || (x == 36 && y == 42) || (x == 44 && y == 42) || (x == 46 && y == 42) || (x == 48 && y == 42) || (x == 30 && y == 44) || (x == 32 && y == 44) || (x == 34 && y == 44) || (x == 36 && y == 44) || (x == 38 && y == 44) || (x == 42 && y == 44) || (x == 44 && y == 44) || (x == 46 && y == 44) || (x == 48 && y == 44) || (x == 50 && y == 44) || (x == 32 && y == 46) || (x == 34 && y == 46) || (x == 36 && y == 46) || (x == 44 && y == 46) || (x == 46 && y == 46) || (x == 48 && y == 46) || (x == 34 && y == 48) || (x == 36 && y == 48) || (x == 44 && y == 48) || (x == 46 && y == 48))
				colorfondo(7);
			else colorfondo(2);
			ir(x, y); cout << " ";
			ir(x + 1, y); cout << " ";
			ir(x, y + 1); cout << " ";
			ir(x + 1, y + 1); cout << " ";
		}
	}
	if (ad != 0){
		ir(x, y); colorfondo(ad); cout << " ";
		ir(x + 1, y); colorfondo(ad); cout << " ";
		ir(x, y + 1); colorfondo(ad); cout << " ";
		ir(x + 1, y + 1); colorfondo(ad); cout << " ";
	}
}
/*----------------------------------------------------------------------*/

//------------------EFECTOS DE CONSOLA Y DE OBJETOS ----------------------------------------
void desvanecimiento(int color, int alto = 62, int largo = 79, int modo = 82, int x = 0, int y = 0){
	if (modo == 82 || modo == 28){
		for (int i = 0; i <= (alto / 2); i++){
			for (int f = 0; f <= largo; f++){
				ir(f + x, i + y); colorfondo(color); cout << " ";
				ir(79 - f + x, alto - i + y); colorfondo(color); cout << " ";
			}Sleep(20);
		}
	}

	if (modo == 46 || modo == 64){
		for (int f = 0; f <= (largo + 1) / 2; f++){
			for (int i = 0; i <= alto; i++){
				ir(f + x, i + y); colorfondo(color); cout << " ";
				ir(79 - f + x, alto - i + y); colorfondo(color); cout << " ";
			}Sleep(20);
		}
	}

	if (modo == 8){
		for (int f = 0; f <= alto; f++){
			for (int i = 0; i <= largo; i++){
				ir(i + x, f + y); colorfondo(color); cout << " ";
			}Sleep(13);
		}
	}

	if (modo == 2){
		for (int f = alto; f >= 0; f--){
			if (f == alto - 1)ir(0, 0); for (int i = 0; i <= largo; i++){
				ir(i + x, f + y); colorfondo(color); cout << " ";
			}Sleep(13);
		}
	}

	if (modo == 6){
		for (int f = largo; f >= 0; f--){
			for (int i = 0; i <= alto; i++){
				ir(f + x, i + y); colorfondo(color); cout << " ";
			}Sleep(13);
		}
	}

	if (modo == 4){
		for (int f = 0; f <= largo; f++){
			for (int i = 0; i <= alto; i++){
				ir(f + x, i + y); colorfondo(color); cout << " ";
			}Sleep(13);
		}
	}

	ir(0, 0);
}
void Endurecimiento(int x, int y, int mov, int ***Cajas){
	int xanterior = x, yanterior = y;
	movinv(mov);
	movi(xanterior, yanterior, mov);
	PBorrar(5, xanterior, yanterior);
	PintarMovil(5, x, y);

	SonidoEndurecimiento();
	for (int i = 10; i <= 16; i++)PintarCaja(5, Cajas[5][i][0], Cajas[5][i][1], 0, 16, 16, 'l');
	Sleep(300);
	for (int i = 10; i <= 16; i++)PintarCaja(5, Cajas[5][i][0], Cajas[5][i][1], 0, 8, 8, 'l');
	Sleep(300);
	for (int i = 10; i <= 16; i++)PintarCaja(5, Cajas[5][i][0], Cajas[5][i][1], 0, 8, 9, 'X');
	Sleep(300);
	for (int i = 10; i <= 16; i++)PintarCaja(5, Cajas[5][i][0], Cajas[5][i][1], 0, 16, 9, 'X');
	Sleep(300);
	for (int i = 10; i <= 16; i++)PintarCaja(5, Cajas[5][i][0], Cajas[5][i][1], 0, 16, 16, 'X');
	Sleep(300);
	for (int i = 10; i <= 16; i++)PintarCaja(5, Cajas[5][i][0], Cajas[5][i][1], 0, 9, 9, 'X');
}
void Teletransporte(int nivel, int x, int y)
{
	int fase1 = 9; int retraso = 80;
	int colorf; int color2; int letra;
	colorf = 1; if (nivel == 4)colorf = 8;
	color2 = 8; if (nivel == 4)color2 = 16;
	letra = 12; if (nivel == 4)letra = 12;

	colorfondo(colorf);
	ir(x - 1, y - 1); cout << " "; ir(x, y - 1); cout << " "; ir(x + 1, y - 1); cout << " ";
	ir(x - 1, y); cout << " "; ir(x + 1, y); cout << " ";
	ir(x - 1, y + 1); cout << " "; ir(x, y + 1); cout << " "; ir(x + 1, y + 1); cout << " ";
	SonidoTeletransporte();
	for (int i = 1; i <= 10; i++){
		colorfondo(fase1); ir(x - 1, y + 1); cout << " "; colorfondo(colorf); ir(x, y + 1); cout << " "; Sleep(retraso);
		colorfondo(fase1); ir(x - 1, y); cout << " "; colorfondo(colorf); ir(x - 1, y + 1); cout << " "; Sleep(retraso);
		colorfondo(fase1); ir(x - 1, y - 1); cout << " "; colorfondo(colorf); ir(x - 1, y); cout << " "; Sleep(retraso);
		colorfondo(fase1); ir(x, y - 1); cout << " "; colorfondo(colorf); ir(x - 1, y - 1); cout << " "; Sleep(retraso);
		colorfondo(fase1); ir(x + 1, y - 1); cout << " "; colorfondo(colorf); ir(x, y - 1); cout << " "; Sleep(retraso);
		colorfondo(fase1); ir(x + 1, y); cout << " "; colorfondo(colorf); ir(x + 1, y - 1); cout << " "; Sleep(retraso);
		colorfondo(fase1); ir(x + 1, y + 1); cout << " "; colorfondo(colorf); ir(x + 1, y); cout << " "; Sleep(retraso);
		colorfondo(fase1); ir(x - 1, y + 1); cout << " "; colorfondo(colorf); ir(x + 1, y + 1); cout << " "; Sleep(retraso);
		if (i == 1)retraso = 50; if (i == 2)retraso = 20; if (i == 3)retraso = 10; if (i == 4)retraso = 5; if (i == 5)retraso = 2; if (i == 6)retraso = 1;
		if (i == 7)retraso = 0;
	}
	for (int i = 1; i <= 10; i++){
		colorfondo(colorf); colorletra(letra);
		ir(x - 1, y - 1); cout << "+"; ir(x, y - 1); cout << "+"; ir(x + 1, y - 1); cout << "+";
		ir(x - 1, y); cout << "+"; ir(x + 1, y); cout << "+";
		ir(x - 1, y + 1); cout << "+"; ir(x, y + 1); cout << "+"; ir(x + 1, y + 1); cout << "+";
		Sleep(10);
		ir(x - 1, y - 1); cout << "x"; ir(x, y - 1); cout << "x"; ir(x + 1, y - 1); cout << "x";
		ir(x - 1, y); cout << "x"; ir(x + 1, y); cout << "x";
		ir(x - 1, y + 1); cout << "x"; ir(x, y + 1); cout << "x"; ir(x + 1, y + 1); cout << "x";
		Sleep(10);
	}
}
void ArmarPuente(int nivel, int x, int y)
{
	for (int i = 10; i <= 16; i++)PintarCaja(nivel, x, y, 0, 10, 8, '*');
	Sleep(120);
	for (int i = 10; i <= 16; i++)PintarCaja(nivel, x, y, 0, 10, 16, 'x');
	Sleep(120);
	for (int i = 10; i <= 16; i++)PintarCaja(nivel, x, y, 0, 10, 9, 'X');
	Sleep(120);
	for (int i = 10; i <= 16; i++)PintarCaja(nivel, x, y, 0, 9, 1, '+');
	Sleep(120);
	for (int i = 10; i <= 16; i++)PintarCaja(nivel, x, y, 0, 9, 1, 'X');
	Sleep(120);
	for (int i = 10; i <= 16; i++)PintarCaja(nivel, x, y, 0, 10, 9, '+');
}
void Retroceder(int nivel, int x, int y)
{
	Musicatiempo(1);
	for (int i = 1; i <= 4; i++){
		ir(x, y); colorfondo(1); colorletra(2); cout << char(219);
		ir(x + 1, y); colorfondo(1); colorletra(3); cout << char(219);
		ir(x, y + 1); colorfondo(1); colorletra(7); cout << char(219);
		ir(x + 1, y + 1); colorfondo(1); colorletra(4); cout << char(219);
		Sleep(100);
		ir(x, y); colorfondo(1); colorletra(4); cout << char(219);
		ir(x + 1, y); colorfondo(1); colorletra(2); cout << char(219);
		ir(x, y + 1); colorfondo(1); colorletra(3); cout << char(219);
		ir(x + 1, y + 1); colorfondo(1); colorletra(7); cout << char(219);
		Sleep(100);
		ir(x, y); colorfondo(1); colorletra(7); cout << char(219);
		ir(x + 1, y); colorfondo(1); colorletra(4); cout << char(219);
		ir(x, y + 1); colorfondo(1); colorletra(2); cout << char(219);
		ir(x + 1, y + 1); colorfondo(1); colorletra(3); cout << char(219);
		Sleep(100);
		ir(x, y); colorfondo(1); colorletra(3); cout << char(219);
		ir(x + 1, y); colorfondo(1); colorletra(7); cout << char(219);
		ir(x, y + 1); colorfondo(1); colorletra(4); cout << char(219);
		ir(x + 1, y + 1); colorfondo(1); colorletra(2); cout << char(219);
		Sleep(100);
	}
}
void PortalInteractivo(int nivel, int x = -1, int y = -1, int modo = 1)//Pinta el movil dependiendo del nivel en la que se encuentre, notese que los modelos pueden cambiar con el nivel
{
	int xportal; int yportal;//coordenadas del portal
	if (nivel == 1){ xportal = 36; yportal = 34; }
	if (nivel == 2){ xportal = 42; yportal = 18; }
	if (nivel == 3){ xportal = 36; yportal = 28; }
	if (nivel == 4){ xportal = 38; yportal = 12; }
	if (nivel == 5) { xportal = 40; yportal = 6; }

	if (nivel == 1)colorfondo(6);
	if (nivel == 2)colorfondo(7);
	if (nivel == 3)colorfondo(5);
	if (nivel == 4)colorfondo(8);
	if (nivel == 5)colorfondo(2);
	if (x == -1 || y == -1){ x = xportal; y = yportal; }
	int color = 1;
	if (modo == 1){
		MusicaAparecePortal();
		for (int i = 2; i <= 16; i++){
			ir(x, y); colorletra(i); cout << char(178);
			ir(x + 1, y); colorletra(i); cout << char(178);
			ir(x, y + 1); colorletra(i); cout << char(178);
			ir(x + 1, y + 1); colorletra(i); cout << char(178);
			Sleep(10);
		}
	}
	if (modo == 2){
		MusicaDesaparecePortal();
		for (int i = 16; i >= 1; i--){
			ir(x, y); colorletra(i); cout << char(178);
			ir(x + 1, y); colorletra(i); cout << char(178);
			ir(x, y + 1); colorletra(i); cout << char(178);
			ir(x + 1, y + 1); colorletra(i); cout << char(178);
			Sleep(10);
		}
	}
	PBorrar(nivel, x, y);
}
void TeclasOcultas(int x, int y)
{
	for (int i = 0; i <= 16; i++){ PintarMovil(0, x, y, i, 1); Sleep(125); }PintarMovil(0, x, y, 9, 1); Sleep(125);
}
//------------------------------------------------------------------------------------------

//----------------------CONTROL DE SPRITES--------------------------------------------------------------------
void jokerGif(int **matriz)
{
	joker01(matriz); GIF(matriz, 0, 54, 0, 41, 2, 5, 0, 0, 0, 36); Sleep(500);
	joker02(matriz); GIF(matriz, 0, 54, 0, 41, 2, 5, 0, 0, 0, 74); Sleep(500);

	RisaJocker();
	for (int i = 0; i <= 7; i++){
		joker03(matriz); GIF(matriz, 0, 41, 0, 41, 2, 5, 1, 16, 0, 78); Sleep(10);
		joker04(matriz); GIF(matriz, 0, 41, 0, 41, 2, 5, 1, 16, 0, 78); Sleep(10);
	}
	colorfondo(2);
	ir(20 + 2, 16 + 6); cout << "    "; ir(30 + 2, 16 + 6); cout << "  ";
	ir(20 + 2, 17 + 6); cout << "    "; ir(30 + 2, 17 + 6); cout << "  ";


}
void DuckHuntGif(int **matriz){

	dh1(matriz);
	for (int i = 0; i <= 34; i++){ GIF(matriz, 0, i, 0, 28, 12, 62 - i, 1, 16); Sleep(1); }
	YouWinYouLose(matriz);
	int nr = nrandom(0, 199); nr /= 100;

	if (nr == 0)GIF(matriz, 0, 14, 30, 54, 42, 12, 1, 16, 0, 78);
	if (nr == 1)GIF(matriz, 17, 31, 32, 54, 42, 12, 1, 16, 0, 78);

	Sleep(200);

	int n = nrandom(1, 200);
	if (n<100)RisaDuckHunt(1);
	if (n >= 100)RisaDuckHunt(2);

	if (n<100)for (int i = 0; i <= 5; i++){
		dh1(matriz); GIF(matriz, 0, 21, 0, 28, 12, 28, 1, 16, 0, 74); Sleep(15);
		dh2(matriz); GIF(matriz, 0, 21, 0, 28, 12, 28, 1, 16, 0, 14); Sleep(15);
	}

	if (n >= 100)for (int i = 0; i <= 10; i++){
		dh1(matriz); GIF(matriz, 0, 21, 0, 28, 12, 28, 1, 16, 0, 74); Sleep(15);
		dh2(matriz); GIF(matriz, 0, 21, 0, 28, 12, 28, 1, 16, 0, 14); Sleep(15);
	}

	dh1(matriz);
	GIF(matriz, 0, 34, 0, 28, 12, 28, 1, 16); Sleep(1);
	for (int i = 0; i <= 36; i++){
		GIF(matriz, 0, 34 - i, 0, 28, 12, 28 + i, 1, 16, 0, 12);
		colorletra(16); ir(17, 27 + i); cout << "                      ";
	}
	ir(0, 0);


}
void NientiendoGif(int **matriz)
{
	int a = nrandom(1, 200);
	if (a<100){
		desvanecimiento(1); Sleep(100);
		ni1(matriz); GIF(matriz, 0, 16, 0, 64, 7, 21, 1, 1, 0, 78); SonidoGameCoin(); Sleep(1000);
		ni2(matriz); GIF(matriz, 0, 16, 0, 65, 6, 21, 1, 1, 0, 98); Sleep(0);
		ni3(matriz); GIF(matriz, 0, 16, 0, 66, 5, 21, 1, 1, 0, 32); Sleep(0);
		ni4(matriz); GIF(matriz, 0, 16, 0, 67, 4, 21, 1, 1, 0, 12); Sleep(0);
		ni5(matriz); GIF(matriz, 0, 16, 0, 68, 4, 21, 1, 1, 0, 78); Sleep(0);
		ni6(matriz); GIF(matriz, 0, 16, 0, 69, 4, 21, 1, 1, 0, 98); Sleep(0);
		ni7(matriz); GIF(matriz, 0, 16, 0, 70, 4, 21, 1, 1, 0, 32); Sleep(0);
		ni8(matriz); GIF(matriz, 0, 16, 0, 71, 4, 21, 1, 1, 0, 12); Sleep(0);
		ni9(matriz); GIF(matriz, 0, 16, 0, 72, 4, 21, 1, 1, 0, 78); Sleep(0);
		ni10(matriz); GIF(matriz, 0, 16, 0, 73, 4, 21, 1, 1, 0, 98); Sleep(0);
		ni11(matriz); GIF(matriz, 0, 16, 0, 74, 3, 21, 1, 1, 0, 32); Sleep(0);
		ni12(matriz); GIF(matriz, 0, 16, 0, 75, 2, 21, 1, 1, 0, 12); Sleep(0);
		ni13(matriz); GIF(matriz, 0, 16, 0, 76, 1, 21, 1, 1, 0, 78); Sleep(1000);

		desvanecimiento(9);
	}
	if (a >= 100){
		desvanecimiento(1); Sleep(100);
		ni1(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 78); SonidoGameCoin(); Sleep(1000);
		ni2(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 98); Sleep(0);
		ni3(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 32); Sleep(0);
		ni4(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 12); Sleep(0);
		ni5(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 78); Sleep(0);
		ni6(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 98); Sleep(0);
		ni7(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 32); Sleep(0);
		ni8(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 12); Sleep(0);
		ni9(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 78); Sleep(0);
		ni10(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 98); Sleep(0);
		ni11(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 32); Sleep(0);
		ni12(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 12); Sleep(0);
		ni13(matriz); GIF(matriz, 0, 16, 0, 77, 1, 21, 1, 1, 0, 78); Sleep(1000);

	}

}
void PushBox(int **matriz){
	int matrizint[63][80] =
	{ { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 5, 5, 5 },
	{ 5, 5, 5, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 5, 5, 5 },
	{ 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 5, 5, 5 },
	{ 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 5, 5, 5 },
	{ 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 5, 5, 5 },
	{ 2, 2, 2, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 3, 3, 3, 3, 3, 3, 3, 9, 9, 3, 3, 3, 9, 9, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 3, 3, 3, 3, 3, 9, 9, 3, 3, 3, 3, 3, 3, 3, 9, 9, 3, 3, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 3, 3, 3, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 9, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 3, 3, 3, 9, 16, 9, 9, 3, 3, 3, 3, 3, 3, 3, 9, 9, 16, 9, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 3, 3, 3, 9, 16, 16, 16, 9, 9, 3, 3, 3, 9, 9, 16, 16, 16, 9, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 3, 9, 16, 16, 16, 16, 16, 9, 9, 9, 16, 16, 16, 16, 16, 9, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 3, 9, 7, 16, 16, 16, 16, 16, 9, 16, 16, 16, 16, 16, 7, 9, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 3, 3, 3, 3, 3, 9, 7, 7, 7, 16, 16, 16, 9, 16, 16, 16, 7, 7, 7, 9, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 3, 3, 3, 3, 3, 9, 7, 7, 7, 7, 7, 16, 9, 16, 7, 7, 7, 7, 7, 9, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 3, 3, 3, 9, 15, 7, 7, 7, 7, 7, 9, 7, 7, 7, 7, 7, 15, 9, 3, 3, 3 },
	{ 3, 3, 3, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 3, 3, 3, 9, 15, 15, 15, 7, 7, 7, 9, 7, 7, 7, 15, 15, 15, 9, 3, 3, 3 },
	{ 5, 5, 5, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 5, 5, 5, 9, 15, 15, 15, 15, 15, 7, 9, 7, 15, 15, 15, 15, 15, 9, 5, 5, 5 },
	{ 5, 5, 5, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 5, 5, 5, 9, 9, 15, 15, 15, 15, 15, 9, 15, 15, 15, 15, 15, 9, 9, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 9, 9, 15, 15, 15, 9, 15, 15, 15, 9, 9, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 9, 9, 15, 9, 15, 9, 9, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 5, 5, 5, 5, 9, 8, 8, 8, 8, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 8, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 9, 9, 5, 5, 5, 5, 5, 5, 5, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 5, 5, 5, 9, 8, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 8, 9, 9, 5, 5, 5, 5, 5, 9, 8, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 8, 9, 9, 9, 5, 5, 5, 5, 5, 5, 9, 8, 8, 8, 9, 9, 5, 5, 5, 9, 8, 8, 8, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 5, 5, 5, 9, 8, 9, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 8, 9, 9, 9, 5, 5, 5, 9, 9, 8, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 8, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 9, 9, 9, 9, 5, 5, 5, 5, 5, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 5, 5, 5, 5, 5, 9, 9, 5, 5, 5, 5, 5, 5, 5, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 7, 9, 7, 9, 7, 9, 7, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 }
	};
	int f, c; for (f = 0; f <63; f++)for (c = 0; c <80; c++)matriz[f][c] = matrizint[f][c];
}
void Cplusplus(int **matriz){
	int matrizint[40][46] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 9, 8, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 0, 0, 0, 0, 9, 8, 8, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 8, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 8, 8, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 8, 8, 8, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 8, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 8, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 8, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 8, 8, 8, 9, 9, 9, 9, 9, 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 8, 8, 8, 8, 9, 9, 0, 0, 0, 0, 9, 9, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 9, 9, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 9, 9, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 7, 7, 7, 9, 9, 9, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 8, 8, 8, 8, 8, 8, 8, 9, 9, 0, 0, 9, 9, 8, 8, 8, 8, 8, 8, 8, 9, 9, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 9, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 9, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 0, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, -1, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 9, 7, 7, 7, 7, 9, 9, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 9, 0, 0, 0, 0, 0, 0, 9, 8, 8, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 9, 7, 7, 7, 9, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 9, 7, 7, 7, 7, 9, 9, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 0, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 0, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, -1, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 0, 0, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 9, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 7, 7, 7, 9, 9, 9, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 9, 9, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 8, 8, 8, 8, 8, 8, 8, 9, 9, 0, 0, 9, 9, 8, 8, 8, 8, 8, 8, 8, 9, 9, 0, 0, 9, 9, 8, 8, 8, 8, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 9, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 9, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 0, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 9, 0, 0, 0, 0, 0, 0, 9, 8, 8, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 0, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 0, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 0, 0, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 9, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 9, 9, 8, 8, 8, 8, 8, 9, 9, 9, 0, 0, 0, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 0, 0, 9, 9, 8, 8, 8, 8, 8, 8, 8, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 8, 8, 8, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f <40; f++)for (c = 0; c <46; c++)matriz[f][c] = matrizint[f][c];

}
void Warning(int color, int fi, int ff, int ci, int cf, int x, int y){
	int matrizint[21][32] =
	{ { 2, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 0, 2, 2, 0 },
	{ 2, 0, 0, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 0, 2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 0, 2, 0, 2, 0, 0, 0 },
	{ 2, 0, 0, 0, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 0, 2, 0, 2, 2 },
	{ 2, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 2, 0, 2, 0, 2, 0, 2, 2, 0, 2, 0, 0, 2 },
	{ 0, 2, 0, 2, 0, 0, 2, 0, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 0, 2, 2, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c;

	for (c = ci; c <= cf; c++){
		for (f = fi; f <= ff; f++){
			if (matrizint[f][c] == 9 || matrizint[f][c] == 2){ ir(x + c - ci, y + f - fi); colorfondo(color); cout << " "; }
		}
	}


}
void Pacmansprites(int **matriz){
	int matrizint[30][41] =
	{ { 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0 },
	{ 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0 },
	{ 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0 },
	{ 0, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0 },
	{ 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
	{ 0, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0 },
	{ 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0 },
	{ 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0 },
	{ 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0 },
	{ 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0 },
	{ 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0 },
	{ 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 0 },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7 },
	{ 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 0 },
	{ 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0 },
	{ 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0 },
	{ 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f <30; f++)for (c = 0; c <41; c++)matriz[f][c] = matrizint[f][c];

}
void LinkSprite(int **matriz){
	int matrizint[19][48] =
	{ { 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 3, 3, 3, 3, 3, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 3, 3, 3, 3, 3, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 3, 3, 3, 3, 3, 3, 9, 0, 0 },
	{ 0, 0, 0, 9, 3, 3, 3, 3, 3, 3, 3, 3, 9, 0, 0, 0, 0, 0, 0, 0, 9, 3, 3, 3, 3, 3, 3, 3, 3, 9, 0, 0, 0, 0, 0, 0, 0, 9, 3, 3, 3, 3, 3, 3, 3, 3, 9, 0 },
	{ 0, 0, 9, 3, 3, 15, 15, 15, 15, 15, 15, 3, 9, 0, 0, 0, 0, 0, 0, 9, 3, 3, 15, 15, 15, 15, 15, 15, 3, 9, 0, 0, 0, 0, 0, 0, 9, 3, 3, 15, 15, 15, 15, 15, 15, 3, 9, 0 },
	{ 0, 0, 9, 3, 15, 15, 7, 7, 15, 15, 15, 15, 9, 0, 0, 0, 0, 0, 0, 9, 3, 15, 15, 7, 7, 15, 15, 15, 15, 9, 0, 0, 0, 0, 0, 0, 9, 3, 15, 15, 7, 7, 15, 15, 15, 15, 9, 0 },
	{ 0, 0, 9, 9, 15, 7, 7, 7, 7, 7, 15, 15, 15, 9, 0, 0, 0, 0, 0, 9, 9, 15, 7, 7, 7, 7, 7, 15, 15, 15, 9, 0, 0, 0, 0, 0, 9, 9, 15, 7, 7, 7, 7, 7, 15, 15, 15, 0 },
	{ 0, 9, 3, 9, 7, 7, 9, 7, 7, 9, 7, 7, 9, 0, 0, 0, 0, 0, 9, 3, 9, 7, 7, 9, 7, 7, 9, 7, 7, 9, 0, 0, 0, 0, 0, 9, 3, 9, 7, 7, 9, 7, 7, 9, 7, 7, 9, 0 },
	{ 9, 3, 3, 9, 7, 7, 9, 7, 7, 9, 7, 7, 9, 0, 0, 0, 0, 9, 3, 3, 9, 7, 7, 9, 7, 7, 9, 7, 7, 9, 0, 0, 0, 0, 9, 3, 3, 9, 7, 7, 9, 7, 7, 9, 7, 7, 9, 0 },
	{ 0, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 0, 0, 0, 0, 0, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 0, 0, 0, 0, 0, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 0 },
	{ 0, 0, 0, 0, 9, 7, 7, 7, 7, 7, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 7, 7, 7, 7, 7, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 7, 7, 7, 7, 7, 7, 9, 0, 0 },
	{ 0, 0, 0, 9, 9, 9, 7, 7, 7, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 3, 3, 7, 7, 7, 7, 3, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 7, 7, 7, 7, 9, 9, 9, 0 },
	{ 0, 0, 9, 7, 7, 7, 3, 15, 15, 3, 3, 9, 0, 0, 0, 0, 0, 0, 0, 9, 7, 7, 3, 3, 15, 15, 3, 3, 7, 7, 9, 0, 0, 0, 0, 0, 0, 0, 9, 3, 3, 15, 15, 3, 7, 7, 7, 9 },
	{ 0, 0, 9, 7, 7, 7, 3, 3, 3, 3, 3, 7, 9, 0, 0, 0, 0, 0, 0, 9, 7, 7, 3, 3, 3, 3, 3, 3, 7, 7, 9, 0, 0, 0, 0, 0, 0, 9, 7, 3, 3, 3, 3, 3, 7, 7, 7, 9 },
	{ 0, 0, 9, 7, 7, 7, 15, 15, 15, 15, 15, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 15, 15, 15, 15, 15, 15, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 15, 15, 15, 15, 15, 7, 7, 7, 9 },
	{ 0, 0, 0, 9, 9, 3, 3, 3, 3, 3, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 3, 3, 3, 3, 3, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 3, 3, 3, 3, 3, 3, 9, 9, 0 },
	{ 0, 0, 0, 0, 9, 3, 3, 3, 3, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 7, 7, 9, 9, 7, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 3, 3, 3, 3, 9, 0, 0 },
	{ 0, 0, 0, 0, 9, 7, 7, 9, 9, 15, 15, 15, 9, 0, 0, 0, 0, 0, 0, 0, 9, 15, 15, 15, 9, 9, 15, 15, 15, 9, 0, 0, 0, 0, 0, 0, 0, 9, 15, 15, 15, 9, 9, 7, 7, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 9, 9, 15, 15, 15, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 15, 15, 15, 9, 9, 9, 9, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f <19; f++)for (c = 0; c <48; c++)matriz[f][c] = matrizint[f][c];
}
void GameOver(int x = 46, int y = 1, int color = 9, int caracter = 219, int demora = 0){
	int matrizint[61][33] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0 },
	{ 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9 }
	};

	int f, c;
	for (c = 0; c <33; c++){
		for (f = 0; f <61; f++){
			if (matrizint[f][c] == 9){ ir(x + c, y + f); colorletra(color); cout << char(caracter); Sleep(demora); }
		}
	}

}
void OpcionesMenu(int opcion, int x, int y){
	int matrizint[33][55] =
	{ { 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 0, 0, 0, 9, 0, 9, 9, 0, 0, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 2, 2, 1, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 0, 0, 0, 9, 0, 9, 9, 0, 0, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 2, 1, 1, 1, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 0, 0, 0, 9, 0, 9, 9, 0, 0, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 0, 0, 0, 9, 0, 9, 9, 0, 0, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 9, 2, 2, 9, 1, 1, 9, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 0, 0, 0, 9, 0, 9, 9, 0, 0, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 1, 9, 9, 9, 1, 1, 9, 9, 9, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 1, 1, 1, 9, 9, 1, 1, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 9, 0, 9, 9, 0, 0, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 9, 9, 0, 0, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 9, 0, 9, 9, 0, 0, 9, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 9, 9, 0, 0, 9, 0, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 0, 0, 9, 9, 0, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 0, 0, 9, 9, 0, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	colorletra(16);
	int f, c;
	for (f = 0; f <33; f++){ for (c = 12; c <55; c++){ if (matrizint[f][c] == 9){ ir(c + x - 12, f + y); cout << char(219); } } }
	if (opcion == 1){
		for (f = 0; f <13; f++)for (c = 0; c <12; c++){ ir(c + x - 14, f + y + 12); colorletra(9); cout << char(219); }
		for (f = 0; f <13; f++)for (c = 0; c <12; c++){ ir(c + x - 4, f + y + 23); colorletra(9); cout << char(219); }
		for (f = 0; f <13; f++){
			for (c = 0; c <12; c++){
				if (matrizint[f][c] == 9){ ir(c + x - 8, f + y - 2); colorletra(16); cout << char(219); }
				if (matrizint[f][c] == 1){ ir(c + x - 8, f + y - 2); colorletra(1); cout << char(219); }
				if (matrizint[f][c] == 2){ ir(c + x - 8, f + y - 2); colorletra(2); cout << char(219); }
			}
		}

	}

	if (opcion == 2){
		for (f = 0; f <13; f++)for (c = 0; c <12; c++){ ir(c + x - 8, f + y - 2); colorletra(9); cout << char(219); }
		for (f = 0; f <13; f++)for (c = 0; c <12; c++){ ir(c + x - 4, f + y + 23); colorletra(9); cout << char(219); }
		for (f = 0; f <13; f++){
			for (c = 0; c <12; c++){
				if (matrizint[f][c] == 9){ ir(c + x - 14, f + y + 12); colorletra(16); cout << char(219); }
				if (matrizint[f][c] == 1){ ir(c + x - 14, f + y + 12); colorletra(1); cout << char(219); }
				if (matrizint[f][c] == 2){ ir(c + x - 14, f + y + 12); colorletra(2); cout << char(219); }
			}
		}
	}
	if (opcion == 3){
		for (f = 0; f <13; f++)for (c = 0; c <12; c++){ ir(c + x - 14, f + y + 12); colorletra(9); cout << char(219); }
		for (f = 0; f <13; f++)for (c = 0; c <12; c++){ ir(c + x - 8, f + y - 2); colorletra(9); cout << char(219); }
		for (f = 0; f <13; f++){
			for (c = 0; c <12; c++){
				if (matrizint[f][c] == 9){ ir(c + x - 4, f + y + 23); colorletra(16); cout << char(219); }
				if (matrizint[f][c] == 1){ ir(c + x - 4, f + y + 23); colorletra(1); cout << char(219); }
				if (matrizint[f][c] == 2){ ir(c + x - 4, f + y + 23); colorletra(2); cout << char(219); }
			}
		}
	}

}
void AsciiFuncion(int **matriz, int cb = 16, int cc = 16, int cr = 16, int ce = 16, int car = 223, int modo = 1)
{
	int f, c;
	if (modo == 1){
		for (f = 0; f < 35; f++){
			for (c = 0; c < 61; c++)
			{
				ir(c + 10, f + 13); colorfondo(9);
				if (matriz[f][c] == 5){
					if (f<13){ colorletra(cc); cout << char(car); }
					else if (f<22){ colorletra(cr); cout << char(car); }
					else{ colorletra(ce); cout << char(car); }
				}
			}
		}//END FORS MODO 1	
	}//end modo 1
	if (modo == 2){
		for (f = 34; f >= 0; f--){
			for (c = 60; c >= 0; c--)
			{
				ir(c + 10, f + 13); colorfondo(9);
				if (matriz[f][c] == 5){
					if (f<13){ colorletra(cc); cout << char(car); }
					else if (f<22){ colorletra(cr); cout << char(car); }
					else{ colorletra(ce); cout << char(car); }
				}
			}
		}//END FORS MODO 2	
	}//end modo 2
	if (modo == 0){
		colorfondo(9); colorletra(cb);
		for (c = 1, f = 0; c <= 59; c++){ ir(c + 10, f + 13); cout << char(205); Sleep(0.5); }
		cout << char(187); Sleep(1);
		for (c = 60, f = 1; f <= 33; f++){ ir(c + 10, f + 13); cout << char(186); Sleep(0.5); }
		ir(60 + 10, 34 + 13); cout << char(188); Sleep(0.5);
		for (c = 59, f = 34; c >= 1; c--){ ir(c + 10, f + 13); cout << char(205); Sleep(0.5); }
		ir(0 + 10, 34 + 13); cout << char(200); Sleep(0.5);
		for (c = 0, f = 33; f >= 1; f--){ ir(c + 10, f + 13); cout << char(186); Sleep(0.5); }
		ir(0 + 10, 0 + 13); cout << char(201); Sleep(0.5);
		for (f = 0; f < 35; f++){ for (c = 0; c < 61; c++){ if (matriz[f][c] == 0){ ir(c + 10, f + 13); cout << " "; }if (matriz[f][c] == 5){ ir(c + 10, f + 13); colorletra(1); cout << char(car); } } }
		for (f = 0; f < 35; f++){ for (c = 0; c < 61; c++){ if (matriz[f][c] == 0){ ir(c + 10, f + 13); cout << " "; }if (matriz[f][c] == 5){ ir(c + 10, f + 13); colorletra(8); cout << char(car); } } }
		for (f = 0; f < 35; f++){ for (c = 0; c < 61; c++){ if (matriz[f][c] == 0){ ir(c + 10, f + 13); cout << " "; }if (matriz[f][c] == 5){ ir(c + 10, f + 13); colorletra(cb); cout << char(car); } } }
	}//end modo 0

}
//-----------------------------------------------------------------------------------------------------------

//------------------------------INTERFACES----------------------------------------------------------
void InterfazCreditos(int **matriz){
	MusicaCreditos();
	desvanecimiento(1);
	UPC(matriz); GIF(matriz, 0, 54, 0, 58, 15, 5, 0, 0, 1, 32); Sleep(1500);

	desvanecimiento(5, 62, 79, 64); Sleep(100);
	int matrizint[63][80] =
	{ { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 5, 5, 13, 13, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 5, 5, 13, 13, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, 1, 1, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, 1, 1, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 7, 7, 9, 9, 9, 9, 5, 5, 13, 13, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 1, 1, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 7, 7, 9, 9, 9, 9, 5, 5, 13, 13, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 1, 1, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 13, 13, 5, 5, 13, 13, 13, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 13, 13, 5, 5, 13, 13, 13, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 13, 13, 5, 5, 13, 13, 13, 13, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 13, 13, 5, 5, 13, 13, 13, 13, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 13, 13, 13, 13, 13, 13, 13, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 13, 13, 13, 13, 13, 13, 13, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 3, 3, 3, 3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 7, 7, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 8, 8, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 3, 3, 3, 3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 7, 7, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 8, 8, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 11, 11, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 7, 7, 7, 7, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 1, 1, 1, 1, 8, 8, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 11, 11, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 7, 7, 7, 7, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 1, 1, 1, 1, 8, 8, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 9, 9, 2, 2, 2, 2, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 11, 11, 11, 11, 3, 3, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 7, 7, 9, 9, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 9, 9, 2, 2, 2, 2, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 11, 11, 11, 11, 3, 3, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 7, 7, 9, 9, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 3, 3, 3, 3, 11, 11, 3, 3, 11, 11, 3, 3, 9, 9, 2, 2, 2, 9, 15, 15, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 3, 3, 3, 3, 11, 11, 3, 3, 11, 11, 3, 3, 9, 9, 2, 2, 2, 9, 15, 15, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5 },
	{ 9, 9, 2, 2, 12, 12, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 9, 9, 9, 9, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 9, 9, 2, 2, 12, 12, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 9, 9, 9, 9, 2, 2, 9, 15, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 9, 9, 2, 2, 12, 12, 2, 2, 9, 9, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5 },
	{ 9, 9, 2, 2, 12, 12, 2, 2, 9, 9, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5 },
	{ 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 9, 9, 16, 16, 16, 16, 16, 16, 9, 9, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 9, 9, 5, 5, 5, 5 },
	{ 5, 9, 9, 2, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 15, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 9, 9, 16, 16, 16, 16, 16, 16, 9, 9, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 9, 9, 5, 5, 5, 5 },
	{ 5, 9, 9, 2, 2, 2, 9, 15, 9, 15, 15, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 1, 1, 16, 16, 16, 16, 16, 16, 16, 16, 9, 9, 9, 9, 9, 9, 16, 16, 16, 16, 1, 1, 9, 9, 5, 5 },
	{ 5, 9, 9, 2, 2, 2, 9, 9, 9, 15, 15, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 1, 1, 16, 16, 16, 16, 16, 16, 16, 16, 9, 9, 9, 9, 9, 9, 16, 16, 16, 16, 1, 1, 9, 9, 5, 5 },
	{ 5, 9, 9, 9, 9, 9, 2, 2, 9, 9, 9, 11, 11, 3, 3, 11, 11, 3, 3, 9, 9, 2, 2, 2, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 1, 1, 16, 16, 16, 16, 16, 16, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 16, 16, 1, 1, 9, 9, 5, 5 },
	{ 5, 9, 9, 9, 15, 9, 2, 2, 9, 9, 9, 11, 11, 3, 3, 11, 11, 3, 3, 9, 9, 2, 2, 2, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 1, 1, 16, 16, 16, 16, 16, 16, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 16, 16, 1, 1, 9, 9, 5, 5 },
	{ 5, 9, 9, 9, 9, 9, 2, 2, 9, 9, 9, 3, 3, 11, 11, 3, 3, 11, 11, 15, 15, 9, 9, 2, 2, 2, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 16, 16, 16, 16, 16, 16, 9, 9, 1, 1, 1, 1, 9, 9, 1, 1, 9, 9, 9, 9, 16, 16, 9, 9, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 9, 9, 9, 9, 9, 3, 3, 11, 11, 3, 3, 11, 11, 15, 15, 9, 9, 2, 2, 2, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 16, 16, 16, 16, 16, 16, 9, 9, 1, 1, 1, 1, 9, 9, 1, 1, 9, 9, 9, 9, 16, 16, 9, 9, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 9, 15, 9, 9, 9, 11, 11, 3, 3, 11, 11, 3, 3, 15, 15, 9, 9, 2, 2, 2, 9, 9, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 9, 9, 16, 16, 16, 16, 16, 16, 9, 9, 1, 1, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 9, 9, 9, 9, 9, 11, 11, 3, 3, 11, 11, 3, 3, 15, 15, 9, 9, 2, 2, 2, 9, 9, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 9, 9, 16, 16, 16, 16, 16, 16, 9, 9, 1, 1, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 11, 11, 3, 3, 11, 11, 9, 9, 2, 2, 2, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 16, 16, 16, 16, 16, 16, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 11, 11, 3, 3, 11, 11, 9, 9, 2, 2, 2, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 16, 16, 16, 16, 16, 16, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 2, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 16, 16, 16, 16, 16, 16, 9, 9, 9, 9, 9, 9, 9, 9, 16, 16, 16, 16, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 9, 9, 2, 2, 2, 9, 2, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 16, 16, 16, 16, 16, 16, 9, 9, 9, 9, 9, 9, 9, 9, 16, 16, 16, 16, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 2, 2, 2, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 9, 9, 9, 9, 5, 5 },
	{ 5, 5, 9, 9, 9, 9, 2, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 9, 9, 9, 9, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 9, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 16, 16, 1, 1, 16, 16, 16, 16, 16, 16, 16, 16, 9, 9, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 9, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 16, 16, 1, 1, 16, 16, 16, 16, 16, 16, 16, 16, 9, 9, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 9, 2, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 1, 1, 16, 16, 16, 16, 16, 16, 9, 9, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 2, 2, 9, 2, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 1, 1, 16, 16, 16, 16, 16, 16, 9, 9, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 16, 16, 16, 16, 9, 9, 5, 5 },
	{ 5, 5, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 16, 16, 16, 16, 9, 9, 5, 5 },
	{ 5, 5, 5, 5, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 5, 5, 5, 5 }
	};
	int f, c; for (f = 0; f <63; f++)for (c = 0; c <80; c++)matriz[f][c] = matrizint[f][c];


	GIF(matriz, 0, 62, 0, 38, 0, 0, 0, 0, 2, 74);
	colorletra(9); colorfondo(5);
	ir(7, 10); cout << " Diego"; ir(7, 11); cout << "  Jara";
	GIF(matriz, 0, 62, 39, 79, 39, 0, 0, 0, 2, 96);
	colorletra(9); colorfondo(5);
	ir(65, 11); cout << " Jeremy"; ir(65, 12); cout << " Tornero";
	esperartecla();
}
void InterfazYouLose(int **matriz)
{
	desvanecimiento(16); Sleep(200);
	MusicaMuerte(2);
	DuckHuntGif(matriz);
	desvanecimiento(9);
}
void InterfazYouWin(int **matriz)
{

	YouWinYouLose(matriz); colorletra(9); colorfondo(1);
	SonidoSpiderman();
	for (int i = 0; i <= 62; i++){ for (int k = 0; k <= 24; k++){ ir(38 + k, i); cout << char(176); }Sleep(20); }//telaranias

	for (int i = 62; i >= 33; i--){ GIF(matriz, i, 62, 0, 18, 41, 0, 2, 109176, 0, 12); Sleep(0); }//Aparece spiderman

	for (int i = 0; i <= 15; i++){ GIF(matriz, 32, 62, 0, 18, 41, i, 2, 109176, 0, 12); Sleep(0); }//Spiderman al centro

	for (int i = 1; i <= 2; i++)//Spiderman parpadea
	{
		GIF(matriz, 32, 62, 0, 18, 41, 15, 0, 0, 0, 12); Sleep(200); GIF(matriz, 32, 62, 19, 37, 41, 15, 0, 0, 0, 12); Sleep(0); GIF(matriz, 32, 62, 38, 56, 41, 15, 0, 0, 0, 12); Sleep(50);
	}
	GIF(matriz, 32, 62, 0, 18, 41, 15, 0, 0, 0, 12); Sleep(1000);

	colorfondo(16); MusicaYouWin();
	for (int f = 0; f <= 62; f++){ for (int i = 0; i <= 37; i++){ ir(i, f); cout << " "; }for (int i = 63; i <= 79; i++){ ir(i, f); cout << " "; }Sleep(13); }//Se rellena la pantalla

	int xa, ya, xb, yb, ta, na;
	na = nrandom(0, 199);
	if ((na / 100) == 0){ xa = 2, ya = 0, xb = 23, yb = 14; }
	if ((na / 100) == 1){ xa = 3, ya = 17, xb = 21, yb = 31; }

	for (int i = yb; i >= ya; i--){ GIF(matriz, i, yb, xa, xb, 10, 0, 1, 16, 0, 12); Sleep(20); }//Aparece You Win
	for (int i = 0; i <= 20; i++){ GIF(matriz, ya, yb, xa, xb, 10, i, 1, 16, 0, 12); Sleep(20); if (i != 0){ ir(10, i - 1); cout << "                       "; } }//yOu Win al centro

	for (int i = 1; i <= 2; i++)//spiderman se despide
	{
		GIF(matriz, 32, 62, 0, 18, 41, 15, 0, 0, 0, 12); Sleep(200); GIF(matriz, 32, 62, 19, 37, 41, 15, 0, 0, 0, 12); Sleep(0); GIF(matriz, 32, 62, 38, 56, 41, 15, 0, 0, 0, 12); Sleep(50);
	}
	GIF(matriz, 32, 62, 0, 18, 41, 15, 0, 0, 0, 12); Sleep(1000);

	for (int i = 16; i <= 32; i++){ GIF(matriz, 32, 62, 0, 18, 41, i, 2, 109176, 0, 12); Sleep(0); }//Spiderman se va

	for (int i = 1; i <= 30; i++){ GIF(matriz, 32, 62 - i, 0, 18, 41, i + 32, 2, 109176, 0, 12); Sleep(0); }//Spiderman desaparece

	desvanecimiento(9, 62, 79, 64);

}
void InterfazCargando(int **matriz)
{
	desvanecimiento(1, 24, 79, 8, 0, 0);
	LinkSprite(matriz); GIF(matriz, 0, 18, 17, 30, 33, 1, 0, 0, 0, 78); CuadroDeTexto(15, 22, 64, 22, 1, 1, 13); int a = 1;
	for (int i = 1; i <= 50; i++){
		if (a == 1){ GIF(matriz, 0, 18, 0, 13, 33, 1, 1, 1, 0, 78); }//1
		if (a == 2){ GIF(matriz, 0, 18, 17, 30, 33, 1, 1, 1, 0, 78); }//0
		if (a == 3){ GIF(matriz, 0, 18, 34, 47, 33, 1, 1, 1, 0, 78); }//2
		if (a == 4){ GIF(matriz, 0, 18, 17, 30, 33, 1, 1, 1, 0, 78); }//0
		ir(14 + i, 22); colorletra(13); colorfondo(1); cout << char(219);
		a++; if (a == 5)a = 1; Sleep(80);
	}
}
void InterfazCongratulations(int **matriz, int **Cantidades){

	char teclac;; bool error = false;
	char *n1; n1 = new char[8];
	char *n2; n2 = new char[8];
	char *c; c = new char[1];
	int ci, fi, cf, ff, an;
	int t1 = -1, t2 = -1;
	do{
		Console::CursorVisible = FALSE;
		int **matrizcon; matrizcon = new int *[63]; for (int i = 0; i <= 62; i++){ matrizcon[i] = new int[80]; for (int k = 0; k <= 79; k++)matrizcon[i][k] = 3; }

		int ant = 0; int anp1 = 0; int anp2 = 0;
		c[0] = Cantidades[8][0]; t1 = Cantidades[8][1]; if (c[0] == '2')t2 = Cantidades[8][2];
		for (int i = 0; i <= t1 - 1; i++)n1[i] = Cantidades[6][i];
		if (c[0] == '2')for (int i = 0; i <= t2 - 1; i++)n2[i] = Cantidades[7][i];


		for (int i = 0; i <= t1 - 1; i++){ BuscarLetra(n1[i], ci, fi, cf, ff); anp1 += cf - ci + 1; }anp1 += t1 - 1; anp1 = 39 - anp1 / 2;
		for (int i = 0; i <= t2 - 1; i++){ BuscarLetra(n2[i], ci, fi, cf, ff); anp2 += cf - ci + 1; }anp2 += t2 - 1; anp2 = 39 - anp2 / 2;

		Abecedario(matriz);

		int yp;
		if (c[0] == '2')yp = 5; else yp = 15;
		for (int i = 0; i <= t1 - 1; i++){
			BuscarLetra(n1[i], ci, fi, cf, ff);
			for (int l = fi; l <= ff; l++)for (int k = ci; k <= cf; k++)matrizcon[yp + l - fi][anp1 + ant + 1 + k - ci] = matriz[l][k];
			an = cf - ci + 1; ant += an + 1;
		}
		ant = 0;
		if (c[0] == '2')for (int i = 0; i <= t2 - 1; i++){
			BuscarLetra(n2[i], ci, fi, cf, ff);
			for (int l = fi; l <= ff; l++)for (int k = ci; k <= cf; k++)matrizcon[yp + 16 + l - fi][anp2 + ant + 1 + k - ci] = matriz[l][k];
			an = cf - ci + 1; ant += an + 1;
		}

		limpiartecla(3);

		//Inicio Pacman Sprites
		desvanecimiento(9);
		Pacmansprites(matriz);
		int modo = 1; int modo2 = 6;
		int rec = 0; int is; int ip; int ref = 0;
		SonidoPacman();
		for (int i = -12; i <= 79; i++){

			if (i<0)rec = i; else rec = 0;
			if (i<0){ is = 0; ip = i; }
			else { is = i; ip = i; }

			if (i>67){ ref = i - 67; }
			if (i>67){ is = i; ip = 67; }

			if (i >= 1){
				if (modo == 1){ for (int l = 0; l <= 29; l++){ ir(i - 1, l); colorfondo(3); cout << " "; }GIF(matrizcon, 0, 29, i - 1, i - 1, i - 1, 0, 0, 0, 0, 14); }
				if (modo == 2){ for (int l = 0; l <= 29; l++){ ir(i - 1, l); colorfondo(3); cout << " "; }GIF(matrizcon, 0, 29, i - 1, i - 1, i - 1, 0, 0, 0, 0, 14); }
				if (modo == 3){ for (int l = 0; l <= 29; l++){ ir(i - 1, l); colorfondo(3); cout << " "; }GIF(matrizcon, 0, 29, i - 1, i - 1, i - 1, 0, 0, 0, 0, 14); }
			}
			if (modo == 1){ GIF(matriz, 0, 12, 0 - rec, 12 - ref, is, 16, 1, 9, 0, 74); Sleep(10); }
			if (modo == 2){ GIF(matriz, 0, 12, 13 - rec, 25 - ref, is, 16, 1, 9, 0, 74); Sleep(10); }
			if (modo == 3){ GIF(matriz, 0, 12, 28 - rec, 40 - ref, is, 16, 1, 9, 0, 74); Sleep(5); }

			if (i >= 1){
				if (i >= 68)ip = i;
				if (modo2 == 4){ for (int l = 30; l <= 62; l++){ ir(80 - ip, l); colorfondo(3); cout << " "; }GIF(matrizcon, 30, 62, 80 - ip, 80 - ip, 80 - ip, 30, 0, 0, 0, 36); }
				if (modo2 == 5){ for (int l = 30; l <= 62; l++){ ir(80 - ip, l); colorfondo(3); cout << " "; }GIF(matrizcon, 30, 62, 80 - ip, 80 - ip, 80 - ip, 30, 0, 0, 0, 36); }
				if (modo2 == 6){ for (int l = 30; l <= 62; l++){ ir(80 - ip, l); colorfondo(3); cout << " "; }GIF(matrizcon, 30, 62, 80 - ip, 80 - ip, 80 - ip, 30, 0, 0, 0, 36); }
			}
			if (i >= 68)ip = 67;
			if (modo2 == 4){ GIF(matriz, 17, 29, 0 + ref, 12 + rec, 67 - ip, 31, 1, 9, 0, 96); Sleep(5); }
			if (modo2 == 5){ GIF(matriz, 17, 29, 15 + ref, 27 + rec, 67 - ip, 31, 1, 9, 0, 96); Sleep(10); }
			if (modo2 == 6){ GIF(matriz, 17, 29, 28 + ref, 40 + rec, 67 - ip, 31, 1, 9, 0, 96); Sleep(10); }

			if (i == 79){
				for (int f = 0; f <= 29; f++){ ir(79, f); colorletra(3); cout << char(219); }
				for (int f = 30; f <= 62; f++){ ir(0, f); colorletra(3); cout << char(219); }
			}
			modo++; if (modo == 4)modo = 1; modo2--; if (modo2 == 3)modo2 = 6;
		}

		//Fin pacman Sprites
		//You are a Winner
		int emp;
		MusicaCongratulations();
		if (c[0] == '2')emp = 42; else emp = 35;
		UPC(matriz); GIF(matriz, 58, 75, 0, 58, 10, emp, 0, 0, 5, 78);
		//
		esperartecla();

		colorfondo(3); colorletra(9);

		ir(0, 0); for (int i = 0; i <= 79; i++)cout << " ";
		ir(0, 0); Escribir("Presiona 'K' para cambiar de nombre o 'E' para salir.", 10); do{
			limpiartecla(3); teclac = _getch();
		} while (teclac != 'K'&&teclac != 'k'&&teclac != 'E'&&teclac != 'e');
		if (teclac == 'E' || teclac == 'e')break;
		Console::CursorVisible = TRUE;
		limpiartecla(3);
		do{
			ir(0, 1); for (int i = 0; i <= 79; i++)cout << " ";
			ir(0, 1); Escribir("  Quieres usar un nombre o dos(1 o 2)? : ", 100, 2); scanf("%1s", c); limpiartecla(1);
		} while (c[0] != '1'&&c[0] != '2');

		do{
			ir(0, 2); for (int i = 0; i <= 79; i++)cout << " ";
			ir(0, 2); if (c[0] == '2')Escribir("  C\243al es tu primer nombre? : ", 100, 2); else Escribir("  C\243al es tu nombre? : ", 100, 2);
			scanf("%8s", n1); limpiartecla(1);
			for (int i = 0; i <= strlen(n1) - 1; i++)
			{
				if ((n1[i] != 32) && (n1[i] <= 47 || n1[i] >= 58) && (n1[i] <= 64 || n1[i] >= 91) && (n1[i] <= 96 || n1[i] >= 123) && (n1[i] <= -97 || n1[i] >= -90) && n1[i] != -126 && n1[i] != -75 && n1[i] != -112 && n1[i] != -42 && n1[i] != -32 && n1[i] != -23)
				{
					error = true; break;
				}error = false;
			}
		} while (error);

		if (c[0] == '2')do{
			ir(0, 3); for (int i = 0; i <= 79; i++)cout << " ";
			ir(0, 3); Escribir("  C\243al es tu segundo nombre?: ", 100, 2); scanf("%8s", n2); limpiartecla(1);
			for (int i = 0; i <= strlen(n2) - 1; i++)
			{
				if ((n2[i] != 32) && (n2[i] <= 47 || n2[i] >= 58) && (n2[i] <= 64 || n2[i] >= 91) && (n2[i] <= 96 || n2[i] >= 123) && (n2[i] <= -97 || n2[i] >= -90) && n2[i] != -126 && n2[i] != -75 && n2[i] != -112 && n2[i] != -42 && n2[i] != -32 && n2[i] != -23)
				{
					error = true; break;
				}error = false;
			}
		} while (error);
		ir(0, 5); Escribir("LISTO!!!!!!!", 100, 4);

		Cantidades[8][0] = c[0]; Cantidades[8][1] = strlen(n1); if (c[0] == '2')Cantidades[8][2] = strlen(n2);
		for (int i = 0; i <= Cantidades[8][1] - 1; i++)Cantidades[6][i] = int(n1[i]);
		if (c[0] == '2')for (int i = 0; i <= Cantidades[8][2] - 1; i++)Cantidades[7][i] = int(n2[i]);

		for (int i = 0; i <= 62; i++)delete[] matrizcon[i]; delete[]matrizcon;

	} while (teclac == 'K' || teclac == 'k');

}
void InterfazGameOver(int **matriz)
{
	desvanecimiento(16); Sleep(200);
	jokerGif(matriz);
	GameOver(46, 1, 1, 219, 1);
	MusicaGameOver();
	GameOver(46, 1, 8, 219, 1);
	GameOver(46, 1, 9, 219, 1);
	desvanecimiento(9);
}
void InterfazInstructions()
{
	int **matriz; matriz = new int *[18]; for (int i = 0; i <= 17; i++)matriz[i] = new int[80];
	int matrizint[18][80] =
	{ { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 15, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 15, 7, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 15, 7, 7, 7, 7, 15, 15, 15, 15, 15, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 15, 7, 7, 7, 15, 15, 9, 9, 9, 15, 15, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 15, 7, 7, 7, 15, 15, 9, 7, 7, 15, 15, 9, 7, 7, 7, 9, 16, 16, 16, 9, 16, 9, 9, 16, 9, 9, 16, 16, 16, 16, 9, 16, 16, 16, 16, 9, 16, 16, 16, 9, 9, 16, 9, 9, 16, 9, 9, 16, 16, 16, 16, 9, 16, 16, 16, 16, 9, 16, 16, 16, 9, 9, 16, 16, 16, 9, 9, 16, 9, 9, 16, 9, 9, 16, 16, 16, 16, 9, 9 },
	{ 9, 15, 7, 7, 7, 15, 15, 9, 7, 7, 15, 15, 9, 7, 7, 7, 9, 9, 16, 9, 9, 16, 16, 9, 16, 9, 16, 16, 9, 9, 9, 9, 9, 16, 16, 9, 9, 16, 9, 9, 16, 9, 16, 9, 9, 16, 9, 16, 16, 9, 9, 16, 9, 9, 16, 16, 9, 9, 9, 16, 9, 9, 16, 9, 9, 9, 16, 9, 16, 16, 9, 16, 9, 16, 16, 9, 9, 9, 9, 9 },
	{ 9, 15, 7, 7, 7, 7, 9, 9, 7, 15, 15, 15, 9, 7, 7, 7, 9, 9, 16, 9, 9, 16, 9, 16, 16, 9, 16, 16, 16, 16, 16, 9, 9, 16, 16, 9, 9, 16, 16, 16, 9, 9, 16, 9, 9, 16, 9, 16, 16, 9, 9, 9, 9, 9, 16, 16, 9, 9, 9, 16, 9, 9, 16, 9, 9, 9, 16, 9, 16, 9, 16, 16, 9, 16, 16, 16, 16, 16, 9, 9 },
	{ 9, 15, 7, 7, 7, 7, 7, 7, 15, 15, 9, 9, 9, 7, 7, 7, 9, 9, 16, 9, 9, 16, 9, 9, 16, 9, 9, 9, 9, 16, 16, 9, 9, 16, 16, 9, 9, 16, 9, 9, 16, 9, 16, 9, 9, 16, 9, 16, 16, 9, 9, 16, 9, 9, 16, 16, 9, 9, 9, 16, 9, 9, 16, 9, 9, 9, 16, 9, 16, 9, 9, 16, 9, 9, 9, 9, 16, 16, 9, 9 },
	{ 9, 15, 7, 7, 7, 7, 7, 7, 15, 15, 9, 7, 7, 7, 7, 7, 9, 16, 16, 16, 9, 16, 9, 9, 16, 9, 16, 16, 16, 16, 9, 9, 9, 16, 16, 9, 9, 16, 9, 9, 16, 9, 16, 16, 16, 16, 9, 9, 16, 16, 16, 16, 9, 9, 16, 16, 9, 9, 16, 16, 16, 9, 9, 16, 16, 16, 9, 9, 16, 9, 9, 16, 9, 16, 16, 16, 16, 9, 9, 9 },
	{ 9, 15, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 15, 7, 7, 7, 7, 7, 7, 15, 15, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 15, 7, 7, 7, 7, 7, 7, 15, 15, 9, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 15, 7, 9, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 9, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 15, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }
	};
	int f, c; for (f = 0; f <18; f++)for (c = 0; c <80; c++)matriz[f][c] = matrizint[f][c];
	GIF(matriz, 0, 17, 0, 79, 0, 0, 0, 0);
	colorletra(1);
	ir(2, 24); Escribir("-El objetivo de juego es acomodar todos los bloques a sus lugares correctos", 1);
	ir(2, 25); Escribir(" para que el personaje quede completo; lo cual activar\240 un portal, por", 1);
	ir(2, 26); Escribir(" donde se pasa al siguiente nivel.", 1);
	ir(2, 28); Escribir("-Se pierde una vida cuando el m\242 cae a un hueco o se le acaban los", 1);
	ir(2, 29); Escribir(" movimientos.");
	ir(2, 31); Escribir("-En cada nivel se puede regresar pasos atr\240s en caso de mover un bloque", 1);
	ir(2, 32); Escribir(" a un lugar inadecuado, pero esto consumir\240 3 movimientos.", 1);
	ir(2, 34); Escribir("-En algunos niveles la juganilidad cambia un poco.", 1);
	ir(2, 36); Escribir("-Si deseas reiniciar el nivel, lo puedes hacer desde el men\243 Pausa, pero", 1);
	ir(2, 37); Escribir(" te costar\240 una vida.", 1);
	ir(2, 43); Escribir("\311\315\315\315\313\315\315\315\313\315\315\315\313\315\315\315\313\315\315\315\313\315\315\315\313\315\315\315\313\315\315\315\313\315\315\315\313\315\315\315\273");
	ir(2, 44); Escribir("\272   \272   \272   \272   \272   \272   \272   \272   \272   \272   \272");
	ir(2, 45); Escribir("\272 Q \272 W \272 E \272 R \272 T \272 Y \272 U \272 I \272 O \272 P \272");
	ir(2, 46); Escribir("\272   \272   \272   \272   \272   \272   \272   \272   \272   \272   \272");
	ir(2, 47); Escribir("\310\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\274");
	ir(3, 48); Escribir("\272   \272   \272   \272   \272   \272   \272   \272   \272   \272");
	ir(3, 49); Escribir("\272 A \272 S \272 D \272 F \272 G \272 H \272 J \272 K \272 L \272");
	ir(3, 50); Escribir("\272   \272   \272   \272   \272   \272   \272   \272   \272   \272");
	ir(3, 51); Escribir("\310\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\313\315\315\312\315\315\315\274");
	ir(4, 52); Escribir("\272   \272   \272   \272   \272   \272   \272   \272");
	ir(4, 53); Escribir("\272 Z \272 X \272 C \272 V \272 B \272 N \272 M \272");
	ir(4, 54); Escribir("\272   \272   \272   \272   \272   \272   \272   \272");
	ir(4, 55); Escribir("\310\315\315\315\312\315\315\315\312\315\315\315\312\315\315\315\312\315\315\315\312\315\315\315\312\315\315\315\274");
	colorfondo(8); colorletra(9);
	ir(39, 44); cout << "   "; ir(39, 45); cout << " P "; ir(39, 46); cout << "   "; Sleep(500); ir(44, 43); cout << "P";
	colorfondo(9); colorletra(1); Escribir(": Sirve para pausar el juego.", 20);
	colorfondo(8); colorletra(9);
	ir(16, 48); cout << "   "; ir(16, 49); cout << " F "; ir(16, 50); cout << "   "; Sleep(500); ir(44, 45); cout << "F";
	colorfondo(9); colorletra(1); Escribir(": Sirve para desactivar o activar", 20); ir(44, 46); Escribir("  el sonido de los movimientos.", 20);
	colorfondo(5); colorletra(9);
	ir(15, 44); cout << "   "; ir(15, 45); cout << " R "; ir(15, 46); cout << "   "; Sleep(500); ir(44, 48); cout << "R";
	colorfondo(9); colorletra(1); Escribir(": Sirve para regresar en tus pasos.", 20);
	colorfondo(7); colorletra(9);
	ir(7, 44); cout << "   "; ir(7, 45); cout << " W "; ir(7, 46); cout << "   "; ir(4, 48); cout << "   "; ir(4, 49); cout << " A "; ir(4, 50); cout << "   ";
	ir(8, 48); cout << "   "; ir(8, 49); cout << " S "; ir(8, 50); cout << "   "; ir(12, 48); cout << "   "; ir(12, 49); cout << " D "; ir(12, 50); cout << "   "; Sleep(500);
	ir(44, 50); cout << "W"; ir(44, 51); cout << "A"; ir(44, 52); cout << "S"; ir(44, 53); cout << "D";
	ir(45, 51); colorfondo(9); colorletra(1); Escribir(": Sirven para mover el m\242vil", 20); ir(45, 52); Escribir("  en todos los niveles.", 20);
	colorfondo(3); colorletra(9);
	ir(11, 44); cout << "   "; ir(11, 45); cout << " E "; ir(11, 46); cout << "   "; Sleep(500); ir(44, 55); cout << "E";
	colorfondo(9); colorletra(1); Escribir(": Sirve para confirmar(como enter).", 20);
	limpiartecla(2);
	esperartecla();
}
void MenuPrincipal(int &nivel, int **matriz, int empezarconmusica = 1){
	int modo; char tecla; int cap;
	if (empezarconmusica == 1)MusicaMenu();

	desvanecimiento(9); Sleep(200);
	int color = nrandom(0, 499);
	if (color <= 99)color = 2; else if (color <= 199)color = 3; else if (color <= 299)color = 4; else color = 7;
	modo = nrandom(0, 499);
	if (modo <= 99)modo = 25; else if (modo <= 199)modo = 45; else if (modo <= 299)modo = 85; else modo = 65;
	PushBox(matriz);
	GIF(matriz, 0, 62, 0, 79); ir(0, 0);
	Cplusplus(matriz);
	esperartecla();
	GIF(matriz, 0, 11, 13, 25, 42, 48, 1, 5, 0, 78); Sleep(250); GIF(matriz, 0, 11, 26, 38, 42, 48, 1, 5, 0, 78); Sleep(250);
	GIF(matriz, 13, 25, 0, 12, 42, 47, 1, 5, 0, 78); Sleep(250); GIF(matriz, 13, 25, 13, 25, 42, 47, 1, 5, 0, 78); Sleep(250); GIF(matriz, 27, 39, 26, 38, 42, 47, 1, 5, 0, 78); Sleep(1000);
	colorfondo(5);
	for (int i = 43; i <= 67; i++){ GIF(matriz, 13, 25, 26, 38, i, 47, 1, 5, 0, 78); Sleep(50); }
	for (int i = 68; i <= 79; i++){ GIF(matriz, 13, 25, 26, 38 - (i - 67), i, 47, 1, 5); Sleep(50); }for (int i = 47; i <= 59; i++){ ir(78, i); cout << "  "; }
	desvanecimiento(9); Sleep(200);
	OpcionesMenu(0, 21, 13); Sleep(50);
	OpcionesMenu(1, 21, 13);

	bool sigue = 1;
	modo = 0;
	while (sigue){

		if (modo == 0){ modo = 1; continue; }

		limpiartecla(2);
		tecla = _getch();
		tecla = toupper(tecla);

		switch (tecla){
		case 'E': {sigue = 0; continue; break; }
		case 'W': {if (modo != 1){ modo--; cap = 25; }break; }//↑
		case 'S': {if (modo != 3){ modo++; cap = 85; }break; }//↓
		default: continue;
		}
		OpcionesMenu(modo, 21, 13);


	}
	if (modo == 1){ nivel = 1; desvanecimiento(9); InterfazInstructions(); }
	if (modo == 2)nivel = 8;
	if (modo == 3)nivel = 9;
	desvanecimiento(9);
}
void InterfazPausa(int **matriz, int &opcion, bool &sonido){
	MusicaPausa();
	Cartelpausa(matriz);
	AsciiFuncion(matriz, 16, 16, 16, 16, 223, 0); Sleep(10);
	char tecla;
	opcion = 1;
	int modo = 1;
	AsciiFuncion(matriz, 16, 11, 16, 16, 223);
	if (sonido){ ir(15, 45); colorletra(16); cout << "Sonido ON  (Presiona 'F' para desactivar el sonido.)"; }
	if (!sonido){ ir(15, 45); colorletra(16); cout << "Sonido OFF (Presiona 'F' para activar el sonido.)   "; }
	bool sigue = 1;
	while (sigue){
		limpiartecla(2);
		tecla = _getch();
		tecla = toupper(tecla);

		switch (tecla){
		case 'P': {sigue = 0; continue; break; }
		case 'F':
		{
			if (sonido)sonido = false; else sonido = true;
			if (sonido){ ir(15, 45); colorletra(16); cout << "Sonido ON  (Presiona 'F' para desactivar el sonido.)"; }
			if (!sonido){ ir(15, 45); colorletra(16); cout << "Sonido OFF (Presiona 'F' para activar el sonido.)   "; }
			break;
		}
		case 'E': {sigue = 0; continue; break; }
		case 'W': {if (opcion != 1){ opcion--; modo = 2; }break; }//↑
		case 'S': {if (opcion != 3){ opcion++; modo = 1; }break; }//↓
		default: continue;
		}//switch
		if (opcion == 1)AsciiFuncion(matriz, 16, 11, 16, 16, 223, modo);
		if (opcion == 2)AsciiFuncion(matriz, 16, 16, 15, 16, 223, modo);
		if (opcion == 3)AsciiFuncion(matriz, 16, 16, 16, 10, 223, modo);


	}
	MusicaPausa(); Sleep(200);
}
//--------------------------------------------------------------------------------------------------


/*--------------------------------------DATA DE OBJETOS Y DATOS INICIALES-------------------------------------------------------*/
void ap(int **paredes, int numeropared, int px, int py)
{
	paredes[numeropared][0] = px; paredes[numeropared][1] = py;
}
void av(int ***vacios, int nivel, int numerovacio, int vx, int vy)
{
	vacios[nivel][numerovacio][0] = vx; vacios[nivel][numerovacio][1] = vy;
}
void ac(int ***Cajas, int nivel, int cx, int cy, int **Cantidades)
{
	int numero = Cantidades[nivel][0];
	Cajas[nivel][numero][0] = cx; Cajas[nivel][numero][1] = cy;
	Cantidades[nivel][0]++;
}
void DataCantidades(int **Cantidades){//0:Cajas, 1:Paredes, 2:Vacios, 3:Huecos
	Cantidades[1][0] = 4; Cantidades[1][1] = 52; Cantidades[1][2] = 0; Cantidades[1][3] = 4;
	Cantidades[2][0] = 6; Cantidades[2][1] = 72; Cantidades[2][2] = 2; Cantidades[2][3] = 6;
	Cantidades[3][0] = 5; Cantidades[3][1] = 53; Cantidades[3][2] = 25; Cantidades[3][3] = 3;
	Cantidades[4][0] = 6; Cantidades[4][1] = 64; Cantidades[4][2] = 15; Cantidades[4][3] = 6;
	Cantidades[5][0] = 17; Cantidades[5][1] = 117; Cantidades[5][2] = 0; Cantidades[5][3] = 10;
}
void DataICajas(int nivel, int***Cajas)
{
	if (nivel == 1){//0: x, 1:y
		Cajas[1][0][0] = 34; Cajas[nivel][0][1] = 14;
		Cajas[1][1][0] = 38; Cajas[nivel][1][1] = 14;
		Cajas[1][2][0] = 36; Cajas[nivel][2][1] = 18;
		Cajas[1][3][0] = 36; Cajas[nivel][3][1] = 30;
	}
	if (nivel == 2){
		Cajas[nivel][0][0] = 36; Cajas[nivel][0][1] = 36;
		Cajas[nivel][1][0] = 38; Cajas[nivel][1][1] = 36;
		Cajas[nivel][2][0] = 40; Cajas[nivel][2][1] = 36;
		Cajas[nivel][3][0] = 44; Cajas[nivel][3][1] = 36;
		Cajas[nivel][4][0] = 46; Cajas[nivel][4][1] = 36;
		Cajas[nivel][5][0] = 48; Cajas[nivel][5][1] = 36;
	}
	if (nivel == 3){
		Cajas[nivel][0][0] = 28; Cajas[nivel][0][1] = 28;
		Cajas[nivel][1][0] = 32; Cajas[nivel][1][1] = 28;
		Cajas[nivel][2][0] = 38; Cajas[nivel][2][1] = 38;
		Cajas[nivel][3][0] = 28; Cajas[nivel][3][1] = 38;
		Cajas[nivel][4][0] = 42; Cajas[nivel][4][1] = 32;
	}
	if (nivel == 4){
		Cajas[nivel][0][0] = 34; Cajas[nivel][0][1] = 14;
		Cajas[nivel][1][0] = 38; Cajas[nivel][1][1] = 14;
		Cajas[nivel][2][0] = 42; Cajas[nivel][2][1] = 14;
		Cajas[nivel][3][0] = 34; Cajas[nivel][3][1] = 38;
		Cajas[nivel][4][0] = 38; Cajas[nivel][4][1] = 38;
		Cajas[nivel][5][0] = 42; Cajas[nivel][5][1] = 38;
	}
	if (nivel == 5){
		Cajas[nivel][0][0] = 38; Cajas[nivel][0][1] = 8;
		Cajas[nivel][1][0] = 42; Cajas[nivel][1][1] = 8;
		Cajas[nivel][2][0] = 40; Cajas[nivel][2][1] = 10;
		Cajas[nivel][3][0] = 40; Cajas[nivel][3][1] = 16;
		Cajas[nivel][4][0] = 38; Cajas[nivel][4][1] = 18;
		Cajas[nivel][5][0] = 42; Cajas[nivel][5][1] = 18;
		Cajas[nivel][6][0] = 20; Cajas[nivel][6][1] = 24;
		Cajas[nivel][7][0] = 60; Cajas[nivel][7][1] = 24;
		Cajas[nivel][8][0] = 32; Cajas[nivel][8][1] = 46;
		Cajas[nivel][9][0] = 48; Cajas[nivel][9][1] = 46;

		Cajas[nivel][10][0] = 32; Cajas[nivel][10][1] = 24;
		Cajas[nivel][11][0] = 34; Cajas[nivel][11][1] = 26;
		Cajas[nivel][12][0] = 46; Cajas[nivel][12][1] = 26;
		Cajas[nivel][13][0] = 48; Cajas[nivel][13][1] = 24;
		Cajas[nivel][14][0] = 38; Cajas[nivel][14][1] = 32;
		Cajas[nivel][15][0] = 42; Cajas[nivel][15][1] = 32;
		Cajas[nivel][16][0] = 40; Cajas[nivel][16][1] = 34;
	}

}
void DataParedes(int nivel, int ***matriz){
	if (nivel == 1){
		ap(matriz[nivel], 0, 26, 10); ap(matriz[nivel], 1, 28, 10); ap(matriz[nivel], 2, 32, 10); ap(matriz[nivel], 3, 34, 10); ap(matriz[nivel], 4, 36, 10); ap(matriz[nivel], 5, 38, 10); ap(matriz[nivel], 6, 40, 10); ap(matriz[nivel], 7, 24, 12); ap(matriz[nivel], 8, 30, 12); ap(matriz[nivel], 9, 42, 12); ap(matriz[nivel], 10, 44, 12); ap(matriz[nivel], 11, 22, 14); ap(matriz[nivel], 12, 28, 14); ap(matriz[nivel], 13, 46, 14); ap(matriz[nivel], 14, 22, 16); ap(matriz[nivel], 15, 34, 16); ap(matriz[nivel], 16, 38, 16); ap(matriz[nivel], 17, 48, 16); ap(matriz[nivel], 18, 22, 18); ap(matriz[nivel], 19, 34, 18); ap(matriz[nivel], 20, 38, 18); ap(matriz[nivel], 21, 48, 18); ap(matriz[nivel], 22, 22, 20); ap(matriz[nivel], 23, 34, 20); ap(matriz[nivel], 24, 38, 20); ap(matriz[nivel], 25, 50, 20); ap(matriz[nivel], 26, 22, 22); ap(matriz[nivel], 27, 34, 22); ap(matriz[nivel], 28, 38, 22); ap(matriz[nivel], 29, 52, 22); ap(matriz[nivel], 30, 22, 24); ap(matriz[nivel], 31, 52, 24); ap(matriz[nivel], 32, 24, 26); ap(matriz[nivel], 33, 36, 26); ap(matriz[nivel], 34, 52, 26); ap(matriz[nivel], 35, 24, 28); ap(matriz[nivel], 36, 36, 28); ap(matriz[nivel], 37, 46, 28); ap(matriz[nivel], 38, 48, 28); ap(matriz[nivel], 39, 50, 28); ap(matriz[nivel], 40, 24, 30); ap(matriz[nivel], 41, 44, 30); ap(matriz[nivel], 42, 26, 32); ap(matriz[nivel], 43, 42, 32); ap(matriz[nivel], 44, 28, 34); ap(matriz[nivel], 45, 42, 34); ap(matriz[nivel], 46, 30, 36); ap(matriz[nivel], 47, 32, 36); ap(matriz[nivel], 48, 40, 36); ap(matriz[nivel], 49, 34, 38); ap(matriz[nivel], 50, 36, 38); ap(matriz[nivel], 51, 38, 38);
	}
	if (nivel == 2){
		ap(matriz[nivel], 0, 52, 8); ap(matriz[nivel], 1, 50, 10); ap(matriz[nivel], 2, 54, 10); ap(matriz[nivel], 3, 28, 12); ap(matriz[nivel], 4, 30, 12); ap(matriz[nivel], 5, 32, 12); ap(matriz[nivel], 6, 50, 12); ap(matriz[nivel], 7, 56, 12); ap(matriz[nivel], 8, 26, 14); ap(matriz[nivel], 9, 34, 14); ap(matriz[nivel], 10, 36, 14); ap(matriz[nivel], 11, 38, 14); ap(matriz[nivel], 12, 40, 14); ap(matriz[nivel], 13, 42, 14); ap(matriz[nivel], 14, 44, 14); ap(matriz[nivel], 15, 46, 14); ap(matriz[nivel], 16, 48, 14); ap(matriz[nivel], 17, 54, 14); ap(matriz[nivel], 18, 26, 16); ap(matriz[nivel], 19, 54, 16); ap(matriz[nivel], 20, 28, 18); ap(matriz[nivel], 21, 30, 18); ap(matriz[nivel], 22, 54, 18); ap(matriz[nivel], 23, 32, 20); ap(matriz[nivel], 24, 52, 20); ap(matriz[nivel], 25, 30, 22); ap(matriz[nivel], 26, 54, 22); ap(matriz[nivel], 27, 30, 24); ap(matriz[nivel], 28, 34, 24); ap(matriz[nivel], 29, 48, 24); ap(matriz[nivel], 30, 54, 24); ap(matriz[nivel], 31, 30, 26); ap(matriz[nivel], 32, 34, 26); ap(matriz[nivel], 33, 36, 26); ap(matriz[nivel], 34, 48, 26); ap(matriz[nivel], 35, 50, 26); ap(matriz[nivel], 36, 54, 26); ap(matriz[nivel], 37, 28, 28); ap(matriz[nivel], 38, 42, 28); ap(matriz[nivel], 39, 56, 28); ap(matriz[nivel], 40, 30, 30); ap(matriz[nivel], 41, 54, 30); ap(matriz[nivel], 42, 32, 32); ap(matriz[nivel], 43, 42, 32); ap(matriz[nivel], 44, 52, 32); ap(matriz[nivel], 45, 30, 34); ap(matriz[nivel], 46, 54, 34); ap(matriz[nivel], 47, 30, 36); ap(matriz[nivel], 48, 54, 36); ap(matriz[nivel], 49, 28, 38); ap(matriz[nivel], 50, 56, 38); ap(matriz[nivel], 51, 28, 40); ap(matriz[nivel], 52, 34, 40); ap(matriz[nivel], 53, 50, 40); ap(matriz[nivel], 54, 56, 40); ap(matriz[nivel], 55, 28, 42); ap(matriz[nivel], 56, 32, 42); ap(matriz[nivel], 57, 52, 42); ap(matriz[nivel], 58, 56, 42); ap(matriz[nivel], 59, 30, 44); ap(matriz[nivel], 60, 54, 44); ap(matriz[nivel], 61, 32, 46); ap(matriz[nivel], 62, 40, 46); ap(matriz[nivel], 63, 42, 46); ap(matriz[nivel], 64, 44, 46); ap(matriz[nivel], 65, 52, 46); ap(matriz[nivel], 66, 34, 48); ap(matriz[nivel], 67, 36, 48); ap(matriz[nivel], 68, 38, 48); ap(matriz[nivel], 69, 46, 48); ap(matriz[nivel], 70, 48, 48); ap(matriz[nivel], 71, 50, 48);
	}
	if (nivel == 3){
		ap(matriz[nivel], 0, 24, 16); ap(matriz[nivel], 1, 26, 18); ap(matriz[nivel], 2, 48, 18); ap(matriz[nivel], 3, 50, 18); ap(matriz[nivel], 4, 20, 20); ap(matriz[nivel], 5, 26, 20); ap(matriz[nivel], 6, 46, 20); ap(matriz[nivel], 7, 52, 20); ap(matriz[nivel], 8, 22, 22); ap(matriz[nivel], 9, 28, 22); ap(matriz[nivel], 10, 43, 24); ap(matriz[nivel], 11, 52, 22); ap(matriz[nivel], 12, 22, 24); ap(matriz[nivel], 13, 30, 24); ap(matriz[nivel], 14, 34, 24); ap(matriz[nivel], 15, 42, 24); ap(matriz[nivel], 16, 52, 24); ap(matriz[nivel], 17, 24, 26); ap(matriz[nivel], 18, 32, 26); ap(matriz[nivel], 19, 36, 26); ap(matriz[nivel], 20, 38, 26); ap(matriz[nivel], 21, 40, 26); ap(matriz[nivel], 22, 46, 26); ap(matriz[nivel], 23, 48, 26); ap(matriz[nivel], 24, 50, 26); ap(matriz[nivel], 25, 26, 28); ap(matriz[nivel], 26, 44, 28); ap(matriz[nivel], 27, 26, 30); ap(matriz[nivel], 28, 44, 30); ap(matriz[nivel], 29, 26, 32); ap(matriz[nivel], 30, 44, 32); ap(matriz[nivel], 31, 46, 32); ap(matriz[nivel], 32, 48, 32); ap(matriz[nivel], 33, 26, 34); ap(matriz[nivel], 34, 50, 34); ap(matriz[nivel], 35, 26, 36); ap(matriz[nivel], 36, 26, 38); ap(matriz[nivel], 37, 26, 40); ap(matriz[nivel], 38, 38, 40); ap(matriz[nivel], 39, 40, 40); ap(matriz[nivel], 40, 42, 40); ap(matriz[nivel], 41, 44, 40); ap(matriz[nivel], 42, 28, 42); ap(matriz[nivel], 43, 36, 42); ap(matriz[nivel], 44, 36, 44); ap(matriz[nivel], 45, 44, 22);
	}
	if (nivel == 4){
		ap(matriz[nivel], 0, 34, 10); ap(matriz[nivel], 1, 36, 10); ap(matriz[nivel], 2, 38, 10); ap(matriz[nivel], 3, 40, 10); ap(matriz[nivel], 4, 42, 10); ap(matriz[nivel], 5, 30, 12); ap(matriz[nivel], 6, 32, 12); ap(matriz[nivel], 7, 44, 12); ap(matriz[nivel], 8, 46, 12); ap(matriz[nivel], 9, 28, 14); ap(matriz[nivel], 10, 48, 14); ap(matriz[nivel], 11, 26, 16); ap(matriz[nivel], 12, 50, 16); ap(matriz[nivel], 13, 26, 18); ap(matriz[nivel], 14, 50, 18); ap(matriz[nivel], 15, 26, 20); ap(matriz[nivel], 16, 50, 20); ap(matriz[nivel], 17, 26, 22); ap(matriz[nivel], 18, 50, 22); ap(matriz[nivel], 19, 26, 24); ap(matriz[nivel], 20, 50, 24); ap(matriz[nivel], 21, 28, 26); ap(matriz[nivel], 22, 48, 26); ap(matriz[nivel], 23, 28, 28); ap(matriz[nivel], 24, 48, 28); ap(matriz[nivel], 25, 30, 30); ap(matriz[nivel], 26, 32, 30); ap(matriz[nivel], 27, 34, 30); ap(matriz[nivel], 28, 42, 30); ap(matriz[nivel], 29, 44, 30); ap(matriz[nivel], 30, 46, 30); ap(matriz[nivel], 31, 30, 32); ap(matriz[nivel], 32, 46, 32); ap(matriz[nivel], 33, 28, 34); ap(matriz[nivel], 34, 48, 34); ap(matriz[nivel], 35, 28, 36); ap(matriz[nivel], 36, 30, 36); ap(matriz[nivel], 37, 32, 36); ap(matriz[nivel], 38, 34, 36); ap(matriz[nivel], 39, 42, 36); ap(matriz[nivel], 40, 44, 36); ap(matriz[nivel], 41, 46, 36); ap(matriz[nivel], 42, 48, 36); ap(matriz[nivel], 43, 28, 38); ap(matriz[nivel], 44, 48, 38); ap(matriz[nivel], 45, 28, 40); ap(matriz[nivel], 46, 48, 40); ap(matriz[nivel], 47, 28, 42); ap(matriz[nivel], 48, 36, 42); ap(matriz[nivel], 49, 38, 42); ap(matriz[nivel], 50, 40, 42); ap(matriz[nivel], 51, 48, 42); ap(matriz[nivel], 52, 30, 44); ap(matriz[nivel], 53, 32, 44); ap(matriz[nivel], 54, 34, 44); ap(matriz[nivel], 55, 42, 44); ap(matriz[nivel], 56, 44, 44); ap(matriz[nivel], 57, 46, 44);
	}
	if (nivel == 5){
		ap(matriz[nivel], 0, 38, 2); ap(matriz[nivel], 1, 40, 2); ap(matriz[nivel], 2, 42, 2); ap(matriz[nivel], 3, 34, 4); ap(matriz[nivel], 4, 36, 4); ap(matriz[nivel], 5, 44, 4); ap(matriz[nivel], 6, 46, 4); ap(matriz[nivel], 7, 32, 6); ap(matriz[nivel], 8, 48, 6); ap(matriz[nivel], 9, 30, 8); ap(matriz[nivel], 10, 50, 8); ap(matriz[nivel], 11, 30, 10); ap(matriz[nivel], 12, 50, 10); ap(matriz[nivel], 13, 28, 12); ap(matriz[nivel], 14, 34, 12); ap(matriz[nivel], 15, 36, 12); ap(matriz[nivel], 16, 44, 12); ap(matriz[nivel], 17, 46, 12); ap(matriz[nivel], 18, 52, 12); ap(matriz[nivel], 19, 28, 14); ap(matriz[nivel], 20, 40, 14); ap(matriz[nivel], 21, 52, 14); ap(matriz[nivel], 22, 28, 16); ap(matriz[nivel], 23, 52, 16); ap(matriz[nivel], 24, 30, 18); ap(matriz[nivel], 25, 50, 18); ap(matriz[nivel], 26, 26, 20); ap(matriz[nivel], 27, 28, 20); ap(matriz[nivel], 28, 30, 20); ap(matriz[nivel], 29, 50, 20); ap(matriz[nivel], 30, 52, 20); ap(matriz[nivel], 31, 54, 20); ap(matriz[nivel], 32, 18, 22); ap(matriz[nivel], 33, 20, 22); ap(matriz[nivel], 34, 22, 22); ap(matriz[nivel], 35, 24, 22); ap(matriz[nivel], 36, 30, 22); ap(matriz[nivel], 37, 38, 22); ap(matriz[nivel], 38, 40, 22); ap(matriz[nivel], 39, 42, 22); ap(matriz[nivel], 40, 50, 22); ap(matriz[nivel], 41, 56, 22); ap(matriz[nivel], 42, 58, 22); ap(matriz[nivel], 43, 60, 22); ap(matriz[nivel], 44, 62, 22); ap(matriz[nivel], 45, 16, 24); ap(matriz[nivel], 46, 36, 24); ap(matriz[nivel], 47, 44, 24); ap(matriz[nivel], 48, 64, 24); ap(matriz[nivel], 49, 16, 26); ap(matriz[nivel], 50, 64, 26); ap(matriz[nivel], 51, 18, 28); ap(matriz[nivel], 52, 20, 28); ap(matriz[nivel], 53, 22, 28); ap(matriz[nivel], 54, 24, 28); ap(matriz[nivel], 55, 36, 28); ap(matriz[nivel], 56, 38, 28); ap(matriz[nivel], 57, 40, 28); ap(matriz[nivel], 58, 42, 28); ap(matriz[nivel], 59, 44, 28); ap(matriz[nivel], 60, 56, 28); ap(matriz[nivel], 61, 58, 28); ap(matriz[nivel], 62, 60, 28); ap(matriz[nivel], 63, 62, 28); ap(matriz[nivel], 64, 26, 30); ap(matriz[nivel], 65, 28, 30); ap(matriz[nivel], 66, 36, 30); ap(matriz[nivel], 67, 44, 30); ap(matriz[nivel], 68, 52, 30); ap(matriz[nivel], 69, 54, 30); ap(matriz[nivel], 70, 30, 32); ap(matriz[nivel], 71, 50, 32); ap(matriz[nivel], 72, 30, 34); ap(matriz[nivel], 73, 50, 34); ap(matriz[nivel], 74, 32, 36); ap(matriz[nivel], 75, 48, 36); ap(matriz[nivel], 76, 32, 38); ap(matriz[nivel], 77, 48, 38); ap(matriz[nivel], 78, 32, 40); ap(matriz[nivel], 79, 48, 40); ap(matriz[nivel], 80, 30, 42); ap(matriz[nivel], 81, 50, 42); ap(matriz[nivel], 82, 28, 44); ap(matriz[nivel], 83, 40, 44); ap(matriz[nivel], 84, 52, 44); ap(matriz[nivel], 85, 28, 46); ap(matriz[nivel], 86, 38, 46); ap(matriz[nivel], 87, 42, 46); ap(matriz[nivel], 88, 52, 46); ap(matriz[nivel], 89, 26, 48); ap(matriz[nivel], 90, 38, 48); ap(matriz[nivel], 91, 42, 48); ap(matriz[nivel], 92, 54, 48); ap(matriz[nivel], 93, 22, 50); ap(matriz[nivel], 94, 24, 50); ap(matriz[nivel], 95, 36, 50); ap(matriz[nivel], 96, 44, 50); ap(matriz[nivel], 97, 56, 50); ap(matriz[nivel], 98, 58, 50); ap(matriz[nivel], 99, 20, 52); ap(matriz[nivel], 100, 36, 52); ap(matriz[nivel], 101, 44, 52); ap(matriz[nivel], 102, 60, 52); ap(matriz[nivel], 103, 22, 54); ap(matriz[nivel], 104, 24, 54); ap(matriz[nivel], 105, 26, 54); ap(matriz[nivel], 106, 28, 54); ap(matriz[nivel], 107, 30, 54); ap(matriz[nivel], 108, 32, 54); ap(matriz[nivel], 109, 34, 54); ap(matriz[nivel], 110, 46, 54); ap(matriz[nivel], 111, 48, 54); ap(matriz[nivel], 112, 50, 54); ap(matriz[nivel], 113, 52, 54); ap(matriz[nivel], 114, 54, 54); ap(matriz[nivel], 115, 56, 54); ap(matriz[nivel], 116, 58, 54);
	}
}
void DataVacios(int nivel, int ***matriz)
{
	if (nivel == 2){
		matriz[2][0][0] = 36; matriz[2][0][1] = 24;
		matriz[2][1][0] = 50; matriz[2][1][1] = 24;
	}
	if (nivel == 3){
		av(matriz, nivel, 0, 22, 18); av(matriz, nivel, 1, 34, 26); av(matriz, nivel, 2, 28, 34); av(matriz, nivel, 3, 30, 34); av(matriz, nivel, 4, 32, 34); av(matriz, nivel, 5, 34, 34); av(matriz, nivel, 6, 36, 34); av(matriz, nivel, 7, 38, 34); av(matriz, nivel, 8, 40, 34); av(matriz, nivel, 9, 42, 34); av(matriz, nivel, 10, 30, 36); av(matriz, nivel, 11, 32, 36); av(matriz, nivel, 12, 34, 36); av(matriz, nivel, 13, 36, 36); av(matriz, nivel, 14, 38, 36); av(matriz, nivel, 15, 40, 36); av(matriz, nivel, 16, 48, 36); av(matriz, nivel, 17, 30, 38); av(matriz, nivel, 18, 32, 38); av(matriz, nivel, 19, 34, 38); av(matriz, nivel, 20, 36, 38); av(matriz, nivel, 21, 46, 38); av(matriz, nivel, 22, 30, 44); av(matriz, nivel, 23, 32, 44); av(matriz, nivel, 24, 34, 46);
	}
	if (nivel == 4){
		av(matriz, nivel, 0, 32, 20); av(matriz, nivel, 1, 36, 20); av(matriz, nivel, 2, 38, 20); av(matriz, nivel, 3, 40, 20); av(matriz, nivel, 4, 44, 20); av(matriz, nivel, 5, 32, 22); av(matriz, nivel, 6, 36, 22); av(matriz, nivel, 7, 38, 22); av(matriz, nivel, 8, 40, 22); av(matriz, nivel, 9, 44, 22); av(matriz, nivel, 10, 32, 24); av(matriz, nivel, 11, 36, 24); av(matriz, nivel, 12, 38, 24); av(matriz, nivel, 13, 40, 24); av(matriz, nivel, 14, 44, 24);
	}
}
void DataHuecos(int nivel, int***matriz)
{
	if (nivel == 1){
		matriz[nivel][0][0] = 30; matriz[nivel][0][1] = 24;
		matriz[nivel][1][0] = 32; matriz[nivel][1][1] = 24;
		matriz[nivel][2][0] = 40; matriz[nivel][2][1] = 24;
		matriz[nivel][3][0] = 42; matriz[nivel][3][1] = 24;
	}
	if (nivel == 2){
		matriz[nivel][0][0] = 30; matriz[nivel][0][1] = 28;
		matriz[nivel][1][0] = 32; matriz[nivel][1][1] = 28;
		matriz[nivel][2][0] = 32; matriz[nivel][2][1] = 30;
		matriz[nivel][3][0] = 52; matriz[nivel][3][1] = 28;
		matriz[nivel][4][0] = 54; matriz[nivel][4][1] = 28;
		matriz[nivel][5][0] = 52; matriz[nivel][5][1] = 30;
	}
	if (nivel == 3){
		matriz[nivel][0][0] = 28; matriz[nivel][0][1] = 24;
		matriz[nivel][1][0] = 26; matriz[nivel][1][1] = 26;
		matriz[nivel][2][0] = 28; matriz[nivel][2][1] = 36;
	}
	if (nivel == 4){
		matriz[nivel][0][0] = 34; matriz[nivel][0][1] = 20;
		matriz[nivel][1][0] = 34; matriz[nivel][1][1] = 22;
		matriz[nivel][2][0] = 34; matriz[nivel][2][1] = 24;
		matriz[nivel][3][0] = 42; matriz[nivel][3][1] = 20;
		matriz[nivel][4][0] = 42; matriz[nivel][4][1] = 22;
		matriz[nivel][5][0] = 42; matriz[nivel][5][1] = 24;
	}
	if (nivel == 5){
		matriz[nivel][0][0] = 34; matriz[nivel][0][1] = 14;
		matriz[nivel][1][0] = 36; matriz[nivel][1][1] = 14;
		matriz[nivel][2][0] = 38; matriz[nivel][2][1] = 14;
		matriz[nivel][3][0] = 42; matriz[nivel][3][1] = 14;
		matriz[nivel][4][0] = 44; matriz[nivel][4][1] = 14;
		matriz[nivel][5][0] = 46; matriz[nivel][5][1] = 14;
		matriz[nivel][6][0] = 38; matriz[nivel][6][1] = 30;
		matriz[nivel][7][0] = 40; matriz[nivel][7][1] = 30;
		matriz[nivel][8][0] = 42; matriz[nivel][8][1] = 30;
		matriz[nivel][9][0] = 40; matriz[nivel][9][1] = 32;
	}

}
void RestaurarTodo(int nivel, int***Cajas, int ***Paredes, int ***Vacios, int ***Huecos, int **Cantidades)
{
	DataCantidades(Cantidades); DataICajas(nivel, Cajas); DataParedes(nivel, Paredes); DataVacios(nivel, Vacios); DataHuecos(nivel, Huecos);
}
/*----------------------------------------------------------------------------------------------------*/

//-------------------------------------------UBICACION DE OBJETOS---------------------------------------
int QueCaja(int nivel, int x, int y, int mov, int ***cajas, int **Cantidades)//Retorna el numero de caja, con la cual es movil va a interactuar con su proximo movimiento
{
	int xsurreal = x, ysurreal = y;
	movi(xsurreal, ysurreal, mov);

	for (int i = 0; i <= Cantidades[nivel][0] - 1; i++)if (xsurreal == cajas[nivel][i][0] && ysurreal == cajas[nivel][i][1])return i;
	return -1;
}
int QueHueco(int nivel, int x, int y, int mov, int ***Huecos, int **Cantidades, int modo = 0)
{
	int r = -1;
	int xsurreal = x, ysurreal = y;
	if (modo == -1)
	{
		movinv(mov); movi(xsurreal, ysurreal, mov);
	}
	if (modo == 0)
	{
	}
	if (modo == 1)
	{
		movi(xsurreal, ysurreal, mov);
	}

	for (int i = 0; i <= Cantidades[nivel][3] - 1; i++)if (xsurreal == Huecos[nivel][i][0] && ysurreal == Huecos[nivel][i][1])r = i;

	return r;
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------CREACION Y ELIMINACION DE OBJETOS------------------------------
void QuitarunaCaja(int nivel, int numero, int ***Cajas, int **Cantidades)//0-Cajas, 1:Paredes, 2:vacios
{
	for (int i = numero; i <= Cantidades[nivel][0] - 2; i++){ Cajas[nivel][i][0] = Cajas[nivel][i + 1][0]; Cajas[nivel][i][1] = Cajas[nivel][i + 1][1]; }
	Cantidades[nivel][0]--;
}
void QuitarunVacio(int nivel, int vacio, int ***Vacios, int **Cantidades)//0-Cajas, 1:Paredes, 2:vacios
{
	for (int i = vacio; i <= Cantidades[nivel][2] - 2; i++){ Vacios[nivel][i][0] = Vacios[nivel][i + 1][0]; Vacios[nivel][i][1] = Vacios[nivel][i + 1][1]; }
	Cantidades[nivel][2]--;
}
void AgregarParedes(int ***Cajas, int ***Paredes, int **Cantidades){
	ap(Paredes[5], 117, Cajas[5][10][0], Cajas[5][10][1]); ap(Paredes[5], 118, Cajas[5][11][0], Cajas[5][11][1]);
	ap(Paredes[5], 119, Cajas[5][12][0], Cajas[5][12][1]); ap(Paredes[5], 120, Cajas[5][13][0], Cajas[5][13][1]);
	ap(Paredes[5], 121, Cajas[5][14][0], Cajas[5][14][1]); ap(Paredes[5], 122, Cajas[5][15][0], Cajas[5][15][1]);
	ap(Paredes[5], 123, Cajas[5][16][0], Cajas[5][16][1]);
}
void DestruirPuente(int nivel, int x, int y)
{
	if (nivel == 2)colorfondo(1);
	if (nivel == 3){ if (x == 34 && y == 26)colorfondo(7); else colorfondo(12); }
	if (nivel == 4)colorfondo(7);
	ir(x, y); cout << " ";
	ir(x + 1, y); cout << " ";
	ir(x, y + 1); cout << " ";
	ir(x + 1, y + 1); cout << " ";

}
void CrearPuente(int nivel, int mov, int ***Cajas, int ***Vacios, int caja, int **Cantidades)
{
	int xcaja = Cajas[nivel][caja][0]; int ycaja = Cajas[nivel][caja][1];
	int xcajaantes = Cajas[nivel][caja][0], ycajaantes = Cajas[nivel][caja][1];
	movinv(mov);
	movi(xcajaantes, ycajaantes, mov);
	int xmovilantes = xcajaantes, ymovilantes = ycajaantes;
	movi(xmovilantes, ymovilantes, mov);
	PBorrar(nivel, xmovilantes, ymovilantes);
	PintarMovil(nivel, xcajaantes, ycajaantes);

	SonidoCajaVacio();
	ArmarPuente(nivel, xcaja, ycaja);
	int numerodevacio;
	PintarPuente(nivel, xcaja, ycaja);
	for (int i = 0; i <= Cantidades[nivel][2] - 1; i++){ if (xcaja == Vacios[nivel][i][0] && ycaja == Vacios[nivel][i][1])numerodevacio = i; }
	QuitarunVacio(nivel, numerodevacio, Vacios, Cantidades);
	QuitarunaCaja(nivel, caja, Cajas, Cantidades);

}
//--------------------------------------------------------------------------------------------------

/*-----------------------CONDICIONES Y CONTROLADORES DE VERDADES-----------------------------*/
bool MovilDentroDeMapa(int nivel, int xoriginal, int yoriginal, int mov, int ***paredes, int **Cantidades){//Retorna true si el movil esta dentro de la consola.
	int x = xoriginal; int y = yoriginal;
	movi(x, y, mov);
	for (int i = 0; i <= Cantidades[nivel][1] - 1; i++)if (x == paredes[nivel][i][0] && y == paredes[nivel][i][1])return false;
	if (x>79 || x<0 || y<0 || y>59)return false;
	return true;
}
bool MovilyCaja(int nivel, int mx, int my, int mov, int ***Cajas, int **Cantidades)//verifica si el movil chocara con una caja en su proximo movimiento
{
	movi(mx, my, mov);
	for (int i = 0; i <= Cantidades[nivel][0] - 1; i++)if (mx == Cajas[nivel][i][0] && my == Cajas[nivel][i][1])return true;
	return false;
}
bool MovilyHueco(int nivel, int mx, int my, int mov, int ***Huecos, int **Cantidades)
{

	for (int i = 0; i <= Cantidades[nivel][3] - 1; i++)if (mx == Huecos[nivel][i][0] && my == Huecos[nivel][i][1])return true;
	return false;

}
bool CajayVacio(int nivel, int *caja, int mov, int ***vacios, int **Cantidades)
{
	int a, b; a = caja[0]; b = caja[1]; movi(a, b, mov);
	for (int i = 0; i <= Cantidades[nivel][2] - 1; i++)if (a == vacios[nivel][i][0] && b == vacios[nivel][i][1])return true;
	return false;
}
bool CajaLugarPermitido(int nivel, int mov, int ***cajas, int caja, int ***pared, int **Cantidades)//Verifica si la caja al ser movida, se pueda mover(Ver Jugabilidad del juego para entederlo mejor)
{
	int a, b; a = cajas[nivel][caja][0]; b = cajas[nivel][caja][1];
	movi(a, b, mov);
	for (int i = 0; i <= Cantidades[nivel][1] - 1; i++)if (a == pared[nivel][i][0] && b == pared[nivel][i][1])return false;
	for (int i = 0; i<caja; i++)if (a == cajas[nivel][i][0] && b == cajas[nivel][i][1])return false;
	for (int i = caja + 1; i <= Cantidades[nivel][0] - 1; i++)if (a == cajas[nivel][i][0] && b == cajas[nivel][i][1])return false;
	return true;
}
bool MovilPuedeMoverse(int *caja, int mov)//Verifica si al movil se le permite mover
{
	mod(caja, mov);
	if (caja[0]<0 || caja[1]>59 || caja[1]<0 || caja[0]>79)return false;
	return true;
}
bool muerte(int nivel, int x, int y, int mov, int cantmovs, int ***vacio, int **Cantidades)//Verifica si el movil muere en su proximo movimiento
{
	int xsurreal = x; int ysurreal = y; int max;

	if (nivel == 1)max = 150;
	if (nivel == 2)max = 150;
	if (nivel == 3)max = 100;
	if (nivel == 4)max = 180;
	if (nivel == 5)max = 500;

	if (cantmovs >= max)return true;
	for (int i = 0; i <= Cantidades[nivel][2] - 1; i++)if (xsurreal == vacio[nivel][i][0] && ysurreal == vacio[nivel][i][1])return true;
	return false;
}
bool ZonaEstable(int nivel, int zona, int ***Cajas, int ***Huecos, int **Cantidades, int modo5 = 0){
	int a, b; a = Huecos[nivel][zona][0]; b = Huecos[nivel][zona][1];
	if (nivel != 5)for (int i = 0; i <= Cantidades[nivel][0] - 1; i++)if (a == Cajas[nivel][i][0] && b == Cajas[nivel][i][1])return true;
	if (nivel == 5 && modo5 == 0)for (int i = 0; i <= Cantidades[nivel][0] - 8; i++)if (a == Cajas[nivel][i][0] && b == Cajas[nivel][i][1])return true;
	if (nivel == 5 && modo5 == 1)for (int i = 0; i <= Cantidades[nivel][0] - 1; i++)if (a == Cajas[nivel][i][0] && b == Cajas[nivel][i][1])return true;
	return false;
}
bool PortalVisible(int nivel, int ***Cajas, int ***Huecos, int **Cantidades)
{
	for (int i = 0; i <= Cantidades[nivel][3] - 1; i++)if (!ZonaEstable(nivel, i, Cajas, Huecos, Cantidades)){ return false; }
	if (nivel == 5){
		if (Cajas[5][10][0] != 32 || Cajas[5][10][1] != 24 || Cajas[5][11][0] != 34 || Cajas[5][11][1] != 26 || Cajas[5][12][0] != 46 || Cajas[5][12][1] != 26 || Cajas[5][13][0] != 48 || Cajas[5][13][1] != 24 || Cajas[5][14][0] != 38 || Cajas[5][14][1] != 32 || Cajas[5][15][0] != 42 || Cajas[5][15][1] != 32 || Cajas[5][16][0] != 40 || Cajas[5][16][1] != 34)
			return false;
	}
	return true;
}
bool CajayHueco(int nivel, int caja, int ***Cajas, int ***Huecos, int **Cantidades)
{
	for (int i = 0; i <= Cantidades[nivel][3] - 1; i++){ if (Cajas[nivel][caja][0] == Huecos[nivel][i][0] && Cajas[nivel][caja][1] == Huecos[nivel][i][1])return true; }
	return false;
}
//----------------------------------------------------------------------------------------------

//------------------------------------------IMPRESION EN CONJUNTO--------------------------------
void PonerCajas(int nivel, int ***cajas, int **Cantidades)//Usando la funcion pintar caja, Pone todas las cajas del nivel
{
	if (nivel != 5){ for (int i = 0; i <= Cantidades[nivel][0] - 1; i++){ PintarCaja(nivel, cajas[nivel][i][0], cajas[nivel][i][1]); } }
	if (nivel == 5){
		for (int i = 0; i <= Cantidades[nivel][0] - 8; i++){ PintarCaja(nivel, cajas[nivel][i][0], cajas[nivel][i][1]); }
		for (int i = 10; i <= Cantidades[nivel][0] - 1; i++){ PintarCaja(nivel, cajas[nivel][i][0], cajas[nivel][i][1], 1); }
	}
}
void PonerHuecos(int nivel, int ***huecos, int ***cajas, int **Cantidades)//Usando la funcion pintar caja, Pone todas las cajas del nivel
{
	for (int i = 0; i <= Cantidades[nivel][3] - 1; i++){ if (!ZonaEstable(nivel, i, cajas, huecos, Cantidades, 1))PintarHueco(nivel, huecos[nivel][i][0], huecos[nivel][i][1]); }
}
void PonerPuentes(int nivel, int ***Vacios, int **Cantidades){
	int maximo;
	if (nivel == 1)maximo = 0; if (nivel == 2)maximo = 2; if (nivel == 3)maximo = 25; if (nivel == 4)maximo = 15; if (nivel == 5)maximo = 0;
	if (Cantidades[nivel][2] != maximo){
		int ***VaciosDeReferencia; VaciosDeReferencia = new int**[6]; for (int i = 1; i <= 5; i++)VaciosDeReferencia[i] = new int*[25];
		for (int i = 1; i <= 5; i++)for (int f = 0; f <= 24; f++)VaciosDeReferencia[i][f] = new int[2];
		DataVacios(nivel, VaciosDeReferencia);
		int next = 0;
		if (Cantidades[nivel][2] != 0){
			for (int i = 0; i <= maximo - 1; i++){
				if (VaciosDeReferencia[nivel][i][0] != Vacios[nivel][i + next][0] || VaciosDeReferencia[nivel][i][1] != Vacios[nivel][i + next][1])
				{
					PintarPuente(nivel, VaciosDeReferencia[nivel][i][0], VaciosDeReferencia[nivel][i][1]); next--;
				}
			}
			if (maximo + next != Cantidades[nivel][2])PintarPuente(nivel, VaciosDeReferencia[nivel][maximo - 1][0], VaciosDeReferencia[nivel][maximo - 1][1]);
		}
		if (Cantidades[nivel][2] == 0){
			for (int i = 0; i <= maximo - 1; i++)PintarPuente(nivel, VaciosDeReferencia[nivel][i][0], VaciosDeReferencia[nivel][i][1]);
		}
	}
}
//------------------------------------------------------------------------------------------------

//-----------------------------------------MANEJO DE POSICIONES------------------------------------
void GuardarPosicion(int &posicion, int tipodemovimiento, int x, int y, int mov, int caja, int ***Cajas, int **Posiciones)
{
	//Se guardan la posicion del movil
	if (posicion == 6){
		for (int i = 1; i <= 4; i++){
			Posiciones[i][0] = Posiciones[i + 1][0];
			Posiciones[i][1] = Posiciones[i + 1][1];
			Posiciones[i][2] = Posiciones[i + 1][2];
			Posiciones[i][3] = Posiciones[i + 1][3];
			Posiciones[i][4] = Posiciones[i + 1][4];
		}//end for
		posicion = 5;
	}//end if posicion==6
	Posiciones[posicion][0] = tipodemovimiento;
	Posiciones[posicion][1] = x;
	Posiciones[posicion][2] = y;
	Posiciones[posicion][3] = mov;
	Posiciones[posicion][4] = caja;
	posicion++;

	if (tipodemovimiento == 1){}//End tipo de movimiento 1

	if (tipodemovimiento == 2){}//End tipo de movimiento 2

	if (tipodemovimiento == 3){}//End tipo de movimiento 3

}
void Regresar(int nivel, int &posicion, int &x, int &y, int mov, int ***Cajas, int ***Vacios, int ***Huecos, int **Cantidades, int **Posiciones, int **matriz){


	if (posicion != 1){

		int xportal; int yportal;//coordenadas del portal

		if (nivel == 1){ xportal = 36; yportal = 34; }
		if (nivel == 2){ xportal = 42; yportal = 18; }
		if (nivel == 3){ xportal = 36; yportal = 28; }
		if (nivel == 4){ xportal = 38; yportal = 12; }
		if (nivel == 5) { xportal = 40; yportal = 6; }

		Retroceder(nivel, x, y);
		PBorrar(nivel, x, y);

		int tipo = Posiciones[posicion - 1][0];
		x = Posiciones[posicion - 1][1];
		y = Posiciones[posicion - 1][2];
		mov = Posiciones[posicion - 1][3];
		int caja = Posiciones[posicion - 1][4];


		if (tipo == 1){ posicion--; PonerHuecos(nivel, Huecos, Cajas, Cantidades); }

		if (tipo == 2)
		{
			int xanterior = x; int yanterior = y; movi(xanterior, yanterior, mov);
			int c = QueCaja(nivel, xanterior, yanterior, mov, Cajas, Cantidades);
			PBorrar(nivel, Cajas[nivel][c][0], Cajas[nivel][c][1]); movinv(mov);
			mod(Cajas[nivel][c], mov); posicion--; PonerHuecos(nivel, Huecos, Cajas, Cantidades); PonerCajas(nivel, Cajas, Cantidades);
		}//Fin tipo 2

		if (tipo == 3)
		{
			int c = Posiciones[posicion - 1][4];
			int xcaja = Posiciones[posicion - 1][1];
			int ycaja = Posiciones[posicion - 1][2];
			movi(xcaja, ycaja, mov);
			int xpuente = xcaja;
			int ypuente = ycaja;
			movi(xpuente, ypuente, mov);
			movinv(mov); posicion--;
			av(Vacios, nivel, Cantidades[nivel][2], xpuente, ypuente);
			Cantidades[nivel][2]++;
			ac(Cajas, nivel, xcaja, ycaja, Cantidades);
			PonerHuecos(nivel, Huecos, Cajas, Cantidades);
			PonerCajas(nivel, Cajas, Cantidades);
			DestruirPuente(nivel, xpuente, ypuente);
		}//Fin tipo 3

		if (PortalVisible(nivel, Cajas, Huecos, Cantidades))PintarPortal(nivel, -1, -1);
		else PBorrar(nivel, xportal, yportal);
		PintarMovil(nivel, x, y);
	}//restriccion de posicion diferente de 1
	else
	{
		Musicatiempo(2);
	}
}
//--------------------------------------------------------------------------------------------------

//----------------------------------------CUADROS DE TEXTO-----------------------------------------
void CuadroDeVidas(int nivel, int vidas, int movimientos, bool cuadro = 0)
{
	int max; int a = 0;
	if (nivel == 1)max = 150; if (nivel == 2)max = 150; if (nivel == 3)max = 100; if (nivel == 4)max = 180; if (nivel == 5)max = 500;
	if (cuadro)CuadroDeTexto(10, 59, 70, 61, 16, 0, 16); colorfondo(16);
	if (vidas == 5){ ir(54, 60); colorletra(4); cout << "Vidas: X" << vidas; }
	if (vidas == 4 || vidas == 3){ ir(54, 60); colorletra(7); cout << "Vidas: X" << vidas; }
	if (vidas == 2 || vidas == 1){ ir(54, 60); colorletra(2); cout << "Vidas: X" << vidas; }
	ir(15, 60); colorletra(9); cout << "NIVEl: " << nivel << "       MOVIMIENTOS: ";
	if (movimientos == max - 20)
	{
		SonidoHurryUp(); for (int i = 0; i <= 24; i++){ if (a == 0){ colorletra(9); a++; } else{ colorletra(2); a--; }ir(43, 60); cout << "20  "; Sleep(100); }
	}
	else{ if (movimientos >= max)cout << "0  "; else cout << max - movimientos << "  "; }
}
void Lore(int nivel){


	desvanecimiento(9);
	if (nivel == 1){
		colorletra(1); CuadroDeTexto(12, 16, 69, 43, 9, 1, 1);
		ir(36, 19); Escribir("NIVEL 1", 1);
		ir(12, 22); Escribir(" Objetivo y Reglas: ", 1);
		ir(12, 24); Escribir("  -Llegar al portal.", 1);
		ir(12, 26); Escribir("  -Empuja todos los bloques hacia sus lugares correctos,", 1);
		ir(12, 28); Escribir("   para que se active el portal.", 1);
		ir(12, 30); Escribir("  -Ten cuidado con la cantidad de movimientos.", 1);
		ir(12, 33); Escribir(" Zonas Permitidas: ", 1);
		CuadroDeTexto(15, 35, 44, 41, 6, 0, 0);
		ir(19, 38); Escribir("M\242vil", 1); PintarMovil(1, 26, 38); ir(32, 38); colorfondo(6); Escribir("Bloques", 1); PintarCaja(1, 41, 38); colorfondo(9); colorletra(1);

	}

	if (nivel == 2){
		colorletra(1); CuadroDeTexto(12, 16, 69, 43, 9, 1, 1);
		ir(36, 19); Escribir("NIVEL 2", 1);
		ir(12, 22); Escribir(" Objetivo y Reglas: ", 1);
		ir(12, 24); Escribir("  -Llegar al portal.", 1);
		ir(12, 26); Escribir("  -Empuja todos los bloques hacia sus lugares correctos,", 1);
		ir(12, 28); Escribir("   para que se active el portal.", 1);
		ir(12, 30); Escribir("  -Ten cuidado con la cantidad de movimientos.", 1);
		ir(12, 33); Escribir(" Zonas Permitidas: ", 1);
		CuadroDeTexto(15, 35, 44, 41, 7, 0, 0); colorletra(9);
		ir(19, 38); Escribir("M\242vil"); PintarMovil(2, 26, 38); ir(32, 38); colorletra(9); colorfondo(7); Escribir("Bloques", 1); PintarCaja(2, 41, 38); colorfondo(9); colorletra(1);

	}

	if (nivel == 3){
		colorletra(1); CuadroDeTexto(12, 8, 69, 52, 9, 1, 1);
		ir(36, 10); Escribir("NIVEL 3", 1);
		ir(12, 14); Escribir(" Objetivo y Reglas: ", 1);
		ir(12, 16); Escribir("  -Llegar al portal.", 1);
		ir(12, 18); Escribir("  -Empuja todos los; bloques hacia sus lugares correctos,", 1);
		ir(12, 20); Escribir("   para que se active el portal.", 1);
		ir(12, 22); Escribir("  -Ten cuidado con la cantidad de movimientos.", 1);
		ir(12, 24); Escribir("   -Puedes empujar bloques al vacio para formar puentes.", 1);
		ir(12, 26); Escribir("  -No te caigas a los vacios", 1);
		ir(12, 29); Escribir(" Zonas Permitidas: ", 1);
		CuadroDeTexto(15, 31, 44, 38, 5, 0, 0);
		ir(18, 35); colorletra(9); Escribir("M\242vil", 1); PintarMovil(3, 26, 35); ir(32, 35);
		colorfondo(5); colorletra(9); Escribir("Bloques", 1); PintarCaja(3, 41, 35); colorfondo(9); colorletra(1);
		ir(12, 41); Escribir("   Huecos: ", 1);
		CuadroDeTexto(15, 43, 29, 50, 12, 0, 0); CuadroDeTexto(30, 43, 44, 50, 7, 0, 0); colorfondo(9); colorletra(1);

	}

	if (nivel == 4){
		colorletra(1); CuadroDeTexto(12, 8, 69, 52, 9, 1, 1);
		ir(36, 10); Escribir("NIVEL 4", 1);
		ir(12, 14); Escribir(" Objetivo y Reglas: ", 1);
		ir(12, 16); Escribir("  -Llegar al portal.", 1);
		ir(12, 18); Escribir("  -Empuja todos los bloques hacia sus lugares correctos,", 1);
		ir(12, 20); Escribir("   para que se active el portal.", 1);
		ir(12, 22); Escribir("  -Ten cuidado con la cantidad de movimientos.", 1);
		ir(12, 24); Escribir("   -Puedes empujar bloques al vacio para formar puentes.", 1);
		ir(12, 26); Escribir("  -No te caigas a los vacios", 1);
		ir(12, 29); Escribir(" Zonas Permitidas: ", 1);
		CuadroDeTexto(15, 31, 29, 38, 1, 0, 0); CuadroDeTexto(30, 31, 44, 38, 5, 0, 0); CuadroDeTexto(45, 31, 59, 38, 15, 0, 0);
		ir(18, 35); colorfondo(1); colorletra(9); Escribir("M\242vil", 1); PintarMovil(4, 26, 35); ir(32, 35);
		colorfondo(5); colorletra(9); Escribir("Bloques", 1); PintarCaja(4, 41, 35); colorfondo(9); colorletra(1);
		ir(12, 41); Escribir("   Huecos: ", 1);
		CuadroDeTexto(15, 43, 59, 50, 7, 0, 0); colorfondo(9); colorletra(1);

	}

	if (nivel == 5){
		colorletra(1); CuadroDeTexto(12, 15, 69, 45, 9, 1, 1);
		ir(36, 17); Escribir("NIVEL 5", 1);
		ir(12, 21); Escribir(" Objetivo y Reglas: ", 1);
		ir(12, 23); Escribir("  -Llegar al portal.", 1);
		ir(12, 25); Escribir("  -Empuja todos los bloques hacia sus lugares correctos,", 1);
		ir(12, 27); Escribir("	para que se active el portal.", 1);
		ir(12, 29); Escribir("  -ALGUNAS PAREDES SON EN REALIDAD BLOQUES", 1);
		ir(12, 31); Escribir("  -DESC\351BRELAS Y AL FINAL D\220JALAS EN SU SITIO.", 1);
		ir(12, 33); Escribir("  -Ten cuidado con la cantidad de movimientos.", 1);
		ir(12, 35); Escribir(" Zonas Permitidas: ", 1);
		CuadroDeTexto(15, 37, 29, 43, 2, 0, 0); CuadroDeTexto(30, 37, 44, 43, 7, 0, 0); colorfondo(2);
		ir(18, 40); colorletra(9); Escribir("M\242vil", 1); PintarMovil(5, 26, 40); ir(32, 40);
		colorfondo(7); colorletra(9); Escribir("Bloques", 1); PintarCaja(5, 41, 40); colorfondo(9); colorletra(1);
	}
	esperartecla();
}
//--------------------------------------------------------------------------------------------------

//----------------------------------FONDOS Y MAPAS DEL JUEGO----------------------------------------
void Fondo01()
{
	string letras = "M@#@#@@@@@MMM@########&&&&&&&&&&&#@#@##@########@#@@#@@#@#########@@@@@#@@#@@#@MM#<?&%%00&##8&&&&&&&&&&&&&&&&&&&&&%<<<?0?&%?<%&?#%?8?<&%?80<&&&&?%&00&8%?8%<&&?@M&*<&&?00&##%&&&&&&&&&&&&&&&&&&&&&%?<%?#?%0%?<<%0.<0.*%&<0/.%&&&&%?000&./0.*%&<&#8<0&%?&000&&&&&&&&&&&&&&%&&&&&&&&%%?&%0%&&&&%%&&?&&?&&&%&%?&&&0&&&&&&&?&&?&&&%&@0*%8&&%&&&&&&&&&%&&&&&&&&&&&000&&&000?&%&&&&&&&00&&&&&&&&&&&&&00008#?%&&000&&&&M?*/#&<&&<&&&&&&&&<%&&&&&&&&&000&&&@#@?&&&&&&&&&00&&&/8<*&&&&&&000&#0<&%<000&&&&M?.%?<?&%?&&&&&&%#<%&&&&&0&&&000&?%000?&&&&&&&&&000%&<%*<&&&&&&000??*&%%?00&&&&&M<%0&%&&%&&&&&&0%&#&&&00&00&&0&0?<&000%&?&&&&&&&&&&&&&0&0&&&&&&000&%%&&&&&&&&&&&@&?&&&&&&&&&&000M0#&&&&8<%00&0&?&<%000?0&&&&&&&&&&&&&&&&&&&&&&&&00&&&&&&&&&&&&&&M&%?&&&&&&&&&000&&&&&&0%.<00&%0/%<%000?<<&0&%%&&&&&&&&&&&&&&&0&&00&&&&&&&0&&&&&&M&&%&&&&&&&&&000&&0&&&&%?&000&&%%%&0&0%?%0&&%<?%&&&&&&&&&&&&&&&&00&&&&&&&&&&&&&&M00&&&&&&&80&&0&&&&&&&&&&&&&&&&&&&0&&&000000%<<?00&&&&&&&&&&&&&&&&&&&&000&&&&&&&M00&&&&&&<8<*&&&&&&&&&&&&&&&&&&&&&&00<000000%%<&00&&&&&&&&&&&&&&&&&&&&00&0&<&&&&M00&&&&&&<%*/&&&&&&&&&&&&&&&%0?&&&&0&<000000&??&00&&&&&&&&&%%&&?%?&&&&0&0&&<&&&8M&&&&&&0%&&%&&&&&&&&&&&&&&&&%0#0&&&0&&00&000&&00&&&&&&&&&?&%&&&?%8%&&&8?0&%&&&&0@&%&&&&&&&&&&&&&&&&&&%&#?%&?%MM0&&&&&&&&&&&&000&&%%&&&000?&&&&&@0M%&%%&*<#&?&&&MM&%?&&&&&&&&&&&&&&&&&?&%./&%<8#%&&&&&&%%&&&&000&%&<&&&000?%&&&&&&0&&%??.*0**&&&8M&%%&&&&&&&&&&&&&&&0&?&?<&&%&0%&0&&&&&0#%&&&0000&%%&&&000#&&&&&&&%0&%%8<&?<&&&&&M&&&<&&&&&&%&&&&&?&&0%000&%%&&&0000&%&80#&&&&&&&?%%&&&&%&88M&&&00000&%8<&&&&&&&0M&&%<&%&&&&&<0?*&%<0&.%00&&%<&&&&0000&&&&&&&&&&&?<<&&%&&<0#8&&&0000MM0%*/&&&&&&0M&&&<&&&&&&0<%<*&%?%/.&000&&<&&%&000&&%000&&&&&%<<%&&&&&<88&&&&0000MM&&.<&&&&&&0M&0%%&%&&&&&0&&00&&0%#%&00&&&&&&&&&&&&0000&&&&&&0&&&&&&&&000&&&&&00#M8%%0&&&&&00@&%%&&&&&&&&&&&%08<@M0&%%&&&&&&&&&&&&&000&#<&&&&&&&&&%00%000&&&&%%0MM0&&&&&&&&%0@&%?%&&&&&&&%%0/0<.8MM<%%/%&&&&&&&&&&&0000?.?&&&&&&&&&0/.000&&&&&??#@&&&&&&&%&<%M&%&@<%&&&&&%0%?%0<8MM&%%%&&&&&&&&&&&&000&<<&&&&&&&&&&%/%000&&&0%%8@&&&&&&&&&&?<M00&8M&&&&&&&&&&&0*&0&&&&&%&&&&&&&&&&&&&&0&&&&&&&&&000000&%&&&&&8%0&M%&&&&&&0&&?M00%##%&&&&&&&&&0?.%&&&&&%?&&&&&&&&&&&&&<&&&&&&&&&&000000&&<&&&80/?0#%&&&&&&8%*%M0&0%&%&&&&&&&&&0/*%&&&&&&?&&&&&&&&&&&&&?%&&&&&&&&&000&0&%0<%&&&?.%?0&&&&?%&&/*<@8?0%000&&0&&%&&&<&&&&&&&%%&&&&&&&&&&&&&&&&&&&&&&&&&00%#&0&&&&&0&&0%&&&&&&00&&0&M&.%&?&0000&&%&&&&&&&&&&&&&&&000&&&&&&&&&&&&&&&&&&&&??M#&&&&&&&00&&#?&&&%###000&M?*<&&<000&&&%&%&&&&&&&&&%?%&000&&&&&&&&&&&&&&&&&&&&0/88&&&&&&&&&00%.<&&&@8%0000@0/&&%?000&&&%&&&&&&&&&&&&#%&00&&&&&&&&&&&&&&&&&&&&&&?&&%&&&&&&&&#&<*&&&&&<&&&&&##/00000&&&&&&&&&&&&&&&&&&0@8&&&&&&&&&&&&&&&&&&&0&&&&&&&&&&&&&&&&&&&&&&&&&%%&%&&M%.?000&&&&&&&&&&&&&&&&&&&@#0&&&&&&&&&&&&&&&&&&&8??&&&&&&&&&&&&&&&&&&&&&&0&?#&0&@?.?&&0&&&&&&&&&&&&&&&&&&&8<%&&&&&&&&0&&&&&&%&&&%.<&&&&&&&&&&&&&&&&&%&&&0&&&&<<%M??&8%0&&&&&&&&&?<%&&&&&&&&&&&&&&&&&&00&&&&&&%&0&%&&&&&&&&&&&&&&&08#8%&&&&&&?<%0@%%%8.?&&&&&&&&&&<#&%%&&&&&&&&&&&&&&&&&&&&&&&8?&&&&&&&&&&&&&&&&&&#00#%&&&0000000M&&?&*/&&&&&&&&&%800&?%&&&&&&&&&&&&&&&%%&&&&0&*/&&&&&&&&&&&&&&&&&8&0&?%&&@#8@###M&&?%*%&&&&&&&&&&&%8&&%&&&&&&&&&&&&&&&&8&&&&&%*%&&&&&%&&&&&&%&&&&#&0%%&&&0000000M&&&&&&&&&&&&&&0000&&@<&&&&&&&&&&&&&&M&&8&%&0&&&&&&&&&&&&&&&%%&0000&%%&&&&&&&&&%@&&&&&&&&&&&&&0&&00000%&&&8<%&&&&&&&&#&%0&&?%&&&&&&&&&&&&&&&%%&000&&&&&&&&&&&&&%M&&&%&&&&&&&&%&&&0&&%&&&&00.<&&&&&&&&@&&&&&??&&&&&&&&&&&&&&&%%&000&&&&&&&&&&&&&%M&&&%%&&&&&&&???&0?&?&&&&0#?&&&&%&%8#0&?&0&?&&&&&&&&&&&&&&&&%%&000&%&&&&&&&&&&&%@&%?%%%&&&&&&?%?&&*&&&&&&&0#08&&&&%&&%000000&&&&&&&&&&&&&&&&%%&&&&&?&&&&&&&&8&%0M&%<%??&&&&&&?&%0<.?&&&&&&80&0<.&&%&0/&00000&&&&&&&&&&&&&&&&%%&&&&%?&%&&&&&&0<.?M&%%<<%&&&&&&%%&&<*&&&&&&0%&&&*?&&%0&?&%&000&&&&&&&&&0&&&&&&&&&&&&&?&&&&&%%%&?<&M0%&&&&&&&&&0000&?0&&&&&00000&&0&&&000%0?0&&&&&&&&&&%0000&&&&&&&&&%&&&&0&0M88%%&M8<?&%%&%&080000&%?&&&&&&%#@&&0?&0%000&%*&&&&&&&&&&8?<000&&&&&&&&&&&&&&&0MM%8/*&M&*?&&<%<%8000000&%?&&&&&?MM8%8/&&&0%0&/.%&&&&&&&&&0.*%&0&&&&&&&&&&&&&&&&MM0&/*&@8<0&??%??0&&0000%?&&&0&?&#M80%%&&%@0&&??&&&%%%%&&&?/&&0%&&&&&&&&&&&&00&&#M8%<%0@8*&00&0&/?%0000&&&&&&&8%0MM8000&0%8##&%&&&&%0#%&&&&&&#8&&&&000&?%&&&&00&8&%&&&0M?*<00&?<<?<%&00&&&&&&0&*<MM0000&&%#8%&%&&&&?0&<&&&&&&#8&&&&&00&&?%&%?00&8/*&&/0M?.%%%&00???%&%&&&&&&&&&*%00&&?&%&%0%&&&&%&&&%<%&&&&&&&&&&&%&00&0<%&?%&%&%*?&&?&M%%&?%?&&&&&&&@&&&&&&&%8<&&0&#@&&&&%%000&&&&&%&00&&&&&&&&&&&&&&&0@%%&&8?&&%00&&&M%%<?&?&8&000#80&&&00/%&*?&&&@@&%&&%%&000&&&&&%%000&&&&&&&&&&&&#&@&&%%&*<&%%&&&&M&&?%%?&0&&&00#&&&&0<.??.<&&?#@?&&&&&&000&&&&&&<&&0&&&&&&&&&&&&&000&&?%.*00<&&&&M%&&&%&00&?<&8&&&&&%??&%<&&&&8%&&&&&&&&&&&&&&&&<??&&&&&&&&&&&&&&0%0&&%&/&&&%&&&&@#%000&08&<?%&&&&&&&%&0000&&&&&&&&&&&&&&&&&&&000?%?000000&&&&&&&&&&&&&&&&&&&&&&&M0/?00&00&%?%&&&&&&0&?%00&&&&&&&&&&&&&&&&&&&&00&&&&000#80&&&&&&&&&&&&&&&&&&&&&&&@?.&00&08&%?&&&&&&&&&?%00&&&&&&&&&&&&%&&&&&&&00&%<&000000&&&&%%&&&&&&&&&&&&&&%&&";
	int arr[4800] = { 15, 8, 8, 8, 8, 14, 14, 14, 14, 14, 8, 15, 15, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 14, 8, 8, 14, 8, 8, 14, 14, 8, 8, 8, 8, 8, 8, 8, 8, 14, 14, 14, 14, 8, 8, 14, 14, 8, 14, 8, 8, 8, 8, 8, 14, 7, 7, 11, 3, 7, 14, 14, 14, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 12, 12, 7, 7, 8, 7, 8, 3, 3, 7, 7, 8, 7, 14, 7, 7, 14, 7, 7, 3, 3, 7, 14, 8, 7, 7, 9, 7, 8, 3, 3, 8, 14, 14, 14, 14, 14, 7, 14, 14, 7, 3, 3, 7, 8, 8, 14, 10, 3, 3, 8, 3, 14, 14, 14, 8, 8, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 7, 7, 8, 7, 3, 11, 3, 7, 12, 12, 7, 14, 10, 10, 14, 10, 10, 3, 11, 3, 14, 10, 10, 7, 9, 7, 8, 11, 3, 3, 14, 14, 14, 8, 10, 10, 14, 10, 3, 3, 8, 3, 8, 8, 14, 7, 14, 14, 3, 7, 14, 14, 14, 14, 8, 8, 9, 9, 9, 7, 7, 8, 8, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 9, 9, 9, 7, 7, 7, 14, 8, 7, 8, 7, 3, 7, 7, 14, 14, 14, 14, 14, 14, 14, 14, 14, 7, 7, 14, 14, 14, 8, 9, 7, 14, 14, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 8, 7, 8, 8, 14, 10, 7, 8, 8, 8, 3, 7, 14, 8, 9, 9, 9, 9, 9, 8, 7, 8, 14, 7, 9, 9, 9, 9, 8, 7, 8, 14, 14, 14, 14, 9, 9, 9, 8, 8, 8, 7, 7, 7, 8, 9, 9, 9, 9, 7, 8, 14, 14, 14, 8, 7, 14, 14, 14, 14, 8, 7, 9, 9, 9, 7, 14, 14, 14, 8, 8, 8, 7, 3, 7, 14, 14, 14, 14, 8, 9, 9, 9, 8, 7, 10, 3, 8, 8, 3, 11, 3, 3, 7, 9, 9, 9, 9, 9, 8, 3, 3, 7, 9, 9, 9, 9, 9, 8, 8, 7, 7, 14, 14, 14, 9, 9, 9, 8, 8, 8, 7, 8, 7, 9, 9, 9, 9, 9, 9, 8, 14, 14, 7, 11, 11, 3, 14, 7, 10, 8, 9, 9, 9, 9, 7, 14, 14, 14, 14, 8, 8, 3, 11, 3, 3, 14, 14, 14, 9, 9, 9, 9, 8, 7, 10, 3, 7, 7, 3, 7, 3, 3, 9, 9, 9, 9, 9, 7, 7, 8, 3, 7, 9, 9, 9, 9, 8, 14, 8, 7, 8, 14, 14, 14, 8, 7, 7, 8, 8, 8, 7, 7, 7, 7, 9, 9, 9, 9, 9, 8, 14, 14, 14, 7, 3, 3, 14, 10, 3, 8, 9, 9, 9, 9, 8, 14, 14, 14, 14, 7, 10, 7, 7, 3, 3, 14, 14, 14, 9, 9, 9, 9, 8, 7, 14, 14, 7, 7, 8, 8, 7, 8, 9, 9, 9, 8, 8, 14, 7, 8, 8, 8, 9, 7, 8, 8, 14, 14, 14, 8, 14, 8, 14, 14, 7, 12, 7, 8, 8, 8, 7, 14, 7, 8, 7, 8, 7, 9, 9, 7, 8, 8, 8, 8, 3, 8, 14, 7, 14, 8, 9, 7, 8, 8, 14, 14, 14, 14, 14, 7, 7, 8, 8, 3, 8, 8, 8, 8, 9, 9, 9, 8, 8, 3, 3, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 14, 14, 14, 8, 8, 8, 8, 9, 8, 14, 14, 7, 7, 14, 14, 14, 11, 3, 7, 8, 12, 7, 14, 14, 14, 7, 8, 8, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 8, 9, 7, 8, 8, 8, 14, 14, 14, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 7, 14, 14, 14, 8, 8, 8, 8, 9, 8, 14, 7, 10, 3, 14, 14, 14, 3, 8, 3, 7, 12, 7, 8, 14, 14, 7, 12, 7, 11, 8, 8, 7, 7, 9, 9, 9, 9, 9, 9, 9, 7, 8, 8, 9, 8, 9, 7, 8, 8, 7, 8, 14, 14, 8, 9, 8, 7, 8, 8, 7, 8, 9, 9, 9, 9, 7, 7, 8, 14, 3, 7, 9, 9, 7, 7, 7, 7, 7, 7, 8, 14, 14, 14, 14, 7, 8, 8, 9, 8, 14, 14, 7, 14, 14, 14, 14, 14, 8, 7, 14, 14, 8, 14, 14, 14, 14, 14, 14, 14, 8, 8, 7, 12, 7, 7, 7, 7, 7, 9, 9, 7, 8, 8, 8, 8, 9, 7, 14, 8, 8, 14, 14, 14, 8, 9, 9, 7, 7, 7, 7, 8, 7, 7, 7, 7, 8, 7, 8, 14, 14, 8, 9, 9, 8, 8, 8, 14, 14, 14, 14, 8, 8, 14, 14, 8, 7, 7, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 14, 8, 7, 14, 14, 14, 14, 14, 14, 14, 14, 12, 12, 14, 14, 14, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 9, 8, 14, 14, 14, 3, 7, 14, 8, 7, 7, 9, 8, 14, 14, 8, 9, 9, 9, 7, 11, 3, 14, 7, 10, 7, 8, 9, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 3, 8, 14, 14, 14, 14, 14, 14, 12, 12, 3, 14, 14, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 9, 8, 14, 14, 14, 8, 11, 3, 7, 9, 9, 9, 8, 14, 14, 8, 9, 9, 8, 7, 3, 3, 14, 10, 3, 8, 8, 9, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 8, 7, 9, 9, 9, 8, 8, 8, 3, 8, 14, 14, 14, 14, 14, 14, 12, 7, 11, 14, 14, 8, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 3, 7, 3, 9, 9, 9, 8, 14, 14, 14, 8, 11, 3, 9, 9, 9, 8, 8, 7, 14, 8, 9, 9, 8, 14, 7, 8, 8, 7, 8, 8, 8, 8, 7, 9, 7, 8, 7, 14, 14, 8, 7, 8, 7, 8, 7, 8, 8, 8, 5, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 14, 14, 14, 14, 14, 7, 14, 8, 9, 9, 7, 14, 14, 14, 7, 9, 7, 7, 8, 8, 7, 7, 8, 7, 7, 14, 14, 14, 7, 14, 14, 7, 14, 9, 9, 8, 8, 8, 3, 3, 7, 9, 9, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 8, 3, 7, 7, 14, 7, 7, 11, 3, 7, 8, 8, 8, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 14, 14, 14, 14, 11, 3, 7, 9, 9, 7, 14, 14, 14, 7, 9, 9, 9, 9, 8, 8, 8, 15, 7, 3, 7, 7, 14, 10, 3, 14, 14, 7, 9, 9, 8, 8, 8, 3, 3, 3, 9, 9, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 11, 3, 7, 7, 10, 3, 3, 3, 3, 8, 8, 11, 13, 9, 9, 9, 9, 9, 7, 7, 9, 9, 9, 8, 14, 14, 14, 14, 3, 3, 3, 9, 9, 7, 14, 14, 14, 7, 7, 9, 9, 9, 7, 8, 8, 8, 11, 11, 3, 7, 7, 10, 10, 14, 10, 10, 9, 9, 8, 8, 8, 14, 3, 7, 9, 9, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 14, 8, 3, 14, 14, 7, 8, 14, 3, 7, 8, 7, 8, 14, 8, 5, 5, 5, 5, 8, 8, 7, 8, 9, 8, 14, 14, 14, 14, 14, 3, 7, 9, 9, 7, 14, 14, 14, 8, 7, 7, 9, 9, 7, 14, 7, 7, 14, 14, 3, 7, 14, 7, 8, 14, 10, 7, 9, 9, 8, 14, 8, 7, 7, 7, 3, 9, 7, 9, 9, 8, 7, 7, 14, 14, 14, 14, 7, 7, 7, 14, 14, 14, 14, 14, 14, 14, 3, 7, 14, 8, 8, 14, 14, 14, 14, 7, 7, 14, 8, 8, 8, 8, 9, 9, 7, 7, 8, 8, 7, 7, 7, 9, 9, 7, 7, 7, 14, 8, 8, 8, 8, 9, 7, 14, 14, 14, 14, 14, 14, 14, 14, 7, 14, 8, 7, 7, 9, 9, 8, 14, 8, 9, 9, 7, 3, 9, 7, 9, 9, 7, 3, 3, 3, 14, 7, 10, 3, 3, 3, 8, 14, 10, 7, 14, 14, 14, 11, 3, 3, 7, 8, 7, 14, 14, 14, 8, 8, 7, 8, 7, 8, 8, 9, 9, 9, 9, 7, 7, 7, 7, 3, 9, 9, 7, 11, 3, 3, 8, 8, 8, 8, 9, 7, 14, 14, 14, 14, 15, 8, 14, 7, 10, 10, 7, 9, 9, 9, 9, 8, 14, 8, 9, 8, 9, 3, 9, 9, 9, 7, 14, 8, 8, 3, 14, 10, 10, 8, 3, 3, 7, 10, 10, 7, 14, 14, 14, 8, 3, 3, 7, 8, 7, 14, 14, 14, 8, 8, 9, 7, 8, 8, 8, 8, 9, 9, 9, 9, 7, 3, 3, 7, 9, 9, 7, 7, 11, 3, 8, 8, 3, 8, 9, 7, 14, 14, 14, 14, 8, 15, 14, 7, 10, 3, 9, 9, 9, 9, 9, 8, 14, 8, 8, 8, 7, 7, 9, 7, 9, 8, 8, 8, 8, 14, 14, 14, 14, 14, 14, 8, 14, 7, 8, 14, 8, 14, 14, 14, 3, 8, 8, 7, 8, 8, 8, 8, 8, 7, 8, 14, 14, 14, 14, 14, 8, 8, 9, 9, 14, 14, 8, 8, 9, 9, 7, 14, 8, 14, 14, 14, 14, 8, 9, 7, 14, 14, 14, 14, 8, 8, 14, 7, 14, 14, 9, 9, 8, 7, 8, 14, 14, 8, 3, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 3, 7, 14, 14, 7, 8, 15, 8, 8, 3, 7, 8, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 14, 14, 14, 14, 14, 7, 8, 9, 9, 8, 7, 9, 9, 9, 9, 7, 14, 14, 7, 14, 14, 14, 8, 9, 7, 7, 3, 3, 14, 15, 15, 8, 7, 8, 8, 9, 9, 7, 3, 3, 7, 14, 8, 3, 3, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 3, 8, 3, 8, 7, 10, 8, 15, 15, 3, 3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 14, 14, 14, 7, 10, 7, 9, 9, 8, 9, 9, 9, 9, 9, 7, 14, 10, 10, 8, 14, 14, 8, 9, 7, 8, 3, 3, 7, 8, 8, 8, 8, 7, 7, 9, 9, 7, 3, 8, 3, 3, 8, 7, 3, 8, 13, 7, 7, 9, 9, 9, 9, 9, 9, 14, 7, 3, 7, 14, 3, 8, 15, 8, 14, 7, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 14, 14, 14, 10, 10, 8, 9, 9, 8, 9, 9, 9, 9, 9, 8, 14, 10, 7, 14, 14, 14, 8, 9, 7, 14, 7, 3, 8, 13, 7, 14, 8, 7, 8, 9, 9, 8, 14, 7, 3, 7, 8, 14, 14, 14, 8, 8, 7, 8, 8, 8, 9, 9, 9, 7, 7, 8, 14, 14, 10, 14, 8, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 7, 14, 9, 9, 9, 8, 7, 7, 14, 8, 7, 7, 9, 9, 8, 9, 9, 8, 14, 14, 14, 14, 14, 14, 7, 7, 14, 8, 9, 7, 14, 14, 7, 8, 8, 15, 14, 8, 7, 7, 9, 9, 8, 14, 8, 14, 7, 8, 14, 14, 14, 8, 8, 7, 8, 8, 7, 9, 9, 9, 9, 9, 9, 8, 7, 10, 7, 9, 9, 9, 9, 9, 7, 3, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 8, 3, 3, 8, 9, 9, 9, 9, 9, 8, 9, 9, 8, 14, 14, 14, 14, 14, 14, 3, 3, 3, 7, 9, 7, 14, 14, 7, 7, 8, 8, 7, 9, 9, 9, 9, 9, 7, 14, 7, 10, 3, 8, 14, 14, 14, 7, 8, 7, 8, 8, 7, 7, 9, 9, 9, 9, 9, 8, 10, 10, 7, 9, 9, 9, 9, 9, 9, 7, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 7, 3, 3, 7, 9, 9, 9, 9, 8, 8, 9, 9, 8, 14, 14, 14, 8, 14, 14, 7, 8, 3, 7, 9, 7, 14, 7, 10, 3, 7, 8, 8, 9, 9, 9, 3, 7, 14, 14, 10, 10, 3, 8, 14, 7, 14, 7, 14, 14, 14, 8, 14, 14, 8, 8, 7, 9, 9, 14, 7, 14, 8, 9, 9, 8, 8, 9, 7, 7, 9, 7, 8, 8, 8, 9, 9, 8, 9, 9, 9, 8, 8, 8, 8, 9, 9, 8, 8, 8, 8, 9, 9, 8, 14, 14, 14, 7, 8, 7, 14, 8, 8, 7, 9, 8, 8, 14, 14, 14, 14, 14, 8, 9, 9, 8, 9, 8, 8, 14, 14, 14, 14, 8, 14, 10, 7, 11, 3, 14, 14, 14, 14, 8, 9, 9, 7, 9, 9, 9, 9, 9, 9, 9, 9, 14, 7, 9, 9, 9, 9, 8, 14, 14, 14, 9, 9, 8, 9, 9, 9, 9, 9, 7, 8, 9, 9, 8, 7, 9, 9, 9, 9, 7, 11, 3, 7, 8, 8, 8, 8, 9, 9, 9, 9, 5, 13, 13, 8, 14, 14, 7, 8, 9, 9, 7, 8, 13, 8, 14, 14, 14, 7, 8, 7, 10, 3, 11, 8, 3, 14, 14, 14, 8, 9, 9, 7, 9, 7, 9, 9, 9, 9, 9, 7, 8, 9, 9, 7, 7, 7, 8, 14, 14, 14, 9, 9, 8, 7, 9, 9, 9, 9, 9, 8, 9, 9, 7, 9, 9, 9, 9, 9, 7, 11, 8, 3, 8, 8, 3, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 7, 10, 7, 9, 9, 7, 8, 8, 3, 8, 14, 14, 8, 8, 8, 7, 8, 8, 7, 7, 14, 14, 14, 8, 9, 7, 7, 9, 9, 9, 9, 9, 9, 9, 8, 8, 9, 9, 8, 8, 7, 8, 14, 14, 14, 9, 9, 8, 8, 7, 7, 9, 9, 9, 8, 9, 9, 7, 9, 9, 7, 7, 7, 14, 14, 7, 3, 8, 7, 3, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 10, 10, 7, 9, 9, 8, 7, 7, 8, 14, 14, 14, 14, 8, 14, 7, 14, 14, 14, 14, 14, 8, 8, 7, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 14, 8, 7, 9, 9, 9, 7, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 14, 8, 14, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 7, 9, 9, 8, 7, 7, 14, 8, 7, 8, 14, 8, 7, 10, 3, 14, 14, 14, 8, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 7, 9, 9, 9, 9, 9, 9, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 14, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 8, 3, 7, 8, 8, 8, 7, 8, 7, 10, 3, 14, 14, 14, 5, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 7, 11, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 9, 9, 9, 9, 7, 7, 9, 9, 8, 7, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 7, 9, 9, 7, 14, 8, 8, 7, 8, 7, 3, 9, 8, 14, 14, 14, 14, 7, 14, 5, 9, 8, 8, 8, 8, 9, 9, 9, 3, 7, 7, 8, 7, 8, 8, 8, 8, 14, 14, 14, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 14, 8, 8, 8, 9, 9, 7, 7, 8, 14, 14, 7, 8, 9, 9, 9, 9, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 13, 13, 8, 7, 8, 8, 8, 8, 7, 7, 7, 7, 7, 8, 8, 3, 7, 14, 14, 10, 7, 5, 9, 8, 8, 9, 9, 9, 9, 9, 9, 3, 8, 7, 3, 7, 14, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 14, 7, 14, 7, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 7, 7, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 11, 3, 7, 14, 10, 7, 5, 9, 8, 7, 9, 9, 9, 9, 9, 7, 8, 8, 11, 3, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 9, 7, 14, 8, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 3, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 7, 3, 7, 7, 10, 7, 5, 9, 8, 9, 9, 9, 9, 9, 8, 8, 8, 7, 8, 8, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 7, 9, 9, 8, 14, 14, 10, 7, 9, 9, 9, 7, 7, 7, 9, 9, 9, 8, 7, 7, 9, 9, 9, 7, 7, 8, 14, 8, 7, 3, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 8, 9, 9, 9, 8, 8, 14, 14, 14, 14, 8, 7, 13, 7, 9, 9, 14, 14, 14, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 8, 8, 14, 7, 14, 14, 8, 9, 9, 9, 9, 8, 9, 9, 8, 9, 9, 9, 9, 7, 8, 7, 9, 7, 14, 14, 14, 14, 7, 9, 9, 9, 9, 7, 14, 8, 8, 8, 8, 8, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 8, 8, 7, 14, 14, 14, 8, 8, 8, 7, 9, 9, 14, 14, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 7, 8, 8, 3, 3, 7, 9, 9, 9, 9, 9, 8, 9, 9, 8, 9, 9, 9, 9, 9, 7, 7, 9, 7, 14, 14, 14, 8, 9, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 9, 7, 8, 9, 9, 9, 7, 9, 9, 9, 7, 8, 9, 9, 9, 7, 8, 9, 7, 14, 14, 8, 7, 7, 8, 9, 9, 14, 8, 10, 7, 7, 9, 9, 9, 9, 9, 9, 9, 8, 8, 7, 3, 11, 8, 3, 9, 9, 9, 9, 9, 9, 8, 9, 9, 8, 7, 9, 9, 9, 9, 9, 5, 9, 7, 14, 14, 14, 8, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 7, 8, 7, 8, 7, 7, 7, 7, 7, 8, 8, 9, 9, 9, 14, 7, 7, 14, 14, 7, 14, 7, 7, 8, 9, 9, 8, 8, 7, 14, 8, 8, 14, 9, 8, 7, 8, 8, 14, 14, 7, 8, 14, 14, 3, 7, 9, 9, 7, 8, 9, 8, 9, 9, 8, 8, 7, 8, 9, 9, 9, 5, 9, 7, 14, 14, 14, 8, 7, 9, 9, 9, 9, 8, 9, 9, 8, 8, 8, 8, 7, 8, 3, 7, 14, 14, 14, 14, 8, 9, 9, 9, 9, 9, 14, 14, 14, 14, 14, 10, 14, 7, 9, 9, 9, 9, 8, 8, 8, 8, 14, 7, 14, 13, 8, 7, 7, 7, 7, 14, 14, 14, 14, 14, 14, 8, 9, 9, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 5, 9, 9, 7, 7, 7, 9, 7, 9, 9, 9, 9, 9, 9, 9, 8, 14, 8, 14, 8, 8, 3, 3, 7, 14, 14, 7, 9, 9, 9, 9, 9, 9, 14, 14, 7, 8, 10, 10, 7, 9, 9, 9, 9, 7, 7, 8, 8, 8, 8, 7, 10, 13, 8, 7, 8, 8, 3, 8, 14, 14, 14, 14, 14, 8, 9, 9, 7, 9, 9, 9, 9, 9, 8, 8, 8, 9, 9, 9, 9, 5, 9, 9, 9, 9, 9, 7, 7, 9, 7, 9, 9, 9, 9, 9, 8, 14, 7, 10, 3, 8, 8, 3, 7, 14, 14, 7, 9, 9, 9, 9, 9, 8, 14, 14, 7, 14, 10, 10, 8, 9, 9, 9, 9, 8, 14, 7, 8, 7, 14, 10, 7, 13, 8, 7, 8, 8, 3, 8, 7, 14, 14, 14, 14, 8, 9, 9, 9, 9, 9, 9, 9, 7, 14, 8, 8, 7, 9, 9, 9, 8, 5, 9, 9, 9, 9, 9, 7, 9, 9, 9, 9, 9, 9, 7, 14, 8, 7, 7, 8, 8, 14, 7, 14, 7, 14, 8, 7, 9, 7, 14, 14, 14, 14, 14, 14, 14, 7, 14, 8, 9, 9, 14, 8, 14, 14, 14, 14, 14, 7, 8, 14, 13, 8, 7, 14, 14, 14, 14, 14, 7, 14, 8, 7, 7, 9, 9, 9, 9, 9, 14, 14, 7, 14, 14, 14, 14, 9, 9, 9, 7, 7, 9, 9, 9, 9, 7, 9, 9, 7, 8, 8, 14, 8, 8, 8, 14, 7, 14, 8, 8, 14, 7, 7, 11, 3, 7, 8, 7, 7, 14, 8, 14, 14, 14, 14, 8, 3, 3, 7, 9, 9, 8, 9, 3, 7, 14, 8, 8, 11, 8, 7, 13, 8, 7, 14, 14, 14, 14, 7, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 14, 14, 7, 7, 14, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 8, 8, 15, 8, 7, 14, 10, 10, 3, 8, 7, 10, 3, 3, 8, 3, 14, 14, 7, 8, 14, 14, 14, 14, 14, 8, 8, 3, 7, 9, 9, 8, 8, 11, 7, 8, 15, 14, 3, 8, 3, 13, 8, 7, 8, 14, 14, 14, 10, 10, 3, 9, 9, 9, 9, 9, 7, 9, 9, 14, 14, 10, 10, 7, 14, 14, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 8, 7, 15, 8, 8, 14, 10, 10, 3, 8, 14, 7, 14, 14, 7, 7, 14, 14, 7, 14, 14, 14, 14, 14, 14, 14, 7, 3, 8, 9, 9, 14, 14, 7, 8, 8, 8, 14, 14, 7, 7, 13, 8, 7, 8, 8, 7, 14, 7, 7, 8, 9, 9, 7, 7, 7, 7, 9, 9, 8, 7, 10, 7, 8, 8, 14, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 7, 8, 14, 14, 8, 8, 8, 8, 14, 7, 7, 7, 14, 8, 14, 10, 14, 14, 14, 14, 14, 14, 7, 14, 14, 14, 14, 14, 14, 14, 7, 9, 9, 9, 9, 14, 14, 14, 14, 15, 15, 14, 14, 14, 14, 13, 8, 7, 8, 8, 8, 8, 7, 8, 8, 9, 9, 7, 8, 8, 7, 9, 9, 9, 9, 7, 14, 8, 8, 8, 8, 8, 8, 14, 14, 14, 7, 3, 7, 8, 3, 8, 14, 14, 14, 14, 14, 14, 14, 8, 8, 7, 14, 8, 7, 10, 3, 14, 14, 14, 14, 7, 7, 14, 14, 7, 8, 14, 14, 8, 9, 9, 9, 9, 9, 14, 8, 10, 7, 8, 8, 14, 14, 14, 14, 5, 9, 7, 8, 8, 7, 3, 11, 9, 9, 9, 9, 7, 8, 8, 7, 9, 9, 9, 9, 9, 7, 8, 8, 11, 8, 8, 9, 8, 14, 14, 8, 11, 3, 3, 11, 3, 3, 14, 14, 14, 14, 7, 3, 3, 11, 3, 8, 8, 7, 10, 7, 14, 14, 14, 14, 14, 7, 14, 14, 7, 8, 7, 14, 7, 9, 9, 9, 9, 8, 14, 14, 10, 7, 14, 14, 14, 8, 14, 14, 9, 8, 7, 8, 7, 8, 8, 8, 9, 7, 9, 9, 7, 7, 7, 7, 7, 9, 9, 9, 9, 8, 7, 8, 8, 8, 8, 7, 8, 14, 14, 8, 8, 3, 7, 8, 3, 3, 14, 14, 14, 14, 10, 3, 8, 7, 3, 14, 8, 7, 14, 14, 14, 14, 7, 7, 8, 7, 14, 14, 14, 8, 8, 8, 7, 9, 7, 8, 8, 14, 14, 14, 7, 14, 8, 14, 14, 8, 8, 8, 8, 9, 8, 7, 7, 14, 14, 14, 14, 8, 9, 9, 8, 7, 14, 14, 14, 14, 14, 9, 9, 7, 8, 8, 8, 8, 8, 8, 8, 8, 14, 8, 8, 8, 14, 7, 7, 14, 14, 7, 14, 7, 7, 14, 14, 8, 8, 8, 8, 3, 3, 7, 14, 14, 7, 8, 8, 8, 14, 14, 14, 8, 8, 8, 7, 9, 7, 14, 14, 7, 7, 14, 10, 3, 8, 8, 7, 13, 13, 7, 9, 9, 8, 9, 9, 7, 14, 14, 14, 8, 9, 9, 8, 11, 3, 7, 14, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 3, 3, 3, 7, 14, 10, 3, 3, 3, 7, 8, 9, 9, 9, 8, 11, 8, 3, 14, 14, 3, 9, 8, 8, 14, 14, 14, 8, 8, 3, 3, 9, 7, 14, 7, 10, 7, 7, 10, 3, 8, 8, 7, 8, 13, 7, 7, 9, 9, 9, 9, 8, 14, 14, 14, 8, 9, 9, 8, 3, 3, 3, 7, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 8, 8, 8, 11, 11, 8, 7, 7, 10, 3, 11, 8, 3, 9, 9, 9, 9, 8, 14, 3, 14, 14, 14, 8, 8, 8, 8, 14, 14, 14, 14, 14, 8, 7, 9, 7, 14, 7, 14, 14, 14, 7, 8, 14, 7, 8, 8, 7, 8, 8, 7, 8, 8, 9, 8, 14, 14, 14, 8, 9, 9, 8, 14, 3, 7, 9, 7, 14, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 7, 14, 8, 14, 14, 14, 3, 7, 14, 10, 8, 14, 7, 7, 9, 9, 7, 7, 8, 14, 7, 14, 14, 14, 8, 8, 8, 8, 14, 14, 14, 8, 7, 9, 9, 9, 7, 8, 3, 7, 14, 14, 14, 14, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 14, 14, 8, 9, 9, 7, 14, 14, 14, 14, 14, 14, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 15, 14, 7, 3, 14, 14, 8, 8, 8, 8, 14, 14, 7, 8, 9, 9, 9, 9, 7, 8, 11, 3, 3, 14, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 14, 14, 7, 7, 7, 11, 14, 14, 14, 14, 8, 14, 8, 8, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 7, 10, 7, 14, 14, 8, 8, 8, 8, 14, 7, 3, 7, 9, 9, 9, 9, 8, 14, 3, 3, 7, 14, 14, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 9, 9, 8, 14, 14, 14, 7, 3, 11, 14, 14, 14, 8, 14, 14, 14, 8, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 14, 14 };

	for (int i = 0; i<letras.length(); i++){
		SetColor(arr[i]); Console::Write(Convert::ToChar(letras[i]));
	}
}
void Fondo02()
{
	string letras = "?<<<<%<<<<%<<<<??<<<<%<<<<%<<<<??<<<<%<<<<%<<<<??<<<<%<<<<%<<<<??<<<<%<<<<%<<<<?**/****//****/****/****//****/****/****//****/****/****//****/****/****//****/**/ . .< .. <. . */ . .< .. <. . */ . .< .. <. . */ . .< .. <. . */ . .< .. <. . *% * /&....%****//***/<****</.  </   *<.  .<*   </   /&*  *&/   ?%   /&....&/ * ??<<<<%<<<<<//*..**..*.*****//<<<<<%<<<<??<<<<%<<<<&88888888**********%<<<<%<<<<?**/****//**//              //**//****/****/****//*<8888888&**********<*//****/**/ . .< .. <//              //? .. <. . */ . .< .. &******************? .. <. . *% * /&....?//.  . .  ..... //%.  *&/   ?%   /&*  .%******************%....&/ * ??<<<<%<<<<<**...***%?%?%%<///<<?888888888888888&?<<******************%<<<<%<<<<?**/****//*/..&88880%%&8888&//*<*###############%/<*******************/*//****/**/ . .< .. ??&&8888%**<8888&//*<*###############%/<*******************? .. <. . *% * /&....%//&8888%**<8888&//*<*###############%/<*******************%....&/ * ??<<<<%<<<<&#888888#0088#88&//*<*###############%/<*******************%<<<<%<<<<?**/****//*<08@@88#8888808#0//*<*?<<<<<?####&<<<</<*******************/*//****/**/ . .< .. %888888#80888880&//*<*%%&00&%?<<<<0&%</<*******************? .. <. . *% * /&....%8@#8888888800@@&//*<*%?%88@0M??&@00&</<*******************%....&/ * ??<<<<%<<<<&888888#8##88888&//*<*%<%%%%%M%?&@%%<</<*******************%<<<<%<<<<?**/****//*<88888#@@@@888??<//*<*8888888&%%%&8888/<*******************/*//****/**/ . .< .. &88888#@@@@&&&*******.8888888888888888**/00&0000&00&0000&00? .. <. . *% * /&*  .888888#@@@@??<*..../..8888888#888#80&0*.<88888888888****%8&&****** * ??<<<<08888888888#@@@@888888#888888888#888##880?%88888888888888***M0<0%M****/<<<?**/**&8888#88888#@@@@888888888#888#888#8###8#0??88888888888888***M%<M*M******/**? . *88888888888#@@@@8888888##888#88##@@@@@@@88888888888888888****8M@@M****. . *%   /888888888#8#@@@@8888888888888888#@@@@@@@88888888888888888*************/ * ?888888##@##@#@@#@@@@@@@#@##@#@@#@##@#@@@@@@@@88888888888888888/************?<<<?88888#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@88888888888888888/************/*/**88888#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@88888/***&@#8<****.************ . *80&&8##@@##@@##@@##@008@@##@@##@@##@@##@@@@@@88888***#8*0<M****%0000008##88/ * ??<<<?%************&?<<<&8888888888888888#@@@@88888/**8#<#/M****%88888888888<<<<?**/**/************<**/**8888888888888888#@@@@88888****&@M@M****%8888888##8&**/**/ . ./************<. . *8888888888888888#@@@@88888<////?&&&&&&?&888@@@@#888* . *% * //************?/ * ?0000000000888888#@@@@8888808888%??&88888888@@@@#888/   ??<<<</************?<<<</............*888#@@@@&&&8888888<**%88888888@@@@#88888888**/***************<**/*.            .888#@@@@??<8808888<**%88888888@@@@#88888888/ . ./************<. . .            .888#@@@@888#888888888###88#888@@@@@88888888% * //************?/ * /. .... .....*888#@@@@888888###888#888888###@@@@@88888888?<<<</************?<<<</*****&&&&&&%<888#@@@@####@@####@@@#@#@##@@#@@@@@##888888**/***************<**/*/88880??%88888888#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@888888/ . ./************?* . <8888&***88888888@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#88888% * //************%/   ?8888&***88888888#@@@@@##########################8#88&&08?<<<</************%88888888@#88888888888#@@@@#888888888888888888888888<<<<%<<<<?**/***************%88888888@@88888888888#@@@@#88???????%???????%????<<*//****/**/ . ./************%888888888888888888888#@@@@#88/<..............***/// .. <. . *% * //************%888888888888888888888#@@@@888/<.            ....//<....&/ * ??<<<</************%888888888888888888888#@@@@888/<             ./**//<<<<<%<<<<?**/***************%888888888888888888888#@@@@888/<...... ......*/**//**//****/**/ . ./*************************<88888888#@@@@888*****/*<%&&&&&<*/**/// .. <. . *% * //*************************/80&&8888#@@@@888*.&8888%??&8888</**//<....&/ * ??<<<</*************************/&<<<?0?%#@@@@0?%8888888<**%8888&%%?//<<<<<%<<<<?**/****************************/*//**<</#@@@@%</8888888<**&8888?<////**//****/**/ . ./*************************// . .088#@@@@8888888#88888#880?%%%?/// .. <. . *% * //*************************/% * /088#@@@@88#8#888#8#88888%</<////<....&/ * ??<<<</*************************/?<<<<&?%@@@@@@@@@@@@@@@@@@88888888&**<<<<<%<<<<?**/****************************/**/**<</@@@@@@@@@@@@@@@@@@888888880..**//****/**/ . ./*************************// . .088@@@@@@@@@@@@@@@@@@88888888888? .. <. . *% * //*********/*****/****/****/% * /08&8#################88&&0880&&8&....&/ * ??<<<<&0000&00&?<<?&%<<<&&<<<%&00?<<<<%<<<<%<?<<??<<<<%<<<<%<<<<??<<<<%<<<<%<<<<?**/**&8888888?*//*/**/***//**088**/****//****/****/****//****/****/****//****/**/ . .08888888? .. <. . */ . .088/ . .< .. <. . */ . .< .. <. . */ . .< .. <. . *% * /08&&888&?.  .<*   </   *%08% * /&....&/ * ?% * /&....&/ * ?% * /&....&/ * ?";
	int arr[4800] = { 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 11, 3, 10, 10, 3, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 2, 10, 3, 3, 10, 2, 10, 3, 3, 10, 2, 2, 10, 3, 3, 2, 2, 10, 3, 3, 10, 2, 10, 3, 11, 3, 2, 2, 3, 11, 3, 2, 2, 10, 3, 3, 10, 2, 10, 3, 11, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 3, 10, 10, 7, 4, 4, 12, 12, 4, 4, 4, 4, 12, 4, 4, 4, 7, 10, 10, 3, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 3, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 11, 11, 11, 11, 11, 11, 11, 8, 1, 9, 9, 9, 9, 9, 9, 9, 9, 1, 7, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 7, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 7, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 11, 3, 10, 10, 3, 3, 10, 10, 4, 4, 4, 12, 4, 12, 4, 4, 12, 12, 12, 12, 12, 4, 10, 10, 3, 10, 2, 2, 3, 11, 3, 2, 2, 10, 3, 3, 10, 2, 10, 3, 11, 3, 2, 2, 10, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 7, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 3, 10, 10, 4, 12, 12, 12, 12, 12, 14, 14, 14, 14, 14, 14, 12, 7, 10, 10, 3, 3, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 3, 3, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 7, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 7, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 8, 10, 10, 3, 10, 10, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 7, 3, 10, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 7, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 7, 7, 8, 14, 14, 14, 14, 14, 12, 12, 12, 14, 14, 14, 14, 8, 10, 10, 3, 10, 10, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 7, 3, 10, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 7, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 11, 3, 10, 10, 3, 3, 7, 7, 8, 14, 14, 14, 14, 14, 12, 12, 12, 14, 14, 14, 14, 7, 10, 10, 3, 10, 10, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 7, 3, 10, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 7, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 11, 11, 11, 11, 11, 11, 3, 10, 10, 3, 10, 10, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 7, 3, 10, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 7, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10, 3, 10, 10, 7, 5, 5, 5, 5, 5, 7, 14, 14, 14, 14, 8, 5, 5, 5, 5, 3, 10, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 7, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 10, 10, 3, 10, 10, 3, 9, 8, 8, 8, 8, 7, 7, 5, 5, 5, 7, 8, 8, 9, 9, 3, 10, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 7, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 11, 3, 10, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10, 3, 10, 10, 3, 9, 9, 8, 8, 8, 8, 15, 9, 9, 7, 8, 8, 8, 7, 9, 3, 10, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 7, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10, 3, 10, 10, 3, 9, 9, 9, 9, 9, 9, 15, 3, 9, 8, 8, 9, 9, 9, 9, 3, 10, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 7, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 3, 3, 3, 10, 10, 3, 10, 10, 11, 11, 11, 11, 11, 11, 11, 8, 7, 9, 7, 8, 11, 11, 11, 11, 3, 10, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 7, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 8, 8, 7, 10, 10, 10, 10, 10, 3, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 11, 3, 2, 2, 10, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 7, 7, 9, 3, 10, 10, 10, 10, 3, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 8, 3, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 8, 8, 7, 9, 9, 9, 9, 9, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 5, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 8, 8, 9, 8, 9, 15, 9, 9, 9, 9, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 15, 9, 9, 8, 9, 15, 9, 9, 9, 9, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 8, 15, 8, 8, 8, 9, 9, 9, 9, 3, 10, 10, 10, 3, 3, 10, 2, 2, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 14, 14, 14, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 9, 3, 10, 10, 10, 3, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 3, 3, 3, 3, 7, 7, 7, 3, 3, 3, 3, 3, 3, 10, 10, 10, 3, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 3, 3, 3, 3, 12, 12, 12, 3, 3, 3, 3, 3, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 8, 11, 11, 11, 11, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 3, 3, 3, 3, 12, 12, 12, 3, 3, 3, 3, 3, 3, 10, 10, 10, 3, 11, 11, 3, 11, 11, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 11, 11, 11, 11, 11, 9, 9, 9, 8, 8, 9, 8, 9, 15, 9, 9, 9, 9, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 3, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 8, 11, 11, 11, 11, 9, 9, 9, 8, 8, 9, 8, 9, 15, 9, 9, 9, 9, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 10, 10, 10, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 8, 11, 11, 11, 11, 9, 1, 1, 1, 1, 7, 7, 7, 7, 7, 7, 7, 7, 11, 11, 11, 11, 14, 14, 14, 14, 8, 11, 11, 11, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 3, 10, 10, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 3, 2, 2, 10, 3, 3, 10, 10, 7, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 3, 10, 10, 10, 7, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 11, 11, 11, 8, 14, 14, 14, 14, 8, 8, 7, 11, 11, 8, 14, 14, 14, 14, 12, 12, 12, 14, 14, 14, 14, 14, 11, 11, 11, 11, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 11, 11, 11, 14, 14, 14, 14, 14, 7, 7, 9, 11, 11, 8, 14, 14, 14, 14, 12, 12, 12, 14, 14, 14, 14, 14, 11, 11, 11, 8, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 3, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 10, 10, 10, 10, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 11, 11, 11, 8, 14, 14, 14, 14, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 11, 11, 11, 11, 11, 3, 10, 10, 10, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 3, 10, 10, 10, 7, 12, 4, 12, 12, 12, 12, 4, 12, 12, 12, 12, 12, 4, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 11, 11, 11, 11, 11, 3, 10, 10, 7, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 3, 10, 10, 10, 7, 12, 12, 12, 12, 12, 14, 14, 14, 14, 14, 14, 14, 7, 11, 11, 11, 14, 14, 14, 14, 14, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 14, 14, 14, 14, 14, 8, 8, 8, 11, 11, 11, 11, 11, 10, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 10, 10, 10, 10, 10, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 11, 11, 11, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 3, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 10, 10, 10, 10, 3, 14, 14, 14, 14, 14, 12, 12, 12, 14, 14, 14, 14, 14, 11, 11, 11, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 3, 10, 10, 10, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 3, 2, 2, 10, 3, 14, 14, 14, 14, 14, 12, 12, 12, 14, 14, 14, 14, 8, 11, 11, 11, 14, 14, 14, 14, 14, 14, 8, 8, 14, 8, 14, 8, 8, 14, 8, 14, 14, 8, 14, 8, 14, 14, 8, 8, 8, 14, 14, 8, 14, 8, 14, 14, 14, 8, 11, 11, 11, 3, 11, 11, 3, 10, 10, 7, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 11, 11, 11, 11, 11, 11, 11, 11, 8, 8, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 11, 11, 11, 11, 11, 11, 11, 11, 8, 8, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 8, 11, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 8, 11, 11, 3, 10, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 10, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 3, 10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 10, 10, 10, 10, 10, 3, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 8, 11, 11, 3, 10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 10, 7, 10, 10, 3, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 3, 10, 4, 12, 12, 12, 12, 12, 4, 12, 12, 12, 12, 12, 12, 4, 7, 10, 7, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 11, 11, 11, 11, 11, 11, 11, 11, 8, 14, 14, 14, 14, 8, 11, 11, 10, 10, 4, 12, 12, 12, 12, 12, 14, 14, 14, 14, 14, 14, 14, 7, 7, 10, 7, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 11, 11, 3, 11, 11, 11, 11, 11, 14, 14, 14, 14, 14, 11, 11, 11, 3, 10, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 7, 7, 10, 7, 10, 10, 3, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 11, 3, 10, 7, 3, 11, 7, 7, 8, 14, 14, 14, 14, 8, 7, 7, 11, 11, 8, 14, 14, 14, 14, 12, 12, 12, 14, 14, 14, 14, 14, 8, 3, 7, 3, 10, 10, 3, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 10, 10, 10, 10, 10, 3, 7, 3, 14, 14, 14, 14, 14, 7, 7, 3, 11, 11, 8, 14, 14, 14, 14, 12, 12, 12, 14, 14, 14, 14, 14, 7, 7, 7, 3, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 3, 10, 10, 10, 10, 11, 11, 11, 8, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 3, 7, 3, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 3, 10, 10, 10, 3, 11, 11, 11, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 7, 3, 7, 7, 3, 10, 10, 3, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 3, 10, 10, 7, 3, 11, 7, 7, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10, 3, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 10, 10, 10, 10, 10, 3, 7, 3, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 3, 10, 10, 10, 10, 11, 11, 11, 8, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 8, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 3, 3, 9, 9, 9, 9, 3, 3, 9, 9, 9, 7, 3, 10, 10, 10, 3, 11, 11, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 11, 11, 11, 3, 11, 11, 11, 11, 3, 11, 11, 11, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 10, 10, 7, 8, 7, 10, 10, 7, 8, 8, 7, 10, 10, 7, 8, 8, 8, 3, 10, 10, 7, 3, 11, 3, 10, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 11, 3, 3, 3, 3, 3, 3, 10, 10, 10, 3, 3, 10, 10, 7, 3, 11, 3, 10, 10, 3, 3, 3, 10, 10, 10, 3, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 10, 3, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 10, 11, 11, 11, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 10, 10, 10, 10, 3, 3, 10, 10, 10, 3, 11, 11, 3, 3, 11, 11, 11, 11, 3, 10, 2, 2, 10, 3, 3, 2, 2, 10, 3, 3, 10, 2, 10, 3, 3, 11, 11, 3, 10, 10, 10, 3, 11, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3, 3, 10, 10, 10, 3, 11, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3, 3, 10, 10, 10, 3, 11, 3, 10, 10, 3, 11, 3, 10, 10, 10, 3 };

	for (int i = 0; i<letras.length(); i++){
		SetColor(arr[i]); Console::Write(Convert::ToChar(letras[i]));
	}
}
void Fondo03()
{
	string letras = "****************************************************************************************************************************************************************************************************************.**.****************************************************************************.<<.******************************************************************************<********************************************************************************/*****************************************************************************&******************************************************************************.*..*.**************************************.***********************************.//..&*************************************....****************************/%%%&/&&***.*****************************....*.............*********************.<**%%00*.<.*************************/////********///////////////////////////////**/*%<<. <.///////////////////////////////*..***.....*.//////////////////////////*/*%00* <*/////////////////////////<<<<<</*****.*///**<<<<<<<<<<<<<<<<<<<<<<<.* .<.?//. /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<** ******<<<<<<<<<<<<<<<<<<<<<<< * .*..??..&/<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*.*../ .</   <<<<<<<<<<<<<<<<<<<<<<< *  /.*00<.**<<<<<<<<<<<<<<<<<<<<<<<<<????????*.*    .. .??????????????????????? * ..*/&/.../<????????????????????????%%%%%%%%?..*...*  /%%%%%%%%%%%%%%%%%%??<<< .  ./.%/***.<%%%%%%%%%%%%%%%%%%%%%%%%&&&&&&&&%./*   /.*<&&&&&&&&&&&&&&&&&&?* .. ..  **/.  ...&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&<?&??<...*/&&&&&&&&&&&&&%%%%??/. .......  ......*%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&<.&&&&&<<//%&&&&&&&&&&&&<******..................*/&&&&&&&&&&&&&&&&&&&&&&&000000%.//&00&<</%000&0000&0%  ........................../?&&&&&&&&&&0000000000&&00000?<<&0000&&&&000&000000&  ............................*%%<%&0&&000000000000<88888&*888888888880%%?&88888* . .......... .............**........<08888880888& *0000&*0&%&0&0000&%%?</?000/  ..... ...  ... .....................*%00000&<%%?0  &###0 %%&&0&&#8&%??%<<%&?.   .........        ...................*<8#80&&&?%0&  .</&?*?%%0&%%&?%?%%*..//     .....**.             ..................<&%0&%%%?%     **<***</?/?**/*.         ....... ..     .....    .................**</?/?**     .*<**.***</*<*... .     .....     .    ./****.    .............   *.***<**<..    */*. /**<<??.. .      .....       .   *//****.   ...........   ..  /**</??*      *   ..*?%<...      **...        ..  .***..***.   ...........        ./?<.       .      ..         .**.        .**.......... .*.   .  ........                   *        .     ....**    .****.**......***.***..  .. .......... ......          /        ..   .******   */////*....... .**.***. .   ...... ... ....******       ?       */*...**//**.  *////*. ....... ... .*..**.  ... .. ... . . .*****       /. ./* *//****///***/*.*//*..  ....... ....   *//. ...    .....      ****     . *<.*/.*///***//*//*///*... .   .........**/*...**          .....   . **/%    .*.<<*//////////*/////***  ..**.   .........*///*.**   ./.*<*.... .  ..***?*    .*?/*.////////*////***... .*///*. ..... .. ...***0..   .<**/****.....*****<<    ..*/<*////***/////**.**//***/**.......   . ..**//**.   ..<</**************/% *//.**/&*////*//////*  */////*..   ....**     .*/*//**.   <??%%?<///********./&////**/<</.//////*/*.   *///*.     .....//*.   ./?/**/*.  ./%<<<**************<8*/*.///***    ****./*.. .**..   .........***. ...//.**..  ./*?<.*...**...***<?<%... **/*........*..**//**.   .  .     .*.**.*.//*./..//.   </**********?***0##8?     */*.*..*..*/*/..**///*.....    .**/.**.. .. */.*<</.  ??/********<?&##M#80**.*.  .**/*...*//***.*.*//*..    .**////../*..   .*//?</../?/*********. /8@@@M**..<< ...*//.* **/*.**..*/////*****//////..//*.    .*.***<<***********.. /8MMMM#*.** ..*.. ..*   */*//**/////////////////*<&%<<<</*//******************. ?0MMM8/#......?&<.      ..**.**********0*****/</8*/*<?.....****...********/</   *&&@0*#@.........   .   .......*///////*//<&&0&<<<**.***.****.*****..*****/*.   ..8&?&MM...........   * .........**////*/<&00<?<<******./*/*/**<*<*/..**//<*   &<#?***MM..............  ...........***/*//?%<</</*********//***//*<*********/.&8M%*.<?#M .......*  .*   .............**?*/* */******/<**.?%/**.*<<<. **/*******&%*%88?&M .......*.. *    ..............**<*.*//******/**.</.....*...*******/* *0*0&M<*##  ... ....     *............... ***&/*<*********..**...    ..******. .<</0M@M@8M    . .......*./?.............. ...*  /.*</***********..*******..... ..*800MMMM@    .........../*...... ...  .....      *<<<***************/</.  .... .<*0MM#M#@      .............. ..        ...      *<</</************/*.<%  ..    .%@#&<MM*...    ............. ..        .....    .<?//<</************/<<*   .... .//*.%&.       .........**....... .      .... .  .<*//*/**********/****/*.   .. .* *MM0*";
	int arr[4800] = { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 3, 3, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 3, 3, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 7, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 3, 3, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 3, 3, 1, 9, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 7, 7, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 7, 7, 7, 7, 3, 3, 8, 1, 9, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 7, 7, 7, 7, 1, 7, 1, 1, 1, 7, 7, 7, 7, 7, 7, 10, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 1, 3, 3, 8, 8, 9, 1, 3, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 3, 3, 1, 1, 3, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 1, 1, 1, 1, 1, 7, 7, 7, 7, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 3, 8, 8, 1, 1, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 7, 7, 7, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 9, 1, 1, 3, 1, 7, 3, 3, 1, 1, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 9, 1, 1, 3, 3, 1, 1, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 7, 3, 3, 9, 2, 3, 9, 9, 2, 2, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 3, 3, 9, 8, 8, 3, 1, 3, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 10, 10, 2, 2, 2, 2, 3, 10, 4, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 3, 1, 1, 1, 3, 9, 8, 3, 1, 1, 1, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 10, 10, 10, 10, 10, 10, 10, 10, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 4, 0, 1, 3, 1, 7, 9, 9, 9, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 11, 11, 11, 11, 11, 11, 11, 11, 3, 3, 10, 10, 10, 10, 10, 10, 10, 10, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 7, 2, 7, 2, 10, 10, 10, 2, 2, 3, 3, 7, 2, 1, 1, 1, 1, 1, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 3, 11, 3, 3, 3, 4, 4, 4, 3, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 11, 11, 3, 3, 3, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 10, 10, 10, 10, 10, 10, 10, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 2, 11, 11, 11, 11, 11, 7, 12, 12, 4, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 3, 3, 3, 3, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 2, 7, 3, 11, 11, 11, 11, 7, 7, 7, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 12, 7, 11, 11, 11, 11, 11, 11, 11, 11, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 3, 3, 3, 3, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 11, 11, 11, 11, 11, 8, 4, 11, 11, 8, 11, 11, 11, 11, 11, 11, 11, 11, 8, 9, 9, 9, 3, 11, 11, 11, 11, 11, 3, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 10, 2, 7, 7, 7, 7, 7, 8, 11, 11, 11, 11, 11, 11, 8, 11, 11, 8, 3, 10, 3, 11, 11, 11, 11, 11, 4, 11, 11, 9, 11, 11, 11, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 2, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 4, 4, 4, 4, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 3, 11, 11, 11, 11, 11, 11, 3, 3, 3, 3, 11, 10, 10, 7, 8, 8, 8, 8, 4, 3, 9, 9, 9, 8, 3, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 7, 4, 4, 10, 10, 10, 10, 10, 10, 10, 10, 7, 4, 4, 4, 4, 4, 0, 0, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 3, 7, 8, 3, 10, 10, 10, 3, 3, 8, 3, 4, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 1, 3, 3, 2, 2, 2, 2, 10, 10, 10, 10, 10, 10, 7, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 3, 3, 9, 8, 9, 9, 9, 3, 9, 9, 10, 10, 10, 2, 10, 9, 9, 12, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 2, 2, 2, 0, 0, 0, 0, 2, 10, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 3, 1, 12, 9, 9, 3, 9, 9, 9, 9, 9, 9, 9, 9, 1, 7, 7, 2, 4, 2, 4, 0, 4, 10, 10, 10, 10, 10, 10, 2, 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 12, 12, 12, 12, 12, 4, 2, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 2, 1, 9, 3, 9, 9, 9, 9, 9, 9, 9, 3, 3, 10, 10, 10, 10, 3, 12, 9, 3, 10, 9, 3, 3, 9, 9, 9, 9, 1, 4, 4, 7, 4, 2, 0, 4, 4, 4, 10, 10, 10, 10, 10, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 4, 2, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 3, 10, 9, 3, 3, 9, 9, 9, 9, 3, 10, 10, 10, 10, 10, 10, 12, 2, 10, 10, 3, 3, 3, 3, 9, 3, 3, 2, 4, 2, 2, 4, 4, 4, 4, 12, 12, 10, 10, 10, 10, 2, 4, 4, 4, 4, 4, 4, 12, 4, 4, 4, 4, 4, 12, 4, 4, 12, 12, 12, 12, 4, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 2, 2, 2, 2, 3, 2, 3, 3, 3, 3, 3, 10, 10, 10, 10, 10, 10, 10, 4, 2, 10, 10, 10, 10, 10, 3, 3, 2, 4, 2, 4, 0, 4, 4, 4, 4, 4, 12, 12, 10, 10, 10, 2, 0, 4, 4, 4, 4, 4, 12, 4, 4, 10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 12, 12, 4, 2, 2, 10, 10, 10, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 4, 10, 10, 10, 10, 10, 10, 10, 4, 2, 10, 10, 10, 2, 2, 2, 2, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 12, 12, 4, 2, 4, 4, 4, 12, 12, 12, 12, 12, 12, 4, 10, 10, 10, 10, 10, 4, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 2, 10, 10, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 2, 2, 3, 3, 3, 3, 3, 3, 2, 4, 10, 10, 10, 10, 10, 10, 10, 12, 2, 10, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 12, 12, 12, 12, 12, 12, 4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 4, 10, 10, 10, 10, 10, 10, 2, 4, 12, 12, 12, 12, 12, 12, 4, 4, 4, 2, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 10, 10, 10, 10, 10, 10, 10, 14, 4, 10, 0, 4, 4, 2, 4, 12, 12, 12, 4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 4, 4, 12, 12, 12, 12, 12, 12, 12, 4, 10, 10, 10, 10, 10, 10, 10, 2, 4, 12, 4, 4, 4, 12, 4, 12, 12, 12, 4, 2, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 10, 10, 10, 10, 10, 2, 2, 12, 4, 10, 4, 12, 12, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 2, 10, 10, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 4, 12, 12, 12, 4, 4, 2, 10, 10, 10, 2, 10, 2, 10, 10, 10, 10, 10, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 10, 10, 10, 10, 10, 4, 2, 4, 12, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 4, 4, 0, 2, 10, 10, 10, 10, 10, 10, 10, 10, 4, 12, 12, 12, 12, 12, 4, 12, 12, 12, 4, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 10, 10, 10, 2, 2, 2, 3, 3, 3, 3, 3, 7, 10, 10, 10, 10, 10, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 4, 4, 12, 4, 4, 2, 10, 10, 10, 10, 10, 10, 10, 10, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 0, 0, 3, 3, 10, 7, 3, 3, 2, 2, 2, 2, 2, 10, 2, 2, 2, 3, 3, 3, 3, 3, 10, 10, 10, 10, 10, 4, 12, 12, 12, 12, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 12, 12, 12, 12, 12, 4, 4, 10, 10, 10, 10, 10, 10, 10, 10, 2, 4, 4, 4, 12, 12, 12, 8, 4, 12, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 2, 3, 3, 3, 3, 3, 3, 3, 3, 10, 10, 10, 2, 12, 12, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 10, 10, 10, 10, 10, 10, 2, 10, 10, 10, 4, 12, 12, 12, 12, 12, 4, 12, 4, 4, 0, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 10, 4, 12, 12, 4, 12, 12, 12, 7, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 4, 4, 10, 10, 10, 10, 7, 4, 4, 2, 2, 10, 10, 4, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 0, 3, 11, 3, 3, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 12, 12, 12, 12, 12, 12, 4, 4, 4, 4, 2, 10, 10, 10, 10, 4, 7, 12, 12, 12, 4, 10, 10, 7, 7, 7, 12, 12, 12, 12, 12, 12, 4, 4, 3, 3, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 8, 12, 12, 12, 4, 12, 12, 12, 12, 12, 12, 4, 4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 12, 12, 4, 12, 4, 4, 4, 12, 4, 2, 10, 10, 10, 2, 4, 12, 12, 12, 12, 4, 2, 10, 3, 3, 7, 12, 12, 12, 12, 12, 4, 4, 4, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 10, 10, 4, 10, 4, 12, 12, 12, 12, 4, 4, 4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 4, 4, 4, 4, 12, 4, 4, 4, 4, 4, 4, 12, 12, 12, 12, 12, 12, 4, 3, 3, 3, 4, 12, 12, 12, 12, 12, 12, 4, 0, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 8, 8, 8, 8, 3, 10, 10, 10, 10, 10, 4, 12, 12, 12, 12, 4, 4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 12, 4, 4, 4, 4, 4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 3, 2, 12, 12, 4, 12, 12, 12, 12, 4, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 8, 8, 8, 8, 8, 8, 8, 7, 7, 10, 7, 10, 10, 10, 10, 4, 4, 12, 12, 4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 4, 12, 12, 12, 4, 4, 4, 0, 4, 4, 4, 7, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 7, 8, 8, 8, 8, 8, 3, 7, 10, 3, 7, 3, 10, 10, 10, 10, 10, 7, 14, 4, 12, 4, 12, 12, 12, 12, 4, 12, 12, 12, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 12, 12, 12, 12, 4, 4, 4, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 7, 8, 15, 15, 15, 15, 8, 3, 10, 7, 3, 10, 10, 10, 10, 10, 10, 2, 10, 4, 4, 4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 7, 7, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 4, 4, 7, 8, 15, 8, 15, 8, 7, 8, 10, 3, 10, 10, 10, 10, 7, 7, 7, 4, 2, 4, 4, 2, 2, 4, 10, 10, 7, 7, 4, 4, 4, 4, 4, 4, 12, 12, 12, 12, 12, 8, 4, 12, 12, 12, 12, 12, 12, 7, 8, 7, 7, 3, 7, 7, 3, 3, 7, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 4, 4, 4, 8, 8, 8, 8, 7, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 0, 0, 4, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 12, 12, 12, 12, 12, 12, 12, 12, 8, 8, 8, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 7, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 8, 8, 7, 8, 8, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 4, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 12, 12, 12, 12, 12, 12, 8, 8, 8, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 3, 3, 3, 3, 7, 3, 3, 3, 7, 2, 3, 3, 3, 3, 3, 3, 10, 2, 2, 7, 7, 8, 7, 7, 7, 7, 8, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 4, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 4, 12, 12, 12, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 3, 3, 3, 3, 3, 3, 3, 2, 8, 8, 15, 7, 7, 10, 7, 7, 8, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 2, 4, 4, 4, 4, 4, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 4, 12, 4, 10, 3, 3, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 3, 3, 3, 3, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 10, 7, 7, 7, 7, 7, 8, 8, 7, 8, 15, 10, 10, 10, 10, 10, 10, 10, 10, 3, 10, 4, 4, 4, 4, 2, 2, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 4, 7, 4, 10, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 3, 1, 1, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 7, 4, 7, 8, 7, 8, 8, 15, 7, 7, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 2, 10, 4, 2, 2, 3, 4, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 7, 7, 7, 8, 15, 8, 15, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 3, 3, 3, 3, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 4, 4, 7, 2, 7, 8, 8, 8, 8, 15, 15, 15, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 2, 10, 10, 10, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 2, 2, 2, 2, 7, 4, 4, 4, 7, 7, 8, 8, 15, 8, 15, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 2, 2, 2, 2, 2, 4, 4, 4, 4, 7, 8, 8, 8, 7, 8, 15, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 3, 2, 2, 10, 2, 2, 7, 4, 4, 4, 7, 7, 7, 7, 7, 8, 4, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 10, 2, 2, 2, 7, 4, 4, 7, 4, 7, 8, 8, 8, 7 };

	for (int i = 0; i<letras.length(); i++){
		SetColor(arr[i]); Console::Write(Convert::ToChar(letras[i]));
	}
}
void Fondo04()
{
	string letras = "###8M@@@&M@@@&@@@@&@@@88@@@&M@@@&M@@@&@@@@&@@@#8@@@&M@@@&M@@@&@@@@&@@@#8@@@8@@@@###8@###&@###&####&###08###%@###&@###&####&###88###%@###&@###&####&###88###0#######8@###&@###&####&###08###%@###&@###&####&###88###%@###&@###&####&###88###0####&&&&#888%#888&8888&88800888%#888%#888&8888&88800888%#888%#888&8888&88800888&0000%%%?........................****...........***..***.....................***.????###8*....................../#888*.........0888%8888/...................8888?#######8*......................*8/88%.........&?&888<080...................0<088#######8*......................*&%<%?.........%%&<&&%%?%...................&%%?&####***/*......................*00<0?.........%&&%&00<0&...................&&<0&////@@@#*...?@@@@.....8@@@&<%%%<####*....&@@@# ....####<....?@@@@*%%%?&@@@&....*#######8*...%####.....####%&?%%?@###*....0###8 ...*@###<....%####<%?%%8###&....*#######8*...%####.....####&#%@@M@###*....0###8 ...*@###<....%####%#&@@M###&....*#######8*...%####.....####%&&<?8@###*....0###8 ...*@###<....%####<&&*&@###&....*####***/*...*   ......*    /<*<<.   .....*   . .....    .....    .**.**    ....*****@@@8*.....................................&###&0###?####<####<#### ........*@@@@###8*.....................................%??&%&<%&%&/&&%&/&&&&/&&*........*#######8*.....................................?<&%&&<&%&&<%%&&<%&&%?%&*........*####&&&&*.....................................8@#&@@@&8@@@%@@@@?@@@@?@<........*8008%%%?*.../&&&&.....%&&&?.****&&&&*....<&&&&.....&&&&/..../&&&&.****?&&&?....*<<<?###8*...%####.....####&8###%@###*....0###8 ...*@###<....%####%###80###&....*#######8*...%####.....####%0<08#@###*....0###8 ...*@###<....%####<0<88M###&....*#######8*...%####.....####%%?%?0@###*....0###8 ...*@###<....%####<&%/&@###&....*####***/*...<///<.....%///*&0?08<///.....?///< ....%///*....<///<<00?0&///*....*///<@@@8*.............*???*...........................................*???*/%%%/#######8*.............%%?%<...........................................%%?%<&?%%<#######8*.............8&#@@*..........................................0&#@@@%@@@#######8*.............%&&/&*..........................................%&&/&&&??0####***/*...*<<<<.....?&%??...../<<<*....*<<</...../<<<*....*<<<<.....?&%?%<<*<<****@@@8*...%@@@@.....#@@@&0###%M@@@*....0@@@# ...*M@@@<....?@@@@.....#@@@&....*@@@@###8*...%####.....####%&<%&&@###*....0###8 ...*@###<....%####.....####&....*#######8*...%####.....####%%<&&0@###*....0###8 ...*@###<....%####.....####&....*####&&&&*...%8888.....8888%#@&8M#888*....&8880 ...*#888<....%8888.....8888%....*8888????*....    ......    .....    ......    .....     .....    ......    ....*<<<<###8*......................................................................*#######8*......................................................................*#######8*......................................................................*####***/*......................................................................*<<<<###8*...?####.....8###&..../@###*....&###8.....####<....<####.....0###&....*8888###8*...%####.....####%..../@###*....0###8 ...*@###<....%####.....####&....*#######8*...%####.....####%..../@###*....0###8 ...*@###<....%####.....####&....*#######8*...%####.....####%..../@###*....0###8 ...*@###<....%####.....####&....*####***/*.../   ......*   .....*.   .....*     ....*    ....*   ......*    ....*****@@@#*................................?###8 ........*8###*.........%###%....*@@@@###8*................................?&<&&*........*&/&&<.........%??&%....*#######8*................................<%?&&*........*&<&&?.........?<&&&*...*####000&*................................%@@?@/........*@@?#&.........0@#%@*...*8888????*.../&&&&.****?&&&?....*&&&&*....<&&&&.....&&&&/...*/&&&&.....?&&&?....*<<<<###8*...%####%###80###%..../@###*....0###8 ...*@###<....%####.....####&....*#######8*...%####<&<00M###%..../@###*....0###8 ...*@###<....%####.....####&....*#######8*...%####/%%<&@###%..../@###*....0###8 ...*@###<....%####.....####&....*####///<*...?<<<?<88%80<<</..../?<<<*....%<<<< ...*&<<<*....?<<<<.....%<<</....*<<<?###8*....    ......    .....    ......    .....*<<<......    *????     ....*8888###8*..........................................&?%%*.........?%?%?.........*#######8*.........................................*#%@@#.........&#&@@<........*#######8*..........................................&&??%.........<&&*&*........*####88808888%8888%8880%888&&888&0888%8888%8880%888&@M@M#0888%88880MM@M&888&&8880@@@@###8M###&@###&####0###&####%M###&@###&####&###0####%M###&@###&####&###0####0###@###8@###&@###&####0###&####%@###&@###&####&###&####%M###&@###&####&###0####0###@###8@###&@###&####0###&####%@###&@###&####&###&####%M###&@###&####&###0####0###@<<<<#000&8008&0008&000&8000%#000&8008&0008&000&8000%#000&8008&0008&000&8000&???&";
	int arr[4800] = { 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 10, 2, 2, 2, 10, 10, 2, 2, 10, 10, 2, 2, 2, 10, 10, 2, 2, 2, 10, 10, 2, 2, 2, 2, 7, 7, 7, 7, 7, 10, 2, 2, 2, 10, 2, 2, 2, 10, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 10, 2, 2, 2, 10, 10, 2, 2, 2, 10, 2, 2, 2, 10, 10, 2, 2, 2, 10, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 7, 8, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 8, 8, 8, 7, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 8, 8, 8, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 7, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 7, 7, 8, 8, 8, 7, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 7, 8, 8, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 2, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 7, 7, 7, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 8, 7, 8, 8, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 7, 8, 7, 7, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 8, 8, 7, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 7, 2, 2, 2, 2, 10, 10, 10, 10, 10, 7, 2, 2, 2, 2, 7, 7, 7, 7, 7, 2, 2, 2, 2, 2, 10, 10, 10, 10, 7, 2, 2, 2, 2, 2, 10, 10, 10, 10, 2, 0, 0, 0, 2, 10, 10, 10, 10, 10, 0, 0, 0, 2, 2, 7, 7, 7, 7, 7, 2, 2, 2, 2, 10, 10, 10, 10, 10, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 8, 7, 8, 7, 7, 8, 7, 8, 7, 8, 8, 7, 8, 7, 8, 8, 7, 7, 7, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 7, 7, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 7, 8, 8, 8, 7, 10, 7, 7, 7, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 2, 10, 10, 2, 10, 7, 8, 7, 8, 7, 10, 10, 2, 10, 7, 8, 8, 7, 8, 7, 7, 7, 7, 7, 7, 8, 8, 8, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 8, 7, 8, 8, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 8, 7, 8, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 7, 7, 7, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 7, 7, 7, 7, 7, 2, 10, 10, 10, 10, 7, 7, 7, 7, 7, 8, 8, 7, 8, 8, 7, 7, 7, 7, 7, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 7, 7, 7, 7, 7, 7, 8, 8, 7, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 7, 7, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 7, 7, 8, 8, 8, 7, 7, 8, 8, 8, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 7, 7, 8, 7, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 10, 2, 2, 2, 2, 10, 10, 10, 10, 10, 10, 2, 2, 2, 2, 10, 10, 2, 10, 10, 2, 2, 2, 2, 10, 10, 10, 10, 10, 10, 2, 2, 2, 2, 10, 10, 10, 10, 10, 2, 2, 2, 2, 2, 10, 10, 10, 10, 10, 2, 2, 2, 2, 10, 10, 10, 10, 10, 10, 2, 2, 2, 2, 10, 10, 10, 10, 10, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 7, 2, 2, 2, 2, 10, 10, 10, 10, 10, 7, 2, 2, 2, 2, 10, 10, 10, 10, 10, 7, 2, 2, 2, 2, 10, 10, 10, 10, 7, 0, 0, 0, 2, 10, 10, 10, 10, 10, 7, 2, 2, 2, 2, 10, 10, 10, 10, 7, 2, 2, 2, 2, 10, 10, 10, 10, 10, 7, 0, 0, 2, 2, 10, 10, 10, 10, 10, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 7, 8, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 8, 7, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 7, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 7, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 7, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 2, 7, 7, 7, 7, 7, 8, 8, 8, 7, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 7, 7, 10, 10, 10, 10, 10, 7, 8, 8, 8, 7, 7, 7, 2, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 7, 8, 8, 7, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 8, 7, 8, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 7, 7, 7, 8, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 8, 8, 8, 8, 7, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 7, 7, 7, 7, 7, 7, 8, 8, 7, 8, 8, 7, 7, 7, 7, 10, 10, 10, 10, 7, 7, 7, 7, 7, 7, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 7, 7, 7, 7, 7, 2, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 7, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 7, 8, 7, 10, 10, 10, 10, 10, 10, 10, 10, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 15, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7 };

	for (int i = 0; i<letras.length(); i++){
		SetColor(arr[i]); Console::Write(Convert::ToChar(letras[i]));
	}
}
void Fondo05()
{
	string letras = "*************   ....*****?0888888888&??????%&8888888880<****....  .*************************    ...****/&888888880<***********<088888888%/***....  .***********************.   ...****<0888888888***************088888888&/***....  .*********************.   ....***?88888888880***************&8888888880<***...   ********************.   ....***?88888800888&***************&88888888888<***...  .*******************    ...***?88888%**/0880***************&888?*/&88888<**...   ..****************.   ...***<88880<****/888***************088?****<88888<**...   .****************   ...***<88880*******&88?*************<880******/08880/**...  .***************.   ...***0888&********<880*************088?*******/08880**...   .**************   ...***&8880**********888&*****..****%888/********/8888%**...   *************.   ...**<8888/**********08880%%%%%%??%&8888**********<8888<**..   .************   ...***0888%***********0888888888888888888***********&8880/**..   ***********.   ..***%8880***********/8888888888888888888************0888%**...  ***********   ...**/8888<***********&8888888888888888888<***********<8880/**..  .*********.   ..***%8880***********%888888888888888888880************0888%**...  *********    ..***8888?**********%8888888880008888888888&***********?8880*/*..  .********   ...**?8888<*********?88888880?.     .%8888888&***********8888?***..  *******.   ..***08888&********<8888880<           ?088888?*********/88880***... .******.   ..**<888888?******/888888&.             .&88888<********&88888<***.. .******   ...**?8888888%*****088888%                 &88880/******%888888%/**....******   ..***&888888888&%%088888&                   &88880/***%088888880/**....*****.   ..**/8888888888888888880       ..***.        088888&&88888888888<***...*****.   ..**<8888%?<&8888888888*     .*********      *888888888888888888?/**...*****.  ..***%888%****/&88888880     .***********.     %88888888&/.**&888&/***..*****   ..***&888<******%888888*    .*************     *8888880/.***./8880/***..*****   ..***0880********088880     ***************     088880*******.8888/***..*****   ..***888&********%8888?    .***************.    /8888<*******.&888</**..*****   ..**/888?********?8888*    *****************    .8888/********?888?/**..*****   ..**<888<********<8888.    *****************     8888*********<888?/**...***.   ..**<888<********<8888    .*****************.    0888*********<888%/**...***.   ..**<888<********<8888    .*****************.    &888*********/888%/***..***.   ..**<888<********<8880    .*****************.    %888*********/888%/***..***.   ..**<888<********<8888    .*****************.    &888*********/888%/***..***.   ..**<888?********<8888    .*****************.    &888*********/888%/***..***.   ..**<888?********<8888.    *****************     0880*********<888%/***..****   ..**/888%********<8888*    *****************     8880.********<888%/***..****   ..***888&********<8888%    .***************.    /8888*********%888?/***..****   ..***0888********088880     ***************     ?8888<.*******&888</***..****   ..***&888<******&888888*    .*************.    .888880*.******0888</***..****.  ..***%888&*..*?08888888&     .************     <8888888%*.***<8880//**..*****.   .***<88880&&88888888888/     .*********.      8888888888%/<<0888&//**..******   ..**/888888888888&888888       .******       &888888888888888888%//**..******   ..***&88888888&<***%8888&                   <8880<**/%8888888888?//**..******   ..**/%8888880/******?8888%                 /8880/******%88888880</***..******.  ..***<888880********.<8888%.              <8880/********<888888&</***.*******.   ..**/08888?*********.?88880*           *&8888<**********%88888?//**..********   ..**/?8888/**********.%88888&<.      *%88888?************88880</***..********   ..**//8888?************&88888880&%&08888888%************/8888%</***..********.   ..**/%8880*************088888888888888888&*************?8888<//***.**********   ..**//8888<************%88888888888888888?*************8888&</***..**********.  ..***/%8880************?88888888888888888<************?8880<//***.************   ..**//0888%.**********?888&/***..**/&888?***********/8888%</***..************.  ..***/?8888/.*********&88&*********.*&88&***********08880<//***.**********.***   ..**//&8880**********888/***********/880**********&8888?//***..***********.**.  ..***/<08880/*******?88&*************088<********%8888&</****.****************   ..**//<88880/******088<*************<88&*******%88880<//***..****************.  ...***/%88888<***.<888***************888<*****%88880<//***..*****************.   ...**//%88888%**<8880***************0880***/088880?</****.*******************.   ..***//%888880&8888&**************.&8880?&888880?<//***..********************   ...***//%88888888880**************.&88888888880?<//***..***********";
	int arr[4800] = { 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 3, 3, 3, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 7, 7, 7, 7, 7, 7, 7, 7, 1, 0, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 0, 4, 4, 5, 7, 7, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 7, 1, 0, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 7, 1, 0, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 1, 1, 0, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 11, 9, 9, 9, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 9, 9, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 1, 1, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 4, 4, 7, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 1, 1, 0, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 1, 1, 0, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 5, 7, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 7, 7, 7, 7, 1, 1, 0, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 0, 4, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 7, 7, 7, 7, 1, 1, 0, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 0, 4, 5, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 7, 7, 7, 7, 7, 1, 1, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 0, 4, 7, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 1, 0, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 5, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 7, 7, 7, 7, 7, 1, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 0, 4, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 7, 7, 7, 7, 7, 1, 0, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 0, 5, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 7, 7, 7, 7, 7, 1, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 0, 0, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 11, 7, 7, 7, 7, 7, 1, 0, 4, 12, 12, 12, 12, 12, 12, 12, 12, 4, 0, 4, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 11, 11, 11, 11, 11, 3, 3, 1, 1, 1, 1, 1, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 7, 7, 7, 7, 7, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 3, 11, 11, 11, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 12, 12, 12, 4, 0, 0, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 4, 4, 12, 12, 12, 12, 12, 12, 4, 0, 0, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 3, 7, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 12, 12, 4, 0, 0, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 12, 12, 4, 0, 1, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 1, 1, 0, 0, 0, 0, 0, 1, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 12, 4, 0, 0, 1, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 3, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 12, 4, 0, 0, 5, 7, 7, 7, 7, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 1, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 4, 12, 12, 12, 12, 12, 4, 4, 0, 7, 7, 7, 7, 7, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 3, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 3, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 7, 7, 7, 7, 7, 4, 12, 12, 12, 12, 12, 4, 0, 0, 7, 7, 7, 7, 7, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 1, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 7, 7, 7, 7, 7, 4, 12, 12, 12, 12, 12, 4, 0, 4, 7, 7, 7, 7, 7, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 3, 1, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 1, 3, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 4, 0, 5, 7, 7, 7, 7, 3, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 11, 3, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 4, 0, 5, 7, 7, 7, 7, 3, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 1, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 3, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 0, 0, 5, 7, 7, 7, 7, 3, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 1, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 1, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 0, 0, 5, 7, 7, 7, 7, 3, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 1, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 1, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 0, 0, 5, 7, 7, 7, 7, 3, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 1, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 1, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 0, 0, 5, 7, 7, 7, 7, 3, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 1, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 1, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 0, 4, 5, 7, 7, 7, 7, 3, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 1, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 1, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 4, 0, 5, 7, 7, 7, 7, 3, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 1, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 4, 0, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 3, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 0, 0, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 1, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 4, 0, 4, 7, 7, 7, 7, 7, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 1, 3, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 4, 0, 4, 5, 7, 7, 7, 7, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 3, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 3, 11, 11, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 4, 0, 4, 5, 7, 7, 7, 7, 3, 11, 11, 11, 11, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 3, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 7, 7, 7, 7, 7, 4, 12, 12, 12, 12, 12, 12, 4, 4, 5, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 1, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 9, 3, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 4, 12, 12, 12, 12, 12, 12, 4, 4, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 1, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 12, 12, 4, 4, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 3, 11, 11, 11, 11, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 12, 12, 4, 0, 4, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 11, 11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 12, 12, 4, 0, 4, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 11, 11, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 12, 12, 12, 0, 4, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 11, 11, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 3, 3, 1, 1, 1, 1, 1, 1, 3, 11, 11, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 4, 5, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 5, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 7, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 3, 7, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 5, 7, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 5, 7, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 3, 7, 7, 7, 7, 7, 7, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 7, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 3, 9, 9, 9, 9, 3, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 7, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 11, 9, 9, 3, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 7, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 4, 5, 7, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 3, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 7, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 4, 5, 5, 7, 7, 7, 7, 7, 7, 3, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 7, 7, 7, 7, 7, 7, 7, 5, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12 };

	for (int i = 0; i<letras.length(); i++){
		SetColor(arr[i]); Console::Write(Convert::ToChar(letras[i]));
	}
}
void mapa01(int **matriz){
	int matrizint[60][80] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 9, 9, 6, 6, 6, 6, 6, 6, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 9, 9, 9, 9, 6, 6, 6, 6, 6, 6, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 14, 14, 14, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c;

	for (f = 0; f < 60; f++)
		for (c = 0; c < 80; c++)
			matriz[f][c] = matrizint[f][c];
}
void mapa02(int **matriz)
{
	int matrizint[60][80] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 9, 9, 1, 1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 1, 1, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 9, 9, 1, 1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 1, 1, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c;

	for (f = 0; f < 60; f++)
		for (c = 0; c < 80; c++)
			matriz[f][c] = matrizint[f][c];
}
void mapa03(int **matriz){
	int matrizint[60][80] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 5, 5, 5, 5, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 5, 5, 5, 5, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 9, 9, 12, 12, 9, 9, 9, 9, 5, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 9, 9, 12, 12, 9, 9, 9, 9, 5, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 5, 5, 12, 12, 12, 12, 7, 7, 1, 1, 1, 1, 1, 1, 12, 12, 12, 12, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 5, 5, 12, 12, 12, 12, 7, 7, 1, 1, 1, 1, 1, 1, 12, 12, 12, 12, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 5, 5, 12, 12, 7, 7, 1, 1, 1, 1, 9, 9, 9, 9, 7, 7, 9, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 5, 5, 12, 12, 7, 7, 1, 1, 1, 1, 9, 9, 9, 9, 7, 7, 9, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 5, 5, 9, 9, 12, 12, 7, 7, 1, 1, 1, 1, 9, 9, 9, 9, 7, 7, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 5, 5, 9, 9, 12, 12, 7, 7, 1, 1, 1, 1, 9, 9, 9, 9, 7, 7, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 9, 9, 12, 12, 7, 7, 7, 7, 1, 1, 1, 1, 1, 1, 7, 7, 1, 1, 7, 7, 9, 9, 5, 5, 5, 5, 9, 9, 12, 12, 5, 5, 5, 5, 5, 5, 9, 9, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 9, 9, 12, 12, 7, 7, 7, 7, 1, 1, 1, 1, 1, 1, 7, 7, 1, 1, 7, 7, 9, 9, 5, 5, 5, 5, 9, 9, 12, 12, 5, 5, 5, 5, 5, 5, 9, 9, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 9, 9, 12, 12, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 9, 9, 12, 12, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 7, 7, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 7, 7, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 5, 5, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 5, 5, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 5, 5, 5, 5, 5, 5, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 5, 5, 5, 5, 5, 5, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 12, 12, 12, 12, 12, 12, 12, 12, 5, 5, 5, 5, 5, 5, 5, 5, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 12, 12, 12, 12, 12, 12, 12, 12, 5, 5, 5, 5, 5, 5, 5, 5, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c;

	for (f = 0; f < 60; f++)
		for (c = 0; c < 80; c++)
			matriz[f][c] = matrizint[f][c];
}
void mapa04(int **matriz){
	int matrizint[60][80] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 1, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 1, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 15, 15, 7, 7, 1, 1, 7, 7, 7, 7, 7, 7, 1, 1, 7, 7, 15, 15, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 15, 15, 7, 7, 1, 1, 7, 7, 7, 7, 7, 7, 1, 1, 7, 7, 15, 15, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 15, 15, 7, 7, 1, 1, 7, 7, 7, 7, 7, 7, 1, 1, 7, 7, 15, 15, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 15, 15, 7, 7, 1, 1, 7, 7, 7, 7, 7, 7, 1, 1, 7, 7, 15, 15, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 15, 15, 7, 7, 1, 1, 7, 7, 7, 7, 7, 7, 1, 1, 7, 7, 15, 15, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 15, 15, 7, 7, 1, 1, 7, 7, 7, 7, 7, 7, 1, 1, 7, 7, 15, 15, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 1, 1, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 1, 1, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 1, 1, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 1, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 1, 1, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 1, 1, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1, 1, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 1, 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 15, 15, 15, 15, 15, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 15, 15, 15, 15, 15, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 5, 5, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 9, 9, 6, 6, 6, 6, 6, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c; for (f = 0; f <60; f++)for (c = 0; c <80; c++)matriz[f][c] = matrizint[f][c];
}
void mapa05(int **matriz){
	int matrizint[60][80] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 7, 7, 9, 9, 9, 9, 9, 9, 7, 7, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 7, 7, 9, 9, 9, 9, 9, 9, 7, 7, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 9, 9, 7, 7, 7, 7, 7, 7, 9, 9, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 9, 9, 2, 2, 7, 7, 7, 7, 2, 2, 7, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 2, 2, 7, 7, 7, 7, 2, 2, 9, 9, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 9, 9, 2, 2, 7, 7, 7, 7, 2, 2, 7, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 2, 2, 7, 7, 7, 7, 2, 2, 9, 9, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 7, 7, 7, 7, 7, 7, 9, 9, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 9, 9, 0, 0, 9, 9, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 9, 9, 0, 0, 9, 9, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int f, c;

	for (f = 0; f < 60; f++)
		for (c = 0; c < 80; c++)
			matriz[f][c] = matrizint[f][c];
}
void dibuja_mapa(int **matriz)
{
	int f, c;
	for (f = 0; f < 60; f++){
		for (c = 0; c < 80; c++)
		{
			ir(c, f); if (matriz[f][c] != 0){ colorletra(matriz[f][c]); cout << char(219); }
		}
	}
}
//--------------------------------------------------------------------------------------------------

/*------------------------------------CONTROL DEL JUEGO-------------------------------------------------*/
void ColocarEscenario(int nivel, int **matriz)
{
	if (nivel == 1){ ir(0, 0); Fondo01(); mapa01(matriz); dibuja_mapa(matriz); }
	if (nivel == 2){ ir(0, 0); Fondo02(); mapa02(matriz); dibuja_mapa(matriz); }
	if (nivel == 3){ ir(0, 0); Fondo03(); mapa03(matriz); dibuja_mapa(matriz); }
	if (nivel == 4){ ir(0, 0); Fondo04(); mapa04(matriz); dibuja_mapa(matriz); }
	if (nivel == 5){ ir(0, 0); Fondo05(); mapa05(matriz); dibuja_mapa(matriz); }

}
void ControlDeMovimiento(int &nivel, int &vidas, int x, int y, int ***Cajas, int ***Paredes, int ***Vacios, int ***Huecos, int **Cantidades, int **Posiciones, int **matriz, bool &sonido)
{
	int xportal; int yportal;//coordenadas del portal
	int xp, yp;//Variables de apoyo para utilizar PBorrar

	if (nivel == 1){ xportal = 36; yportal = 34; }
	if (nivel == 2){ xportal = 42; yportal = 18; }
	if (nivel == 3){ xportal = 36; yportal = 28; }
	if (nivel == 4){ xportal = 38; yportal = 12; }
	if (nivel == 5) { xportal = 40; yportal = 6; }

	int caso = 0;//Esta variable sirve para que, cuando el portal aparezca, solo suene la primera vez, Y tambien para que el portal desaparezca(despues de que haya aparecido),
	//cuando se mueva una caja. 

	int cantmovs = 0;//cantidad de movientos

	int opcionmenu;//opcion de menu

	int posicion = 1;

	CuadroDeVidas(nivel, vidas, cantmovs, 1);//poner la barra de vida
	char teclac = 20;
	bool sigue;
	bool si = true, no = false;
	sigue = si;

	while (sigue){

		int mov;//Variable importante que se usa en todo el programa, que asigna un valor a cada uno de los cuatro posibles movimientos

		int caja;//Esta variable es asignada por la funcion QueCaja, que retorna la caja con la cual el movil esta interactuando

		Posiciones[0][0] = posicion;

		char tecla;//Sera usada para captar las teclas de movimiento WASD o la de pausa P.

		//Entramos a esta condicional, cuando se presiona una tecla, sino el bucle while se sige ejecutando muchas veces, por eso es necesario un Sleep
		if (teclac != 10){
			limpiartecla(2);
			tecla = _getch();
		}//El valor de _getch() es la ultima tecla presionada, y este es asignada a nuestro valor "tecla"
		else teclac = 20;
		tecla = toupper(tecla);

		switch (tecla){

		case 'C': {teclac = _getch();
			if (teclac == 'c' || teclac == 'C'){ teclac = _getch(); if (teclac == 'c' || teclac == 'C'){ nivel++; sigue = no; } else { tecla = teclac; teclac = 10; } }
			else { tecla = teclac; teclac = 10; }continue; break; }//SOLO USO TECNICO, sirve para pasar de nivel a nivel

		case 'K': {teclac = _getch();
			if (teclac == 'k' || teclac == 'K'){ teclac = _getch(); if (teclac == 'k' || teclac == 'K'){ SonidoTroll(1); TeclasOcultas(x, y); } else { tecla = teclac; teclac = 10; } }
			else { tecla = teclac; teclac = 10; }continue; break; }

		case 'X': {teclac = _getch();
			if (teclac == 'x' || teclac == 'X'){ teclac = _getch(); if (teclac == 'x' || teclac == 'X'){ SonidoTroll(2); TeclasOcultas(x, y); } else { tecla = teclac; teclac = 10; } }
			else { tecla = teclac; teclac = 10; }continue; break; }

		case 'H': {teclac = _getch();
			if (teclac == 'h' || teclac == 'H'){ teclac = _getch(); if (teclac == 'h' || teclac == 'H'){ SonidoTroll(3); TeclasOcultas(x, y); } else { tecla = teclac; teclac = 10; } }
			else { tecla = teclac; teclac = 10; }continue; break; }

		case 'M': {teclac = _getch();
			if (teclac == 'm' || teclac == 'M'){ teclac = _getch(); if (teclac == 'm' || teclac == 'M'){ SonidoTroll(4); TeclasOcultas(x, y); } else { tecla = teclac; teclac = 10; } }
			else { tecla = teclac; teclac = 10; }continue; break; }

		case 'F': {if (sonido == 0)sonido = 1; else sonido = 0; continue; break; }

		case 'R':
			if (posicion != 1){
				Regresar(nivel, posicion, x, y, mov, Cajas, Vacios, Huecos, Cantidades, Posiciones, matriz);
				cantmovs += 3; CuadroDeVidas(nivel, vidas, cantmovs);
			}
			else{ Musicatiempo(2); }continue; break;

		case 'P': {//Con esta tecla entramos al modo pausa

			InterfazPausa(matriz, opcionmenu, sonido);//Se pone el dialogo de pausa
			if (opcionmenu == 1){
				ColocarEscenario(nivel, matriz); PonerCajas(nivel, Cajas, Cantidades);//Si se escoge continuar, nada cambia,
				PonerHuecos(nivel, Huecos, Cajas, Cantidades); PonerPuentes(nivel, Vacios, Cantidades); PintarMovil(nivel, x, y); CuadroDeVidas(nivel, vidas, cantmovs, 1);
				if (PortalVisible(nivel, Cajas, Huecos, Cantidades))PintarPortal(nivel, -1, -1);
				continue;
			}//Se coloca todo de nuevo

			if (opcionmenu == 2){ InterfazYouLose(matriz); vidas--; sigue = no; continue; }//Si se escoge reset, aparece la interfaz youlose y se pierde una vida
			if (opcionmenu == 3){ nivel = 7; sigue = no; continue; }//si se escoge exit, se sale del controlador de movimientos, pero con nivel=7
			break; }//fin opciones menu

		case 'W': mov = 1; break;//↑
		case 'S': mov = 2; break;//↓
		case 'D': mov = 3; break;//→
		case 'A': mov = 4; break;//←
		default: continue;
		}

		//El movimiento del movil, se divide en dos grandes opciones o posibilidades: La primera es cuando el movil no choca ninguna caja, y la seguna cuando si lo hace.

		xp = x; yp = y;

		if (!MovilyCaja(nivel, x, y, mov, Cajas, Cantidades)){//-La PRIMERA POSIBILIDAD DE MOVIMIENTO, es básicamente cuando la siguiente zona del móvil será una normal

			if (MovilDentroDeMapa(nivel, x, y, mov, Paredes, Cantidades)){
				GuardarPosicion(posicion, 1, x, y, mov, -1, Cajas, Posiciones);; movi(x, y, mov); cantmovs++; if (sonido)SonidoMovilSeMueve(1);
				//Se borra la antigua posicion del móvil
				//Es importante borrar las antiguas coordenadas del movil en este punto, de lo contrario, eventualmente se modificaran y no se podran borrar
			}//Antes de darle sus nuevas coordenadas
			// al movil hay que verificar si este choca con una pared. Si se puede mover se le modifica las coordenadas.
			else//se llega a esta parte del codigo si el movil choco con una pared(solo para sonido)
			{
				if (sonido)SonidoMovilNoSeMueve(); continue;
			}//sonido cuando el movil no se mueve

		}//termina la Primera Posibilidad de Movimiento

		else if (MovilyCaja(nivel, x, y, mov, Cajas, Cantidades)){//-La SEGUNDA POSIBILIDAD DE MOVIMIENTO de la caja es cuando choca con una caja
			caja = QueCaja(nivel, x, y, mov, Cajas, Cantidades);//-Primero hay que saber con que caja esta interactuando el movil, por eso almacenamos el numero de la caja en la variable 'caja'
			//-Muchos procesos se del primero movimiento se iran repitendo, porque estamos en un else, y cuando se llega aca, es porque no se ejecuto el if

			if (CajaLugarPermitido(nivel, mov, Cajas, caja, Paredes, Cantidades)){//Este bool, nos dice si la caja empujada se puede mover, y por ende si el móvil tambien lo puede hacer
				//-En todos los niveles trabajamos con objetos de 2*2 pixeles, por lo tanto el movil también se moverá 2 pixeles.
				//-OJO: Modficar las coordenadas solo implica cambiarlas, esto no signifca que el movil se moverá. De eso se encarga la funcion PintarMovil

				if (CajayVacio(nivel, Cajas[nivel][caja], mov, Vacios, Cantidades)){
					GuardarPosicion(posicion, 3, x, y, mov, caja, Cajas, Posiciones);
					mod(Cajas[nivel][caja], mov); movi(x, y, mov); cantmovs++;
					CrearPuente(nivel, mov, Cajas, Vacios, caja, Cantidades);
				}//Esta posibilidad esta dentro de CajaLugarPermitido, pero se pone afuera
				//para mantener cierta noción de orden
				//-Cuando se llege a este punto, se borrara de las matrices tanto la caja como el vacio que colisionaron.                      

				else if (!CajayVacio(nivel, Cajas[nivel][caja], mov, Vacios, Cantidades)){

					if (nivel != 5){
						GuardarPosicion(posicion, 2, x, y, mov, caja, Cajas, Posiciones); mod(Cajas[nivel][caja], mov); movi(x, y, mov); cantmovs++;
						if (CajayHueco(nivel, caja, Cajas, Huecos, Cantidades))SonidoCajaHueco(); else if (sonido)SonidoMovilSeMueve(2);
					}
					//Para todos los niveles hasta el 4, llegado a este punto, el móvil se moverá

					if (nivel == 5){//*Caso excepcional en nivel 5
						if (!PortalVisible(nivel, Cajas, Huecos, Cantidades)){
							GuardarPosicion(posicion, 2, x, y, mov, caja, Cajas, Posiciones);
							mod(Cajas[nivel][caja], mov); movi(x, y, mov); cantmovs++;
							if (CajayHueco(nivel, caja, Cajas, Huecos, Cantidades))SonidoCajaHueco(); else if (sonido)SonidoMovilSeMueve(2);
						}
						//Aca es donde se modican las coorenadas
						//tanto del movil como de la caja
						//Si es que el portal no está activo, cuaquier caja puede moverse
						else if (PortalVisible(nivel, Cajas, Huecos, Cantidades)){
							if (caja<10){
								GuardarPosicion(posicion, 2, x, y, mov, caja, Cajas, Posiciones);
								mod(Cajas[nivel][caja], mov); movi(x, y, mov); cantmovs++;
								if (CajayHueco(nivel, caja, Cajas, Huecos, Cantidades))SonidoCajaHueco(); else if (sonido)SonidoMovilSeMueve(2);
							}
							else { SonidoMovilNoSeMueve(); continue; }
						}
						//Si es que el portal ya está activo, solo se pueden mover las cajas celestes, las negras(que tienen numero del 10 al 16) no se moverán    	
					}//fin caso excepcional nivel 5 

				}//fin segundasubposiblidad

			}//Fin if Cajalugarpermitido

			else if (!CajaLugarPermitido(nivel, mov, Cajas, caja, Paredes, Cantidades))//Se pone el else para poner un sonido de bloqueo
			{
				if (sonido)SonidoMovilNoSeMueve(); continue;
			}//Sonido de cuando el movil no se mueve

		}//termina la Segunda Posibilidad de Movimiento

		//Esta segunda parte de Control de Movimiento contiene  todas las restricciones respecto al portal, y también sera acá donde se use el PintarMovil

		if (nivel != 5){//siempre separamos el nivel 5 del resto pooque tienen varias diferencias

			PonerCajas(nivel, Cajas, Cantidades);//Ya que alguna caja cambio de lugar, se vuelven a colocar
			PBorrar(nivel, xp, yp);
			PintarMovil(nivel, x, y);//Luego se coloca al movil en sus nuevas coordendas
			if (PortalVisible(nivel, Cajas, Huecos, Cantidades)){
				if (caso == 0){ PortalInteractivo(nivel, -1, -1, 1); caso = 2; }
				//Cuando aparece el portal,se ejecuta un sonido, luego la variable caso cambia de valor para que de esta manera no se siga reproduciendo
				PintarPortal(nivel, -1, -1);//Finalmente se pone el portal

				if (x == xportal&&y == yportal){ Teletransporte(nivel, xportal, yportal); InterfazYouWin(matriz); nivel++; sigue = no; continue; }
				//Si el movil coincide con las coordenadas del portal, mientras este esta visible, Aparece la interfas You Win
				// El nivel aumenta en uno y se sale del control de movimientos

			}//fin PortalVisible

			else if (!PortalVisible(nivel, Cajas, Huecos, Cantidades)){//Esta parte del código se ejecuta cuando el nivel es menor a 4 y el portal no es visible
				if (nivel == 1)PBorrar(1, xportal, yportal, 6); if (nivel == 3)PBorrar(3, xportal, yportal, 5);//Se utiliza la funcion adicional de PBorrar, para borrar el portal.
				//El portal no debe ser visible, mientras que todos los huecos no esten llenos. Por eso es necesario esta función para borrar el portal, despues de que se activó, cuando se mueve
				//una caja.
				//Esto solo es para el nivel 1 y 3( el 5 más abajo), pues solo en estos niveles se puede mover la caja despues de dejaralas en su sitio.
				PonerCajas(nivel, Cajas, Cantidades); PBorrar(nivel, xp, yp); PonerHuecos(nivel, Huecos, Cajas, Cantidades); PintarMovil(nivel, x, y);
				//Finalmente, como parte del código en general se Colocan los Huecos, las Cajas, el movil
				if (caso == 2){ PortalInteractivo(nivel, -1, -1, 2); }
				caso = 0; //El caso regresa a cero para que cuando se vuelva a activar el portal suene una vez de nuevo
			}//Fin !PortalVisible

		}//Fin nivel!=5

		if (nivel == 5){//Solo cuando el nivel es 5

			if (PortalVisible(nivel, Cajas, Huecos, Cantidades)){//Cuando el portal es visible
				PonerCajas(nivel, Cajas, Cantidades); PBorrar(nivel, xp, yp); PintarMovil(5, x, y);
				if (x == xportal&&y == yportal){ Teletransporte(nivel, xportal, yportal); nivel = 6; sigue = no; continue; }
				//Si se pasa el nivel 5, no se muestra la interfaz You Win, si no defrente la Congratulations
				if (caso == 0){ Endurecimiento(x, y, mov, Cajas); PortalInteractivo(nivel, -1, -1, 1); AgregarParedes(Cajas, Paredes, Cantidades); caso = 2; }PintarPortal(nivel, -1, -1);
			}
			//Como en el anterior caso, respecto al sonido, las paredes solo se endurecen la primera vez

			//Se colocan Los elemntos(ES MUY IMPORTANTE EL ORDEN)

			else if (!PortalVisible(nivel, Cajas, Huecos, Cantidades)){//Cuando el portal no es visible
				PBorrar(5, xportal, yportal, 2);
				PonerCajas(nivel, Cajas, Cantidades); if (MovilyHueco(nivel, xp, yp, mov, Huecos, Cantidades))PintarHueco(nivel, xp, yp);
				else PBorrar(nivel, xp, yp); PintarMovil(5, x, y);
				if (caso == 2)PortalInteractivo(nivel, -1, -1, 2);
				caso = 0;
			}//Se borra el portal y se habilita la opción de que suene denuevo, la próxima vez que se active


			//A diferencia de PortalVisible acá si se Colocan los Huecos, porque en PortalVisible y no es necesario y causa una especie de parpadeo
		}//Fin if nivel==5

		CuadroDeVidas(nivel, vidas, cantmovs);//En este punto se vuelve a imprimir el CuadrodeVidas(Recordando que este se imprime fuera del while)
		if (muerte(nivel, x, y, mov, cantmovs, Vacios, Cantidades)){
			PintarMuerte(x, y); if (vidas != 1)InterfazYouLose(matriz); vidas--;
			if (vidas == 0)nivel = 7; sigue = no; continue;
		}//Si se llega a 0 vidas inmediatamente(por eso esta al principio) se sale del nivel y se va a la interfaz Game Over.

		//se activa la animación Pintarmuerte, Y se activala IntefazyouLose si es que tiene mas de 1 vida. En el caso de que solo le hubiera quedado una(Antes de que le quiten esa) se activa
		//defrente la Interfaz GameOver


	}//fin while
}
void ControlDeNiveles(int **matriz, int &nivel, int***Cajas, int***Paredes, int***Vacios, int ***Huecos, int **Cantidades, int **Posiciones)
{
	int vidas; int empezarconmusica = 0;

	bool sonido = 1;//Decide si el juego tendra sonido de movimientos o no

	while (nivel != 9){
		if (nivel == 0){ MenuPrincipal(nivel, matriz, empezarconmusica); vidas = 5; }//MENU

		if (nivel <= 5 && nivel >= 1){//NIVELES DE JUEGO
			int xinicio, yinicio;//Coordenadas de inicio del movil
			if (nivel == 1){ xinicio = 36; yinicio = 34; }
			if (nivel == 2){ xinicio = 42; yinicio = 40; }
			if (nivel == 3){ xinicio = 48; yinicio = 22; }
			if (nivel == 4){ xinicio = 38; yinicio = 12; }
			if (nivel == 5){ xinicio = 40; yinicio = 40; }

			Lore(nivel);//Se muetra el Lore del nivel

			ColocarEscenario(nivel, matriz);//Pone el escenario del nivel
			RestaurarTodo(nivel, Cajas, Paredes, Vacios, Huecos, Cantidades);//Regresa las coordenadas de todo a sus valores iniciales

			PonerCajas(nivel, Cajas, Cantidades); PonerHuecos(nivel, Huecos, Cajas, Cantidades);//Se pintas la cajas y los huecos
			PintarMovil(nivel, xinicio, yinicio);//Se pinta el movil

			ControlDeMovimiento(nivel, vidas, xinicio, yinicio, Cajas, Paredes, Vacios, Huecos, Cantidades, Posiciones, matriz, sonido);//Empieza el control de movimiento
		}//FIN NIVELES DE JUEGO

		if (nivel == 6){ InterfazCongratulations(matriz, Cantidades); nivel = 8; }// Muesta la interfaz de congratulation
		if (nivel == 7){ InterfazGameOver(matriz); nivel = 0; empezarconmusica = 1; }//Muesta la interfaz de GAME OVER
		if (nivel == 8){ InterfazCreditos(matriz); nivel = 0; }//Muestra la interfaz de los creditos
		if (nivel == 9)break;//Se sale del control de niveles, con lo cual del juego	

	}//fin while
}
/*------------------------------------------------------------------------------------------------------*/

void DescripcionDelPrograma(){/*//=====================================NOTAS INCIALES===========================================//
							  -Primeros nombres del juego:
							  -Nombre del equipo:
							  -Integrantes:

							  Introduccion: '             ' es un juego basado en SilverSphere, y consiste en desplazar cajas hacia lugares especificos, lo cual abrira un portal, para pasar de nivel.
							  La programacion de este juego esta orientado a una mecanica repleta de uso de funciones,el uso de matrices, y tambien al uso de condiciones de verdad(bool);
							  una especie de emulacion a la programacion OOP(Programacion Orientada a Objetos).
							  El juego tiene por tematica usar personajes,ya sean de consolas antiguas o de comics, como mapa del juego, con estilo retro-gamer..

							  -------------------------------------------------------------MODO DE JUEGO "SILVER SPHERE"--------------------------------------------------------------------------------
							  Jugabilidad: Conceptos Basicos: *Movil: Es el personaje del juego, sera lo que el jugador pueda mover
							  *Vidas: Se le atribuye al movil.Es la cantidad de intentos que te quedan.
							  *Muerte: Se le atribuye al movil.Pierdes una vida
							  *Zonas: Son lugares estaticos del juego, que de alguna manera, tienen implicancia con el movil y con los objetos.
							  -Zona normal: Es una zona, por la cual el movil se puede desplazar, sin nigun tipo de incoveniente.
							  -Zona vulnerables: Hasta el momento son solo los vacios, el movil al llegar a estos lugares, muere.
							  -Paredes: Son zonas incorrutibles,infranqueables e inpenetrables; en el sentido de que ni el movil, ni ningun objeto pueden ocupar
							  su lugar.
							  -Puentes: Practicamente, lo mismo que zonas normales, se originan cuando una caja llega a un vacio.
							  *Objetos: Son todas las "cosas", que pueden interactuar con el movil.
							  -Objetos con espacio propio: Son espacios que tienen 3 dimensiones, como las cajas
							  -Objetos Planos: Son objetos de dos dimensiones,los objetos con 3 dimensiones pueden "ponerse encima" de ellos.
							  -Cajas: El movil al chocar con ellas, las mueve una unidad en la misma direccion que avanza.
							  -Vacios: Son espacios vulnerables; una caja al caer en él, sirve de puente para el movil.
							  -Huecos: Es un objeto plano, que sirve de lugar de referencia para las cajas.
							  -Portal: Sirve para avanzar al siguiente nivel. No obstante este aparece bajo ciertas circunstacias.
							  -??????
							  Conceptos de verdad y condiciones: *Perdida de Vida: Esto hace que se reinicie el nivel, se da cuando:
							  -Cuando el movil llega a una zona vulnerable.
							  -Cuando el jugador se rinde
							  *Perdida de Juego: O llamado tambien Game Over, se da cuando:
							  -El movil se queda sin vidas.
							  -El jugador decide salir del juego
							  *La caja se puede desplazar siempre y cuando, el nuevo lugar donde seria desplazada, no este ocupado por Paredes o por objetos
							  con espacio propio.
							  *Caja estable: Se atribuye a la relacion explicita entre los huecos y las cajas, la cual verifica que una caja se
							  "encuentre encima" de un hueco.
							  *Visibilidad del portal: Ocurre cuando todas la cajas son cajas estables.
							  *Pase De nivel: Ocurre cuando el movil, llega al portal, cuando se ecuentra visible.
							  *Pase De juego: Cuando se completan exitosamente todos los niveles
							  *El movil no se movera si su siguiente lugar es una pared, o si al empujar una caja, esta, no se mueve.

							  ------------------------------------------------------------FIN MODO DE JUEGO "SILVER SPHERE"----------------------------------------------------------------------------

							  ---------------------------------------------------------OTRO MODO DE JUEGO(VARIABLES DE SILVER SPHERE)????????????????---------------------------------------------------
							  =========================================================================================================================================================================//*/
}
void main(){

	//La matriz 'matriz' de dos dimensiones sirve para dibujar mapas y algunos gifs, sera usado por funciones como dibujar
	int **matriz, f; matriz = new int *[136]; for (f = 0; f <= 135; f++)matriz[f] = new int[80];
	//---------------------------------Mesaje Incial------------------------------------------------------------------------//
	Console::CursorVisible = FALSE;
	InterfazCargando(matriz);
	Sleep(1000);
	Console::SetWindowSize(80, 40);
	desvanecimiento(9, 40);
	Warning(2, 0, 4, 0, 31, 23, 1); Warning(1, 5, 26, 6, 26, 29, 7);
	ir(0, 26); colorletra(1); colorfondo(9);
	Escribir("   Para poder jugar PushBox configura la consola de Windows a 8x8.\n", 1);
	Escribir("   Si no sabes hacerlo, sigue los siguientes pasos: \n", 1);
	Escribir("      1. Click derecho en la parte superior de la consola.\n", 1);
	Escribir("      2. Entra a 'Propiedades' o 'Properties'.\n", 1);
	Escribir("      3. Entra a la pesta\244a 'Font' o 'Fuente'.\n", 1);
	Escribir("      4. Aseg\243rate de que la fuente sea 'Raster Fonts' o 'Mapa de bits'\n", 1);
	Escribir("     	   de tama\244o 8x8.\n", 1);
	Escribir("   Presiona siempre 'E' para aceptar(funciona como enter).\n \n", 1);
	Escribir("              Juego creado en la UPC, 2014 por Diego Jara y Jeremy Tornero.", 1);
	ir(0, 0);
	SonidoAlarma();
	limpiartecla(2);
	while (1){ Warning(9, 0, 4, 0, 31, 23, 1); Sleep(500); Warning(2, 0, 4, 0, 31, 23, 1); Sleep(500); if (_kbhit()){ int t = _getch(); if (t == 'e' || t == 'E')break; } }Warning(10, 0, 4, 0, 31, 23, 1);

	//-------------------------------------------------CONFIGURACION DE LA CONSOLA----------------------------------------------//
	for (int i = 40; i <= 63; i++){ Console::SetWindowSize(80, i); Sleep(15); }
	int **Cantidades; Cantidades = new int*[9]; for (int i = 1; i <= 8; i++)Cantidades[i] = new int[8];
	char *n1; n1 = new char[8];
	char *n2; n2 = new char[8];
	char *c; c = new char[1];
	bool error = false;
	desvanecimiento(9, 21, 79, 46, 0, 41);
	colorletra(1); colorfondo(9);
	Console::CursorVisible = TRUE;
	ir(30, 46); Escribir("NOMBRE DEL JUGADOR", 100, 2);
	ir(0, 48); Escribir("* Cada nombre puede tener 8 car\240cteres incluido n\243meros, e\244es y tildes.", 100, 2);
	do{
		ir(0, 49); for (int i = 0; i <= 79; i++)cout << " ";
		ir(0, 49); Escribir("  Quieres usar un nombre o dos(1 o 2)? : ", 100, 2); scanf("%1s", c); limpiartecla(1);
	} while (c[0] != '1'&&c[0] != '2');

	do{
		ir(0, 50); for (int i = 0; i <= 79; i++)cout << " ";
		ir(0, 50); if (c[0] == '2')Escribir("  C\243al es tu primer nombre? : ", 100, 2); else Escribir("  C\243al es tu nombre? : ", 100, 2);
		scanf("%8s", n1); limpiartecla(1);
		for (int i = 0; i <= strlen(n1) - 1; i++)
		{
			if ((n1[i] != 32) && (n1[i] <= 47 || n1[i] >= 58) && (n1[i] <= 64 || n1[i] >= 91) && (n1[i] <= 96 || n1[i] >= 123) && (n1[i] <= -97 || n1[i] >= -90) && n1[i] != -126 && n1[i] != -75 && n1[i] != -112 && n1[i] != -42 && n1[i] != -32 && n1[i] != -23)
			{
				error = true; break;
			}error = false;
		}
	} while (error);


	if (c[0] == '2')do{
		ir(0, 51); for (int i = 0; i <= 79; i++)cout << " ";
		ir(0, 51); Escribir("  C\243al es tu segundo nombre?: ", 100, 2); scanf("%8s", n2); limpiartecla(1);
		for (int i = 0; i <= strlen(n2) - 1; i++)
		{
			if ((n2[i] != 32) && (n2[i] <= 47 || n2[i] >= 58) && (n2[i] <= 64 || n2[i] >= 91) && (n2[i] <= 96 || n2[i] >= 123) && (n2[i] <= -97 || n2[i] >= -90) && n2[i] != -126 && n2[i] != -75 && n2[i] != -112 && n2[i] != -42 && n2[i] != -32 && n2[i] != -23)
			{
				error = true; break;
			}error = false;
		}
	} while (error);
	ir(34, 53); Escribir("LISTO!!!!!!!", 100, 4);
	Cantidades[8][0] = c[0]; Cantidades[8][1] = strlen(n1); if (c[0] == '2')Cantidades[8][2] = strlen(n2);
	for (int i = 0; i <= Cantidades[8][1] - 1; i++)Cantidades[6][i] = int(n1[i]);
	if (c[0] == '2')for (int i = 0; i <= Cantidades[8][2] - 1; i++)Cantidades[7][i] = int(n2[i]);

	Sleep(1000);
	//63 caracteres de altura como minimo para que la consola no de un "salto", al llegar a una esquina
	Console::Clear();
	system("color 80");//color de fondo por defecto: plomo, color de letra por defecto: negro
	Console::CursorVisible = FALSE;//Oculta el cursor
	//-------------------------------------------------------------------------------------------------------------------------//


	//-------------------------------------------------DECLARACION DE MATRICES----------------------------------------------//


	int **Posiciones; Posiciones = new int*[6]; for (int i = 1; i <= 5; i++)Posiciones[i] = new int[5]; Posiciones[0] = new int[1];
	//La matriz 'Cantidades' guarda el numero de objetos que tiene cada nivel, ya sean cajas, paredes, huecos o vacios.

	//La matriz es de tamaño 8*4, pero de los 8 solo se usan 5, que es la cantidad de  niveles.
	//La segunda dimension es 4 porque es el numero de objetos, por convención lo asignamos de la siguiente manera:
	//Cantidades[nivel][0]----->Cajas,
	//Cantidades[nivel][1]----->Paredes,
	//Cantidades[nivel][2]----->Huecos,
	//Cantidades[nivel][3]----->Vacios,
	NientiendoGif(matriz);//Se muesrta la animacion de Nientiendo y la portada
	desvanecimiento(1);
	Pixelmen(matriz); GIF(matriz, 0, 59, 0, 41, 19, 1, 0, 0, 1, 78); ir(33, 62); SonidoPixelmen(); colorfondo(1); colorletra(9); cout << "ENTERTAINMENT";
	Sleep(3000);
	desvanecimiento(9); ir(34, 30); colorletra(1); colorfondo(9); cout << "Presents..."; Sleep(1500);
	int nivel;//Sera el nivel activo en el que se encuentre el juego(Dentro del main esta en desuso)
	nivel = 0;//solo con la excepcion de que en main se le inicia en 0


	//======================================================CAJAS DE TODOS LOS NIVELES======================================//
	int ***Cajas;
	Cajas = new int**[8];//Primera Dimension: Nivel
	for (int i = 1; i <= 5; i++)Cajas[i] = new int*[17];//Segunda Dimension: Numero De Caja
	for (int i = 1; i <= 5; i++){ for (int f = 0; f <= 16; f++)Cajas[i][f] = new int[2]; }//Tercera Dimension: Coordenadas
	//=======================================================================================================================//

	//===========================================================PAREDES DE TODOS LOS NIVELES=================================//
	int ***Paredes;
	Paredes = new int**[8];//Primera Dimension: Nivel
	for (int i = 1; i <= 5; i++)Paredes[i] = new int*[124];//Segunda Dimension: Numero De Pared
	for (int i = 1; i <= 5; i++){ for (int f = 0; f <= 123; f++)Paredes[i][f] = new int[2]; }//Tercera Dimension: Coordenadas
	//=======================================================================================================================//

	//===========================================================VACIOS DE TODOS LOS NIVELES=================================//
	int ***Vacios;
	Vacios = new int**[8];//Primera Dimension: Nivel
	for (int i = 1; i <= 5; i++)Vacios[i] = new int*[25];//Segunda Dimension: Numero De Vacio
	for (int i = 1; i <= 5; i++){ for (int f = 0; f <= 24; f++)Vacios[i][f] = new int[2]; }//Tercera Dimension: Coordenadas
	//=======================================================================================================================//

	//===========================================================HUECOS DE TODOS LOS NIVELES=================================//
	int ***Huecos;
	Huecos = new int**[8];//Primera Dimension: Nivel
	for (int i = 1; i <= 5; i++)Huecos[i] = new int*[10];//Segunda Dimension: Numero De Hueco
	for (int i = 1; i <= 5; i++){ for (int f = 0; f <= 9; f++)Huecos[i][f] = new int[2]; }//Tercera Dimension: Coordenadas
	//===========================================================HUECOS DE TODOS LOS NIVELES=================================//

	ir(0, 0);//Centrando bien la consola.
	MusicaMenu();
	ControlDeNiveles(matriz, nivel, Cajas, Paredes, Vacios, Huecos, Cantidades, Posiciones);//El control de niveles nos pide todo lo declarado acá.

}