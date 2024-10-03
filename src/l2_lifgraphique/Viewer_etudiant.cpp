
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "draw.h"        // pour dessiner du point de vue d'une camera
#include "Viewer_etudiant.h"

using namespace std;





/*
 * Exemple de definition de fonction permettant la creation du Mesh de votre Objet.
 */
void ViewerEtudiant::init_cube()
{

    m_cube = Mesh(GL_TRIANGLE_STRIP);
    static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };
    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };

    for (int i=0; i<6; i++) // i = numéro de la face
    {
        // La normale à la face
        m_cube.normal(n[i][0], n[i][1], n[i][2]);
        // Les 4 sommets de la face
        m_cube.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );
        m_cube.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );
        m_cube.vertex( pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );
        m_cube.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );
        m_cube.restart_strip(); // Demande un nouveau strip
    }
}

void ViewerEtudiant::init_cone()
{
    // Variation de l’angle de 0 à 2𝝿
    const int div = 25;
    float alpha;
    float step = 2.0 * M_PI / (div);
    // Choix de la primitive OpenGL
    m_cone = Mesh(GL_TRIANGLE_STRIP);
    for (int i=0;i<=div;++i) {
    alpha = i * step; // Angle varie de 0 à 2𝝿
    m_cone.normal(Vector(cos(alpha)/sqrtf(2.f), 0, sin(alpha)/sqrtf(2.f)));
    m_cone.vertex(Point(cos(alpha), 0, sin(alpha)));
    m_cone.normal(Vector(cos(alpha)/sqrtf(2.f), 1.f/sqrtf(2.f), sin(alpha)/sqrtf(2.f)));
    m_cone.vertex(Point(0, 1, 0));
    }
}

void ViewerEtudiant::init_disque()
{
// Variation de l’angle de 0 à 2𝝿
const int div = 25;
float alpha;
float step = 2.0 * M_PI / (div);
// Choix primitive OpenGL
m_disque = Mesh( GL_TRIANGLE_FAN );
m_disque.normal( Vector(0,1,0) ); // Normale à la surface
m_disque.vertex( Point(0,0,0) ); // Point du centre du disque
// Variation de l’angle de 0 à 2𝝿
for (int i=0; i<=div; ++i)
{
alpha = i * step;
m_disque.normal( Vector(0,1,0) );
m_disque.vertex( Point(cos(alpha), 0, sin(alpha)) );
}
}

void ViewerEtudiant::init_sphere()
{
    // Variation des angles alpha et beta
    const int divBeta = 16;
    const int divAlpha = divBeta/2;
    int i,j;
    float beta, alpha, alpha2;
    // Choix de la primitive OpenGL
    m_sphere = Mesh(GL_TRIANGLE_STRIP);
    // Variation des angles alpha et beta
    for(int i=0; i < divAlpha; ++i)
    {
    alpha = -0.5f * M_PI + float(i) * M_PI / divAlpha;
    alpha2 = -0.5f * M_PI + float(i+1) * M_PI / divAlpha;
    for(int j = 0; j <= divBeta; ++j)
    {
    beta = float(j) * 2.f * M_PI / (divBeta);
    m_sphere.normal( Vector(cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)) );
    m_sphere.vertex( Point(cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)) );
    m_sphere.normal( Vector(cos(alpha2) * cos(beta), sin(alpha2), cos(alpha2) * sin(beta)));
    m_sphere.vertex( Point(cos(alpha2) * cos(beta), sin(alpha2), cos(alpha2) * sin(beta)) );
    } // boucle sur les j, angle beta, dessin des sommets d’un cercle
    m_sphere.restart_strip(); // Demande un nouveau strip
    } // boucle sur les i, angle alpha, sphère = superposition de cercles
}


void ViewerEtudiant::init_cylinder()
{
    const int div = 25;  // Number of divisions for the cylinder
    float alpha;         // Angle in radians
    float step = 2.0f * M_PI / div; // Step size for each division in radians

    // Initialize the mesh for the cylinder, starting with the side
    m_cylinder = Mesh(GL_TRIANGLE_STRIP);
    
    // Create the side surface of the cylinder
    for (int i = 0; i <= div; ++i)
    {
        alpha = i * step;
        
        // Normal vector for smooth shading
        Vector normal(cos(alpha), 0, sin(alpha));
        
        // Add bottom and top vertices at this angle
        m_cylinder.normal(normal);
        m_cylinder.vertex(Point(cos(alpha), -1, sin(alpha)));
        
        m_cylinder.normal(normal);
        m_cylinder.vertex(Point(cos(alpha), 1, sin(alpha)));
    }

}

void ViewerEtudiant::init_plane_body() {
    // Variation des angles alpha et beta
    const int divBeta = 16;
    const int divAlpha = divBeta/2;
    int i,j;
    float beta, alpha, alpha2;
    // Choix de la primitive OpenGL
    m_plane_body = Mesh(GL_TRIANGLE_STRIP);
    // Variation des angles alpha et beta
    for(int i=0; i < divAlpha; ++i)
    {
    alpha = -0.5f * M_PI + float(i) * M_PI / divAlpha;
    alpha2 = -0.5f * M_PI + float(i+1) * M_PI / divAlpha;
    for(int j = 0; j <= divBeta; ++j)
    {
    beta = float(j) * 2.f * M_PI / (divBeta);
    m_plane_body.normal( Vector(5 * cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)) );
    m_plane_body.vertex( Point(5 * cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)) );
    m_plane_body.normal( Vector(5 * cos(alpha2) * cos(beta), sin(alpha2), cos(alpha2) * sin(beta)));
    m_plane_body.vertex( Point(5 * cos(alpha2) * cos(beta), sin(alpha2), cos(alpha2) * sin(beta)) );
    } // boucle sur les j, angle beta, dessin des sommets d’un cercle
    m_plane_body.restart_strip(); // Demande un nouveau strip
    } // boucle sur les i, angle alpha, sphère = superposition de cercles
}

