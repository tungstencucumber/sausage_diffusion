#ifndef DIFFUSION_GRAPHICS_ENGINE_DRAWABLEPARTICLE_H
#define DIFFUSION_GRAPHICS_ENGINE_DRAWABLEPARTICLE_H

#include "Circle.h"
#include "Particle.h"

class DrawableParticle: public Circle, public Particle {
public:
    DrawableParticle(double m, double r, Vector2D &_x, Vector2D &_v);

    void update(double dt, sf::RenderWindow &w);

    void setLoc(const Vector2D &_loc);
};


#endif //DIFFUSION_GRAPHICS_ENGINE_DRAWABLEPARTICLE_H
