/*
 * Refresh.h
 *
 *  Created on: 26/04/2013
 *      Author: Juan
 */

#ifndef REFRESH_H_
#define REFRESH_H_

#include "TimeRegister.h"

class RefreshData {
public :
	enum RefreshType {NEVER = false,ALWAYS = true,MILLIS,SECONDS,MINUTES,HOURS,DAYS};

	RefreshType refreshType;
	uint16_t refreshValue;

	RefreshData():refreshType(NEVER){}
	virtual ~RefreshData(){}

	void setRefreshData(uint16_t refreshValue,RefreshType refreshType){
		this->refreshType = refreshType;
		this->refreshValue = refreshValue;
	}
	void setRefreshMillis(uint16_t rawMillis){
			this->refreshType = MILLIS;
			this->refreshValue = rawMillis;
	}
	void setRefreshData(RefreshData otro){setRefreshData(otro.refreshValue,otro.refreshType);}

	unsigned long getRefreshRawMillis(){
		switch (refreshType) {
			case SECONDS: return refreshValue*MILLIS_A_SECONDS;
			case MINUTES: return refreshValue*MILLIS_A_MINUTES;
			case HOURS: return refreshValue*MILLIS_A_HOURS;
			case DAYS: return refreshValue*MILLIS_A_DAYS;
			default : return refreshValue;
		}
	}

};

class Refresh : public TimeRegister, public RefreshData {

public :

	Refresh() : RefreshData(),TimeRegister(){}
	virtual ~Refresh(){}

	void initRefresh(uint16_t refreshValue,RefreshType refreshType){
		setRefreshData(refreshValue,refreshType);
		//definirIntervalo();
		recordMillis();
	}
	void initRefresh(RefreshData data){initRefresh(data.refreshValue,data.refreshType);}
	void initRefresh(uint16_t rawMillis){setRefreshMillis(rawMillis);recordMillis();}

	boolean shouldRefresh(){

		switch (refreshType){
			case ALWAYS : return true;
			case NEVER : return false;
			case MILLIS : return  timeOver(getMillis());
			case SECONDS : return  timeOver(getSeconds());
			case MINUTES : return timeOver(getMinutes());
			case HOURS :return timeOver(getHours());
			case DAYS : return timeOver(getDays());
			default : return false;
		}

	}

	unsigned long leftMillis(){return getRefreshRawMillis() - getMillis();}
	void printLeftChronoTime(Stream *stream){printChronoTimeFor(leftMillis(),stream);}
protected:

	/*
	unsigned long (Refresco::*intervalo)();
	void definirIntervalo(){
		switch (tipoRefresco){
			case MILISEGUNDOS : intervalo = &Refresco::millisPasados;break;
			case SEGUNDOS : intervalo = &Refresco::segundosPasados;break;
			case MINUTOS : intervalo = &Refresco::minutosPasados;break;
			case HORAS : intervalo = &Refresco::horasPasadas;break;
			case DIAS : intervalo = &Refresco::diasPasados;break;
			default : break;
		}
	}


	bool timeOver(){
		bool r = ((this->*intervalo)() >= (unsigned long)valorRefresco);
		if(r){grabarMillis();}
		return r;
	}

	*/
	bool timeOver(unsigned long pasados){
		bool r = (pasados >= (unsigned long)refreshValue);
		if(r){recordMillis();}
		return r;
	}

};

#endif /* REFRESH_H_ */
