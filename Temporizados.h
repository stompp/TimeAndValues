/*
 * Temporizados.h
 *
 *  Created on: 09/03/2013
 *      Author: Juan
 */

#ifndef TEMPORIZADOS_H_
#define TEMPORIZADOS_H_

#include <Arduino.h>
#include "../Time/Time.h"
#define TIEMPO_ESPERA 30
#define TIEMPO_GUARDA 5
#define MINUTOS_DIA 1440
class TemporizadoDias {

public :

	TemporizadoDias();
	virtual ~TemporizadoDias();
	// cada cuantos dias
	uint8_t periodoDias;
	// iniciando dentro de n dias
	uint8_t diasRestantes;
	// a que hora
	uint8_t hora, minuto;

	long minutosDia();
	long minutosRestantes();
	long minutosPasados();
	bool reiniciarCuentaDias();


};


class Temporizado{

public :
	typedef enum  {PARADO = 0x00,ESPERANDO = 0x01,ACTIVO = 0x02} EstadosT;
	boolean programado;
	EstadosT estado;
	// cada cuantos dias
	int16_t periodoDias;
	// dentro de n dias
	int16_t diasRestantes;
	// a que hora
	uint8_t hora, minuto;
	uint16_t totalMinutos;
	typedef void(*funcion)(void);
//	void (*FuncionEspera)();
	funcion _funcionParo;
	funcion _funcionInicio;
	funcion _funcionFin;
//	void (*_funcionParo)(void);
//	void (*_funcionInicio)(void);
//	void (*_funcionFin)(void);

	void programar(uint8_t _totalMinutos, uint8_t h,uint8_t m,
						uint16_t _periodoDias, uint16_t _diasRestantes){
		totalMinutos = _totalMinutos;
		hora = h;
		minuto = m;
		periodoDias = _periodoDias;
		diasRestantes = _diasRestantes;
		programado = true;
	}

	void asignarFunciones(void(*funcionParo)(),void(*funcionInicio)(),void(*funcionFin)()){
		_funcionParo = funcionParo;
		_funcionInicio = funcionInicio;
		_funcionFin = funcionFin;
	}


	long minutosDia()
	/**
	 * Devuelve el
	 * @return total de minutos desde las 00:00 hasta la hora del
	 * tiempo programado.
	 */
	{
		return (60*long(hora) + long(minuto));
	}

	long minutosRestantes(){


		long minutos_restantes;
		minutos_restantes = (minutosDia() - hour()*60 - minute());

		if (minutos_restantes </*=*/ 0) return (minutos_restantes + MINUTOS_DIA);
		else return (minutos_restantes);
	}

	long minutosPasados(){


		long minutos_pasados;
		minutos_pasados = (hour()*60 + minute() - minutosDia() );

		if (minutos_pasados < 0) return (MINUTOS_DIA + minutos_pasados);
		else return (minutos_pasados);
	}
	bool renovarDias(){
		// periodico,renueva
		if(diasRestantes == 0 && periodoDias > 0){
			diasRestantes = periodoDias;
			estado = PARADO;
			return true;
		// riego puntual
		}

		return false;
	}
	boolean actualizar(){

		if(!programado) return false;

		switch (estado) {

			case PARADO:

				if (minutosRestantes() <= TIEMPO_ESPERA) {
					estado = ESPERANDO;
					//INDICAR
					return true;
				}
				return false;

			case ESPERANDO:

				// es la hora o algun minuto pasado
				if (minutosPasados() <= TIEMPO_GUARDA){

					//resta un dia
					diasRestantes--;
					// si es el dia
					if(diasRestantes <= 0){
						//INDICAR
						_funcionInicio();
					// no es el dia,vuelve a la espera
					}else {
						// INDICAR

						estado = PARADO;
					}
					return true;

				}

				return false;
			case ACTIVO:

				// pasado el tiempo
				if(minutosPasados() >= totalMinutos){
					_funcionParo();

					// renueva el riego si no es único
					if(!(programado = renovarDias())){
						// INDICAR FIN
						_funcionFin();
					}

					return true;
				}
				return false;

		}
	}



};


#endif /* TEMPORIZADOS_H_ */
