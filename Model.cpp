#include "Model.h"
#include "Trainer.h"
#include <iostream>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include <stdlib.h>
 
using namespace std;

Model::Model(){

    time = 0;

    //Initializes various locations for each building object that is created
    Point2D t1Loc(5,1); 
    Point2D t2Loc(10,1);
    Point2D c1Loc(1,20);
    Point2D c2Loc(10,20);
    Point2D g1Loc(0,0);
    Point2D g2Loc(5,5);

    PokemonCenter* C1 = new PokemonCenter(1, 1, 100, c1Loc);
    PokemonCenter* C2 = new PokemonCenter(2, 2, 200, c2Loc);

    center_ptrs[0] = C1;
    center_ptrs[1] = C2;

    PokemonGym* G1 = new PokemonGym(10, 1, 2, 3, 1, g1Loc);
    PokemonGym* G2 = new PokemonGym(20, 5, 7.5, 4, 2, g2Loc);
    
    gym_ptrs[0] = G1;
    gym_ptrs[1] = G2;

    Trainer* T1 = new Trainer("Ash", 1, 'T', 1, t1Loc);
    Trainer* T2 = new Trainer("Misty", 2, 'T', 2, t2Loc);

    trainer_ptrs[0] = T1;
    trainer_ptrs[1] = T2;

    object_ptrs[0] = C1;
    object_ptrs[1] = C2;
    object_ptrs[2] = G1;
    object_ptrs[3] = G2;
    object_ptrs[4] = T1;
    object_ptrs[5] = T2;

    num_objects = 6;
    num_trainers = 2;
    num_centers = 2;
    num_gyms = 2;

    cout << "Model default constructed." << endl;

}


Model::~Model(){
    for (int i = 0; i < num_objects; i++) {
        delete object_ptrs[i];
    }
    cout << "Model destructed." << endl;
}


Trainer* Model::GetTrainerPtr(int id){
    int index = 0;
    for (int i = 0; i < num_trainers ; i++){
        if (trainer_ptrs[i]->GetId() == id)
            index = i;
    }
    return trainer_ptrs[index];
}

PokemonCenter* Model::GetPokemonCenterPtr(int id){
    int index = 0;
    for (int i = 0; i < num_centers ; i++){
        if (center_ptrs[i]->GetId() == id)
            index = i;
    }
    return center_ptrs[index];
}

PokemonGym* Model::GetPokemonGymPtr(int id){
    int index = 0;
    for (int i = 0; i < num_gyms ; i++){
        if (gym_ptrs[i]->GetId() == id)
            index = i;
    }
    return gym_ptrs[index];

}

bool Model::Update(){
    time++;
    int notFaintCount = 0;
    int hasBattles = 0;
    bool objectResult = false;
    bool oneObjTrue = false;

    for (int i = 0; i < num_objects ; i++){
        objectResult = object_ptrs[i]->Update();
        if (objectResult && !oneObjTrue){
            oneObjTrue = true;      //gets return value if one object's update function returns true
        }
        
        if (num_trainers > 0 && i < num_trainers) {
            if (!trainer_ptrs[i]->HasFainted()){
                notFaintCount++;               //increments if a trainer hasn't fainted, so if all are fainted, it = 0
            }
        } 

        if (num_gyms > 0 && i < num_gyms) {
            if (gym_ptrs[i]->GetNumBattlesRemaining() != 0){
                    hasBattles++;            //increments if a gym still has battles, so if there are non, it = 0
            }
        }
    }

    if (hasBattles == 0 ){
        cout << "GAME OVER: You win! All battles done!" << endl;
        exit(EXIT_SUCCESS);
    }

    if (notFaintCount == 0){
        cout << "GAME OVER: You lose! All of your Trainer's pokemon have fainted!" << endl;
        exit(EXIT_SUCCESS);
    }

    return oneObjTrue;
}

void Model::Display(View& view){
    cout << "Time: " << time << endl;
    view.Clear();
    for (int i = 0; i < num_objects; i ++)
        view.Plot(object_ptrs[i]);
    view.Draw();
}


void Model::ShowStatus(){
    cout << "Time: " << time << endl;
    for (int i = 0; i < num_objects ; i++){
        object_ptrs[i]->ShowStatus();
    }
}