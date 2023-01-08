#ifndef MODEL_H
#define MODEL_H

#include "Model.h"
#include "Trainer.h"
#include <iostream>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include <stdlib.h>
 
using namespace std;

class Model {
    private:
        int time;
        GameObject* object_ptrs[10];
        int num_objects;
        Trainer * trainer_ptrs[10];
        int num_trainers;
        PokemonCenter * center_ptrs[10];
        int num_centers;
        PokemonGym * gym_ptrs[10];
        int num_gyms;

    public:
        Model();
        ~Model();
        Trainer * GetTrainerPtr(int id);
        PokemonCenter * GetPokemonCenterPtr(int id);
        PokemonGym * GetPokemonGymPtr(int id);
        bool Update();
        void Display(View& view);
        void ShowStatus();

};


#endif