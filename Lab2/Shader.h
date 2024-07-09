#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
	// the program pointer ID
	unsigned int ID;

	// constructor reads and builds the shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;

		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
		fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);

		try 
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();		
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode   = vShaderStream.str();
			fragmentCode = fShaderStream.str();		
		}

		catch(ifstream::failure e)
		{
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;
		//compile the shaders
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		printShaderInfoLog(vertex);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		printShaderInfoLog(fragment);

		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		// print linking errors if any
		printProgramInfoLog(ID);

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// use/activate the shader
	void use() 
	{ 
		glUseProgram(ID); 
	} 


	void printShaderInfoLog(GLuint obj)
	{
		int success;
		glGetShaderiv(obj, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			int infologLength = 0;
			int charsWritten  = 0;
			char *infoLog;

			glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);

			int shaderType;
			glGetShaderiv(obj, GL_SHADER_TYPE, &shaderType);

			if (shaderType == GL_VERTEX_SHADER)
				printf("ERROR::VERTEX SHADER::COMPILATION FAILED::\n");

			else if (shaderType == GL_FRAGMENT_SHADER)
				printf("ERROR::FRAGMENT SHADER::COMPILATION FAILED::\n");

			printf("%s\n",infoLog);
			free(infoLog);
		}
	}

	void printProgramInfoLog(GLuint obj)
	{
		int success;
		glGetProgramiv(obj, GL_LINK_STATUS, &success);

		if (!success)
		{
			int infologLength = 0;
			int charsWritten  = 0;
			char *infoLog;

			glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

			infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);

			printf("ERROR::SHADER PROGRAM::LINKING FAILED::\n");
			printf("%s\n",infoLog);
			free(infoLog);
		}
	}

};
