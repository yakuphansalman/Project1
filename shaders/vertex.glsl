#version 330 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inGizmos;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vec3 fragPos;
flat out vec3 normal;
out vec2 texCoord;
out vec3 gizmosCoord;

void main()
{
    fragPos = vec3(uModel * vec4(inPosition,1.0));
    normal = mat3(transpose(inverse(uModel)))*inNormal;
    gl_Position = uProjection*uView*uModel*vec4(inPosition, 1.0);
    texCoord = inTexCoord;
}