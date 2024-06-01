#include <iostream>
#include "mediator.h"
#include "carparts.h"

using namespace std;

int main() {
  // Create a new car.
  Mediator *MyCar = new Mediator();

  // Start the engine.
  MyCar->MyEngine->Start();
  cout << "Engine Started!" << endl;

  // Accelerate.
  MyCar->MyWheels->Accelerate(20);
  cout << "The car is going: " <<
    MyCar->MyWheels->GetSpeed() << endl;

  // Apply the brakes.
  MyCar->MyBrakes->Apply(20);
  cout << "Applying the brakes." << endl;
  cout << "The car is going: " <<
    MyCar->MyWheels->GetSpeed() << endl;

  // Stop the car.
  MyCar->MyBrakes->Apply(80);
  cout << "Applying the brakes." << endl;
  cout << "The car is going: " <<
    MyCar->MyWheels->GetSpeed() << endl;

  // Shut off the engine.
  MyCar->MyEngine->Stop();
  cout << "Engine Stopped" << endl;
  return 0;
}
