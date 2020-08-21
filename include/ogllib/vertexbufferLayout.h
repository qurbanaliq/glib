#pragma once

#include <GL/glew.h>
#include <vector>

/*
* This struct represents a vertex element. A vertex element can be a vertex
* position, a vertex texture coordinate or vertex normal, for example.
*/
struct VertexbufferElement
{
    unsigned int type; // type of data
    unsigned int count; // size of data
    bool normalized;

    /*
    * Returns the size of a data type in bytes as defined by OpenGL
    */
    static unsigned int getSize(unsigned int type);
};

/*
* This class represents the layout of the data stored in a vertex buffer
*/
class VertexbufferLayout
{
    private:
        std::vector<VertexbufferElement> mElements;
        unsigned int mStride;
    public:
        /*
        * Create a vertex buffer layout
        */
        VertexbufferLayout();
        
        /*
        * Push a float element to the layout
        */
       void push(unsigned int count);

       /*
        * Get the vertex buffer elements
        */
       std::vector<VertexbufferElement> getElements() const;

       /*
        * Get the stride
        */
       unsigned int getStride() const;
};