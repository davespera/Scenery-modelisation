
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

/*void ViewerEtudiant::init_square() {
    m_square = Mesh(GL_TRIANGLE_STRIP);

    m_square.color(Color(1,1,1));
    
    // Define vertices for the square (2D plane in 3D space)
    static float pt[4][3] = {
        {-1, -1, 0},  // Bottom-left corner
        {1, -1, 0},  // Bottom-right corner
        {-1, 1, 0},  // Top-right corner
        {1, 1, 0}   // Top-left corner
    };

    // Define texture coordinates for the square
    static float texcoords[4][2] = {
        {0, 0},  // Texture coordinate for bottom-left
        {1, 0},  // Texture coordinate for bottom-right
        {1, 1},  // Texture coordinate for top-right
        {0, 1}   // Texture coordinate for top-left
    };

    // Normal vector for the square (facing along the positive Z-axis)
    // Set the normal for the square
    m_square.normal(0, 0, 1);
    
    // Define the vertices and corresponding texture coordinates
    for (int i = 0; i < 4; i++) {
        m_square.texcoord(texcoords[i][0], texcoords[i][1]);  // Add texture coordinates
        m_square.vertex(pt[i][0], pt[i][1], pt[i][2]);
    }

}*/

void ViewerEtudiant::init_quad()
{
m_quad = Mesh(GL_TRIANGLE_STRIP);
m_quad.color( Color(1, 1, 1));

m_quad.normal( 0, 0, 1 );

m_quad.texcoord( 0, 0 );
m_quad.vertex( -1, -1, 0 );

m_quad.texcoord( 1, 0 );
m_quad.vertex( 1, -1, 0);

m_quad.texcoord( 0, 1 );
m_quad.vertex( -1, 1, 0 );

m_quad.texcoord( 1, 1 );
m_quad.vertex(1, 1, 0 );
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
    m_cone.texcoord(i/div, 0);
    m_cone.normal(Vector(cos(alpha)/sqrtf(2.f), 0, sin(alpha)/sqrtf(2.f)));
    m_cone.vertex(Point(cos(alpha), 0, sin(alpha)));
    //up
    m_cone.texcoord(i/div, 1);
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
        m_cylinder.texcoord(i/div, 0);
        m_cylinder.normal(normal);
        m_cylinder.vertex(Point(cos(alpha), -1, sin(alpha)));
        
        m_cylinder.texcoord(i/div, 1);
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

            m_terrain.texcoord((i+1)/im.width(), j/im.height());
            m_terrain.normal( -terrainNormal(im, i+1, j) ); //maybe remove -
            m_terrain.vertex( Point(i+1, 25.f * im(i + 1, j).r, j) );

            m_terrain.texcoord(i/im.width(), j/im.height());
            m_terrain.normal( -terrainNormal(im, i, j) );
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
    math_texture = read_texture(0, "data/debug2x2red.png");

    papillon_texture = read_texture(0, "data/papillon.png");

    monde_texture = read_texture(0, "data/monde.jpg");

    tree_texture = read_texture(0, "data/billboard/arbre3.png");

    m_terrainTexture = read_texture(0, "data/terrain/terrain_texture.png");
    // Image servant de carte de hauteur
    m_terrainAlti = read_image("data/terrain/terrain.png");

    //Création du Mesh_texture
    
    init_terrain(m_terrainAlti);
    init_quad();
    
    return 0;
}

/* unsigned int ViewerEtudiant::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}  */

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
   
    gl.texture(monde_texture);
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

            float treeHeightOffset = 0.5f;

            // Define the tree's transformation
            Transform final_T = T * Translation(i, altitude + treeHeightOffset, j) * Scale(0.5); // Scale if trees are too large

            // Draw the tree
            draw_tree(final_T);
        }
    }
}

/*void ViewerEtudiant::draw_cubeMap(const Transform &T) {
    vector<std::string> faces;
{
    "data/cubemap/skybox/right.jpg",
    "data/cubemap/skybox/left.jpg",
    "data/cubemap/skybox/top.jpg",
    "data/cubemap/skybox/bottom.jpg",
    "data/cubemap/skybox/front.jpg",
    "data/cubemap/skybox/back.jpg"
};


unsigned int cubemapTexture = loadCubemap(faces);  

    gl.texture(cubemapTexture);
    gl.model( T );
    gl.draw( m_cube );
}*/

int ViewerEtudiant::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);

    manageCameraLight();

    gl.camera(m_camera);

    gl.debug_normals(0.5);
    
    
    /// Appel de la fonction render() de la class Viewer
    /// pour que vous voyez apparaitre un premier objet
    /// a supprimer ensuite
    //Viewer::render();

    Transform T = Translation (0,0,0);
    Transform X = Translation (0,0,0) * Scale(0.25, 0.25, 0.25);
    Transform Y = Translation(-5, 0, 0);
    Transform Z = Translation (5,0,0);
    Transform R = Translation (5,5,5);
    /// Appel des fonctions du type 'draw_votreObjet'
    //draw_cube(Translation (0,0,0));
    //draw_cone(Y);
    //draw_cylinder(Z);
    //draw_sphere(Translation (5,5,0));

    //draw_plane(Translation (0,0,0));

    draw_terrain(X);
    draw_multitrees(X, m_terrainAlti);
    //draw_cubeMap(R);
    
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
