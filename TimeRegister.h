#ifndef TIMEREGISTER_H_
#define TIMEREGISTER_H_
#include <Arduino.h>

#define MILLIS_A_SECONDS 1000UL
#define MILLIS_A_MINUTES 60000UL
#define MILLIS_A_HOURS 3600000UL
#define MILLIS_A_DAYS 86400000UL

class TimeRegister {
public :

	/** @Constructor Set to now when created*/
	TimeRegister(){recordMillis();}
	virtual ~TimeRegister(){}

	// STATIC METHODS

	/** Gets full seconds in rawMillis*/
	unsigned long static getSecondsFor(unsigned long rawMillis){return rawMillis/MILLIS_A_SECONDS;}
	/** Gets full minutes in rawMillis */
	unsigned long static getMinutesFor(unsigned long rawMillis){return rawMillis/MILLIS_A_MINUTES;}
	/** Gets full hours in rawMillis */
	unsigned long static getHoursFor(unsigned long rawMillis){return rawMillis/MILLIS_A_HOURS;}
	/** Gets full days in rawMillis */
	unsigned long static getDaysFor(unsigned long rawMillis){return rawMillis/MILLIS_A_DAYS;}


	/** Gets chrono millis in rawMillis @return 0-999*/
	uint16_t static chronoMillisFor(unsigned long rawMillis){return rawMillis%MILLIS_A_SECONDS;}
	/** Gets chrono seconds in rawMillis @return 0-59*/
	uint16_t static chronoSecondsFor(unsigned long rawMillis){return (rawMillis%MILLIS_A_MINUTES)/MILLIS_A_SECONDS;}
	/** Gets chrono minutes in rawMillis @return 0-59*/
	uint16_t static chronoMinutesFor(unsigned long rawMillis){return (rawMillis%MILLIS_A_HOURS)/MILLIS_A_MINUTES;}
	/** Gets chrono hours in rawMillis @return 0-23*/
	uint16_t static chronoHoursFor(unsigned long rawMillis){return (rawMillis%MILLIS_A_DAYS)/MILLIS_A_HOURS;}
	/** Gets chrono days in rawMillis @return ¿0-54?*/
	uint16_t static chronoDaysFor(unsigned long rawMillis){return getDaysFor(rawMillis);}

	/** Gets full millis since sinceMillis indicated */
	unsigned long static getMillis(unsigned long sinceMillis){return millis() - sinceMillis;}
	/** Gets full seconds since sinceMillis indicated */
	unsigned long static getSeconds(unsigned long sinceMillis){return getSecondsFor(getMillis(sinceMillis));}
	/** Gets full minutes since sinceMillis indicated */
	unsigned long static getMinutes(unsigned long sinceMillis){return getMinutesFor(getMillis(sinceMillis));}
	/** Gets full hours since sinceMillis indicated */
	unsigned long static getHours(unsigned long sinceMillis){return getHoursFor(getMillis(sinceMillis));}
	/** Gets full days since sinceMillis indicated */
	unsigned long static getDays(unsigned long sinceMillis){return getDaysFor(getMillis(sinceMillis));}

	/** Gets chrono millis @return 0-999*/
	uint16_t static chronoMillis(unsigned long sinceMillis){return chronoMillisFor(getMillis(sinceMillis));}
	/** Gets chrono seconds @return 0-59*/
	uint16_t static chronoSeconds(unsigned long sinceMillis){return chronoSecondsFor(getMillis(sinceMillis));}
	/** Gets chrono minutes @return 0-59*/
	uint16_t static chronoMinutes(unsigned long sinceMillis){return chronoMinutesFor(getMillis(sinceMillis));}
	/** Gets chrono hours @return 0-23*/
	uint16_t static chronoHours(unsigned long sinceMillis){return chronoHoursFor(getMillis(sinceMillis));}
	/** Gets chrono days @return ¿0-54?*/
	uint16_t static chronoDays(unsigned long sinceMillis){return chronoDaysFor(getMillis(sinceMillis));}

	// OBJECT METHODS

	/** Gets full millis since last record*/
	unsigned long getMillis(){return getMillis(lastRecord);}
	/** Gets full seconds since last record*/
	unsigned long getSeconds(){return getSeconds(lastRecord);}
	/** Gets full minutes since last record */
	unsigned long getMinutes(){return getMinutes(lastRecord);}
	/** Gets full hours since last record */
	unsigned long getHours(){return getHours(lastRecord);}
	/** Gets full days since last record */
	unsigned long getDays(){return getDays(lastRecord);}

	/** Gets chrono millis since last record @return 0-999*/
	uint16_t chronoMillis(){return chronoMillis(lastRecord);}
	/** Gets chrono seconds since last record @return 0-59*/
	uint16_t chronoSeconds(){return chronoSeconds(lastRecord);}
	/** Gets chrono minutes since last record @return 0-59*/
	uint16_t chronoMinutes(){return chronoMinutes(lastRecord);}
	/** Gets chrono hours since last record @return 0-23*/
	uint16_t chronoHours(){return chronoHours(lastRecord);}
	/** Gets chrono days since last record @return ¿0-54?*/
	uint16_t chronoDays(){return chronoDays(lastRecord);}

	/** Sets register millis record time */
	void recordMillis(unsigned long sinceMillis) {lastRecord = sinceMillis;}
	/** Sets register millis record time to now millis*/
	void recordMillis(){recordMillis(millis());}

	// EXTRA METHODS
	void printChronoTimeFor(unsigned long rawMillis,Stream *stream){
		if(chronoHoursFor(rawMillis)< 10 )stream->print("0");
		stream->print(chronoHoursFor(rawMillis));
		stream->print(":");
		printChronoTimeMSMFor(rawMillis,stream);

	}

	/** prints Mimutes:Seconds:Milliseconds on stream
	 * format MM:SS:mmm
	 */
	void printChronoTimeMSMFor(unsigned long rawMillis,Stream *stream){

		if(chronoMinutesFor(rawMillis)< 10 )stream->print("0");
		stream->print(chronoMinutesFor(rawMillis));
		stream->print(":");
		if(chronoSecondsFor(rawMillis)< 10 )stream->print("0");
		stream->print(chronoSecondsFor(rawMillis));
		stream->print(":");
		if(chronoMillisFor(rawMillis)< 100 )stream->print("0");
		if(chronoMillisFor(rawMillis)< 10 )stream->print("0");
		stream->print(chronoMillisFor(rawMillis));
	}

	void printChronoTime(Stream *stream){printChronoTimeFor(lastRecord,stream);}


protected:
	unsigned long lastRecord;
};






// TIME STRINGS





#endif /* TIMEREGISTER_H_ */