void ViewerEtudiant::init_plane_wings()
{

    m_plane_wings = Mesh(GL_TRIANGLE_STRIP);
    static float pt[8][3] = { {-1,-0.2,-5}, {1,-0.2,-5}, {1,-0.2,5}, {-1,-0.2, 5}, {-1,0.2,-5}, {1,0.2,-5}, {1,0.2,5}, {-1,0.2,5} };
    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };

    for (int i=0; i<6; i++) // i = numéro de la face
    {
        // La normale à la face
        m_plane_wings.normal(n[i][0], n[i][1], n[i][2]);
        // Les 4 sommets de la face
        m_plane_wings.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );
        m_plane_wings.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );
        m_plane_wings.vertex( pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );
        m_plane_wings.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );
        m_plane_wings.restart_strip(); // Demande un nouveau strip
    }
}

void ViewerEtudiant::init_plane_aileron()
{
        // Variation de l’angle de 0 à 2𝝿
    const int div = 25;
    float alpha;
    float step = 2.0 * M_PI / (div);
    // Choix de la primitive OpenGL
    m_plane_aileron = Mesh(GL_TRIANGLE_STRIP);
    for (int i=0;i<=div;++i) {
    alpha = i * step; // Angle varie de 0 à 2𝝿
    m_plane_aileron.normal(Vector(cos(alpha)/sqrtf(2.f), 0, 0.5 * sin(alpha)/sqrtf(2.f)));
    m_plane_aileron.vertex(Point(cos(alpha), 0, 0.5 * sin(alpha)));
    m_plane_aileron.normal(Vector(cos(alpha)/sqrtf(2.f), 1.f/sqrtf(2.f), sin(alpha)/sqrtf(2.f)));
    m_plane_aileron.vertex(Point(0, 1, 0));
    }
}







int ViewerEtudiant::init()
{
    Viewer::init();
    
    m_camera.lookat( Point(0,0,0), 150 );
    
    
    /// Appel des fonctions init_votreObjet pour creer les Mesh
    
    init_cube();
    init_cone();
    init_sphere();
    init_cylinder();
    init_disque();
    
    init_plane_body();
    init_plane_wings();
    init_plane_aileron();

    /// Chargement des textures
    
    
    return 0;
}



/*
 * Exemple de definition de fonction permettant l affichage
 * de 'votreObjet' subissant la Transform T
 */
void ViewerEtudiant::draw_cube(const Transform& T)
{
// gl.texture(....);
 gl.model( T );
 gl.draw( m_cube);
 //gl.debug_normals(1); //To debug normals
}

void ViewerEtudiant::draw_cone(const Transform& T)
{
// gl.texture(....);
    gl.model( T );
    gl.draw( m_cone);
    Transform Tch = T * Translation( 0, 0, 0);
    gl.model( Tch );
    gl.draw( m_disque);
}

void ViewerEtudiant::draw_sphere(const Transform& T)
{
// gl.texture(....);
 gl.model( T );
 gl.draw( m_sphere);
}

void ViewerEtudiant::draw_cylinder(const Transform& T)
{
// gl.texture(....);
 gl.model( T );
 gl.draw( m_cylinder);

 Transform Tch = T * Translation( 0, -1, 0);
gl.model( Tch );
gl.draw( m_disque);

Transform Tcb = T * Translation( 0, 1, 0)
* Rotation( Vector(1,0,0), 180);
gl.model( Tcb );
gl.draw( m_disque);
}

void ViewerEtudiant::draw_plane_body(const Transform& T)
{
// gl.texture(....);
 gl.model( T );
 gl.draw( m_plane_body );
}

void ViewerEtudiant::draw_plane_wings(const Transform& T)
{
// gl.texture(....);
 gl.model( T );
 gl.draw( m_plane_wings);
 //gl.debug_normals(1); //To debug normals
}

void ViewerEtudiant::draw_plane_aileron(const Transform& T)
{
// gl.texture(....);
    gl.model( T );
    gl.draw( m_plane_aileron);
    Transform Tch = T * Translation( 0, 0, 0);
    gl.model( Tch );
    gl.draw( m_disque);
}
/*
 * Fonction dans laquelle les appels pour les affichages sont effectues.
 */
int ViewerEtudiant::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    manageCameraLight();

    gl.camera(m_camera);
    
    
    /// Appel de la fonction render() de la class Viewer
    /// pour que vous voyez apparaitre un premier objet
    /// a supprimer ensuite
    //Viewer::render();
    
    Transform T = Translation (1,0,10);
    Transform Z = Translation (5,0,0);
    /// Appel des fonctions du type 'draw_votreObjet'
    //draw_cube(Translation (0,0,0));
    /*draw_cone(T);
    draw_cylinder(Z);
    draw_sphere(Translation (5,5,0));*/

    draw_plane_body(Translation (0,0,0));
    draw_plane_wings(Translation (0,0,0));
    draw_plane_aileron(Translation (2,1,0));
    
    return 1;
    
}


/*
 * Fonction dans laquelle les mises a jours sont effectuees.
 */
int ViewerEtudiant::update( const float time, const float delta )
{
    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.
    
    
    
    return 0;
}


/*
 * Constructeur.
 */

ViewerEtudiant::ViewerEtudiant() : Viewer()
{
}


/*
 * Programme principal.
 */
int main( int argc, char **argv )
{
    ViewerEtudiant v;
    v.run();
    return 0;
}
