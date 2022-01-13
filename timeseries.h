/*
ID 305079253
Naveh Benveniste
ID 318781127
Gilad Aharoni
 */
#include <vector>
#include<map>
#include <string>
#include <fstream>
#include "anomaly_detection_util.h"
#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;
class TimeSeries{

private:
	map<string, vector<float>> records;

public:
	TimeSeries(){};
	TimeSeries(map<string, vector<float>> recordsMap);
	TimeSeries(const char *CSVfileName);
	vector<float> getColumnByTitle(string title) const;
	vector<string> getTItlesList() const;
	int getColumnsNumber() const;
	int getLinesNumber() const;
		//returning array of points (x,y)\in vec(title1)Xvec(title2)
	Point** getTwoColumns(string title1, string title2) const;

	//returning the value in column(title), line nuber LINE.
	float getByKeyLine(string title, int line) const;





};



#endif /* TIMESERIES_H_ */
