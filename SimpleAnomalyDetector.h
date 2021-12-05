/*
ID 305079253
Naveh Benveniste
ID 318781127
Gilad Aharoni
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>


struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
	correlatedFeatures(string feature1, string feature2, const TimeSeries& ts);
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	//set of correlated features
	vector<correlatedFeatures> cf;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	//create cf by timeseries
	virtual void learnNormal(const TimeSeries& ts);

	//return anoamly report vector, can get a table
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}

};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
