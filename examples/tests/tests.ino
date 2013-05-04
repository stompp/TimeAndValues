#include <SD.h>
#include <Time.h>
#include <SDLogger.h>
//#include <ArduinoBasicIO.h>
//#include <TimeRegister.h>
#include <XString.h>
SDLogger logger;
XString st;

float values[] = {231.12f,-302001.33f,10219.21f};

int getSize(float* array){return(sizeof(array)/sizeof(array[0]));}
void setup(){

//	//logger.initSD(4);
//	Serial.begin(9600);
//	Serial.println("(s) to Start");
//	Serial.println();
//	while(Serial.read() != 's');
//
//	float value = values[1];
//	Serial.print(F("Float Value : "));
//	Serial.println(value);
//	Serial.println();
//
//	st.formatEFloat(value);
//	Serial.print(F("Formatted e float String : "));
////	st.print2Stream(&Serial);
//	Serial.println(st);
//	Serial.println();
//
//	Serial.print(F("Parsed e float : "));
//	Serial.println(st.getEFloat());

//	logger.initSD(4);
	Serial.begin(9600);
////	logger.setLogFileName("lines.txt");
//
//	Serial.println(F("(s) to Start"));
//	Serial.println();
//	while(Serial.read() != 's');
//
//
//	logger.openLogFile("lines.txt",0);
//	XFile* file = logger.getFile();
//	st = file->readNextCSVString();
//	while(!st.isEmpty()){
//		Serial.println(st);
//		st = file->readNextCSVString();
//	}
//	file->seek(0);
//	file->jumpCSV();
//	file->writeByteCSV(133);
//
//	file->print2Stream(&Serial);







//	while(logger.jumpCSV()){
//		Serial.println(logger.readNextCSVFloat());
//	}

//	while(logger.jumpCSV()){
//		logger
//	}


//	logger.close();
//	Serial.println(F("END"));











}





void loop(){




}


