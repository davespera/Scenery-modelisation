
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>


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
    static int f[6][4] = { {0,1,3,2}, {5,4,6,7}, {2,1,6,5}, {0,3,4,7}, {3,2,7,6}, {1,0,5,4} };
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
    static float texcoords[8][2] = {
        {0.0f, 0.0f}, // Vertex 0
        {1.0f, 0.0f}, // Vertex 1
        {1.0f, 1.0f}, // Vertex 2
        {0.0f, 1.0f}, // Vertex 3
        {0.0f, 0.0f}, // Vertex 4
        {1.0f, 0.0f}, // Vertex 5
        {1.0f, 1.0f}, // Vertex 6
        {0.0f, 1.0f}  // Vertex 7
    };

    for (int i=0; i<6; i++) // i = numéro de la face
    {
        // La normale à la face
        m_cube.normal(n[i][0], n[i][1], n[i][2]);
        // Les 4 sommets de la face
        for (int j=0; j<4; j++) {
            int vertexIndex = f[i][j];
            
            m_cube.texcoord(texcoords[vertexIndex][0], texcoords[vertexIndex][1]);
            m_cube.vertex( pt[vertexIndex][0], pt[vertexIndex][1], pt[vertexIndex][2] );
        } 
        m_cube.restart_strip(); // Demande un nouveau strip
    }
}

void ViewerEtudiant::init_quad()
{
    m_quad = Mesh(GL_TRIANGLE_STRIP);
    m_quad.color( Color(1, 1, 1));

    m_quad.normal( 0, 0, 1 );

    m_quad.texcoord( 0, 0 ); // sommet 0
    m_quad.vertex( -1, -1, 0 ); 

    m_quad.texcoord( 1, 0 ); // sommet 1
    m_quad.vertex( 1, -1, 0);

    m_quad.texcoord( 0, 1 ); // sommet 2
    m_quad.vertex( -1, 1, 0 );

    m_quad.texcoord( 1, 1 ); // sommet 3
    m_quad.vertex(1, 1, 0 );
}

void ViewerEtudiant::init_quad_anim()
{
    m_quad_anim = Mesh(GL_TRIANGLE_STRIP);
    m_quad_anim.color( Color(1, 1, 1));

    m_quad_anim.normal( 0, 0, 1 );

    m_quad_anim.texcoord( 0, 0 ); // sommet 0
    m_quad_anim.vertex( -1, -1, 0 ); 

    m_quad_anim.texcoord( 1, 0 ); // sommet 1
    m_quad_anim.vertex( 1, -1, 0);

    m_quad_anim.texcoord( 0, 1 ); // sommet 2
    m_quad_anim.vertex( -1, 1, 0 );

    m_quad_anim.texcoord( 1, 1 ); // sommet 3
    m_quad_anim.vertex(1, 1, 0 );
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
        //circle
        m_cone.texcoord(float(i)/div, 0);
        m_cone.normal(Vector(cos(alpha)/sqrtf(2.f), 0, sin(alpha)/sqrtf(2.f)));
        m_cone.vertex(Point(cos(alpha), 0, sin(alpha)));
        //up
        m_cone.texcoord(float(i)/div, 1);
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

            m_sphere.texcoord( beta / (2.0 * M_PI), 0.5 + (alpha / M_PI) );
            m_sphere.normal( Vector(cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)) );
            m_sphere.vertex( Point(cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)) );

            m_sphere.texcoord( beta / (2.0 * M_PI), 0.5 + (alpha2 / M_PI) );
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
        m_cylinder.texcoord(float(i)/div, 0);
        m_cylinder.normal(normal);
        m_cylinder.vertex(Point(cos(alpha), -1, sin(alpha)));
        
        m_cylinder.texcoord(float(i)/div, 1);
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

            m_terrain.texcoord(float(i+1)/im.width(), float(j)/im.height());
            m_terrain.normal( terrainNormal(im, i+1, j) ); //maybe remove -
            m_terrain.vertex( Point(i+1, 25.f * im(i + 1, j).r, j) );

            m_terrain.texcoord(float(i)/im.width(), float(j)/im.height());
            m_terrain.normal( terrainNormal(im, i, j) );
            m_terrain.vertex( Point(i, 25.f * im(i, j).r, j) );
        }
        m_terrain.restart_strip();
    }
}

