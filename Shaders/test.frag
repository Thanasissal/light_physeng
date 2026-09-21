#version 330 core

// Receives the color variable from the vertex shader
in vec3 ourColor;

// The final color output to the screen
out vec4 FragColor;

void main()
{
    // Output the color with an alpha (opacity) of 1.0
    FragColor = vec4(ourColor, 1.0);
}