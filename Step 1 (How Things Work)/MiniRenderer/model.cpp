#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_(), uv_()
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail())
        return;
    std::string line;
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 3, "vt "))
        {
            iss >> trash;
            Vec2f uv;
            for (int i = 0; i < 2; i++) // Only two values should be read
                iss >> uv[i];
            uv_.push_back(uv);
        }
        else if(!line.compare(0, 2, "v "))
        {
            iss >> trash;
            Vec3f v;
            for (int i = 0; i < 3; i++)
                iss >> v[i];
            verts_.push_back(v);
        }
        else if (!line.compare(0, 2, "f "))
        {
            std::vector<int> f;
            int itrash, idx, uv_idx;
            iss >> trash;
            while (iss >> idx >> trash >> uv_idx >> trash >> itrash)
            {
                idx--;    // Adjust for 0-based indexing
                uv_idx--; // Adjust for 0-based indexing
                // Assuming you want to store the vertex index and corresponding texture index together
                f.push_back(idx);
                f.push_back(uv_idx);
            }
            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " vt# " << uv_.size() << " f# " << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}
Vec2f Model::uv(int i)
{
    return uv_[i];
}
int Model::nuvs()
{
    return (int)uv_.size();
}
std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}