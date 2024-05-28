#include <iostream>
#include <iomanip>
#include "Calendario.h"
using namespace std;
Calendario::Calendario(int mes, int anio)
{
    this->mes = mes;
    this->anio = anio;
}

bool Calendario::EsBisiesto()
{
    return ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0));
}

int Calendario::ObtenerDiaMes()
{
    switch (mes)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return EsBisiesto() ? 29 : 28;
    default:
        return 31;
    }
}

int Calendario::DiaSemana()
{
    if (mes < 3)
    {
        mes += 12;
        anio -= 1;
    }
    int k = anio % 100;
    int j = anio / 100;
    int f = 1 + (13 * (mes + 1)) / 5 + k + k / 4 + j / 4 + 5 * j;
    return ((f + 5) % 7 + 1) % 7; // Ajuste para que 0 sea domingo
}

int Calendario::GenerarCal()
{
    const int diasSemana = 7;
    const int semanas = 6; // Máximo número de semanas que puede tener un mes
    int diaInicial = DiaSemana();
    int diasEnMes = ObtenerDiaMes();
    int dia = 1;

    // Llenar la matriz con los días del mes
    for (int i = 0; i < semanas; ++i)
    {
        for (int j = 0; j < diasSemana; ++j)
        {
            if (i == 0 && j < diaInicial)
            {
                cal[i][j] = 0;
            }
            else if (dia <= diasEnMes)
            {
                cal[i][j] = dia++;
            }
            else
            {
                cal[i][j] = 0;
            }
        }
    }
}

void Calendario::Imprimir()
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (cal[i][j] == 0)
            {
                cout << "   ";
            }
            else
            {
                cout << setw(2) << cal[i][j] << " ";
            }
        }
        cout << endl;
    }
}
