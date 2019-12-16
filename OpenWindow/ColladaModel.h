#ifndef __MODEL_s__
#define __MODEL_s__
#pragma once

#include "ColladaModel.h"
#include "tinyxml2.h"
#include "geometry.h"
#include "tgaimage.h"
#include "joint.h"
#include "animator.h"
#include "animation.h"

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class ColladaModel {
private:
	int face_count;
	int vertex_count;
	//int normal_count;
	//int texcoord_count;
	int joint_count;

	Joint rootjoint;
	int rootindex=0;
	Matrix roottransform;

	Animator animator;

	std::vector<std::vector<Vec3i> > faces_; //vertex/normal/uv
	std::vector<Vec3f> vertices_;
	std::vector<Vec3f> normals_;
	std::vector<Vec2f> texturecos_;


	std::vector<std::vector<Vec2i>> vertexweights_; //joint/weight
	std::vector<Vec3i> jointIDs_;
	std::vector<float> weights_;

	TGAImage diffusemap_;
	TGAImage normalmap_;
	TGAImage specularmap_;

	void load_texture(std::string filename, const char* suffix, TGAImage& img);
public:
	ColladaModel(const char* filename);
	~ColladaModel();

	int nfaces();
	int nvertices();

	Vec3f vertix(int iface, int nthvert);
	Vec3f vertix(int i);

	Vec3f normal(int iface, int nthvert);
	Vec3f normal(Vec2f uv);

	Vec2f uv(int iface, int nthvert);

	Matrix Transform;
	Matrix Rotation;
	Matrix Scale;
	Matrix Translation;

	void translate(Vec3f tr);
	void rotate(Vec3f rot);
	void scale(Vec3f scl);
	void ApplyTransform();

	TGAColor diffuse(Vec2f uv);
	float specular(Vec2f uv);
	std::vector<int> face(int idx);

	/////////////////////////////
	Joint getrootjoint();

	void doanimation(Animation animation);

	void updateanimator();

	std::vector<Matrix> getjointtransforms();

	void addjointtoarray(Joint parent, std::vector<Matrix>);
};
#endif
