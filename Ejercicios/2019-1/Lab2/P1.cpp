#include <iostream>
#include <iomanip>

#define MAX_LINEA 84
#define MAX_DISTRITO 20
#define NO_DEFINIDO -9999

using namespace std;

void separarLineas(char c, int cantidad) {
	for (int i = 0; i < cantidad; i++) {
		cout.put(c);
	}
	cout << endl;
}

int main() {
	int codigo, dia, mes, anho, i, numCaracteres = 0, numTemp = 0, numHumedad = 0, numPrec = 0;
	double tempCelsius, tempFarenheit, humedad, precTiempo, precCantidad;
	double sumaTempCelsius = 0, sumaTempFarenheit = 0, sumaHumedad = 0, sumaPrecTiempo = 0, sumaPrecCantidad = 0;
	char c;
	// Colocar título del reporte
	cout << setw(MAX_LINEA/2 + 14) << "REGISTRO CLIMATICO DEL PAIS" << endl;
	separarLineas('=', MAX_LINEA);
	// Colocar cabecera del reporte
	cout << setw(MAX_DISTRITO/2 + 3) << "CIUDAD" << setw(MAX_DISTRITO/2 + 5) << "CODIGO" << setw(10) << "FECHA"
		 << setw(16) << "TEMPERATURA" << setw(10) << "HUMEDAD" << setw(19) << "PRECIPITACIONES" << endl;
	cout << setw(MAX_DISTRITO + 26) << "ºC" << setw(7) << "ºF" << setw(8) << '%' << setw(14) << "TIEMPO(s)"
		 << setw(9) << "CANTIDAD" << endl;
	separarLineas('-', MAX_LINEA);
	// Leer y ordenar datos
	/* while (true) {
		// Verificar si terminó el archivo
		c = cin.peek();
		if (cin.eof()) break;
		
	} */
	// Leer el nombre del distrito
	numCaracteres = 0;
	while (true) {
		// Intentamos leer el código
		cin >> codigo;
		if (!cin.fail()) break;
		cin.clear();
		// Escribimos una palabra del nombre del distrito
		while (true) {
			c = cin.get();
			if (c == ' ') break;
			cout.put(c);
			numCaracteres++;
		}
		cout.put(' ');
		numCaracteres++;
	}
	for (i = numCaracteres; i <= MAX_DISTRITO; i++) {
		cout.put(' ');
	}
	// Escribir el código
	cout << setw(7) << codigo;
	// Leer el conjunto de datos climáticos
	while (true) {
		// Intentamos leer el día de la fecha
		cin >> dia;
		if (cin.fail()) {
			cin.clear();
			// Leer los datos climáticos de una fecha
			while (true) {
				c = cin.get();
				if (c == '\n') break;
				switch (c) {
					// Leer temperatura
					case 'T':
					case 't':
						// Intentar leer el número
						cin >> tempCelsius;
						if (cin.fail()) {
							tempCelsius = tempFarenheit = NO_DEFINIDO;
							cin.clear();
						} else {
							c = cin.get();
							switch (c) {
								// Convertir de Celsius a Farenheit
								case 'C':
								case 'c':
									tempFarenheit = (9*tempCelsius/5.0) + 32;
									break;
								// Convertir de Farenheit a Celsius
								case 'F':
								case 'f':
									tempFarenheit = tempCelsius;
									tempCelsius = 5*(tempFarenheit - 32)/9.0;
									break;
							}
							// Añadir al promedio
							sumaTempCelsius += tempCelsius;
							sumaTempFarenheit += tempFarenheit;
							numTemp++;
						}
						break;
					// Leer humedad
					case 'H':
					case 'h':
						// Intentar leer el número
						cin >> humedad;
						if (cin.fail()) {
							humedad = NO_DEFINIDO;
							cin.clear();
						} else {
							// Convertir de decimal a porcentaje
							if (cin.get() != '%') {
								humedad *= 100;
							}
							// Añadir al promedio
							sumaHumedad += humedad;
							numHumedad++;
						}
						break;
					// Leer precipitación
					case 'P':
					case 'p':
						// Intentar leer el número
						cin >> precTiempo;
						if (cin.fail()) {
							precTiempo = NO_DEFINIDO;
							precCantidad = NO_DEFINIDO;
							cin.clear();
						} else {
							c = cin.get();
							switch (c) {
								// Convertir de horas a segundos
								case 'H':
								case 'h':
									precTiempo *= 3600;
									break;
								// Convertir de minutos a segundos
								case 'M':
								case 'm':
									precTiempo *= 60;
									break;
							}
							// Leer la cantidad
							cin >> precCantidad;
							// Añadir al promedio
							sumaPrecTiempo += precTiempo;
							sumaPrecCantidad += precCantidad;
							numPrec++;
						}
						break;
				}
			}
		} else {
			// Ver si terminamos de leer la fecha
			c = cin.get();
			if (c == '/') {
				// Intentamos leer el mes de la fecha
				cin >> mes;
				// Ver si terminamos de leer la fecha
				c = cin.get();
				if (c == '/') {
					// Caso 1: dd/mm/aaaa
					cin >> anho;
				} else {
					// Caso 2: --/mm/aaaa
					anho = mes;
					mes = dia;
					dia = NO_DEFINIDO;
					if (c == '\n') break;
				}
			} else {
				// Caso 3: --/--/aaaa
				anho = dia;
				dia = mes = NO_DEFINIDO;
				if (c == '\n') break;
			}
		}
	}
	// Calcular los promedios
	separarLineas('-', MAX_LINEA);
	return 0;
}

