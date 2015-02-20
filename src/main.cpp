#include "appModel.h"
#include "appView.h"
#include "appController.h"
#include "helper/visualisation.h"
#include "helper/assetloader.h"

#include <GL/glut.h>


int main(int argc, char **argv) {
  // init assetloader
  //AssetLoader *assetLoader;

  // MVC architecture
  AppModel *appModel = new AppModel();

  Visualisation *visualisation = new Visualisation(appModel);
  AppController *appController = new AppController(appModel);
  AppView *appView = new AppView(appController, appModel, visualisation);

  // open file dialog and read selected calendar data file
  appView->openfileDialogBox();
  
  // initialise window
  const char *title = "3D Calendar Visualisation";
  appView->setWindowSize(800,600);
  appView->setWindowTitle(title);
  appView->start(argc, argv);

  return 0;
}
