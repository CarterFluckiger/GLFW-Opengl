#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
    GLuint Program;
    // Constructor generates the shader on the fly
    //Pre conditions- That the vertexPath and FragmentPath requirements are fufilled.  Also needs the shader files
    //Post conditions- The shader is created and is attached to a program
    Shader( const GLchar *vertexPath, const GLchar *fragmentPath )
    {
        //  Retrieve the vertex and the fragment code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // makes sure the ifstream can throw exceptions
        vShaderFile.exceptions ( std::ifstream::badbit );
        fShaderFile.exceptions ( std::ifstream::badbit );
        //Try catch to find the vertex and fragment shader
        try
        {
            // Open files
            vShaderFile.open( vertexPath );
            fShaderFile.open( fragmentPath );
            std::stringstream vShaderStream, fShaderStream;
            // reads the files in
            vShaderStream << vShaderFile.rdbuf( );
            fShaderStream << fShaderFile.rdbuf( );
            // stops reading in the file and closes it
            vShaderFile.close( );
            fShaderFile.close( );
            // makes what it read in, into a c string
            vertexCode = vShaderStream.str( );
            fragmentCode = fShaderStream.str( );
        }
        catch ( std::ifstream::failure e )
        {
            //catch statement that throws an error message
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar *vShaderCode = vertexCode.c_str( );
        const GLchar *fShaderCode = fragmentCode.c_str( );
        //creates the gluint vertex and fragment
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];
        // Vertex shader
        vertex = glCreateShader( GL_VERTEX_SHADER );
        glShaderSource( vertex, 1, &vShaderCode, NULL );
        glCompileShader( vertex );
        // glGetShaderiv is meant to show error in the console if there are any
        glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
        if ( !success )
        {
            glGetShaderInfoLog( vertex, 512, NULL, infoLog );
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Fragment shader
        fragment = glCreateShader( GL_FRAGMENT_SHADER );
        glShaderSource( fragment, 1, &fShaderCode, NULL );
        glCompileShader( fragment );
           // glGetShaderiv is meant to show error in the console if there are any
        glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
        if ( !success )
        {
            glGetShaderInfoLog( fragment, 512, NULL, infoLog );
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Shader program and creates it
        this->Program = glCreateProgram( );
        glAttachShader( this->Program, vertex );
        glAttachShader( this->Program, fragment );
        glLinkProgram( this->Program );
        // Print linking errors if there are any
        glGetProgramiv( this->Program, GL_LINK_STATUS, &success );
        if (!success)
        {
            glGetProgramInfoLog( this->Program, 512, NULL, infoLog );
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        // Delete the shaders as because I have them "attached" to my program and no longer need them
        glDeleteShader( vertex );
        glDeleteShader( fragment );
        
    }
    //Basically a get function that return the shader currently being used
    void Use( )
    {
        glUseProgram( this->Program );
    }
};

#endif
