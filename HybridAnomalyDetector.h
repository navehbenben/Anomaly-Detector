

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
private:
	float corolationThres = 0.9;
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
	void set_corolationThres(float t);
	float get_corolationThres();

};

bool isCircleDefult(correlatedFeatures c);

#endif /* HYBRIDANOMALYDETECTOR_H_ */
