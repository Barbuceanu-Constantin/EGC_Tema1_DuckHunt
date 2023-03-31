#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include "Duck.h"
constexpr auto pi = 3.14;

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

float v[27];
float angle, wing1Angle, wing2Angle, basicSpeed;
int grassScalex, grassScaley;
int skyScalex, skyScaley;
int touchTheSky;
int sem, nrDucks;                                       //pt. starea unghiului
bool ok, evadat, firstDuck, impuscat;                   //ok e folosit la rotatia aripilor
float x1p, y1p;
float ax, ay;
float numaratorScale, numitorScale, scaleScore, nrOfSeconds;
float duckTimeLimit, currentDuckTime, spreeImageTime;
int killingSpree, nrOfKillingSprees;
glm::mat3 head, body, wing1, wing2, beak, grass, sky, globalMatrix, life, bullet, wireframe, score, spree;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

float min(float a, float b, float c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    if (c >= a && c >= b) return c;
}

float max(float a, float b, float c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    if (c <= a && c <= b) return c;
}

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int abs(int x, int y) {
    if (x - y < 0) return y - x;
}

void Tema1::CreateComponents() {
    Mesh* mesh;

    mesh = Duck::CreateMesh("body", glm::vec3(1, 0, 0), true, v);
    firstDuck ? AddMeshToList(mesh) : meshes["body"] = mesh;

    mesh = Duck::CreateMesh("wing1", glm::vec3(1, 0, 0), true, v);
    firstDuck ? AddMeshToList(mesh) : meshes["wing1"] = mesh;

    mesh = Duck::CreateMesh("wing2", glm::vec3(1, 0, 0), true, v);
    firstDuck ? AddMeshToList(mesh) : meshes["wing2"] = mesh;

    mesh = Duck::CreateMesh("head", glm::vec3(1, 0, 0), true, v);
    firstDuck ? AddMeshToList(mesh) : meshes["head"] = mesh;
    meshes["head"]->SetDrawMode(GL_TRIANGLE_FAN);

    mesh = Duck::CreateMesh("beak", glm::vec3(1, 0, 0), true, v);
    firstDuck ? AddMeshToList(mesh) : meshes["beak"] = mesh;
}

void Tema1::InitAngle() {
    srand(time(0));
    do {
        angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.14));
    } while (abs(angle - 1.52) < 0.6 || abs(angle - 0) < 0.25 || abs(angle - 3.14) < 0.6);
    angle < 1.52 ? sem = 0 : sem = 1;
}

void Tema1::InitMatrixes() {
    head = body = wing1 = wing2 = beak = grass = sky = globalMatrix = life = bullet = wireframe = spree = glm::mat3(1);

    globalMatrix *= transform2D::Translate(v[25], v[26]) * transform2D::Rotate(angle) * transform2D::Translate(-v[25], -v[26]);
    head *= transform2D::Translate(v[1] + 10, v[4]);
    //Initializez factorii de scalare pentru iarba.
    grassScalex = 128;
    grassScaley = 20;
    grass *= transform2D::Scale(grassScalex, grassScaley);

    //Initializez factorii de scalare pt cer.
    skyScalex = 128;
    skyScaley = 52;
    sky *= transform2D::Translate(0, 200) * transform2D::Scale(skyScalex, skyScaley);

    //Initializez pozitia la care voi pune vietile.
    life *= transform2D::Translate(1100, 600);

    //Initializez pozitia la care voi pune gloantele.
    bullet *= transform2D::Translate(25, 600) * transform2D::Scale(2, 5);

    //Initializez pozitia wireframeului si a scoreului.
    wireframe *= transform2D::Translate(25, 500) * transform2D::Scale(40, 5);

    //Initializez pozitia imaginii de killingSpree.
    spree *= transform2D::Translate(600, 400) * transform2D::Scale(10, 10);
}

void Tema1::InitBodyPoints() {
    x1p = v[0];
    y1p = v[3];
}

void Tema1::InitOthers() {
    //De cate ori a atins rata marginea de sus.
    touchTheSky = 0;

    //Variabile legate de impuscare
    impuscat = false;

    //Initializez unghiul de rotatie pentru fiecare din cele 2 aripi.
    wing1Angle = wing2Angle = 0;
    ok = false;

    //Initializez starea de evadat.
    evadat = false;

    ax = ay = 0;

    bullets = 3;
}

void Tema1::InitDuck() {
    CreateComponents();

    //Initializez unghiul de pornire.
    InitAngle();

    //Setez pe coordonatele centrului cercului(capului) drept punctul in jurul caruia se invarte initial pt. unghiul de start.
    //Rotatia de la reflexii se face in jurul altui punct.
    v[25] = v[1] + 10;
    v[26] = v[4];

    //Initializez matricile componentelor;
    InitMatrixes();

    //Coordonatele patrulaterului.
    InitBodyPoints();

    InitOthers();

    //Aici maresc viteza ratelor odata la 3 rate.
    ++nrDucks;
    if (nrDucks % 3 == 0) basicSpeed += 50;
    currentDuckTime = 0;
}

