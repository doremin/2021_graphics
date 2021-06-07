#include "Object.h"

void Object::init_buffer_objects() 
{
    // TODO
    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, mMesh->mNumVertices * sizeof(aiVector3D), mMesh->mVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, mMesh-> mNumVertices * sizeof(aiColor4D), mMesh->mColors[0], GL_STATIC_DRAW);

    for (int i = 0; i < mMesh->mNumFaces; i++) {
        Face face;
        face.num_indices = mMesh->mFaces[i].mNumIndices;
        glGenBuffers(1, &face.index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face.index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3, mMesh->mFaces[i].mIndices, GL_STATIC_DRAW);
        faces.push_back(face);
    }
}

glm::mat4 Object::get_model_matrix()
{   
    glm::mat4 mat_model = glm::mat4(1.0f);
    
    // TODO
    mat_model = glm::translate(mat_model, vec_translate) * mat_rotate * glm::scale(mat_model, vec_scale);

    return mat_model;
}

void Object::draw(int loc_a_position, int loc_a_color)
{
    // TODO
    
    glEnableVertexAttribArray(loc_a_position);
    glEnableVertexAttribArray(loc_a_color);

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glVertexAttribPointer(loc_a_color, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
    
    
    for (int i = 0; i < faces.size(); i++) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faces[i].index_buffer); 
        glDrawElements(GL_TRIANGLES, faces[i].num_indices, GL_UNSIGNED_INT, (void*)0);
    }

    glDisableVertexAttribArray(loc_a_position);
    glDisableVertexAttribArray(loc_a_color);
}
    
void Object::print_info()
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