#include "../include/fatum/scene.h"
#include "../include/fatum/window.h"
using namespace fatum;
void IScene::switchScene(unsigned int id){
	parent->switchScene(id); 
};