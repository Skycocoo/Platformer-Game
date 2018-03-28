// Yuxi Luo (yl4217), March 27, 2018
// CS3113 Game Programming

#ifndef DynamicObj_hpp
#define DynamicObj_hpp

#include "Object.h"

class DynamicObj: public Object{
public:

    DynamicObj();
    DynamicObj(GLuint texture, const glm::vec3& pos = glm::vec3(0, 0, 0), const glm::vec3& velo = glm::vec3(0, 0, 0));

    void update(float elapsed);
    void render(const Matrix& view);

    void updateVelo(float elapsed);
    bool collide(float elapsed, const Object& rhs);

protected:
    // should set float or else it would set to garbage value
    glm::vec3 velo;
    glm::vec3 acce;

    glm::vec3 fric;
    glm::vec3 grav;

    // linear interpolation
    void lerp(glm::vec3& orig, const glm::vec3& prop, const glm::vec3& tar = glm::vec3(0, 0, 0)) const;

};

#endif /* DynamicObj_hpp */
