#pragma once
#include <iostream>

#include "object.h"
#include "../gl_tweaks.h"
namespace fatum::object {
	class Rectangle : public IDrawable {
		const std::array< gl::Vertex, 4 > vertices;
		gl::RGBAColor color;
		


		GLuint VBO;
		GLuint VAO;
		GLuint EBO;
		
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

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}
		//Manual 
		Rectangle(gl::ShaderProgram program, gl::Vertex p1, gl::Vertex p2, gl::Vertex p3, gl::Vertex p4) : program(program),
			vertices{ { p1, p2, p3, p4 } }
		{

			GLuint indices[6] = {
				0, 1, 3,
				1, 2, 3
			}; ;
			

			glGenBuffers(1, &EBO);
			glGenBuffers(1, &VBO);
			glGenVertexArrays(1, &VAO);

			// 1. Привязываем VAO
			glBindVertexArray(VAO);
			// 2. Копируем наш массив вершин в буфер для OpenGL
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			// 3. Устанавливаем указатели на вершинные атрибуты 
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			//4. Отвязываем VAO
			glBindVertexArray(0);

			uniform[Color] = glGetUniformLocation(program, "selected_color");

		}
		//Auto
		Rectangle(gl::ShaderProgram program, float x, float y, float w, float h) : program(program),
			vertices{ {
				{x, y, 0.f },

				{x, y - h, 0.f },

				{x + w, y - h, 0.f},

				{x + w, y, 0.f}
			} }
		{
			GLuint indices[6] = {
				0, 1, 3,
				1, 2, 3
			}; ;


			glGenBuffers(1, &EBO);
			glGenBuffers(1, &VBO);
			glGenVertexArrays(1, &VAO);

			// 1. Привязываем VAO
			glBindVertexArray(VAO);
			// 2. Копируем наш массив вершин в буфер для OpenGL
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			// 3. Устанавливаем указатели на вершинные атрибуты 
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			//4. Отвязываем VAO
			glBindVertexArray(0);

			uniform[Color] = glGetUniformLocation(program, "selected_color");

		}
		
	};
}