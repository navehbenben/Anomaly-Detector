
/*
ID 305079253
Naveh Benveniste
ID 318781127
Gilad Aharoni
 */
#ifndef COMMANDS_H_
#define COMMANDS_H_
#include<iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"
#include "timeseries.h"



using namespace std;

struct dataCLI {
	HybridAnomalyDetector* detector;
	TimeSeries *train, *test;
	vector<AnomalyReport>* reports;
};


class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
};


class DIO2: public DefaultIO{
	private:
	DefaultIO *dio;
	public:
	DIO2(DefaultIO* dio1){
		dio = dio1;
	}
	virtual char * csvfile(){
		return nullptr;
	}
	virtual string read(){
		return dio->read();
	}
	virtual void write(string text){
		dio->write(text);
	}
	virtual void write(float f){
		dio->write(f);
	}
	virtual void read(float* f){
		dio->read(f);
	}
};

// you may add here helper classes


// you may edit this class
class Command{
protected:
	DefaultIO* dio;
	dataCLI* userData;
public:
	Command(DefaultIO* dio, dataCLI* ud):dio(dio),userData(ud){}
	virtual void execute()=0;
	Command(){

	}
	virtual ~Command(){}
};

//note: the DIO2 do for us the converts. we are always from the server prespective in the commands line.

class uploadCSV:public Command{
	public:
	uploadCSV(DefaultIO* dio, dataCLI* ud){
		this->dio = dio;
		this->userData = ud;

		//super:(dio,ud);
	}
	uploadCSV(){
		dio = nullptr;
		userData = nullptr;
	}
	virtual void execute(){
		dio->write("Please upload your local train CSV file.\n");
		//const char * csvFile; //creating csv file by the special IO - should read the file - it could be an address from the user or lines with "done" by the server. at the end of the day it should be new file in the server side.
		        //Getting the train csv
        ofstream trainFile("TrainCsvFile.csv");
        string trainline = dio->read() + '\n';
        while (trainline != "done\n") {
            trainFile << trainline;
            trainline = dio->read() + '\n';
        }
        trainFile.close();
		userData->train = new TimeSeries("TrainCsvFile.csv");
        dio->write("Upload complete.\n");

		dio->write("Please upload your local test CSV file.\n");
		//const char * trainCsvFile;//by the same way
		ofstream testFile("anomalyTest.csv");
        string testline = dio->read() + '\n';
        while (testline != "done\n") {
            testFile << testline;
            testline = dio->read() + '\n';
        }
        testFile.close();
		userData->test = new TimeSeries("anomalyTest.csv");
		dio->write("Upload complete.\n");
	}
};





// class UploadFileToCsv: public Command {
//     string description = "1.upload a time series csv file\n";
//     int rows = 0;
// public:
//     UploadTS(DefaultIO* dio): Command(dio) {};

//     virtual void execute() {
//         //Getting the train csv
//         dio->write("Please upload your local train CSV file.\n");
//         ofstream trainFile("TrainCsvFile.csv");
//         string trainline = dio->read() + '\n';
//         while (trainline != "done\n") {
//             trainFile << trainline;
//             trainline = dio->read() + '\n';
//         }
//         trainFile.close();
//         dio->write("Upload complete.\n");

//         //Getting the test csv
//         dio->write("Please upload your local test CSV file.\n");
//         ofstream testFile("anomalyTest.csv");
//         string testline = dio->read() + '\n';
//         while (testline != "done\n") {
//             this->rows++;
//             testFile << testline;
//             testline = dio->read() + '\n';
//         }
//         testFile.close();
//         this->rows--;
//         dio->write("Upload complete.\n");
//     }

//     virtual void printDes() {
//         dio->write(description);
//     }

//     int* getRows() {
//         return &this->rows;
//     }
// };





class setAlgorithm: public Command{
//do option 2- easy set get things.
	public:
	setAlgorithm(DefaultIO* dio, dataCLI* ud){
		this->dio = dio;
		this->userData = ud;
	}
	setAlgorithm(){
		dio = nullptr;
		userData = nullptr;
	}
	virtual void execute(){
		dio->write("The current correlation threshold is "+to_string((userData->detector)->get_corolationThres())+"\n");
		float new_cor;
		dio->write("please choose a value between 0 and 1.\n");
		dio->read(&new_cor);
		while (new_cor < 0 || new_cor>1)
		{
			dio->write("please choose a value between 0 and 1.\n");
			dio->read(&new_cor);
		}
		userData->detector->set_corolationThres(new_cor);
	}
};


