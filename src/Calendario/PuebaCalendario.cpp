#include <iostream>
#include <iomanip>
using namespace std;

// Función para determinar si un anio es bisiesto
bool esBisiesto(int anio)
{
    return ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0));
}

// Función para obtener el número de días en un mes específico
int obtenerDiasEnMes(int mes, int anio)
{
    switch (mes)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return esBisiesto(anio) ? 29 : 28;
    default:
        return 31;
    }
}

// Función para obtener el día de la semana del primer día del mes
// Usamos el algoritmo de Zeller modificado para que 0 = domingo
int obtenerDiaDeLaSemana(int dia, int mes, int anio)
{
    if (mes < 3)
    {
        mes += 12;
        anio -= 1;
    }
    int k = anio % 100;
    int j = anio / 100;
    int f = dia + (13 * (mes + 1)) / 5 + k + k / 4 + j / 4 + 5 * j;
    return ((f + 5) % 7 + 1) % 7; // Ajuste para que 0 sea domingo
}

void generarCalendario(int mes, int anio, int calendario[6][7])
{
    const int diasSemana = 7;
    const int semanas = 6; // Máximo número de semanas que puede tener un mes
    int diaInicial = obtenerDiaDeLaSemana(1, mes, anio);
    int diasEnMes = obtenerDiasEnMes(mes, anio);
    int dia = 1;

    // Llenar la matriz con los días del mes
    for (int i = 0; i < semanas; ++i)
    {
        for (int j = 0; j < diasSemana; ++j)
        {
            if (i == 0 && j < diaInicial)
            {
                calendario[i][j] = 0;
            }
            else if (dia <= diasEnMes)
            {
                calendario[i][j] = dia++;
            }
            else
            {
                calendario[i][j] = 0;
            }
        }
    }
}

void imprimirCalendario(int calendario[6][7])
{
    cout << "Do Lu Ma Mi Ju Vi Sa" << endl;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (calendario[i][j] == 0)
            {
                cout << "   ";
            }
            else
            {
                cout << setw(2) << calendario[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main()
{
    int mes = 5; // Septiembre
    int anio = 2024;
    int calendario[6][7] = {0};

    generarCalendario(mes, anio, calendario);
    imprimirCalendario(calendario);

    return 0;
}