#include "Mesh.h"

void check_error(std::string tag) {
    GLenum err;
    err = glGetError();
    if (err == GL_NO_ERROR) {
        std::cout << "no error" << tag << std::endl;
    } else if (err == GL_INVALID_ENUM) {
        std::cout << " invalid enum" << tag << std::endl;
    } else if (err == GL_INVALID_VALUE) {
        std::cout << " invalid value" << tag << std::endl;
    } else if (err == GL_INVALID_OPERATION) {
        std::cout << " invalid operation" << tag << std::endl;
    } else if (err == GL_OUT_OF_MEMORY) {
        std::cout << " out of memory" << tag << std::endl;
    } else if (err == GL_STACK_UNDERFLOW) {
        std::cout << " underflow" << tag << std::endl;
    } else if (err == GL_STACK_OVERFLOW) {
        std::cout << "overflow" << tag << std::endl;
    } else if (err == GL_INVALID_FRAMEBUFFER_OPERATION) {
        std::cout << "frame buffer operation" << tag << std::endl;
    }
}
void Mesh::init_buffer_objects() 
{
    // TODO : initialize position, normal, index buffer
    // use your code from the previous assignment
    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, mMesh->mNumVertices * sizeof(aiVector3D), mMesh->mVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, mMesh-> mNumVertices * sizeof(aiVector3D), mMesh->mNormals, GL_STATIC_DRAW);

    for (int i = 0; i < mMesh->mNumFaces; i++) {
        Face face;
        face.num_indices = mMesh->mFaces[i].mNumIndices;
        glGenBuffers(1, &face.index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face.index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3, mMesh->mFaces[i].mIndices, GL_STATIC_DRAW);
        faces.push_back(face);
    }
}

void Mesh::draw(int loc_a_position, int loc_a_normal)
{
    // TODO : draw a mesh
    // use your code from the previous assignment
    glEnableVertexAttribArray(loc_a_position);
    glEnableVertexAttribArray(loc_a_normal);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glVertexAttribPointer(loc_a_normal, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    
    for (int i = 0; i < faces.size(); i++) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faces[i].index_buffer); 
        glDrawElements(GL_TRIANGLES, faces[i].num_indices, GL_UNSIGNED_INT, (void*)0);
    }
    glDisableVertexAttribArray(loc_a_position);
    glDisableVertexAttribArray(loc_a_normal);
}
    
void Mesh::print_info()
{
    std::cout << "print mesh info" << std::endl;

    std::cout << "num vertices " << mMesh->mNumVertices << std::endl;
    for (int i = 0; i < mMesh->mNumVertices; ++i)
    {
        aiVector3D vertex = mMesh->mVertices[i];
        std::cout << "  vertex  (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;

        if (mMesh->mColors[0] != NULL)
        {
            aiColor4D color = mMesh->mColors[0][i];
            std::cout << "  color  (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
        }
    }
}