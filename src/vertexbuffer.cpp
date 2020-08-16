#include "ogllib/vertexbuffer.h"

Vertexbuffer::Vertexbuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &mID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Vertexbuffer::~Vertexbuffer()
{
    glDeleteBuffers(1, &mID);
}

void Vertexbuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, mID);
}

void Vertexbuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}