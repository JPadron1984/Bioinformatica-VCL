// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;

// ---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner) : TForm(Owner) {
	datos1 = new float[20000];
	datos2 = new float[20000];
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
float TForm7::fminimo(float *lista, int k) { // Funcion que ubica el valor minimo de una lista

	float min = lista[0];

	for (int i = 0; i < k; i++) {
		if (lista[i] < min) {
			min = lista[i];
		}

	}
	return min;
}

// ---------------------------------------------------------------------------
float TForm7::fmaximo(float *lista, int k) { // Funcion que ubica el valor maximo de una lista

	float max = lista[0];

	for (int i = 0; i < k; i++) {
		if (lista[i] > max) {
			max = lista[i];
		}

	}
	return max;
}

// ---------------------------------------------------------------------------
void TForm7::Areagrafica() {

	Canvas->Pen->Style = psDot; // estilo punteado de pluma
	Canvas->Pen->Width = 0.1;
	Canvas->Brush->Color = clWhite; // color blanco de pluma
	Canvas->FillRect(R); // rellenar en tamaño y posicion en relacion en R
	Canvas->Pen->Color = clGreen; // color de linea punteada

	W = R.Width(); // ancho del bevel1
	H = R.Height(); // alto bevel1

	Canvas->MoveTo(R.left + (W / 2), R.Top);
	Canvas->LineTo(R.left + (W / 2), R.Bottom);
	Canvas->MoveTo(R.left, R.Top + (H / 2));
	Canvas->LineTo(R.right, R.Top + (H / 2));
}

// ---------------------------------------------------------------------------
void TForm7::Graficar(float * dato, int k) {

	int y1, y2, x1, x2, escY, escX, xoffset, yoffset;

	Canvas->Pen->Style = psSolid;
	Canvas->Pen->Width = 1;
	Canvas->Pen->Color = clRed;

	W = R.Width() / 2; // ancho del bevel1
	H = R.Height() / 2; // alto bevel1

	escX = k; // escala en x en funcion de la cantidad de valores de la lista
	escY = (fmaximo(dato, k) - fminimo(dato, k)) * 0.7; // escala en y en funcion del valor mas alto en la lista

	xoffset = R.Left + W/2; // alineamiento en eje x
	yoffset = R.Top + H; // elineamiento en eje y

	for (int i = 0; i < k - 1; i++) {

		y1 = (dato[i] * H) / escY; // datos[i]"valor de lista"*H"alto medio del bevel"
		y2 = (dato[i + 1] * H) / escY; // datos[i+1]"valor siguiente de lista"
		x1 = (i * W) / escX; // i"posicion en x"*(W/2)"punto medio del bevel"
		x2 = ((i + 1) * W) / escX; // valor en y de la linea

		y1 = yoffset - y1;
		y2 = yoffset - y2;
		x1 = x1 + xoffset;
		x2 = x2 + xoffset;

		Canvas->MoveTo(x1, y1);
		Canvas->LineTo(x2, y2);
	}
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

void __fastcall TForm7::Button1Click(TObject *Sender) {
	fstream fin; // declaracion de variable tipo fstream

	if (OpenDialog1->Execute()) // condicion ejecutar opendialog
	{
		AnsiString Fila = OpenDialog1->FileName;
		// declaracion de variable ansistring

		char * filename = Fila.c_str(); // declaracion de lista tipo char con el nombre de archivo y ubicacion a traves de la variable Fila

		fin.open(filename); // Posicionando sobre el archivo
		fin >> n; // Primer valor que seria de la cantidad de lineas se guarda en n
		for (int i = 0; i < n; i++) {
			fin >> datos1[i]; // carga de datos del archivo en la lista en la posicion i
		}
		fin.close(); // cierre archivo
	}
	R = Bevel1->BoundsRect;
	Areagrafica();
	Graficar(datos1, n);
}

// ---------------------------------------------------------------------------

void __fastcall TForm7::Button2Click(TObject *Sender) {
	fstream fin; // declaracion de variable tipo fstream

	if (OpenDialog2->Execute()) // condicion ejecutar opendialog
	{
		AnsiString Fila = OpenDialog2->FileName;
		// declaracion de variable ansistring

		char * filename = Fila.c_str(); // declaracion de lista tipo char con el nombre de archivo y ubicacion a traves de la variable Fila

		fin.open(filename); // Posicionando sobre el archivo
		fin >> n; // Primer valor que seria de la cantidad de lineas se guarda en n
		for (int i = 0; i < n; i++) {
			fin >> datos2[i]; // carga de datos del archivo en la lista en la posicion i
		}
		fin.close(); // cierre archivo
	}
	R = Bevel2->BoundsRect;
	Areagrafica();
	Graficar(datos2, n);
}
// ---------------------------------------------------------------------------

