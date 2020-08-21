#pragma once

#include <GL/glew.h>

/*
* This class creates a vertex buffer in OpenGL
*/
class Vertexbuffer
{
    private:
        unsigned int mID;
    public:
        /*
        * Create a vertex buffer object given array of data
        */
        Vertexbuffer(const void* data, unsigned int size);
        ~Vertexbuffer();

        /*
        * Bind this vertex buffer
        */
        void bind() const;

        /*
        * Unbind this vertex array
        */
        void unbind() const;
};