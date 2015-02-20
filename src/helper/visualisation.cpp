#include "visualisation.h"
#include "../../lib/drawtext/text3d.h"

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <cmath>


Visualisation::Visualisation(AppModel *newAppModel) {
  appModel = newAppModel;
  mode = 1;
  prototype_name = new char[64];
  getPrototypeName();
  tile_dimension = 0.5f;
  init();
}

void Visualisation::init() {
  // this week from monday
  int total_weeks = 10;
  int upper_limit = 7*total_weeks; // 6 weeks in front

  int week = 0;
  int weekday = calendar.getWeekDay();
//  int today = calendar.getDay();
    
  int offset = 1-weekday; // where monday starts from 1, since 0 is not the initial state
  weekday = 1;
  char date_buff[32];
  
  for(int i=0; i<upper_limit; i++) {
    sprintf(date_buff, "%s", calendar.getDate(offset));
    int day = calendar.parseDay(date_buff);
    aDay aday;
    aday.week = week;
    aday.weekday = weekday;
    aday.day = day;

    days.push_back(aday); // push back
    
    offset++;
    weekday+=1;
    
    if((i+1)%7 == 0) { week++; weekday = 1; }
  }

  // fix offeset from today for visualisation
  weekday = calendar.getWeekDay();
  printf("weekday:%d\n", weekday);
  appModel->setSelectedBuff(-weekday+1.0);

}

void Visualisation::draw(int frame) {

  smooth_selection(frame);

  switch(mode) {
    case 1:
      prototype_1();
      break;
    case 2:
      prototype_2();
      break;
    case 3:
      prototype_3();
      break;
    case 4:
      prototype_4();
      break;
    case 5:
      prototype_5();
      break;
    default:
      break;  
  } 

}

void Visualisation::drawTile(int weekday, int day) {
  // init 3dtext
  t3dInit();

  char *buff = new char[4];
  snprintf(buff, 4, "%d", day);

  glColor3f(1.0,1.0,1.0);
  glutSolidCube(tile_dimension);

  glPushMatrix();
    glColor3f(0.8,0.2,0.2);
    glScalef(0.1, 0.6, 0.1);
    glTranslatef(0.0, 0.5, 0.0);    
    drawText(buff);
  glPopMatrix();

  
}

void Visualisation::drawText(const char* text) {
  float text_scale;
  text_scale = computeScale(text);

  glPushMatrix();
  glScalef(text_scale, text_scale, text_scale);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	t3dDraw3D(text, 0.0, 0.0, 0.2);
	glPopMatrix();

}

float Visualisation::computeScale(const char* text) {
	float maxWidth = 0.0;
  float maxHeight = 0.0;
  float maxScale = 0.0;
	float width = t3dDrawWidth(text);
  float height = t3dDrawHeight(text);
	if (width > maxWidth) {
		maxWidth = width;
  }
  if (height > maxHeight) {
    maxHeight = height;   
  }

  if (maxHeight > maxWidth) {
    maxScale = maxHeight;
  } else {
    maxScale = maxWidth;
  }

	return 2.6f / maxScale;
}

// getters
char* Visualisation::getPrototypeName() {
  switch(mode) {
    case 1: 
      strcpy(prototype_name, "Prototype 1: Curved Perspective view");
      name_length = strlen(prototype_name);
      break;
    case 2: 
      strcpy(prototype_name, "Prototype 2: Flat Perspective view");
      name_length = strlen(prototype_name);
      break;
    case 3:
      strcpy(prototype_name, "Prototype 3: Time Tunnel view");
      name_length = strlen(prototype_name);
      break;
    case 4:
      strcpy(prototype_name, "Prototype 4: 3D Lexis Pencil");
      name_length = strlen(prototype_name);
      break;
    case 5:
      strcpy(prototype_name, "Prototype 5: 3D Fibonacci Spiral");
      name_length = strlen(prototype_name);
      break;
    default:
      break;
  }  
  return prototype_name;
}

int Visualisation::getPrototypeNameLen() {
  return name_length;
}

// setters
void Visualisation::setPrototype(int newMode) {
  mode = newMode;
}


// PROTOTYPE FOR VISUALISATIONS
void Visualisation::prototype_1() {

  selected = appModel->getSelected();

  glPushMatrix();
    glTranslatef(0, -1.25, -2.5);
    glRotatef(20.0, 1.0, 0.0,0.0);

//    // tile -1
//    glPushMatrix();
//      glColor3f(1.0,1.0,1.0);
//      prototype_1_curve(-1.0+selected);
//      glScalef(2.0, 0.1, 2.0);
//      drawTile(1, 5);      
//    glPopMatrix();

//    // tile 0
//    glPushMatrix();
//      glColor3f(1.0,1.0,1.0);
//      prototype_1_curve(0.0+selected);
//      glScalef(2.0, 0.1, 2.0);
//      drawTile(1, 6);      
//    glPopMatrix();

//    // tile 1
//    glPushMatrix();
//      glColor3f(1.0,1.0,1.0);
//      prototype_1_curve(1.0+selected);
//      glScalef(2.0, 0.1, 2.0);
//      drawTile(1, 7);      
//    glPopMatrix();


    // DRAWS ALL DAYS CREATED IN INIT FUNCTION
    int week, weekday, day;

    for(unsigned int i=0; i<days.size(); i++) {
      week = days[i].week;
      weekday = days[i].weekday;
      day = days[i].day;
      glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        prototype_1_curve(i+selected);
        glScalef(2.0, 0.1, 2.0);
        drawTile(week, day);   
      glPopMatrix();
    }


  glPopMatrix();

}

