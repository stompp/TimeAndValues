#include <Refresh.h>

Refresh r;


void setup(){

	Serial.begin(9600);
	r.initRefresh(15,Refresh::SECONDS);

}


void loop(){


	r.printLeftChronoTime(&Serial);
	Serial.println();
	delay(50);
	if(r.shouldRefresh()) {
		Serial.println("END!");
		while(1);
	}

}
