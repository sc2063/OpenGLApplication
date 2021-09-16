#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 m_Color;
layout(location = 2)in vec2 m_TexCoord;

out vec3 outColor;
out vec2 TexCoord;

uniform mat4 Transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * Transform * position;
	//gl_Position = position ;
	outColor = m_Color;
	TexCoord = m_TexCoord;
}
#shader fragment
#version 330 core

out vec4 fragColor;

in vec2 TexCoord;
in vec3 outColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
void main()
{
	vec4 texColor= texture(texture0,TexCoord);
	fragColor = mix(texColor,vec4(outColor,1.0),0.01);
}