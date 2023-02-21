#include "main.h"
pros::ADIDigitalOut endgameRight('E');
pros::ADIDigitalOut endgameLeft('F');
pros::ADIDigitalOut endgameLock('A');

void endgameShoot(){
    endgameRight.set_value(true);
    endgameLeft.set_value(true);
}
void endgameShoot2(){
    endgameRight.set_value(false);
    endgameLeft.set_value(false);
}

bool endgame = false;
bool endgameLocker = false;


void endgameButton(){
    if(master.get_digital_new_press(DIGITAL_RIGHT)){
        endgame = !endgame;
        
        endgameRight.set_value(endgame);
        endgameLeft.set_value(endgame);


  }

}