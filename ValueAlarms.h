#ifndef VALUEALARMS_H_
#define VALUEALARMS_H_

#include <Arduino.h>
#include "Refresh.h"

//template class<T>
class Conditions {

public :

	enum ConditionsTypes  {OFF,EQUALS,LESS_THAN,GREATER_THAN,BETWEEN,NOT_BETWEEN} conditionType;
	Conditions():conditionType(OFF){}
	virtual ~Conditions(){};
	/** Differnt types of conditions avaialable */

	/** Conditions' values*/
	int condition[2];
	/** Sets value to check */
	void setConditionType(ConditionsTypes conditionType){this->conditionType = conditionType;}

	/** Sets simple condition data*/
	void setConditions(ConditionsTypes conditionType = OFF, int conditionValue = 0xffff){
		setConditionType(conditionType);
		condition[0] = conditionValue;
	}
	/** Sets double condition data*/
	void setConditions(ConditionsTypes conditionType, int conditionValue0,int conditionValue1){
		setConditions(conditionType,conditionValue0);
		condition[1] = conditionValue1;
	}
	/** Sets by copying from the input*/
	void setConditions(Conditions other){setConditions(other.conditionType,other.condition[0],other.condition[1]);}

	/** Checks wether value is under defined conditions*/
	bool checkConditions(int value){
		switch (conditionType){
			case OFF : return false;
			case EQUALS : return (value == condition[0]);
			case LESS_THAN : return (value < condition[0]);
			case GREATER_THAN : return (value > condition[0]);
			case BETWEEN : return ((value >= condition[0]) && (value <= condition[1]));
			case NOT_BETWEEN : return !((value >= condition[0]) && (value <= condition[1]));

//			case EQUALS : return equals(value);
//			case LESS_THAN : return isLessThan(value);
//			case GREATER_THAN : return isGreaterThan(value);
//			case BETWEEN : return isBetween(value);
//			case NOT_BETWEEN : return isNotBetween(value);

			default : return false;
		}
	}

	void setEquals(int value){setConditions(EQUALS,value);}
	void setLessThan(int value){setConditions(LESS_THAN,value);}
	void setGreaterThan(int value){setConditions(GREATER_THAN,value);}
	void setBetween(int lowValue,int highValue){setConditions(BETWEEN,lowValue,highValue);}
	void setNotBetween(int lowValue,int highValue){setConditions(NOT_BETWEEN,lowValue, highValue);}

	// external value input
//	bool equals(int value){return value == condition[0];}
//	bool isLessThan(int value){return (value < condition[0]);}
//	bool isGreaterThan(int value){return (value > condition[0]);}
//	bool isBetween(int value){return ((value >= condition[0]) && (value <= condition[1]));}
//	bool isNotBetween(int value){return !isBetween(value);}

//	bool operator ==(int value) {return equals(value);}
//	bool operator <(int value) {return isLessThan(value);}
//	bool operator >(int value){return isGreaterThan(value);}


};
//template <typename T>
class ValueConditions : public Conditions{

public :

	ValueConditions() : Conditions(){}
	virtual ~ValueConditions(){}

	/** Stored value that will be checked */
	int value;
	/** Updates value to check */
	void setValue(int newValue){value = newValue;}
	/** Checks if inner value is under conditions*/
	bool checkConditions(){return Conditions::checkConditions(value);}
	//bool operator bool(){return checkConditions();}


//	bool equals(){return Conditions::equals(value);}
//	bool isLessThan(int value){return isLessThan(value);}
//	bool isGreaterThan(int value){return isGreaterThan(value);}
//	bool isBetween(int value){return isBetween(value);}
//	bool isNotBetween(int value){return isNotBetween(value);}

	/** Turns off conditions checking. Calling to checkConditions() will always return false*/
	void conditionsOff(){setConditions();}

//	bool operator ==(int value) {Conditions c; c.setEquals(value);return c.equals(this->value);}
//	bool operator <(int value) {return isLessThan(value);}
//	bool operator >(int value){return isGreaterThan(value);}

};

class Alarm{
protected :
	bool _alarmState ;
public :
	Alarm():_alarmState(false){}
	virtual	~Alarm(){}
	bool alarmState(){return _alarmState;}
	void sleepAlarm(){_alarmState = false;}
	virtual bool alarmChanged() = 0;
	virtual bool isOn(){return _alarmState;}
	virtual bool isOff(){return !_alarmState;}
	void setAlarmState(bool state) {_alarmState = state;}

	void operator = (bool state) { setAlarmState(state);}
	bool operator == (bool state) { return _alarmState==state;}
};

class ValueAlarm : public Refresh, public ValueConditions, public Alarm{


public :

		ValueAlarm() : Refresh(),ValueConditions(),Alarm(){}
		virtual ~ValueAlarm(){}

		/** Inits alarm
		 * @param conditions
		 * @param refreshData Refresh parameters see RefreshData
		 * */
		void initValueAlarm(Conditions conditions,RefreshData refreshData){
			setConditions(conditions);
			initRefresh(refreshData);
		}

		virtual bool alarmChanged(){
			if(!shouldRefresh()) {return false;}
			bool previous = alarmState();
			setAlarmState(checkConditions());
			return (previous != alarmState());

		}

};



#endif /* VALUEALARMS_H_ */
