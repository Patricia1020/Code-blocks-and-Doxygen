#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <map>
#include <iterator>
#include <vector>
#include "date.h"
#include "time.h"
#include "weather.h"
#include "bstpointer.h"
using namespace std;
/**use typedef struct for option 5**/
typedef struct
{
    Date d ;
    Time t;
    float rad;
} WindLogType;

void printmenu1();/** @brief print option no 1, @return void */
void printmenu2();/** @brief print option no 2, @return void */
void printmenu3();/** @brief print option no 3, @return void */
void printmenu4();/** @brief print option no 4, @return void */
void printmenu5();/** @brief print option no 5, @return void */
void readallfile();/** @brief read value from file, @return void */

int filecount = 0;
int error = 0;
int menu;
int month = 1;
int year = 1;
int day = 1;
float avgspeed = 0;
float radiation = 0;
float avgtemp = 0;
Date Dt;
weather Wt;
Time T;
vector<WindLogType> windlog;
BstPointer<float> bst;
int main()
{
    readallfile();
    cout<<filecount<<" files loaded with "<<error<<" error(s)."<<endl;
    do
    {
    cout << "----------------------------------------------------------------------\n"
         << "Welcome to Our Weather Log!! You can choose options below: \n"
         << "1: Average Wind Speed (km/h) and Air Ambient Temperature (deg C) for \n   specific month and year (print only)\n"
         << "2: Average Wind Speed (km/h) and Air Ambient Temperature (deg C) for \n   each month of specific year (print only)\n"
         << "3: Total Solar Radiation (kWh/m^2) for each month of specific year \n   (print only)\n"
         << "4: Average Wind Speed (km/h), Air Ambient Temperature (deg C), and \n   Total Solar Radiation(kWh/m^2) for each month of specific year \n   (for the output you can see on WindSolarTemp.csv)\n"
         << "5: Highest Solar Radiation (W/m^2) that is recorded for specific time \n   and specific day (print only)\n"
         << "6: Exit!!! \n"
         << "----------------------------------------------------------------------\n"
         << "Select Options in number: ";
         cin >> menu;
         switch(menu)
         {
            case 1:
            cout <<"enter month: ";
            cin>>month;
            cout <<"enter year: ";
            cin>>year;
            printmenu1();
            break;

            case 2:
            cout <<"enter year: ";
            cin>>year;
            printmenu2();
            break;

            case 3:
            cout <<"enter year: ";
            cin>>year;
            printmenu3();
            break;

            case 4:
            cout <<"enter year: ";
            cin>>year;
            printmenu4();
            break;

            case 5:
            cout <<"enter day: ";
            cin>>day;
            cout <<"enter month: ";
            cin>>month;
            cout <<"enter year: ";
            cin>>year;
            printmenu5();
            break;

            case 6:
            break;

            default:
            break;
         }
    }while(menu < 6 && menu > 0);
    cout<<"Done!"<<endl;
    return menu;
}

void readallfile()
{
    //local variable are declared below:
    string dd   ="00";
    string mm ="00";
    string yyyy  ="0000";
    string hour  ="00";
    string minute="00";
    string line;
    string s1,s2,s3;
    float totalspeed = 0;
    float totalrad = 0;
    float totaltemp = 0;
    float hourlyradiation;
    int countspeed = 0;
    int countrad = 0;
    int counttemp = 0;

    ifstream infile;
    string fileName ;
    string listoffile;
    ifstream filelist;
    filelist.open("data/met_index.txt");
    while (!filelist.eof())
    {
        getline(filelist, listoffile,'\n');
        fileName="data/"+listoffile; //set file name to be opened
        infile.open(fileName.c_str());//open the specified file
        if (!infile.is_open()) // check if all files are valid
        {error++;}
        else
        {
           while(!infile.eof())
           {
	            // this function to get date and time from file
		        getline(infile, dd, '/');
		        getline(infile, mm, '/');
		        getline(infile, yyyy, ' ');
		        getline(infile, hour, ':');
		        getline(infile, minute, ',');

                // i<10 because we want to get rid of first 10 column
                for(int i = 0; i < 10; i++)
                {getline(infile, s1,',');}
                getline(infile, s2,',');
                infile.ignore(50,',');
                infile.ignore(50,',');
                infile.ignore(50,',');
                infile.ignore(50,',');
                infile.ignore(50,',');
			    getline(infile, s3,'\n');
		        // this function is to convert string to integer or float
		        int days = atoi(dd.c_str());
		        int months= atoi(mm.c_str());
		        int years= atoi(yyyy.c_str());
		        int hours= atoi(hour.c_str());
		        int minutes= atoi(minute.c_str());
                float s = atof(s1.c_str());
		        float sr= atof(s2.c_str());
		        float t = atof(s3.c_str());

                /**for option 5**/
                WindLogType T1;//create a record
                T1.d.setDate(day,month,year);
                if(T1.d.getDay() == days && T1.d.getMonth() == months && T1.d.getYear() == years)
                {
                    T1.t.setTime(hours,minutes);
                    T1.rad = sr;
                    if(sr > 100)
                    {
                        windlog.push_back(T1);
                        bst.insertNode(sr);
                    }
                }
                getline(infile,line,'\n');

                /**for option 1-4**/
                if(Dt.getYear() == years)
                {
                    if(Dt.getMonth() == months)
                    {
                        totalspeed += s * 3.6;
                        countspeed++;
                        avgspeed = totalspeed/countspeed;

                        if(sr >= 100)
                        {
                            totalrad += sr;
                            countrad++;
                            hourlyradiation = totalrad / 6;
                            radiation = (hourlyradiation/1000)*2 ;
                        }

                        totaltemp += t;
                        counttemp++;
                        avgtemp = totaltemp/counttemp;
                    }
                }
            }
            filecount++;
        }
        infile.close();
    }
    filelist.close();
}

