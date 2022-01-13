#include "CLI.h"
#include "commands.h"

using namespace std;

CLI::CLI(DefaultIO* dio) {
    this->dio = new DIO2(dio);
    handler = new dataCLI();
}



void CLI::start(){
    //create a commands vector.
    //create a loop that get symbols for the option pick and match it.
    string menu = "Welcome to the Anomaly Detection Server.\nPlease choose an option:\n1.upload a time series csv file\n2.algorithm settings\n3.detect anomalies\n4.display results\n5.upload anomalies and analyze results\n6.exit\n";
    handler->detector = new HybridAnomalyDetector();
    dio->write(menu);
    string input = dio->read();
    while (input.compare("6"))
    {
       if (stoi(input)==1)
       {
           uploadCSV one = uploadCSV(dio, handler);
           one.execute();
       }
        if (stoi(input)==2)
       {
           setAlgorithm two = setAlgorithm(dio,handler);
           two.execute();
           
       }
        if (stoi(input)==3)
       {
            detectAnomalies three = detectAnomalies(dio,handler); 
            three.execute();  
       }
        if (stoi(input)==4)
       {
           displayResults four = displayResults(dio,handler);
           four.execute();
       }
        if (stoi(input)==5)
       {
           uploadAnomaliesAnalize five = uploadAnomaliesAnalize(dio, handler);
           five.execute();
       }
       dio->write(menu);
       input = dio->read();
    }
    
}



CLI::~CLI() {
}

