
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts){
	SimpleAnomalyDetector abtype = SimpleAnomalyDetector();
	abtype.learnNormal(ts);
	cf = abtype.getNormalModel();
	for (auto correlatedFeautre = begin(cf); correlatedFeautre != end(cf); correlatedFeautre++){
		if ((*correlatedFeautre).corrlation >= 0.5 && (*correlatedFeautre).corrlation<corolationThres)
		{
			int size = ts.getLinesNumber();
			(*correlatedFeautre).mincircle = new Circle(findMinCircle(ts.getTwoColumns((*correlatedFeautre).feature1,(*correlatedFeautre).feature2),size));
		}		
	}
}


bool isCircleDefult(correlatedFeatures c){
	if(c.mincircle->center.x==0&&c.mincircle->center.y==0&&c.mincircle->radius==0){
		return true;
	}
	return false;
}


vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries& ts){
	SimpleAnomalyDetector abtype = SimpleAnomalyDetector(cf);
	vector<AnomalyReport> reports = abtype.detect(ts);	
	int lines = ts.getLinesNumber();
	for (size_t i = 0; i < lines; i++)
	{	
		int cfsize = cf.size();
		for ( size_t j = 0; j < cfsize; j++){
			if (!isCircleDefult(cf[j]))
			{
				correlatedFeatures samp = cf[j];
				string featureA = samp.feature1;
				string featureB = samp.feature2;
				if (!Cor_isInCircle(*(samp.mincircle),Point(ts.getColumnByTitle(featureA)[i], ts.getColumnByTitle(featureB)[i]))) {
					string descrip = featureA + "-" + featureB;
					AnomalyReport* report = new AnomalyReport(descrip, i+1);
					reports.push_back(*report);
				}
			}	
		}		
	}
	return reports;
}


void HybridAnomalyDetector::set_corolationThres(float t){
	corolationThres = t;
}
float HybridAnomalyDetector::get_corolationThres(){
	return corolationThres;
}