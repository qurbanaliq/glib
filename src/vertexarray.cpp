#include "ogllib/vertexarray.h"

Vertexarray::Vertexarray()
{
    glGenVertexArrays(1, &mID);
    bind();
}

Vertexarray::~Vertexarray()
{
    glDeleteVertexArrays(1, &mID);
}

void Vertexarray::addVertexbuffer(const Vertexbuffer& vb, const VertexbufferLayout& layout)
{
    // get the vertex buffer layout elements
    const std::vector<VertexbufferElement> elements = layout.getElements();
    unsigned int offset = 0; // offset between elements
    // loop through the elements to define the layout
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                layout.getStride(), (const void*)offset);
        offset += element.count * VertexbufferElement::getSize(element.type);
    }
}

void Vertexarray::bind()
{
    glBindVertexArray(mID);
}

void Vertexarray::unbind()
{
    glBindVertexArray(0);
}