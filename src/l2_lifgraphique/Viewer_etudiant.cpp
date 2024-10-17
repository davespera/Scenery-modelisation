
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

Vector terrainNormal(const Image& im, const int i, const int j) {

    //Calcul de la normale au point (i, j) de l'image
    int ip = i-1;
    int in = i+1;
    int jp = j-1;
    int jn = j+1;

    Point a( ip, im(ip, j).r, j );
    Point b( in, im(in, j).r, j );
    Point c( i, im(i, jp).r, jp );
    Point d( i, im(i, jn).r, jn);

    Vector ab = normalize(b - a);
    Vector cd = normalize(d - c);

    Vector n = cross(ab, cd);

    return n;
}

void ViewerEtudiant::init_terrain(const Image& im) {
    
    m_terrain = Mesh(GL_TRIANGLE_STRIP); 

    for(int i=1; i<im.width()-2; ++i) {
        for(int j=1; j<im.height()-1; ++j) {

            m_terrain.normal( terrainNormal(im, i+1, j) );
            m_terrain.vertex( Point(i+1, 25.f * im(i + 1, j).r, j) );

            m_terrain.normal( terrainNormal(im, i, j) );
            m_terrain.vertex( Point(i, 25.f * im(i, j).r, j) );
        }
        m_terrain.restart_strip();
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

    /// Chargement des textures
    // Image servant de carte de hauteur
    m_terrainAlti = read_image("data/terrain/terrain.png");

    //Création du Mesh
    init_terrain(m_terrainAlti);
    
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

void ViewerEtudiant::draw_plane(const Transform& T)
{
    //gl.debug_normals(0.5);
    //Plane body
    // gl.texture(....);
    Transform Tpb = T * Rotation(Vector(0, 0, 1),  90) * Scale(1,4,1);
    gl.model( Tpb );
    gl.draw(m_sphere);
    //Has to be rotated because sphere is built with circles created along the y axis connected with triangles
    //If you stretch other axis than y you'be stretching the circles, not the triangles, which is what we want

    //Plane motor l
    // gl.texture(....);
    Transform Tml = T * Translation(0,-0.75,-3) * Rotation(Vector(0, 0, 1),  90) * Scale (0.5, 1, 0.5);
    gl.model( Tml );
    gl.draw( m_sphere );

    //Plane motor r
    // gl.texture(....);
    Transform Tmr = T * Translation(0,-0.75,3) * Rotation(Vector(0, 0, 1),  90) * Scale (0.5, 1, 0.5);
    gl.model( Tmr );
    gl.draw( m_sphere );

    //Rotation AFTER scaling (ie scale should be on the rightmost side), if before you rotate the axis but they will be scaled 
    //according to the default xyz axis, not the rotated ones, since all operations are done in the same plane,
    //matrices only serve to explain where unitary vectors (which serve as axis) are located in the default plane

    //Plane wings
    // gl.texture(....);
    Transform Tw = T * Scale (1, 0.2, 5);
    gl.model( Tw );
    gl.draw( m_cube );
    //gl.debug_normals(1); //To debug normals

    //Plane aileron
    // gl.texture(....);
    Transform Ta = T * Translation(2, 1, 0) * Scale(1, 1, 0.25);
    gl.model( Ta );
    gl.draw( m_cone);
    Transform Tch = T * Translation( 2, 1, 0) * Scale (1, 1, 0.25);
    gl.model( Tch );
    gl.draw( m_disque);
}

/*
 * Fonction dans laquelle les appels pour les affichages sont effectues.
 */
void ViewerEtudiant::draw_terrain(const Transform &T) {
    gl.model( T );
    gl.draw( m_terrain );
}

int ViewerEtudiant::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    manageCameraLight();

    gl.camera(m_camera);
    
    
    /// Appel de la fonction render() de la class Viewer
    /// pour que vous voyez apparaitre un premier objet
    /// a supprimer ensuite
    //Viewer::render();
    
    Transform T = Translation (0,0,0);
    Transform Z = Translation (5,0,0);
    /// Appel des fonctions du type 'draw_votreObjet'
    //draw_cube(Translation (0,0,0));
    /*draw_cone(T);
    draw_cylinder(Z);
    draw_sphere(Translation (5,5,0));*/

    draw_plane(Translation (0,0,0));

    draw_terrain(T);
    
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
