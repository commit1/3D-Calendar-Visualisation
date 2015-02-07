#include "appModel.h"
#include <string.h>
#include <stdio.h>
#include <fstream>
using namespace std;

// constructor
AppModel::AppModel() {
  position_z = 0.0;
  mode = 1;
}

// methods
void AppModel::readFile(const char *newFilePath) {
  filePath = newFilePath;
  printf("filepath:%s\n", filePath);
  
  const char *suffix = ".csv";
  bool isCSV = has_suffix(filePath, suffix);
  //printf("has_suffix:%s\n", value?"true":"false"); // testing whether file has suffix .csv else ics

  if(isCSV) {
    parseCSV(); // PARSE CSV FORMAT
  } else {
    parseICS(); // PARSE ICS/iCal FORMAT
  }

}

void AppModel::parseCSV() {
  ifstream infile;
  infile.open(filePath);
  char line[256];
  
  while (infile) {
    infile.getline(line, 256);
    // PROCESS LINE
    if(infile) printf("%s\n", line);
  }

  infile.close();

}

void AppModel::parseICS() { 
  ifstream infile;
  infile.open(filePath);
  char line[256];
  
  while (infile) {
    infile.getline(line, 256);
    // PROCESS LINE
    if(infile) printf("%s\n", line);
  }

  infile.close();
}



// getter
float AppModel::getPosition_z() {
  return position_z;
}

int AppModel::getVisualisationMode() {
  return mode;
}

// setter
void AppModel::setPosition_z(float new_z) {
  position_z = new_z;
}

void AppModel::setVisualisationMode(int new_mode) {
  mode = new_mode;
}

bool AppModel::has_suffix(const char *str, const char *suffix) {
  bool value = false;
  int suff_size = strlen(suffix);
  int str_size = strlen(str);  

  bool check_1 = false;
  bool check_2 = false;

  // minimal comparison, file name must be atleast the size of its extension name
  if(str_size >= suff_size) { check_1 = true; }  
  // comparison of ending substring, if correct file type
  if(strcmp(str + str_size - suff_size, suffix) == 0) { check_2 = true; }  
  // both cases must be true
  if(check_1 && check_2) {
    value = true;
  }

  return value;
}
