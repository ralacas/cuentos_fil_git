//
//  Letra.cpp
//  cuento_openCv
//
//  Created by Alberto Fernández Casuso on 07/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Letra.h"
void Letra::bajar(){
    _posY += _velY;
}

void Letra::subir(){
    _posY --;
}

void Letra::stop(){
    
}