void Visualisation::prototype_2() {
  // prototype_2: Flat perspective view
  scale = 0.9;
  gap = 1.0-scale;
  float center = -(tile_dimension+gap)*4.0;
//  float center = (0.5*tile_dimension) -(tile_dimension)*(7.0*0.5f) -gap*(7.0*0.5f);
  

  // DRAW GRID
  glPushMatrix();
    glTranslatef(center,-1.25, -3.75);
    glRotatef(10.0, 1.0, 0.0,0.0);

    // DRAWS ALL DAYS CREATED IN INIT FUNCTION
    int week, weekday, day;

    for(unsigned int i=0; i<days.size(); i++) {
      week = days[i].week;
      weekday = days[i].weekday;
      day = days[i].day;
      prototype_2_drawTile(week, weekday, day);
    }

  glPopMatrix();
}

void Visualisation::prototype_3() { 
  // prototype_3: Time tunnel view
  int segments = 7;
  float radius = 0.3;
  //float height = 0.3;

  // guide lines
  for (float i = 0.0; i < segments; i += 1.0) {
    float angle = M_PI * i * 2.0 / segments ;
    float nextAngle = M_PI * (i + 1.0) * 2.0 / segments;

    /* compute sin & cosine */
    float x1 = radius * sin(angle), y1 = radius * cos(angle);
    float x2 = radius * sin(nextAngle), y2 = radius * cos(nextAngle);

    glBegin(GL_LINE_LOOP);

      glColor3f(1.0,1.0,1.0);
      
      // near
      glVertex3f(x1, y1, -1.0);
      glVertex3f(x2, y2, -1.0);
      glVertex3f(0, 0, -1.0);

      // far
      glVertex3f(x1, y1, -25.0);
      glVertex3f(x2, y2, -25.0);
      glVertex3f(0, 0, -25.0);

    glEnd();
   }

  // points
  glPointSize(10.0f);
  glBegin(GL_POINTS);
  for (float i = 0.0; i < segments+1; i += 1.0) {
    float angle = M_PI * i * 2.0 / segments ;
    float nextAngle = M_PI * (i + 1.0) * 2.0 / segments;

    /* compute sin & cosine */
    float x1 = radius * sin(angle), y1 = radius * cos(angle);
    float x2 = radius * sin(nextAngle), y2 = radius * cos(nextAngle);

    glColor3f(1.0,0.0,0.0);
      
    // near
    //glVertex3f(x1, y1, -1.0);
    //glVertex3f(x2, y2, -1.0);

    // mid point
    glVertex3f((x1+x2)*0.5, (y1+y2)*0.5, -1.0);
   
  }
  glEnd();

}

void Visualisation::prototype_4() { 
  // prototype_4: Lexis Pencil
  // draw 3d text
  t3dInit();

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);
    const char* word_1 = "SHARIF HERE!";
    drawText(word_1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0f, -0.2f, -8.0f);
    const char* word_2 = "FRIDAY";
    drawText(word_2);
  glPopMatrix();

}

void Visualisation::prototype_5() {
  // prototype_5: Fibonacci spiral view
  float rotations = 5; //How many times the spiral rotates around until it stops.
  float theta, nextTheta;
  float epsilon = 0.1f * 2.0f * M_PI;
  float x1, y1, z1;
  float x2, y2, z2;


  glBegin(GL_LINES);
  for(theta = 0.0f; theta < rotations * 2.0f * M_PI; theta += epsilon) {
    x1 = sin(theta) * theta;
    y1 = cos(theta) * theta;
    z1 = theta;

    nextTheta = theta+epsilon;    
    x2 = sin(nextTheta) * nextTheta;
    y2 = cos(nextTheta) * nextTheta;
    z2 = nextTheta;

    glVertex3f(x1,y1,z1-10);
    glVertex3f(x2,y2,z2-10);

  }
  glEnd();
}

void Visualisation::prototype_1_curve(float index) {
  // place on curve 
  float z = (index+1.0)*(-1.5); // adjustment
  float far = -5.0;
  float range = far - 0.0;
  float tmp;
  float spacing;

  if(z > far && z < 0) {
    tmp = (far-z)/range;
    //printf("angled %f:%f\n", z,tmp);  
    spacing = 0.1;
    glTranslatef(0.0, -spacing*z, z);
    glRotatef(tmp*90.0+10.0, 1.0,0.0,0.0);
  } else if (z <= far) {
    //printf("flat top %f:%f\n", z, 0.0);
    spacing = 0.1;
    glTranslatef(0.0, -spacing*z, z);
    glRotatef(10.0, 1.0,0.0,0.0);
  } else if (z >= 0) {
    //printf("facing screen %f:%f\n", z, 1.0);
    spacing = 0.5;
    glTranslatef(0.0, (-spacing*z)-(z*0.25), 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
  }


}

void Visualisation::prototype_2_drawTile(int week, int weekday, int day) {
  glPushMatrix();
    glColor3f(1.0,1.0,1.0);    
    glTranslatef(weekday*tile_dimension+gap*weekday,0,-week*tile_dimension+gap*-week);
    glScalef(1.0, 0.05, 1.0);
    drawTile(weekday, day);
  glPopMatrix();
}

void Visualisation::smooth_selection(int frame) {
  // smooth selection animation
  float tmp = appModel->getSelected();
  float selected_buff = appModel->getSelectedBuff();

  // removes stutter
  if(selected_buff<=0.01 && selected_buff >= -0.01) {
    appModel->emptySelectedBuff();
  }

  // adds sliding animation
  if(selected_buff != 0) {
    if(frame%2==0) {
      if(selected_buff>0) {
        tmp+=0.05;
        appModel->setSelectedBuff(-0.05);
        appModel->setSelected(tmp);
      } else if(selected_buff<0) {
        tmp-=0.05;
        appModel->setSelectedBuff(0.05);
        appModel->setSelected(tmp);        
      }
    }
  }

}
