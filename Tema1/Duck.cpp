#include "Tema1.h"
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* CreateBullet(char name[10]) {
    int triangleNr = 2;

    vector<VertexFormat> vertices;
    vector<unsigned int> indices;

    vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(0.f, 0.f, 0.f));
    indices.push_back(0);
    vertices.emplace_back(glm::vec3(10, 0, 0), glm::vec3(0.f, 0.f, 0.f));
    indices.push_back(1);
    vertices.emplace_back(glm::vec3(10, 10, 0), glm::vec3(0.f, 0.f, 0.f));
    indices.push_back(2);
    vertices.emplace_back(glm::vec3(0, 10, 0), glm::vec3(0.f, 0.f, 0.f));
    indices.push_back(3);

    // Create a new mesh from buffer data
    Mesh* mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);
    return mesh;
}

Mesh* CreateLife(char name[10]) {
    int triangleNr = 20;
    float piValue = 3.141;
    float aux;

    vector<VertexFormat> vertices;
    vector<unsigned int> indices;

    vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(1.f, 0.f, 0.f));

    for (int i = 0; i < triangleNr; i++)
    {
        aux = piValue * 2 * i / triangleNr;

        vertices.emplace_back(glm::vec3(15 * cos(aux), 15 * sin(aux), 0), glm::vec3(1.f, 0.f, 0.f));
        indices.push_back(i);
    }

    indices.push_back(triangleNr);
    indices.push_back(1);

    // Create a new mesh from buffer data
    Mesh* mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);

    return mesh;
}

Mesh* CreateBckd(char name[10], glm::vec3 color) {
    int triangleNr = 2;

    vector<VertexFormat> vertices;
    vector<unsigned int> indices;

    vertices.emplace_back(glm::vec3(0, 0, 0), color);
    indices.push_back(0);
    vertices.emplace_back(glm::vec3(10, 0, 0), color);
    indices.push_back(1);
    vertices.emplace_back(glm::vec3(10, 10, 0), color);
    indices.push_back(2);
    vertices.emplace_back(glm::vec3(0, 10, 0), color);
    indices.push_back(3);

    // Create a new mesh from buffer data
    Mesh* mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);
    return mesh;
}

