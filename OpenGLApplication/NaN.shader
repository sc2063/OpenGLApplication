#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 m_Color;

out vec3 outColor;

void main()
{
	gl_Position = position;
	outColor = m_Color;
}
#shader fragment
#version 330 core

out vec4 fragColor;

in vec3 outColor;

void main()
{
	fragColor = vec4(outColor,1.0);
}