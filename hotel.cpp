/* 
 * File:   hotel.cpp
 * Author: MHerzog
 *
 * Created on March 6, 2015, 4:56 PM
 */

#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

//number of months + total
const int MONTHS = 13;
//number of service codes
const int SERVICES = 5;
//array of months+ total
const string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                         "Jul", "Aug", "Sep", "Oct", "Nov", "Dec", "Total"};
//array of service code titles
const string services[] = {"Lodging", "Dining", "Conferences", "Receptions", "Spa"};

int main(int argc, char** argv) {
    //file reading from
    std::ifstream salesIn("hotel.txt");
    //file writing to
    std::ofstream salesOut("hotelAnswer.txt");

    //  Variables
    string values;
    string invoiceID, serviceCode, invoiceDate, saleAmount;
    int service;
    int month;
    double total = 0;
    string tokens[4];
    double answer[MONTHS][SERVICES];
    

    //while file has next line to read from
    while (!salesIn.eof()) {
        //read line
        getline(salesIn, values);
        //separate invoiceID
        invoiceID = values.substr(0, 6);
        //separate serviceCode
        serviceCode = values.substr(7, 1);
        //separate invoiceDate
        invoiceDate = values.substr(9, 10);
        //separate saleAmount
        saleAmount = values.substr(20);

        //tokenize substrings
        tokens[1] = serviceCode;
        tokens[2] = invoiceDate;
        tokens[3] = saleAmount;

        //number of lines in file
        double sales[6350];
        
        //convert serviceCode to int
        service = atoi(tokens[1].c_str());
        //convert invoiceDate to int
        month = atoi(tokens[2].c_str());
        //convert saleAmount to float
        total = atof(tokens[3].c_str());

        answer[month-1][service] += total;
        answer[month-1][SERVICES-1] += total;
        //totals
        answer[MONTHS - 1][service] += total;
    }//while not end of file

    salesOut << "\t\t\t Hotel 2012 Receipt Totals by Month and Service Type" << endl;
    salesOut << "\t\t\t Produced by Mariana Herzog" << endl;
    salesOut << "\t\t\t Date: March 7, 2015" << endl;

    //print rows
    for (int i = 0; i < SERVICES; i++) {
        salesOut << " " << std::setw(18) << services[i];
    }
    salesOut << endl;
    //print columns
    for (int i = 0; i < MONTHS; i++) {
        salesOut << std::setw(5) << months[i];
        //print table body
        for (int j = 0; j < SERVICES; j++) {
            salesOut << std::setw(18) << answer[i][j];
        }
        salesOut << endl;
    }

    //close file
    salesOut.close();
    return 0;
}

