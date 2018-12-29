#include <iostream>
#include <string.h>

#include "animal.h"
#include "cow.h"
#include "duck.h"
#include "chicken.h"

using namespace std;

#define SIZE_OF_ARR 2
#define MAX_NAME_LEN 50

/*------------------------------------------------------------------------------------*/

void showAnimal(Animal* _animal);

void SetNameFromUserInput(Animal* _animal); 

void SomeChecks();
void InteractiveMain();

/*------------------------------------------------------------------------------------*/

int main() 
{
	
	SomeChecks();
	InteractiveMain();
		
	return 0;
}

/*------------------------------------------------------------------------------------*/

void showAnimal(Animal* _animal)
{
	_animal->Show();
}


/*------------------------------------------------------------------------------------*/

void InteractiveMain()
{

	int animalToCreate;
	Animal* animal = NULL;
	
	while(animal == NULL){
		cout << "which animal do you want to create: (1=cow 2=chicken 3=duck)" << endl;
		cin>> animalToCreate;
		
		switch(animalToCreate) {
			case 1 : animal = Cow::createInstance("para tova"); break;			
			case 2 : animal = Chicken::createInstance("tarnegol gibor"); break;			
			case 3 : animal = Duck::createInstance("barvaz nehmad");  break;
			
			default: return;
		}
	}
	
	int cont = 1;
	int ch = 0;
	
	while(cont) {
		cout << endl;
		cout << "1 - set name" 	<< endl;
		cout << "2 - show" 	<< endl;
		cout << "3 - make sound" 	<< endl;
		cout << "4 - number of animals that have been created from this kind" 	<< endl;
		cout << "5 - number of animals that can be still created from this kind" 	<< endl;
		cout << "Please, choose option: ";
	
		cin >> ch;
		
		switch(ch) {
			case 1 : SetNameFromUserInput(animal)  ; break;			
			case 2 : animal->Show()  ; break;			
			case 3 : animal->MakeSound()  ; break;
			case 4 : cout << animal->getNumOfAnimalsCreated() << endl ; break;
			case 5 : cout << animal->getNumOfAnimalsLeftToCreate() << endl ; break;
			
			default: cont = 0;
		}
	}
	 
	delete animal; 


}

/*------------------------------------------------------------------------------------*/

void SomeChecks(){
	int i=0;

	cout << "-----------------------------COW-----------------------------" << endl;
	Cow* cow = Cow::createInstance("Para Yafa");
	cow->MakeSound();
	
	while(cow){	
		cow->Show();
		delete cow;
		cow = Cow::createInstance("Para Yafa");
	}
	
	cout << "-----------------------------DUCK-----------------------------" << endl;
	Duck* duck = Duck::createInstance("Barvaz Hamud");
	duck->MakeSound();
	duck->Show();
	delete duck;
	
	cout << "----------------------------CHICKEN----------------------------" << endl;
	Chicken* chicken = Chicken::createInstance("Tarnegol Gibor");
	chicken->MakeSound();
	chicken->Show();
	delete chicken;
	cout << "---------------------------------------------------------------" << endl;
	
	
	duck = Duck::createInstance("Barvaz Hamud");
	duck->Show();
	chicken = Chicken::createInstance("Tarnegol Gibor");
	chicken->Show();
	
	bool chk = (*chicken) > (*duck) ; 
	cout << "is chicken greater then duck : " << chk << endl ;
	
	chk = (*duck) >  (*chicken) ; 
	cout << "is duck greater then chicken : " << chk << endl ;
	
	delete duck;
	delete chicken;
	cout << "---------------------------------------------------------------" << endl;
	
	
	cout << "polimorfic example of calling virtual method Show : " << endl ;
	
	chicken = Chicken::createInstance("Tarnegol Gibor");
	chicken->setNumOfEggs(555);
	
	duck = Duck::createInstance("Barvaz Hamud", 777);
	
	Animal* arrOfAnimals[SIZE_OF_ARR];
	arrOfAnimals[0] = chicken;
	arrOfAnimals[1] = duck;
		
	for(i=0; i<SIZE_OF_ARR; i++){
		showAnimal( arrOfAnimals[i] );
	} 
	
	delete duck;
	delete chicken;
	cout << "---------------------------------------------------------------" << endl;
	
	

}

/*------------------------------------------------------------------------------------*/

void SetNameFromUserInput(Animal* _animal){
	char name[MAX_NAME_LEN];
	
	cout << "please enter name : " ;
	cin >> name;
	
	_animal->setName(name);

}

/*------------------------------------------------------------------------------------*/