void ViewerEtudiant::init_cubemap() 
{
    // Set up primitive type for cubemap mesh
    m_cubemap = Mesh(GL_TRIANGLE_STRIP);

    // Cube vertices (corners)
    static const float vertices[8][3] = {
        {-1, -1, -1}, {1, -1, -1}, {1, -1, 1}, {-1, -1, 1},
        {-1, 1, -1}, {1, 1, -1}, {1, 1, 1}, {-1, 1, 1}
    };

    // Cube faces (each face uses four vertices)
    static const int faces[6][4] = { 
        {0,1,3,2}, {5,4,6,7}, {2,1,6,5}, 
        {0,3,4,7}, {3,2,7,6}, {1,0,5,4} 
    };

    // Normal vectors for each face
    static const float normals[6][3] = {
        {0, -1, 0}, {0, 1, 0}, {1, 0, 0}, 
        {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}
    };

    // Texture coordinates for each face
    static const vec2 texcoords[6][4] = {
                            //Down
                            {{1/4.f,0.f},{2/4.f,0.f},{1/4.f,1/3.f},{2/4.f,1/3.f}},

                            //Up
                            {{2/4.f,1.f},{1/4.f,1.f},{2/4.f,2/3.f}, {1/4.f,2/3.f},},

                            //Right
                            {{1/4.f,1/3.f},{3/4.f,1/3.f},{2/4.f,2/3.f}, {3/4.f,2/3.f}},

                            //Left
                            {{0.f,1/3.f},{1/4.f,1/3.f},{0.f,2/3.f}, {1/4.f,2/3.f}},


                            //Front
                            {{1/4.f,1/3.f},{2/4.f,1/3.f},{1/4.f,2/3.f}, {2/4.f,2/3.f}},


                            //Back
                            {{1/4.f,1/3.f},{1.f,1/3.f},{3/4.f,2/3.f},{1.f,2/3.f}}

                            };

    // Define each face's vertices, normals, and texture coordinates
    for (int i = 0; i < 6; i++) 
    {
        // Set normal for the current face
        m_cubemap.normal(normals[i][0], -normals[i][1], normals[i][2]);
        m_cubemap.texcoord(texcoords[i][0].x, texcoords[i][0].y);

        // Define vertices and texture coordinates for the face
        for (int j = 0; j < 4; j++) 
        {
            m_cubemap.texcoord(texcoords[i][j].x, texcoords[i][j].y);
            m_cubemap.vertex(vertices[faces[i][j]][0], vertices[faces[i][j]][1], -vertices[faces[i][j]][2]);
        }

        // Start a new strip for the next face
        m_cubemap.restart_strip();
    }
}


int ViewerEtudiant::init()
{
    Viewer::init();
    
    m_camera.lookat( Point(0,0,0), 150 );
    
    
    /// Appel des fonctions init_votreObjet pour creer les Mesh

    init_quad();
    init_quad_anim();
    init_cube();
    init_cone();
    init_sphere();
    init_cylinder();
    init_disque();
    init_cubemap();

    /// Chargement des textures
    math_texture = read_texture(0, "data/debug2x2red.png");
    papillon_texture = read_texture(0, "data/papillon.png");
    monde_texture = read_texture(0, "data/monde.jpg");
    tree_texture = read_texture(0, "data/billboard/arbre3.png");
    cubemap_texture = read_texture(0, "data/cubemap/skybox.png");
    fire_texture = read_texture(0, "data/fire.png");
    sun_texture = read_texture(0, "data/sun.jpg");
    sea_texture = read_texture(0, "data/cubemap/cubemap_opensea/opensea_negy.png");

    //Terrain
    m_terrainTexture = read_texture(0, "data/terrain/terrain_texture.png");
    m_terrainAlti = read_image("data/terrain/terrain.png"); // Image servant de carte de hauteur

    //Création du Mesh_texture
    
    init_terrain(m_terrainAlti);

    m_alpha = read_mesh("data/alpha.obj");
    
    return 0;
}

/*
 * Exemple de definition de fonction permettant l affichage
 * de 'votreObjet' subissant la Transform T
 */
void ViewerEtudiant::draw_cube(const Transform& T)
{
    gl.texture(math_texture);
    gl.model( T );
    gl.draw( m_cube);

}

void ViewerEtudiant::draw_cone(const Transform& T)
{
    gl.texture(monde_texture);
    gl.model( T );
    gl.draw( m_cone);
    Transform Tch = T * Translation( 0, 0, 0);
    gl.model( Tch );
    gl.draw( m_disque);
}

void ViewerEtudiant::draw_sphere(const Transform& T)
{
    gl.texture(monde_texture);
    gl.model( T );
    gl.draw( m_sphere);
}

