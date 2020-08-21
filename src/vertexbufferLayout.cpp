#include "ogllib/vertexbufferLayout.h"

unsigned int VertexbufferElement::getSize(unsigned int type)
{
    switch(type)
    {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
    }
    return 0;
}

VertexbufferLayout::VertexbufferLayout() : mStride(0)
{

}

void VertexbufferLayout::push(unsigned int count)
{
    mElements.push_back({GL_FLOAT, count, GL_FALSE});
    mStride += count * VertexbufferElement::getSize(GL_FLOAT);
}

std::vector<VertexbufferElement> VertexbufferLayout::getElements() const
{
    return mElements;
}

unsigned int VertexbufferLayout::getStride() const
{
    return mStride;
}