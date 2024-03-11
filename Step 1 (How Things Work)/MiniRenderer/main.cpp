#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

const int width = 1080;
const int height = 1080;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{

	bool steep = false;
	// Check if the dy is Greater than dx then we need to swap it to draw more pixels in line
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	// We want to draw from left to right. so... yeah...
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	// Go Pixel by pixel on x axis (or y but its flipped)
	for (int x = x0; x <= x1; x++)
	{

		// If its fliped set the flipped pixel
		if (steep)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}
		error2 += derror2;
		if (error2 > dx)
		{
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}
Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P)
{
	Vec3f s[2];
	for (int i = 2; i--;)
	{
		s[i][0] = C[i] - A[i];
		s[i][1] = B[i] - A[i];
		s[i][2] = A[i] - P[i];
	}
	Vec3f u = cross(s[0], s[1]);
	if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
		return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	return Vec3f(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

void triangle(Vec3f *pts, float *zbuffer, TGAImage &image, TGAColor color)
{
	Vec2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	Vec2f clamp(image.get_width() - 1, image.get_height() - 1);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			bboxmin[j] = std::max(0.f, std::min(bboxmin[j], pts[i][j]));
			bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
		}
	}
	Vec3f P;
	for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++)
	{
		for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++)
		{
			Vec3f bc_screen = barycentric(pts[0], pts[1], pts[2], P);
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
				continue;
			P.z = 0;
			for (int i = 0; i < 3; i++)
				P.z += pts[i][2] * bc_screen[i];
			if (zbuffer[int(P.x + P.y * width)] < P.z)
			{
				zbuffer[int(P.x + P.y * width)] = P.z;
				image.set(P.x, P.y, color);
			}
		}
		
	}
}

Vec3f world2screen(Vec3f v)
{
	return Vec3f(int((v.x + 1.) * width / 2. + .5), int((v.y + 1.) * height / 2. + .5), v.z);
}
void DrawModelFilled(Model *model)
{

	TGAImage image(width, height, TGAImage::RGB);

	float *zbuffer = new float[width * height];
	for (int i = width * height; i--; zbuffer[i] = -std::numeric_limits<float>::max())
		;
	Vec3f light_dir(-1, -1, -1); // define light_dir
	light_dir.normalize();
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		Vec3f pts[3];
		Vec3f world_coords[3];

		for (int j = 0; j < 3; j++)
		{
			pts[j] = world2screen(model->vert(face[j]));
			world_coords[j] = model->vert(face[j]);
		}
		Vec3f n = cross((world_coords[2] - world_coords[0]) , (world_coords[1] - world_coords[0]));
		n.normalize();
		float intensity = n * light_dir;

		// std::cout << intensity << std::endl;
		if (intensity > 0)
		{
			triangle(pts, zbuffer, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
		}
	}
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

	// for (int i = 0; i < model->nfaces(); i++)
	// {

	// 	std::vector<int> face = model->face(i);
	// 	Vec2i screen_coords[3];
	// 	Vec3f world_coords[3];
	// 	for (int j = 0; j < 3; j++)
	// 	{
	// 		Vec3f v = model->vert(face[j]);
	// 		screen_coords[j] = Vec2i((v.x + 1.) * width / 2., (v.y + 1.) * height / 2.);
	// 		world_coords[j] = v;
	// 	}
	// 	Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
	// 	n.normalize();
	// 	float intensity = n * light_dir;
	// 	if (intensity >= 0)
	// 	{

	// 		Vec2i trianglePoints[3] = {screen_coords[0], screen_coords[1], screen_coords[2]};
	// 		triangle(trianglePoints, zbuffer, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
	// 	}
	// }
}

void DrawModelWireframe(Model *model, TGAImage &image)
{
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		for (int j = 0; j < 3; j++)
		{
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j + 1) % 3]);
			int x0 = (v0.x + 1.) * width / 2.;
			int y0 = (v0.y + 1.) * height / 2.;
			int x1 = (v1.x + 1.) * width / 2.;
			int y1 = (v1.y + 1.) * height / 2.;
			line(x0, y0, x1, y1, image, white);
		}
	}
}

int main(int argc, char **argv)
{
	Model *model = NULL;

	if (argc == 2)
	{
		model = new Model(argv[1]);
	}
	else
	{
		model = new Model("Models/african_head.obj");
	}
	DrawModelFilled(model);
	delete model;
	return 0;
}
