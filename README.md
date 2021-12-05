# content
this is ex2 of the first milestone in advanced programming. the main process is:
we have a timeseries object -the data, an simpleanomalydetector object uses the method learnNormal on that data and saves the correlated features. 
the simpleanomalydetector object get another data in the detect method and look for anomalies, and export an anomaly report.

## MainTrain.cpp
a basic test for the whole assignment. it should have more extremistic inputs.

## anomaly_detection_util h & cpp
from the last assignment, containing the Line class and statistic tools for data series.

## timeseries cpp & h
the main object that store the time series data. we should add some methods for easy access to lines and columns.

## simpleAnomalyDetector cpp & h
an interface for anomaly detector and struct of correlated features.

## Anomaly_detector.h
implementation of simple_Anomaly_detector for timeseries data.