Mesh* Duck::CreateMesh(const std::string &name, glm::vec3 color, bool fill, float v[])
{
    string body("body");
    string wing1("wing1");
    string wing2("wing2");
    string head("head");
    string beak("beak");
    string grass("grass");
    string sky("sky");
    string life1("life1");
    string life2("life2");
    string life3("life3");
    string bullet1("bullet1");
    string bullet2("bullet2");
    string bullet3("bullet3");
    string wireframe("wireframe");
    string score("score");
    string spree("spree");

    glm::vec3 bodyA, bodyB, bodyC;
    glm::vec3 wing1A, wing1B, wing1C;
    glm::vec3 wing2A, wing2B, wing2C;
    glm::vec3 beakA, beakB, beakC;

    int x1, y1, x2, y2, x3, y3;

    srand(time(0));

    if (name.compare(body) == 0) {
        int firstDigit, secondDigit, thirdDigit;
        firstDigit = 1 + rand() % 9;
        secondDigit = 1 + rand() % 9;
        thirdDigit = 1 + rand() % 9;
        x1 = 0 + (firstDigit * 100 + secondDigit * 10 + thirdDigit);
        x2 = x1 + 100;
        x3 = x1;
        y1 = 50;
        y2 = y1 + 50;
        y3 = y1 + 100;

        v[0] = x1; v[1] = x2; v[2] = x3;
        v[3] = y1; v[4] = y2; v[5] = y3;

        bodyA = glm::vec3(x1, y1, 0);
        bodyB = glm::vec3(x2, y2, 0);
        bodyC = glm::vec3(x3, y3, 0);

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(bodyA, color),
            VertexFormat(bodyB, color),
            VertexFormat(bodyC, color)
        };

        Mesh* mesh = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2 };

        mesh->InitFromData(vertices, indices);
        return mesh;
    } else if (name.compare(wing1) == 0) {
        x1 = (v[1] + v[0]) / 2;
        y1 = (v[4] + v[3]) / 2;
        x2 = x1 - 12;
        x3 = x1 + 12;
        y2 = y1 - 30;
        y3 = y2;

        v[6] = x1; v[7] = x2; v[8] = x3;
        v[9] = y1; v[10] = y2; v[11] = y3;

        wing1A = glm::vec3(x1, y1, 0);
        wing1B = glm::vec3(x2, y2, 0);
        wing1C = glm::vec3(x3, y3, 0);

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(wing1A, color),
            VertexFormat(wing1B, color),
            VertexFormat(wing1C, color)
        };

        Mesh* mesh = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2 };

        mesh->InitFromData(vertices, indices);
        return mesh;
    } else if (name.compare(wing2) == 0) {
        x1 = (v[2] + v[1]) / 2;
        y1 = (v[5] + v[4]) / 2;
        x2 = x1 - 12;
        x3 = x1 + 12;
        y2 = y1 - 30;
        y3 = y2;

        v[12] = x1; v[13] = x2; v[14] = x3;
        v[15] = y1; v[16] = y2; v[17] = y3;

        wing2A = glm::vec3(x1, y1, 0);
        wing2B = glm::vec3(x2, y2, 0);
        wing2C = glm::vec3(x3, y3, 0);

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(wing2A, color),
            VertexFormat(wing2B, color),
            VertexFormat(wing2C, color)
        };

        Mesh* mesh = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2 };

        mesh->InitFromData(vertices, indices);
        return mesh;
    } else if (name.compare(head) == 0) {
        int triangleNr = 20;
        float piValue = 3.141;
        float aux;

        vector<VertexFormat> vertices;
        vector<unsigned int> indices;

        vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(1.f, 1.f, 0.f));

        for (int i = 0; i < triangleNr; i++)
        {
            aux = piValue * 2 * i / triangleNr;

            vertices.emplace_back(glm::vec3(17 * cos(aux), 17 * sin(aux), 0), glm::vec3(1.f, 1.f, 0.f));
            indices.push_back(i);
        }

        indices.push_back(triangleNr);
        indices.push_back(1);

        // Create a new mesh from buffer data
        Mesh* mesh = new Mesh(name);
        mesh->InitFromData(vertices, indices);

        return mesh;
    } else if (name.compare(beak) == 0) {
        x1 = v[1] + 50;
        y1 = v[4];
        x2 = v[1] + 25;
        x3 = x2;
        y2 = v[4] + 5;
        y3 = v[4] - 5;

        v[18] = x1; v[19] = x2; v[20] = x3;
        v[21] = y1; v[22] = y2; v[23] = y3;

        beakA = glm::vec3(x1, y1, 0);
        beakB = glm::vec3(x2, y2, 0);
        beakC = glm::vec3(x3, y3, 0);

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(beakA, color),
            VertexFormat(beakB, color),
            VertexFormat(beakC, color)
        };

        Mesh* mesh = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2 };

        mesh->InitFromData(vertices, indices);

        //In v[25], v[26] pun xCentruDreptunghi si yCentruDreptunghi.
        //v[25] = (v[18] + v[0]) / 2;
        //v[26] = (v[10] + v[16]) / 2;

        return mesh;
    } else if (name.compare(grass) == 0) {
        return CreateBckd("grass", glm::vec3(0.f, 1.f, 0.f));
    } else if (name.compare(sky) == 0) {
        return CreateBckd("sky", glm::vec3(0.f, 0.f, 1.f));
    } else if (name.compare(life1) == 0) {
        return CreateLife("life1");
    } else if (name.compare(life2) == 0) {
        return CreateLife("life2");
    } else if (name.compare(life3) == 0) {
        return CreateLife("life3");
    } else if (name.compare(bullet1) == 0) {
        return CreateBullet("bullet1");
    } else if (name.compare(bullet2) == 0) {
        return CreateBullet("bullet2");
    } else if (name.compare(bullet3) == 0) {
        return CreateBullet("bullet3");
    } else if (name.compare(wireframe) == 0) {
        return CreateBckd("wireframe", glm::vec3(0.5f, 0.5f, 0.f));
    } else if (name.compare(score) == 0) {
        return CreateBckd("score", glm::vec3(0.f, 0.5f, 0.5f));
    } else if (name.compare("spree") == 0) {
        return CreateBckd("spree", glm::vec3(1.f, 0.f, 0.f));
    }

    return NULL;
}


