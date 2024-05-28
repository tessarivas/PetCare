class Calendario
{
private:
    int mes;
    int anio;
    int cal[6][7]={0};
public:
    Calendario(int mes, int anio);
    bool EsBisiesto();
    int ObtenerDiaMes();
    int DiaSemana();
    int GenerarCal();
    void Imprimir();
};

