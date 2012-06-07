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
private:
    int _posX;
    int _posY;
    float _velX;
    float _velY;
    char _letra;
public:
    //Constructor setea la letra al ser creado.
    Letra(char letra){
        _letra = letra;
    }
    //Funcion que retorna la letra
    char retLetra(){return _letra;};
    
    //Setea las posiciones
    void setPosX (int posX){_posX = posX;};
    void setPosY (int posY){_posY = posY;};
    
    //Retorna las posiciones
    int retPosX(){return _posX;};
    int retPosY(){return _posY;};
    
    //Setea las velocidades
    void setVelX (float velX){_velX = velX;};
    void setVelY (float velY){_velY = velY;};
    
    //Retorna las velocidades
    float retVelX(){return _velX;};
    float retVelY(){return _velY;};
    
    //Setea la letra despues de crear el objeto
    void setLetra(char letra){_letra = letra;};
    
    //Mueve la letra
    void bajar();
    void subir();
    
    //Para la letra
    void stop();
};


#endif
