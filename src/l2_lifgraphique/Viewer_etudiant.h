
#ifndef VIEWER_ETUDIANT_H
#define VIEWER_ETUDIANT_H

#include "Viewer.h"
#include <vector>

class ViewerEtudiant : public Viewer
{
public:
    ViewerEtudiant();

    int init();
    int render();
    int update( const float time, const float delta );

protected:
    
    /* -----------------------------------------
     Pour creer un nouvel objet vous devez :
     
     1. declarer ici dans le fichier Viewer_etudiant.h
     le Mesh,
     la texture si besoin,
     une fonction 'init_votreObjet'
     une fonction 'draw_votreObjet(const Transform& T)'
     
     --- Rq : regarder comment cela est effectue dans le fichier Viewer.h
     
     
     2. Appeler la fonction 'init_votreObjet' dans la fonction 'init' du Viewer_etudiant.cpp
     --- Rq : regarder comment cela est effectue dans le fichier Viewer.cpp
     
     
     3. Appeler la fonction 'draw_votreObjet' dans la fonction 'render' du Viewer_etudiant.cpp
     --- Rq : regarder comment cela est effectue dans le fichier Viewer.cpp
     
      ----------------------------------------- */
    
    
    /// Declaration des Mesh

    Mesh m_cube;
    Mesh m_quad;
    Mesh m_quad_anim;
    Mesh m_cylinder;
    Mesh m_sphere;
    Mesh m_cone;
    Mesh m_disque;
    Mesh m_plane_body;
    Mesh m_terrain;
    Mesh m_cubemap;

    /// Declaration des Textures
    GLuint math_texture;
    GLuint papillon_texture;
    GLuint monde_texture;
    GLuint tree_texture;
    GLuint cubemap_texture;
    GLuint fire_texture;
    GLuint m_terrainTexture;
    GLuint sun_texture;

    Image m_terrainAlti;

    Transform m_Tplane;

    /// Declaration des fonction de creation de Mesh du type init_votreObjet()

    void init_cube(); 
    void init_quad();
    void init_quad_anim();
    void init_sphere();
    void init_cone();
    void init_cylinder();
    void init_disque();
    void init_plane_body();
    void init_terrain(const Image& im);
    void init_cubemap();
 
    /// Declaration des fonctions draw_votreObjet(const Transform& T)

    void draw_cube(const Transform & T);
    void draw_sphere(const Transform & T);
    void draw_cylinder(const Transform & T);
    void draw_cone(const Transform & T);
    void draw_plane(const Transform & T);
    void draw_terrain(const Transform &T);
    void draw_tree(const Transform &T);
    void draw_multitrees(const Transform &T, const Image& im);
    void draw_cubemap(const Transform &T);
    void draw_fire(const Transform &T);
    void draw_sun(const Transform &T);
};

#endif