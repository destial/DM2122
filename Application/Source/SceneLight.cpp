#include "SceneLight.h"
#include "Application.h"
#include "Utility.h"
#include <iostream>

SceneLight::SceneLight() {}

SceneLight::~SceneLight() {}

Transform sun;
Transform mercury;

void SceneLight::Init() {
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);

	light[0].position.Set(0, 2, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 100, 100, 100);
	meshList[GEO_LIGHT] = MeshBuilder::GenerateSphere("light", Color(1.f, 1.f, 1.f), 30, 30, 1);
	meshList[GEO_SUN] = MeshBuilder::GenerateSphere("sun", Color(.9f, .9f, 0.f), 30, 30, 1);
	meshList[GEO_SUN]->material.kAmbient.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SUN]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SUN]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SUN]->material.kShininess = 1.f;
	//meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", Color(0.9f, 0.9f, 0.9f), 50, 50);
	//meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1.f, 1.f, 1.f), 30, 20);

	Mtx44 projection; 
	projection.SetToPerspective(45.0f, 40.0f / 30.0f, 0.1f, 100.0f);
	projectionStack.LoadMatrix(projection);
	camera.Init(Vector3(25, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SceneLight::Update(double dt) {
	if (Application::IsKeyPressed('1')) {
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2')) {
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('3')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} 
	if (Application::IsKeyPressed('4')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	unsigned LSPEED = 10.f;
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	sun.rotate -= 1;
	mercury.rotate -= 0.5;
	camera.Update(dt);
}

void SceneLight::RenderMesh(Mesh* mesh, bool enableLight) {
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}

void SceneLight::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y,
		camera.position.z, camera.target.x, camera.target.y,
		camera.target.z, camera.up.x, camera.up.y, camera.up.z
	);
	modelStack.LoadIdentity();

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	RenderMesh(meshList[GEO_AXES], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SUN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5, 0, 5);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SUN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-5, 0, -5);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SUN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5, 0, -5);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SUN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-5, 0, 5);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SUN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(5, 0, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SUN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-5, 0, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SUN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 5);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SUN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -5);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SUN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHT], false);
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	modelStack.Translate(0, -5, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();*/
}

void SceneLight::Exit() {
	for (int i = 0; i < NUM_GEOMETRY; i++) {
		if (meshList[i]) delete meshList[i];
	}
	glDeleteProgram(m_programID);
}
