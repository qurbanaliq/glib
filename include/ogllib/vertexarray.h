/*
 * vertexarray.h
 * 
 * This module contains a Vertexarray class to create and bind a vertexArray
 * in an OpenGL scene
 *
 * Created on: Jul 8, 2020
 * Qurban Ali (qurbanaliqureshi@gmail.com)
 */


#pragma once

#include "ogllib/vertexbuffer.h"
#include "ogllib/vertexbufferLayout.h"

/*
* This class represents a Vertex Array
*/
class Vertexarray
{
    private:
        unsigned int mID;
    public:
        
        /*
        * Create a Vertex Array
        */
        Vertexarray();
        ~Vertexarray();

        /*
        * Add a vertex buffer along with it's layout
        */
        void addVertexbuffer(const Vertexbuffer& vb, const VertexbufferLayout& layout);

        /*
        * Bind the vertex array
        */
        void bind();

        /*
        * Unbind the vertex array
        */
        void unbind();
};