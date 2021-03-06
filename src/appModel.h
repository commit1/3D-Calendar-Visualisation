/*
 * The model class interface for the visualisation software. 
 * Skeleton code for various methods and accessors on the data
 * model to maintain synchrony of data between classes.
 *
 * Copyright (c) 2015 Sharif UDDIN
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#ifndef APPMODEL_H
#define APPMODEL_H

#include "helper/event.h"
#include "helper/calendar.h"

#include <string>
#include <vector>
using namespace std;


class AppModel {

  public:
    // constructor
    AppModel();

    // methods
    void parseCSV(const char* filePath);
    void parseICS(const char* filePath);
    bool has_suffix(const char *word, const char *suffix); // used to determine file type
    bool has_prefix(const char *word, const char *prefix);
    int compareDateEvent(int day, int month, int year);    // returns index to event_array if the date matches

    // getters
    int getWindowWidth();
    int getWindowHeight();
    float getPosition_x();
    float getPosition_y();
    float getPosition_z();
    float getRotationAngle();
    float getSelected();
    float getSelectedBuff();
    int getSelectedWeek();
    int getSelectedDateIndex(); // <- use to find selected date index
    int getCurrentDateIndex();  // <- use to find todays date index

    int getEventIcon(int index);
    int getEventImportance(int index);
    char* getEventSubject(int index);
    char* getEventStartDate(int index);
    char* getEventStartTime(int index);
    char* getEventEndDate(int index);
    char* getEventEndTime(int index);
    char* getEventLocation(int index);

    int getVisualisationMode();
    bool getPickingMode();
    int getPicked_x();
    int getPicked_y();

    bool getSwapBuffer();

    // setters
    void setWindowSize(int new_width, int new_height);
    void setPosition_x(float new_x);
    void setPosition_y(float new_y);
    void setPosition_z(float new_z);
    void setRotationAngle(float new_angle);

    void setSelected(float new_selected);
    void setSelectedBuff(float new_selected_buff);
    void emptySelectedBuff();
    void setSelectedDateIndex(int new_selected_date);
    void setCurrentDateIndex(int new_current_date);
    void setSelectedWeek(int new_week);

    void setVisualisationMode(int new_mode);
    void setPickingMode(bool value);
    void setPickingLocation(int x, int y);

    void setSwapBuffer(bool value);


  private:
    // variables
    int width, height;
    float position_x, position_y, position_z;   // the camera position
    float angle; // rotation 

    Calendar calendar;

    float selected;
    float selected_buff;
    int selected_date_index;
    int current_date_index;
    int selected_week;

    int mode;                                   // visualisation mode is the chosen mode
    bool pickingMode_enabled;
    int clicked_x, clicked_y;
    bool swapBuffer;

    vector<Event> event_array;  // array holds all events from parsed data file

    // methods
    void trim(std::string &str);   // used to trim extra spaces
    
};

#endif