void Tema1::InitBackgroundComponent(char name[20]) {
    Mesh* mesh;

    mesh = Duck::CreateMesh(name, glm::vec3(1, 0, 0), true, v);
    AddMeshToList(mesh);
    meshes[name]->SetDrawMode(GL_TRIANGLE_FAN);
}

void Tema1::InitBackground() {
    InitBackgroundComponent("grass");
    InitBackgroundComponent("sky");
    InitBackgroundComponent("life1");
    InitBackgroundComponent("life2");
    InitBackgroundComponent("life3");
    InitBackgroundComponent("bullet1");
    InitBackgroundComponent("bullet2");
    InitBackgroundComponent("bullet3");
    InitBackgroundComponent("wireframe");
    InitBackgroundComponent("score");
    InitBackgroundComponent("spree");
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    basicSpeed = 300;
    lives = 3;
    firstDuck == true;
    scaleScore = 1;
    nrDucks = 1;

    InitBackground();

    InitDuck();

    score *= transform2D::Scale(scaleScore, 1);
    numaratorScale = 2;
    numitorScale = 1;

    //Aici setez numarul de secunde cat sa stea maxim pe ecran rata pana la evadare.
    duckTimeLimit = 7;

    //Aici initializez matricea de scor.
    score = glm::mat3(1);
    score *= transform2D::Translate(25, 500) * transform2D::Scale(1, 5);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::FallingDown() {
    float var = - angle - pi / 2;
    switch (sem) {
        case 0:
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(var) * transform2D::Translate(-v[1], -v[4]);
            break;
        case 1:
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(var) * transform2D::Translate(-v[1], -v[4]);
            break;
        case 2:
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(var) * transform2D::Translate(-v[1], -v[4]);
            break;
        case 3:
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(var) * transform2D::Translate(-v[1], -v[4]);
    }
    angle = -3.14 / 2;
}

void Tema1::Evadare() {
    float var = - angle + pi / 2;
    switch (sem) {
        case 0:
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(var) * transform2D::Translate(-v[1], -v[4]);
            break;
        case 1:
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(var) * transform2D::Translate(-v[1], -v[4]);
            break;
        case 2:
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(var) * transform2D::Translate(-v[1], -v[4]);
            break;
        case 3:
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(var) * transform2D::Translate(-v[1], -v[4]);
    }
    evadat = true;
    angle = 3.14 / 2;
    --lives;
    currentDuckTime = 0;
    killingSpree = 0;
}

void Tema1::Reflexie() {
    //
    //Aici este logica de facut reflexiile.
    if (sem == 0) {
        if (v[25] >= 1280) {
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(-angle + pi - angle) * transform2D::Translate(-v[1], -v[4]);
            sem = 1;
            angle = 3.14 - angle;
        } 
        else if (v[26] >= 720) {
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(-2 * angle) * transform2D::Translate(-v[1], -v[4]);
            sem = 2;
            angle = -angle;
        }
    } else if (sem == 1) {
        if (v[26] >= 720) {
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(-2 * angle) * transform2D::Translate(-v[1], -v[4]);
            sem = 3;
            angle = -angle;
        } 
        else if (v[25] <= 0) {
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(-angle + pi - angle) * transform2D::Translate(-v[1], -v[4]);
            sem = 0;
            angle = 3.14 - angle;
        }
    } else if (sem == 2) {
        if (v[26] <= 0) {
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(-2 * angle) * transform2D::Translate(-v[1], -v[4]);
            sem = 0;
            angle = -angle;
        }
        else if (v[25] >= 1280) {
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(-angle -3.14 -angle) * transform2D::Translate(-v[1], -v[4]);
            sem = 3;
            angle = -angle - 3.14;
        }
    } else if (sem == 3) {
        if (v[26] <= 0) {
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(-angle + 2 * pi - angle) * transform2D::Translate(-v[1], -v[4]);
            sem = 1;
            angle = -angle + 2 * pi;
        }
        else if (v[25] <= 0) {
            globalMatrix *= transform2D::Translate(v[1], v[4]) * transform2D::Rotate(-2 * angle + 3.14) * transform2D::Translate(-v[1], -v[4]);
            sem = 2;
            angle = -angle + 3.14;
        }
    }
}

void Tema1::WingRotate() {
   //
   //Aici este logica de miscat aripile.
    if (ok == false && wing2Angle < 0.5) {
        wing1Angle -= 0.02;
        wing2Angle += 0.02;
    }
    else if (wing2Angle == 0.5) {
        ok = true;
        wing1Angle += 0.02;
        wing2Angle -= 0.02;
    }
    else if (ok == true && wing2Angle > 0) {
        wing1Angle += 0.02;
        wing2Angle -= 0.02;
    }
    else if (wing2Angle == 0) {
        ok = false;
        wing1Angle -= 0.0005;
        wing2Angle += 0.0005;
    }
    wing1 *= transform2D::Translate(v[6], v[9]) * transform2D::Rotate(wing1Angle) * transform2D::Translate(-v[6], -v[9]);
    wing2 *= transform2D::Translate(v[12], v[15]) * transform2D::Rotate(wing2Angle) * transform2D::Translate(-v[12], -v[15]);
    //Aici este logica de miscat aripile.
    //
}

void Tema1::RenderObjects() {
    RenderMesh2D(meshes["score"], shaders["VertexColor"], score * transform2D::Scale(scaleScore, 1));
    RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], wireframe);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], grass);

    switch (lives) {
        case 1:
            RenderMesh2D(meshes["life1"], shaders["VertexColor"], life);
            break;
        case 2:
            RenderMesh2D(meshes["life1"], shaders["VertexColor"], life);
            RenderMesh2D(meshes["life2"], shaders["VertexColor"], life * transform2D::Translate(50, 0));
            break;
        case 3:
            RenderMesh2D(meshes["life1"], shaders["VertexColor"], life);
            RenderMesh2D(meshes["life2"], shaders["VertexColor"], life * transform2D::Translate(50, 0));
            RenderMesh2D(meshes["life3"], shaders["VertexColor"], life * transform2D::Translate(100, 0));
            break;
    }
    
    switch (bullets) {
        case 1:
            RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], bullet);
            break;
        case 2:
            RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], bullet);
            RenderMesh2D(meshes["bullet2"], shaders["VertexColor"], bullet * transform2D::Translate(20, 0));
            break;
        case 3:
            RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], bullet);
            RenderMesh2D(meshes["bullet2"], shaders["VertexColor"], bullet * transform2D::Translate(20, 0));
            RenderMesh2D(meshes["bullet3"], shaders["VertexColor"], bullet * transform2D::Translate(40, 0));
            break;
    }

    if (lives > 0 && killingSpree < 5) {
        RenderMesh2D(meshes["head"], shaders["VertexColor"], globalMatrix * head);
        RenderMesh2D(meshes["body"], shaders["VertexColor"], globalMatrix);
        RenderMesh2D(meshes["wing1"], shaders["VertexColor"], globalMatrix * wing1);
        RenderMesh2D(meshes["wing2"], shaders["VertexColor"], globalMatrix * wing2);
        RenderMesh2D(meshes["beak"], shaders["VertexColor"], globalMatrix);
    } else if (killingSpree == 5) {
        RenderMesh2D(meshes["spree"], shaders["VertexColor"], spree);
    }

    RenderMesh2D(meshes["sky"], shaders["VertexColor"], sky);
}