void ViewerEtudiant::draw_cylinder(const Transform& T)
{
    gl.texture(monde_texture);
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

    //Plane body
    gl.texture(math_texture);
    Transform Tpb = T * Rotation(Vector(0, 0, 1),  90) * Scale(1,4,1);
    gl.model( Tpb );
    gl.draw(m_sphere);
    //Has to be rotated because sphere is built with circles created along the y axis connected with triangles
    //If you stretch other axis than y you'be stretching the circles, not the triangles, which is what we want

    //Plane motor l
    gl.texture(math_texture);
    Transform Tml = T * Translation(0,-0.75,-3) * Rotation(Vector(0, 0, 1),  90) * Scale (0.5, 1, 0.5);
    gl.model( Tml );
    gl.draw( m_sphere );

    //Plane motor r
    gl.texture(math_texture);
    Transform Tmr = T * Translation(0,-0.75,3) * Rotation(Vector(0, 0, 1),  90) * Scale (0.5, 1, 0.5);
    gl.model( Tmr );
    gl.draw( m_sphere );

    //Rotation AFTER scaling (ie scale should be on the rightmost side), if before you rotate the axis but they will be scaled 
    //according to the default xyz axis, not the rotated ones, since all operations are done in the same plane,
    //matrices only serve to explain where unitary vectors (which serve as axis) are located in the default plane

    //Plane wings
    gl.texture(math_texture);
    Transform Tw = T * Scale (1, 0.2, 5);
    gl.model( Tw );
    gl.draw( m_cube );
    //gl.debug_normals(1); //To debug normals

    //Plane aileron
    gl.texture(math_texture);
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

    gl.alpha_texture(0.5f);
    gl.texture(m_terrainTexture);
    gl.model( T );
    gl.draw( m_terrain );
}

void ViewerEtudiant::draw_tree(const Transform &T) {

    gl.alpha_texture(tree_texture); //maybe like this gl.alpha_texture(tree_texture, 0.8);
    //by default 0.5
    gl.model( T );
    gl.draw( m_quad );

    gl.alpha_texture(tree_texture);
    gl.model( T * Rotation(Vector(0, 1, 0), 180));
    gl.draw( m_quad );

    gl.alpha_texture(tree_texture);
    gl.model( T * Rotation(Vector(0, 1, 0), 90));
    gl.draw( m_quad );

    gl.alpha_texture(tree_texture);
    gl.model( T * Rotation(Vector(0, 1, 0), -90));
    gl.draw( m_quad );
}

void ViewerEtudiant::draw_multitrees(const Transform &T, const Image& im) {
    // Define the frequency or positions for trees
    int treeSpacing = 10; // Adjust spacing as needed

    for (int i = treeSpacing; i < im.width(); i += treeSpacing) {
        for (int j = treeSpacing; j < im.height(); j += treeSpacing) {
            // Retrieve the terrain altitude at (i, j)
            float altitude = 25.f * im(i, j).r;

            float treeHeightOffset = 1;

            // Define the tree's transformation
            Transform final_T = T * Translation(i, altitude + treeHeightOffset, j); // Scale if trees are too large

            // Draw the tree
            draw_tree(final_T);
        }
    }
}

///Procedure pour dessiner le cube-map
void ViewerEtudiant::draw_cubemap(const Transform &T)
{
    gl.alpha_texture(0.5f);
    gl.model(T);
    gl.texture(cubemap_texture);
    gl.draw(m_cubemap);

}

void ViewerEtudiant::draw_fire(const Transform &T)
{
    gl.alpha_texture(fire_texture);
    gl.model(T);
    gl.draw(m_quad_anim);
}

void ViewerEtudiant::draw_sun(const Transform &T)
{
    gl.alpha_texture(sun_texture);
    gl.model(T);
    gl.draw(m_sphere);
}

void ViewerEtudiant::draw_sea(const Transform &T)
{
    gl.alpha_texture(sea_texture);
    gl.model(T);
    gl.draw(m_quad);
}

