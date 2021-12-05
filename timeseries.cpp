/*
ID 305079253
Naveh Benveniste
ID 318781127
Gilad Aharoni
 */
#include "timeseries.h"


map<string, vector<float>> readFromFile(const char *CSVfileName) {
    map<string, vector<float>> recordsArray;
    ifstream csvFile;
    csvFile.open(CSVfileName);
    string csvstr;
  
    csvFile >> csvstr;
    while (!csvstr.empty())
    {
 
        string seperate = csvstr.substr(0, csvstr.find(","));
        csvstr.replace(csvstr.find(seperate), seperate.length() + 1, "");
        recordsArray[seperate] = vector<float>(0);
    }

    while (csvFile >> csvstr)
    {
        for (auto pair : recordsArray)
        {
            string seperate = csvstr.substr(0, csvstr.find(","));
            csvstr.replace(csvstr.find(seperate), seperate.length() + 1, "");
            recordsArray[pair.first].push_back(stof(seperate));
        }
    }

    csvFile.close();
    return recordsArray;
}

TimeSeries::TimeSeries(map<string, vector<float>> recordsMap)
{
    records = recordsMap;
}

int TimeSeries::getLinesNumber() const {
    string as;
    for (auto string: getTItlesList()){
        as = string;
        break;
    }
    vector<float> samp = getColumnByTitle(as);
    return samp.size();
}

vector<string> TimeSeries::getTItlesList() const
{
    vector<string> title_list(0);
    for (auto pair : records)
        title_list.push_back(pair.first);
    return title_list;
}

TimeSeries::TimeSeries(const char *CSVfileName) {
    records = readFromFile(CSVfileName);
}

vector<float> TimeSeries::getColumnByTitle(string title) const
{
    return records.at(title);
}


int TimeSeries::getColumnsNumber() const
{
    return records.size();
}

//returning the value in column(title), line nuber LINE.
float TimeSeries::getByKeyLine(string title, int line) const
{
    return (this->getColumnByTitle(title))[line];
}

Point **TimeSeries::getTwoColumns(string title1, string title2) const
{
    Point ** array = new Point*[getLinesNumber()];
    vector<float> vec1 = getColumnByTitle(title1), vec2 = getColumnByTitle(title2);
    for (size_t i = 0; i < getLinesNumber(); i++)
    {
        Point* point =new Point(vec1[i],vec2[i]);
        array[i] = point;
    }
    return array;
}
