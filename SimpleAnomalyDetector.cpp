/*
ID 305079253
Naveh Benveniste
ID 318781127
Gilad Aharoni
 */
#include "SimpleAnomalyDetector.h"
#include <vector>
#include <string.h>


//constructor for the correlated features
correlatedFeatures::correlatedFeatures(string feature1, string feature2, const TimeSeries &ts)
{
	this->feature1 = feature1;
	this->feature2 = feature2;
	float pears = abs(pearson( &ts.getColumnByTitle(feature1)[0], &ts.getColumnByTitle(feature2)[0],ts.getLinesNumber()));
	this->corrlation = pears;
	Point** points = ts.getTwoColumns(feature1, feature2);
	lin_reg = linear_reg(points, ts.getLinesNumber());
	float maxThreshold = 0;
	for (size_t i = 0; i < ts.getLinesNumber(); i++)
	{
		float localThreshold = abs(lin_reg.f(points[i]->x) - points[i]->y);
		if (maxThreshold < localThreshold)
		{
			maxThreshold = localThreshold;
		}
	}
	delete points;
	this->threshold = maxThreshold;
}

SimpleAnomalyDetector::SimpleAnomalyDetector()
{
	cf = std::vector<correlatedFeatures>();
}

SimpleAnomalyDetector::~SimpleAnomalyDetector()
{
	//
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts)
{
	int size = ts.getLinesNumber();
	
	vector<string> names = ts.getTItlesList();
	//choose every diffrent 2-tuple.
	for (auto title1 = begin(names); title1 != end(names); title1++)
	{
		string correlated = "error";
		float maxPearson = -1;
		for (auto title2 = title1; title2 != end(names); title2++)
		{
			if (title1 != title2)
			{
				float pears = abs( pearson (&ts.getColumnByTitle(*title1)[0], &ts.getColumnByTitle(*title2)[0], size));
				if (pears > maxPearson)
				{
					maxPearson = pears;
					correlated = *title2;
				}
			}
		}
		if (maxPearson >= 0.8)
		{
			//add it to the corrolations vector.
			correlatedFeatures cor = correlatedFeatures(*title1, correlated, ts);
			cf.push_back(cor);
		}
	}
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts)
{
	//create a new vector of reports.
	vector<AnomalyReport> reports;
	//iterate every line in the timeseries data.
	for (int i=0; i< ts.getLinesNumber();i++)
	{
		//pick every couple of corrations.
		for (auto correlated: cf)
		{
			string featureA = correlated.feature1, featureB = correlated.feature2;
			//the condition check if the values of the two columns corrolated as in the original data.
            float y_expected = correlated.lin_reg.f(ts.getByKeyLine(featureA,i));
            float y_founded = ts.getByKeyLine(featureB,i);
			if (abs(y_expected-y_founded)>=(correlated.threshold*1.1)){
				//add to the reports vector a new report.
				string descrip = featureA + "-" + featureB;
				AnomalyReport* report = new AnomalyReport(descrip, i+1);
				reports.push_back(*report);
			}
		}
	}
	return reports;
}
