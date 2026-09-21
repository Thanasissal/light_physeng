#version 330 core

// This matches the layout(location = 0) in your glVertexAttribPointer
layout (location = 0) in vec3 aPos;
// This matches the layout(location = 1) for your colors
layout (location = 1) in vec3 aColor;

// The uniforms you set in C++ using myShader.setMat4()
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// We pass the color to the fragment shader
out vec3 ourColor;

void main()
{
    // Order of multiplication is strict: Projection * View * Model * Position
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    // Pass the color straight through to the next step
    ourColor = aColor;
}