void printmenu1()
{
    Dt.setMonth(month);
    Dt.setYear(year);
    readallfile();
    Wt.SetWindSpeed(avgspeed);
    Wt.SetTemperature(avgtemp);
    if(avgspeed >0 && avgtemp >0)
    {cout << Dt.monthConvert(month) << " "<< Dt.getYear() <<": "<< Wt.GetWindSpeed() << " km/h, " << Wt.GetTemperature() << " degree C"<<endl;}
    else
    {cout << Dt.monthConvert(month) << " "<< Dt.getYear() <<": no record"<<endl;}
    avgspeed = 0;
    avgtemp = 0;
    radiation = 0;
    windlog.clear();
    bst.deleteTree();
}

void printmenu2()
{
    Dt.setYear(year);
    for(int i=1; i<=12; i++)
    {
       Dt.setMonth(i);
       readallfile();
       Wt.SetWindSpeed(avgspeed);
       Wt.SetTemperature(avgtemp);
       if(avgspeed > 0 && avgtemp >0)
       {cout << Dt.monthConvert(i) <<": "<< Wt.GetWindSpeed() << " km/h, " << Wt.GetTemperature() << " degree C"<<endl;}
       else
       {cout << Dt.monthConvert(i) <<": no record"<<endl;}
       avgspeed = 0;
       avgtemp = 0;
       radiation = 0;
    }
    windlog.clear();
    bst.deleteTree();
}

void printmenu3()
{
    Dt.setYear(year);
    for(int i=1; i<=12; i++)
    {
       Dt.setMonth(i);
       readallfile();
       Wt.SetRadiation(radiation);
       if(radiation > 0)
       {cout << Dt.monthConvert(i) << ": "<< Wt.GetRadiation() << " kWh/m^2"<<endl;}
       else
       {cout << Dt.monthConvert(i) <<": no record"<<endl;}
       radiation = 0;
       avgspeed = 0;
       avgtemp = 0;
    }
     windlog.clear();
     bst.deleteTree();
}

void printmenu4()
{
    ofstream ofile("WindSolarTemp.csv");
    Dt.setYear(year);
    ofile << Dt.getYear() << endl;
    ofile << "WAST " << ", "<<"S "<<", "<< "T "<<", "<< "SR "<<endl;
    for(int i=1; i<=12; i++)
    {
       Dt.setMonth(i);
       readallfile();
       Wt.SetWindSpeed(avgspeed);
       Wt.SetTemperature(avgtemp);
       Wt.SetRadiation(radiation);
       if(avgspeed > 0 && avgtemp >0 && radiation > 0)
       {ofile << Dt.monthConvert(i) <<", "<< Wt.GetWindSpeed() << ", " << Wt.GetTemperature() << ", " << Wt.GetRadiation() <<endl;}
       else
       {ofile <<"";}
       avgspeed = 0;
       avgtemp = 0;
       radiation = 0;
    }
    cout << "print done!!!"<<endl;
    windlog.clear();
    bst.deleteTree();
}

void printmenu5()
{
    float maxrad = 0;
    map<string, float> Map;
    WindLogType H;
    H.d.setDate(day,month,year);
    readallfile();

    for(unsigned i=0; i<windlog.size();i++)
    {maxrad = bst.maxValue();}

    cout << "Date: " << H.d.getDay() << " " << H.d.monthConvert(month) << " " << H.d.getYear()<<endl;
    if(maxrad > 100)
    {
        Map.insert(pair<string, float>("Max Solar Radiation: ", maxrad ));
        map<string, float>::iterator itr;

        for(itr = Map.begin(); itr != Map.end(); itr++)
        {cout << itr->first << itr->second << " W/m^2"<< endl;}

        cout << "Time: "<<endl;
        for(unsigned i=0; i < windlog.size();i++)
        {
            if(windlog.at(i).rad == maxrad)
            {cout << windlog.at(i).t << endl;}
        }
    }
    else
    {cout << "no record!!"<<endl;}

    radiation = 0;
    avgspeed = 0;
    avgtemp = 0;
    maxrad = 0;
    Map.clear();
    windlog.clear();
    bst.deleteTree();
}
