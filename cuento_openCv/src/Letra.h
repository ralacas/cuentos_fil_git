//
//  Letra.h
//  cuento_openCv
//
//  Created by Alberto Fernández Casuso on 07/06/12.
//  Copyright (c) 2012 Perros y gatos en una caja. All rights reserved.
//

#ifndef cuento_openCv_Letra_h
#define cuento_openCv_Letra_h
#include <iostream>
#include "ofMain.h"

class Letra{
public:
    
    int posX;
    int posY;
    float velX;
    float velY;
    char letra;
    
    //Constructor & destructor
    Letra(){};
    ~Letra();
    
    //Mueve la letra
    void bajar();
    void subir();
    
    //Para la letra
    void stop();
};


#endif
