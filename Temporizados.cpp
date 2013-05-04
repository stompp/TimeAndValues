#include "Temporizados.h"
TemporizadoDias::TemporizadoDias(){}
TemporizadoDias::~TemporizadoDias(){}
long TemporizadoDias::minutosDia()
/**
 * Devuelve el
 * @return total de minutos desde las 00:00 hasta la hora del
 * tiempo programado.
 */
{
	return (60*long(hora) + long(minuto));
}

long TemporizadoDias::minutosRestantes(){


	long minutos_restantes;
	minutos_restantes = (minutosDia() - hour()*60 - minute());

	if (minutos_restantes <= 0) return (minutos_restantes + MINUTOS_DIA);
	else return (minutos_restantes);
}

long TemporizadoDias::minutosPasados(){


	long minutos_pasados;
	minutos_pasados = (hour()*60 + minute() - minutosDia() );

	if (minutos_pasados < 0) return (MINUTOS_DIA + minutos_pasados);
	else return (minutos_pasados);
}

bool TemporizadoDias::reiniciarCuentaDias(){
	if(diasRestantes == 0 && periodoDias > 0){
		diasRestantes = periodoDias;
		return true;
	}

	return false;

}