class detectAnomalies:public Command{
	public:
	detectAnomalies(DefaultIO* dio, dataCLI* ud){
		this->dio = dio;
		this->userData = ud;
	}
	detectAnomalies(){
		dio = nullptr;
		userData = nullptr;
	}
	virtual void execute(){
		userData->detector->learnNormal(*(userData->train));
		userData->reports = new vector<AnomalyReport>(userData->detector->detect(*(userData->test)));
		dio->write("anomaly detection complete.\n");
	}
};

class displayResults: public Command{
	public:
	displayResults(DefaultIO* dio, dataCLI* ud){
		this->dio = dio;
		this->userData = ud;
	}
	displayResults(){
		dio = nullptr;
		userData = nullptr;
	}
	virtual void execute(){
		for(auto report = begin(*userData->reports); report != end(*userData->reports); report++){
			dio->write(to_string((*report).timeStep)+"\t"+(*report).description+"\n");
		}
		dio->write("done\n");
	}	
};

class uploadAnomaliesAnalize:public Command{

	vector<pair<long int,long int>>  realReports(){
		vector<pair<long int,long int>> anomalies = vector<pair<long int,long int>>();
		string input = dio->read();
		while(input != "done"){
			string seperate = input.substr(0, input.find(","));
			long int start = stol(seperate);
            input.replace(input.find(seperate), seperate.length() + 1, "");
			seperate = input.substr(0,input.find("\n"));
			long int end = stol(seperate);
			input.replace(input.find(seperate), seperate.length() + 1, "");
			anomalies.push_back(pair<long int,long int>(start,end));
			input = dio->read();
		}
		return anomalies;


	}

	vector<pair<long int,long int>> algoReports(){
		
		vector<pair<long int,long int>> arReports = vector<pair<long int,long int>>();
		int size = userData->reports->size();
 		for (int i=0; i < size; i++) {
            long int getFirst = (*userData->reports)[i].timeStep;
            while ((i < size) && ((*userData->reports)[i].description == (*userData->reports)[i+1].description) &&
                   ((*userData->reports)[i+1].timeStep - (*userData->reports)[i].timeStep == 1)) {
                i++;
            }
            arReports.emplace_back(getFirst, (*userData->reports)[i].timeStep);
        }
        
		return arReports;

	}
	public:
	uploadAnomaliesAnalize(DefaultIO* dio, dataCLI* ud){
		this->dio = dio;
		this->userData = ud;
	}
	uploadAnomaliesAnalize(){
		dio = nullptr;
		userData = nullptr;
	}
	
virtual void execute(){
		this->dio->write("Please upload your local anomalies file.\n");
		vector<pair<long, long>> TrueReports = this->realReports();
		this->dio->write("Upload complete.\n");
		vector<pair<long, long>> ReportsRepetition = algoReports();

		float P = TrueReports.size();
		int totalLines = userData->test->getLinesNumber();
        int rowsOfAnomalies = 0;
		for (pair<long, long> pair : TrueReports)
		{
			int end = int (pair.second);
            int start = int (pair.first);
            rowsOfAnomalies += (end - start + 1);
		}
		int N = totalLines - rowsOfAnomalies;
        float TP = 0, FP = 0;
        bool flag;


        for (pair<long, long> oneReport: ReportsRepetition) {
            flag = false;
			for (pair<long, long> anomalyOccurrence : TrueReports)
			{

				if (oneReport.first >= anomalyOccurrence.first &&
                         oneReport.first <= anomalyOccurrence.second) {
                    flag = true;
                    break;
                } 
                else if (oneReport.second <= anomalyOccurrence.second &&
                         oneReport.second >= anomalyOccurrence.first) {
                    flag = true;
                    break;
                } 
                else if (oneReport.first <= anomalyOccurrence.first &&
                         oneReport.second >= anomalyOccurrence.second) {
                    flag = true;
                    break;
                }
                    
                else if (oneReport.first >= anomalyOccurrence.first &&
                         oneReport.second <= anomalyOccurrence.second) {
                    flag = true;
                    break;
                }
			}
			if (flag) {
                TP++;
            } else
                FP++;
        }
		        float TPrate = TP / P;
        TPrate = TPrate * 1000;
        TPrate = floor(TPrate);
        TPrate = TPrate/1000;
        float FPrate = FP / float(N);
        FPrate = FPrate * 1000;
        FPrate = floor(FPrate);
        FPrate = FPrate/1000;
        dio->write("True Positive Rate: ");
        this->dio->write(TPrate);
        this->dio->write("\n");
        dio->write("False Positive Rate: ");
        this->dio->write(FPrate);
        this->dio->write("\n");

	}
};

class exit: public Command{
	public:
	exit(DefaultIO* dio, dataCLI* ud){
		this->dio = dio;
		this->userData = ud;
	}

};




#endif /* COMMANDS_H_ */
