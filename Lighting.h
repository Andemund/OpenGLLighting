#pragma once

#define PI 3.1415926
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Lighting {

	struct Direction_Light {

		bool status;
		glm::vec3 direction;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular; 
	};


	struct Point_Light {

		bool status;
		glm::vec3 position;
		float constant;
		float linear;
		float quadratic;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;

		//my code start
		int count_rotate = 0;
		float rotate_radius = 0;
		float angle_X = 0;
		float angle_Y = 0;
		float angle_Z = 0;
		float angle_delta = 0.2f;
		bool used = false;
		//my code end
	};

public:

	Direction_Light direction_light;
	Point_Light point_light;

	Lighting() {}

	~Lighting() {}

	void init()
	{
		direction_light.status = true;
		direction_light.direction = glm::vec3(0.0f, -1.0f, -1.0f);
		direction_light.ambient = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
		direction_light.diffuse = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
		direction_light.specular = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		point_light.status = true;
		point_light.position = glm::vec3(1.2f, 1.0f, 2.0f);
		point_light.ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
		point_light.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		point_light.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		point_light.constant = 1.0f;
		point_light.linear = 0.09f;
		point_light.quadratic = 0.032f;
	};

	//my code start
	void rotate_X(glm::vec3 object_center)
	{
		//point_light.rotate_radius = sqrt(pow((object_center[1] - point_light.position[1]), 2) + pow((object_center[2] - point_light.position[2]), 2));
		//point_light.angle_X = acos((object_center[2] - point_light.position[2]) / point_light.rotate_radius) * 180.0 / PI + point_light.angle_delta;
		//point_light.position[1] = sin(point_light.angle_X * PI / 180.0) * point_light.rotate_radius + object_center[1];
		//point_light.position[2] = cos(point_light.angle_X * PI / 180.0) * point_light.rotate_radius + object_center[2];
		point_light.used = true;
		float ty = point_light.position[1];
		float tz = point_light.position[2];
		ty = point_light.position[1] * cos(glm::radians(point_light.angle_delta)) - point_light.position[2] * sin(glm::radians(point_light.angle_delta));
		tz = point_light.position[2] * cos(glm::radians(point_light.angle_delta)) + point_light.position[1] * sin(glm::radians(point_light.angle_delta));
		point_light.position[1] = ty;
		point_light.position[2] = tz;
	}


	void rotate_Y(glm::vec3 object_center)
	{
		point_light.rotate_radius = sqrt(pow((object_center[0] - point_light.position[0]), 2) + pow((object_center[2] - point_light.position[2]), 2));
		point_light.angle_Y = acos((object_center[0] - point_light.position[0]) / point_light.rotate_radius) * 180.0 / PI + point_light.angle_delta;
		point_light.position[0] = cos(point_light.angle_Y * PI / 180.0) * point_light.rotate_radius + point_light.position[0];
		point_light.position[2] = sin(point_light.angle_Y * PI / 180.0) * point_light.rotate_radius + point_light.position[2];
	}

	void rotate_Z(glm::vec3 object_center)
	{
		point_light.rotate_radius = sqrt(pow((object_center[0] - point_light.position[0]), 2) + pow((object_center[1] - point_light.position[1]), 2));
		point_light.angle_Z = acos((object_center[1] - point_light.position[1]) / point_light.rotate_radius) * 180.0 / PI + point_light.angle_delta;
		point_light.position[1] = cos(point_light.angle_Z * PI / 180.0) * point_light.rotate_radius + point_light.position[1];
		point_light.position[0] = sin(point_light.angle_Z * PI / 180.0) * point_light.rotate_radius + point_light.position[0];
	}

	//my code end
};