int ViewerEtudiant::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);

    manageCameraLight();

    gl.camera(m_camera);

    //gl.debug_normals(0.5);
    
    
    /// Appel de la fonction render() de la class Viewer
    /// pour que vous voyez apparaitre un premier objet
    /// a supprimer ensuite
    //Viewer::render();

    Transform T = Translation (0,0,0);
    Transform X = Translation (0,0,0) * Scale(0.25, 0.25, 0.25);
    Transform Y = Translation(-5, 0, 0);
    Transform Z = Translation (5,0,0);
    Transform R = Translation (5,5,5);
    Transform Cubemap = Scale(50, 50, 50);
    Transform S = Translation (0, 30, 0) * Scale(10, 10, 10);
    Transform F = Translation(30, 20, 0) * Scale(10, 10, 10);
    Transform P = Translation(30, 30, 0);
    Transform Terrain = Scale(0.525,0.5,0.525) * Translation(-95,-20,-95);
    Transform Sea = Translation(0, -8, 0) * Scale(50, 50, 50) * Rotation(Vector(1, 0, 0), -90);
    
    gl.model(Identity());
    gl.draw(m_alpha);

    draw_cubemap(Cubemap);
    /// Appel des fonctions du type 'draw_votreObjet'
    draw_cube(T);
    draw_cone(Y);
    draw_cylinder(Z);
    draw_sphere(Translation (5,5,0));

    //draw_plane(Translation (0,0,0));

    draw_terrain(Terrain);
    draw_multitrees(Terrain, m_terrainAlti);

    draw_plane(m_Tplane);
    //draw_plane(Identity()); //shows original plane
    
    draw_fire(F);
    draw_fire(F * Rotation(Vector(0, 1, 0), 180));

    draw_sun(S);

    draw_sphere(m_Tplanet * P);

    draw_sea(Sea);

   
    
    return 1;
    
}


/*
 * Fonction dans laquelle les mises a jours sont effectuees.
 */
int ViewerEtudiant::update( const float time, const float delta )
{
    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.
    
    float ts = time/1000.0f; // conversion en secondes
    int te = int(ts); // conversion en entier
    int tf = 10 * ts;

    // Calculate the current stage of the fire
    int stage = (tf % 9); // There are 9 stages, so we use modulo 9

    // Calculate the texture coordinates for the current stage
    float texCoordStart = stage / 9.0f;
    float texCoordEnd = (stage + 1) / 9.0f;

    // Update the quad with the new texture coordinates
    m_quad_anim.texcoord(0, texCoordStart, 0); // vertex 0
    m_quad_anim.vertex(-1, -1, 0);

    m_quad_anim.texcoord(1, texCoordEnd, 0); // vertex 1
    m_quad_anim.vertex(1, -1, 0);

    m_quad_anim.texcoord(2, texCoordStart, 1); // vertex 2
    m_quad_anim.vertex(-1, 1, 0);

    m_quad_anim.texcoord(3, texCoordEnd, 1); // vertex 3
    m_quad_anim.vertex(1, 1, 0);

    //Q1
    /*float angleRot = 2 * M_PI/7;
    T_plane = Rotation(Vector(0, 0, 1), angleRot * te);*/

    //Q2
    /*int ite = te /m_anim.nb_points();
    float poids = ts -te;
    Point po = m_anim[ite];
    int ite_suiv = (ite + 1) % m_anim.nb_points();
    Point p1 = m_anim[ite_suiv];
    Vector pos = Vector(po) + poids * (Vector(p1) - Vector(po));
    m_Tplane = Translation(pos); //Objet mis à la position pos*/

    //Q3
    int ite = te /m_anim.nb_points();
    float poids = ts -te;
    int ite_suiv = (ite + 1) % m_anim.nb_points();
    int ite_suiv2 = (ite_suiv + 1) % m_anim.nb_points();

    Point p0 = m_anim[ite];
    Point p1 = m_anim[ite_suiv];
    Point p2 = m_anim[ite_suiv2];
    Vector pos = Vector(p0) + poids * (Vector(p1) - Vector(p0));
    Vector pos_suiv = Vector(p1) + poids * (Vector(p2) - Vector(p1));

    Vector dir = normalize(pos_suiv - pos);
    Vector up(0, 1, 0);
    Vector right = cross(dir, up);
    //m_Tplane = Translation(pos) * Rotation(right, 90) * Rotation(dir, 90);
    m_Tplane = Translation(pos) * Rotation(dir, 90) * Rotation(up, 90) * Rotation(right, 90) * Rotation(Vector(0, 0, 1), 180); //Check how to remove last rotation

    // Calculate the circular trajectory
    float radius = 10.0f; // Adjust the radius as needed
    float speedFactor = 3.0f; // Adjust this factor to control the speed
    float angle = 2.0f * M_PI * (ts / speedFactor); // Full circle over time

    // Calculate the new position along the circular trajectory
    float x = radius * cos(angle);
    float z = radius * sin(angle);
    Vector circular_pos = Vector(x, pos.y, z);

    // Calculate the direction of movement along the circular trajectory
    Vector circular_dir = normalize(Vector(-sin(angle), 0, cos(angle)));

    // Apply the transformations: translation to the circular position and rotation to align with the direction
    m_Tplanet = Translation(circular_pos) * Rotation(up, 90) * Rotation(Vector(0, 1, 0), angle * 180 / M_PI);

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
