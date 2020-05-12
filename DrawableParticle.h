#ifndef DIFFUSION_GRAPHICS_ENGINE_DRAWABLEPARTICLE_H
#define DIFFUSION_GRAPHICS_ENGINE_DRAWABLEPARTICLE_H

#include "Circle.h"
#include "particle.h"

class DrawableParticle: public Circle, public Particle {
public:
    DrawableParticle(double m, double r, double* _x, double* _v);

    void update(double dt, sf::RenderWindow &w);

    void setLoc(const Vector2D &_loc);
};


#endif //DIFFUSION_GRAPHICS_ENGINE_DRAWABLEPARTICLE_H
