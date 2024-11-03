#pragma once
#include <iostream>

#include "object.h"
#include "../gl_tweaks.h"
namespace fatum::object {
	class Triangle : public IDrawable{
		std::array<gl::Vertex, 3> vertices;
		gl::RGBAColor color;
		GLuint VBO;
		GLuint VAO;
		gl::ShaderProgram program;
		enum Uniform {
			Color
		};
	public:
		virtual gl::RGBAColor getColor() const {
			return color;
		}
		virtual void setColor(gl::RGBAColor c) {
			color = c;
			glUseProgram(program);
			glUniform4f(uniform.at(Uniform::Color), color.r, color.g, color.b, color.a);
		}
		


		virtual void onUpdate() override {
			glUseProgram(program);
			glBindVertexArray(VAO);

			glUniform4f(uniform.at(Uniform::Color), color.r, color.g, color.b, color.a);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glBindVertexArray(0);
		}

		//auto
		Triangle(gl::ShaderProgram program, gl::Vertex p1, gl::Vertex p2, gl::Vertex p3) : program(program), vertices{ p1, p2, p3 } {
			glGenBuffers(1, &VBO);
			glGenVertexArrays(1, &VAO);

			// 1. Привязываем VAO
			glBindVertexArray(VAO);
			// 2. Копируем наш массив вершин в буфер для OpenGL
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
			// 3. Устанавливаем указатели на вершинные атрибуты 
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			//4. Отвязываем VAO
			glBindVertexArray(0);

			uniform[Color] = glGetUniformLocation(program, "selected_color");

		}
		//manual
		Triangle(gl::ShaderProgram program, float x,float y, float a, float h) : program(program),
			vertices{{
				{x,y},
				{x+a/2,y+h},
				{x+a,y}
			}}
		{
			glGenBuffers(1, &VBO);
			glGenVertexArrays(1, &VAO);	

			// 1. Привязываем VAO
			glBindVertexArray(VAO);
			// 2. Копируем наш массив вершин в буфер для OpenGL
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
			// 3. Устанавливаем указатели на вершинные атрибуты 
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			//4. Отвязываем VAO
			glBindVertexArray(0);
			
			uniform[Color] = glGetUniformLocation(program, "selected_color");
		
		}
	};
} 