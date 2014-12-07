//
//  TexturedMaterial.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/27/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_TexturedMaterial_h
#define RayTracingPractical_TexturedMaterial_h
class TexturedMaterial : public Material
{
public:
    GLuint textureName;
    GLint filteringMode;
    
    TexturedMaterial(const char* filename,
                     GLint filtering = GL_LINEAR_MIPMAP_LINEAR
                     ){
        unsigned char* data;
        int width;
        int height;
        int nComponents = 4;
        
        data = stbi_load(filename, &width, &height, &nComponents, 0);
        
        if(data == NULL) return;
        
        // opengl texture creation comes here
        glGenTextures(1, &textureName);  // id generation
        glBindTexture(GL_TEXTURE_2D, textureName);      // binding
        
        if(filtering == GL_LINEAR_MIPMAP_LINEAR) {
            if(nComponents == 4)
                gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
            else if(nComponents == 3)
                gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
        
        if(nComponents == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //uploading
        else if(nComponents == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //uploading
        }

        delete data;
    }
    
    void apply() {
        Material::apply();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureName);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexEnvi(GL_TEXTURE_ENV,
                  GL_TEXTURE_ENV_MODE, GL_MODULATE);
//        glDisable(GL_TEXTURE_2D);
//        glDisable(GL_BLEND);
        
    }
    
};

#endif
