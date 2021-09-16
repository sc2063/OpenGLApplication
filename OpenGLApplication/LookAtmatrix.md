glm::mat4 LookAtmatirx(glm::vec3 position, glm::vec3 Target,glm::vec3 worldUp)
{
	// 1. Position = known
	// 2. Calculate cameraDirection
	glm::vec3 zaxis = glm::normalize(position - Target);
	// 3. Get positive right axis vector
	glm::vec3 xaxis = glm::normalize(glm::cross(worldUp, zaxis));
	// 4. Calculate camera up vector
	glm::vec3 yaxis = glm::cross(zaxis, xaxis);

	// Create translation and rotation matrix
	// In glm we access elements as mat[col][row] due to column-major layout
	glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
	
	//摄像机位置向量
	translation[3][0] = -position.x; 
	translation[3][1] = -position.y;
	translation[3][2] = -position.z;
	
	glm::mat4 rotation = glm::mat4(1.0f);

	//R:右向量 U:上向量 D:方向向量
	rotation[0][0] = xaxis.x;//Rx
	rotation[0][1] = yaxis.x;//Ux
	rotation[0][2] = zaxis.x;//Dx
	
	rotation[1][0] = xaxis.y;//Ry
	rotation[1][1] = yaxis.y;//Uy	
	rotation[1][2] = zaxis.y;//Dy

	rotation[2][0] = xaxis.z;//Rz
	rotation[2][1] = yaxis.z;//Uz	
	rotation[2][2] = zaxis.z;//Dz

	return rotation * translation;

}