void Tema1::UpdateBodyPoints(float fx, float fy) {
    x1p += fx;
    y1p += fy;
}

void Tema1::Update(float deltaTimeSeconds)
{
    float fx = cos(angle) * basicSpeed * deltaTimeSeconds;
    float fy = sin(angle) * basicSpeed * deltaTimeSeconds;
    globalMatrix = transform2D::Translate(fx, fy) * globalMatrix;
    v[25] += fx; v[26] += fy;

    currentDuckTime += deltaTimeSeconds;
    if (killingSpree < 5) {
        if (!impuscat) {
            UpdateBodyPoints(fx, fy);
            if (v[26] >= 720) {
                touchTheSky++;
            }

            if (touchTheSky == 2 || (touchTheSky == 1 && evadat)) {
                firstDuck = false;
                evadat = false;
                touchTheSky = 0;
                InitDuck();
            }

            Reflexie();
            WingRotate();
            if (v[26] < 0 || (currentDuckTime > duckTimeLimit && !evadat)) {
                /*
                    Aici am implementata logica ca daca intra in iarba evadeaza.
                    Daca se depaseste timpul per rata evadeaza si in acel caz.
                */
                Evadare();
            }
        } else {
            FallingDown();
            if (v[26] <= 0) {
                firstDuck = false;
                touchTheSky = 0;
                InitDuck();
            }
        }
        RenderObjects();
    } else {
        spreeImageTime += deltaTimeSeconds;
        if (spreeImageTime < 5) {
            spree = transform2D::Translate(650, 450) * transform2D::Rotate(0.02) * transform2D::Translate(-650, -450) * spree;
            RenderObjects();
        } else {
            spreeImageTime = 0;
            killingSpree = 0;
            currentDuckTime = 0;
            ++nrOfKillingSprees;
            InitDuck();
        }
    }
}


void Tema1::FrameEnd()
{

}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
  
}

void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    --bullets;
    // Add mouse button press event
    // Body Shot.
    if (mouseX > x1p - 250 && mouseX < x1p + 250)
        if (mouseY > y1p - 250 && mouseY < y1p + 250) {
            if (!evadat && bullets > 0) {
                impuscat = true;
                numaratorScale++;
                numitorScale++;
                scaleScore *= numaratorScale / numitorScale;
                ++killingSpree;
                if (killingSpree == 5) {
                    int i = 0;
                    do {
                        score *= transform2D::Scale(scaleScore, 1);
                        numaratorScale++;
                        numitorScale++;
                        scaleScore = numaratorScale / numitorScale;
                        ++i;
                    } while (i < 10);
                }
            }
        }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

}

void Tema1::OnWindowResize(int width, int height)
{

}