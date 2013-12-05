/*
 * main.cpp
 *
 *  Created on: 22/11/2013
 *      Author: iago
 */
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "StringTokenizer.h"
#include <map>

using namespace std;
typedef unsigned char byte;

bool contains(string key, map<string, byte> mymap) {
	map<string, byte>::iterator it = mymap.find(key);
	if (it == mymap.end()) {
		return false;
	}
	return true;
}


int main(int argc, char* argv[]) {
	int datasize = 0;
	unsigned int featuresSize = 0;
	unsigned int featurePos = 0;
	unsigned int i = 0;
	string line;
	string token;
	byte data;
	vector<byte> lastCategory; //Cuantas categorias tiene cada feature.
	vector<map<string, byte> > translationsVector; //Vector de mapas de traduccion
	map<string, byte> translations; //mapa de traduccion string->byte ara cada feature

//Parse console arguments.
	if (argc < 2) {
		cout << argv[0] << "\n";
		cout << argv[1] << "\n";
		printf("Usage: <inputfilename> [options]\n");
		exit(-1);
	}

	char* inputFilename = argv[1];

	ifstream inputFile(inputFilename);
	ofstream outputFile("data.mrmr", ios::out | ios::binary);

//Count lines and features.
	if (inputFile.is_open()) {
		//Ignore first line (headers from csv)
		getline(inputFile, line);
		StringTokenizer strtk(line, ",");
		while (strtk.hasMoreTokens()) {
			token = strtk.nextToken();
			featuresSize++;
		}
		while (getline(inputFile, line)) {
			++datasize;
		}

//Print lines and features
		cout << "Number of samples  in csv file: " << datasize  << "\n";
		cout << "Number of features in csv file: " << featuresSize << "\n";

//write datasize and featuresize:
		outputFile.write(reinterpret_cast<char*>(&datasize), sizeof(datasize));
		outputFile.write(reinterpret_cast<char*>(&featuresSize),
				sizeof(featuresSize));

//Set pointer into beginning of the file.
		inputFile.clear();
		inputFile.seekg(0, inputFile.beg);

//Initialize translation map.
		for (i = 0; i <= featuresSize; ++i) {
			map<string, byte> map;
			translationsVector.push_back(map);
			lastCategory.push_back(0);
		}

		//Ignore first line (headers from csv)
		getline(inputFile, line);

//Read and translate file to binary.
		while (getline(inputFile, line)) {
			featurePos = 0;
			StringTokenizer strtk(line, ",");
			while (strtk.hasMoreTokens()) {
				token = strtk.nextToken();
				featurePos++;
				if (!contains(token, translationsVector[featurePos])) {
					translationsVector[featurePos][token] =
							lastCategory[featurePos];
					lastCategory[featurePos]++;
				}
				data = translationsVector[featurePos][token];
				outputFile.write(reinterpret_cast<char*>(&data), sizeof(byte)); //TODO: Guardar en un buffer los bytes de la linea y escribir linea a linea.
			}
		}
		cout << "ALL OK \n";
		outputFile.flush();
		outputFile.close();
		inputFile.close();
	} else {
		cout << "Error loading file.\n";
		exit(-1);
	}
	return 0;

}
