#ifndef ATOMO_H
#define ATOMO_H

class Atom {
friend class Ensemble;
friend class PosyVel;
private:
    double coordX_ ;
    double coordY_ ;
    double coordZ_ ;
    double velX_ ;
    double velY_ ;
    double velZ_;
    double mass_ ;
    std::string name_ ;
public:
    Atom();
    Atom(double, double, double,
         double, double, double,
         double, std::string);
    ~Atom();
    void imprimir();
};

#endif 
