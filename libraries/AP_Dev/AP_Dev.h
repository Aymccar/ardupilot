#pragma once 

class Dev {
public: 
    Dev(); //Because we are not registering Dev into the DAL (Device Abstraction Layer) we have to construct the object manually
    void yayFunction();
};
